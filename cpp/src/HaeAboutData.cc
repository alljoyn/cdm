/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <assert.h>
#include <alljoyn/hae/LogModule.h>
#include <alljoyn/hae/HaeAboutData.h>
#include <alljoyn/hae/DeviceTypeDescription.h>

#include "HaeAboutCustomFields.h"

namespace ajn {
namespace services {

HaeAboutData::HaeAboutData()
{
    InitializeCustomFieldDetails();
}

HaeAboutData::HaeAboutData(const char* defaultLanguage) :
    AboutData(defaultLanguage)
{
    InitializeCustomFieldDetails();
}


HaeAboutData::HaeAboutData(const MsgArg arg, const char* language) :
    AboutData(arg, language)
{
    InitializeCustomFieldDetails();

    QStatus status = CreatefromMsgArg(arg, language);
    if (ER_OK != status) {
        QCC_LogError(status, ("%s: failed to parse MsgArg.", __func__));
    }
}

HaeAboutData::~HaeAboutData()
{
}

QStatus HaeAboutData::SetCountryOfProduction(const char* country, const char* language)
{
    QStatus status = ER_OK;
    MsgArg arg;
    status = arg.Set(GetFieldSignature(COUNTRY_OF_PRODUCTION.c_str()), country);
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: failed to set MsgArg.", __func__));
        return status;
    }
    status = SetField(COUNTRY_OF_PRODUCTION.c_str(), arg, language);
    return status;
}

QStatus HaeAboutData::GetCountryOfProduction(char** country, const char* language)
{
    QStatus status = ER_OK;
    MsgArg* arg = NULL;
    status = GetField(COUNTRY_OF_PRODUCTION.c_str(), arg, language);
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: failed to get field.", __func__));
        return status;
    }
    status = arg->Get(GetFieldSignature(COUNTRY_OF_PRODUCTION.c_str()), country);
    return status;
}

QStatus HaeAboutData::SetCorporateBrand(const char* brand, const char* language)
{
    QStatus status = ER_OK;
    MsgArg arg;
    status = arg.Set(GetFieldSignature(CORPORATE_BRAND.c_str()), brand);
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: failed to set MsgArg.", __func__));
        return status;
    }
    status = SetField(CORPORATE_BRAND.c_str(), arg, language);
    return status;
}

QStatus HaeAboutData::GetCorporateBrand(char** brand, const char* language)
{
    QStatus status = ER_OK;
    MsgArg* arg = NULL;
    status = GetField(CORPORATE_BRAND.c_str(), arg, language);
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: failed to get field.", __func__));
        return status;
    }
    status = arg->Get(GetFieldSignature(CORPORATE_BRAND.c_str()), brand);
    return status;
}


QStatus HaeAboutData::SetProductBrand(const char* brand, const char* language)
{
    QStatus status = ER_OK;
    MsgArg arg;
    status = arg.Set(GetFieldSignature(PRODUCT_BRAND.c_str()), brand);
    if (status != ER_OK) {
        return status;
    }
    status = SetField(PRODUCT_BRAND.c_str(), arg, language);
    return status;
}

QStatus HaeAboutData::GetProductBrand(char** brand, const char* language)
{
    QStatus status = ER_OK;
    MsgArg* arg = NULL;
    status = GetField(PRODUCT_BRAND.c_str(), arg, language);
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: failed to get field.", __func__));
        return status;
    }
    status = arg->Get(GetFieldSignature(PRODUCT_BRAND.c_str()), brand);
    return status;
}

QStatus HaeAboutData::SetLocation(const char* location, const char* language)
{
    QStatus status = ER_OK;
    MsgArg arg;
    status = arg.Set(GetFieldSignature(LOCATION.c_str()), location);
    if (status != ER_OK) {
        return status;
    }
    status = SetField(LOCATION.c_str(), arg, language);
    return status;
}

QStatus HaeAboutData::GetLocation(char** location, const char* language)
{
    QStatus status = ER_OK;
    MsgArg* arg = NULL;
    status = GetField(LOCATION.c_str(), arg, language);
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: failed to get field.", __func__));
        return status;
    }
    status = arg->Get(GetFieldSignature(LOCATION.c_str()), location);
    return status;
}

QStatus HaeAboutData::SetDeviceTypeDescription(const DeviceTypeDescription *deviceTypes)
{
    QStatus status = ER_OK;

    const DeviceTypeDescription::DescriptionsType& descriptions = deviceTypes->GetDescriptions();
    const size_t elemSize = descriptions.size();
    size_t elemCount = 0;

    MsgArg* typeAndObjPath = new MsgArg[elemSize];
    for(DeviceTypeDescription::DescriptionsType::const_iterator itr = descriptions.begin(); itr != descriptions.end(); ++itr) {
        status = typeAndObjPath[elemCount].Set("(uo)", itr->first, itr->second.c_str());
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: failed to set MsgArg.", __func__));
            delete[] typeAndObjPath;
            return status;
        }
        ++elemCount;
    }
    assert(elemCount == elemSize);

    MsgArg deviceTypeDescriptions;
    status = deviceTypeDescriptions.Set(GetFieldSignature(DEVICE_TYPE_DESCRIPTION.c_str()), elemSize, typeAndObjPath); // a(uo)
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: failed to set MsgArg.", __func__));
        delete[] typeAndObjPath;
        return status;
    }

    status = SetField(DEVICE_TYPE_DESCRIPTION.c_str(), deviceTypeDescriptions);

    delete[] typeAndObjPath;
    return status;
}

QStatus HaeAboutData::GetDeviceTypeDescription(DeviceTypeDescription **deviceTypes)
{
    QStatus status = ER_OK;
    MsgArg* arg = NULL;

    (*deviceTypes)->ResetDescriptions();

    status = GetField(DEVICE_TYPE_DESCRIPTION.c_str(), arg);
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: failed to get field.", __func__));
        return status;
    }
    MsgArg* elemArg = NULL;
    size_t elemSize = 0;
    status = arg->Get(GetFieldSignature(DEVICE_TYPE_DESCRIPTION.c_str()), &elemSize, &elemArg);
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: failed to get MsgArg.", __func__));
        return status;
    }

    for(size_t i = 0; i < elemSize; ++i) {
        DeviceType type;
        char* objectPath = NULL;

        status = elemArg->Get("(uo)", &type, &objectPath);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: failed to get MsgArg.", __func__));
            return status;
        }

        (*deviceTypes)->AddDeviceType(type, objectPath);

        elemArg++;
    }

    return status;
}


void HaeAboutData::InitializeCustomFieldDetails()
{
    SetNewFieldDetails(COUNTRY_OF_PRODUCTION.c_str(),   LOCALIZED, "s");
    SetNewFieldDetails(CORPORATE_BRAND.c_str(),         LOCALIZED, "s");
    SetNewFieldDetails(PRODUCT_BRAND.c_str(),           LOCALIZED, "s");
    SetNewFieldDetails(LOCATION.c_str(),                REQUIRED | LOCALIZED | ANNOUNCED, "s");
    SetNewFieldDetails(DEVICE_TYPE_DESCRIPTION.c_str(), REQUIRED | ANNOUNCED, "a(uo)");
}

} //namespace services
} //namespace ajn
