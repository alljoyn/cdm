/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <sstream>
#include <assert.h>
#include <alljoyn/cdm/LogModule.h>
#include <alljoyn/cdm/CdmAboutData.h>
#include <alljoyn/cdm/DeviceTypeDescription.h>
#include <CdmAboutKeys.h>
#include <qcc/StringSource.h>
#include <qcc/XmlElement.h>

using ajn::services::CdmAboutKeys;

namespace ajn {
namespace services {

CdmAboutData::CdmAboutData()
{
    InitializeCustomFieldDetails();
}

CdmAboutData::CdmAboutData(const char* defaultLanguage) :
    AboutData(defaultLanguage)
{
    InitializeCustomFieldDetails();
}


CdmAboutData::CdmAboutData(const MsgArg arg, const char* language) :
    AboutData(arg, language)
{
    InitializeCustomFieldDetails();

    QStatus status = CreatefromMsgArg(arg, language);
    if (ER_OK != status) {
        QCC_LogError(status, ("%s: failed to parse MsgArg.", __func__));
    }
}

CdmAboutData::~CdmAboutData()
{
}

QStatus CdmAboutData::CreateFromXml(const char* aboutDataXml)
{
    return CreateFromXml(qcc::String(aboutDataXml));
}

QStatus CdmAboutData::CreateFromXml(const qcc::String& aboutDataXml)
{
    qcc::String  deviceDescriptionOpen ="<" + DEVICE_TYPE_DESCRIPTION + ">";
    qcc::String  deviceDescriptionClose ="</" + DEVICE_TYPE_DESCRIPTION + ">";
    size_t deviceBegin = aboutDataXml.find(deviceDescriptionOpen);
    size_t deviceEnd = aboutDataXml.find( deviceDescriptionClose ) + deviceDescriptionClose.length();

    QStatus status = AboutData::CreateFromXml(aboutDataXml);
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: unexpected return from AboutData::CreateFromXml.", __func__));
    } else {
        qcc::StringSource source(aboutDataXml);
        qcc::XmlParseContext pc(source);
        status = qcc::XmlElement::Parse(pc);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: unable to parse DeviceTypeDescriptionXml.", __func__));
            status = ER_ABOUT_ABOUTDATA_MISSING_REQUIRED_FIELD;
        } else {
            const qcc::XmlElement* root = pc.GetRoot();

            qcc::String descriptionXmlTag = "TypeDescription";
            qcc::String descriptionXmlTypeTag = "device_type";
            qcc::String descriptionXmlPathTag = "object_path";

            std::vector<const qcc::XmlElement*> descriptionChildren = root->GetChild(DEVICE_TYPE_DESCRIPTION)->GetChildren(descriptionXmlTag);
            if (0 == descriptionChildren.size()) {
                status = ER_ABOUT_ABOUTDATA_MISSING_REQUIRED_FIELD;
                QCC_LogError(status, ("%s: unable to find descriptions Xml Tag.", __func__));
            } else {
                DeviceTypeDescription description;
                int numberDescriptions =0;
                for (size_t i = 0; i < descriptionChildren.size(); i++) {
                    qcc::String codeText =descriptionChildren[i]->GetChild(descriptionXmlTypeTag)->GetContent();
                    qcc::String pathText =descriptionChildren[i]->GetChild(descriptionXmlPathTag)->GetContent();
                    std::stringstream convert(codeText.c_str());
                    uint code;
                    if (!(convert>>code)) {
                        status = ER_ABOUT_ABOUTDATA_MISSING_REQUIRED_FIELD;
                        QCC_LogError(status, ("%s: Could not convert device type to a uint", __func__));
                        continue;
                    } else {
                        description.AddDeviceType((DeviceType)code , pathText);
                        numberDescriptions++;
                    }
                }
                if (numberDescriptions) {
                    status = SetDeviceTypeDescription(&description);
                }
                //Check to see if location included in XML  About::CreateFromXml will return ER_OK without a location
                if (NULL == root->GetChild(LOCATION)) {
                    status = ER_ABOUT_ABOUTDATA_MISSING_REQUIRED_FIELD;
                }
            }
        }
    }
    return status;
}

QStatus CdmAboutData::SetCountryOfProduction(const char* country, const char* language)
{
    QStatus status = ER_OK;
    MsgArg arg;
    status = arg.Set(GetFieldSignature(CdmAboutKeys::COUNTRY_OF_PRODUCTION.c_str()), country);
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: failed to set MsgArg.", __func__));
        return status;
    }
    status = SetField(CdmAboutKeys::COUNTRY_OF_PRODUCTION.c_str(), arg, language);
    return status;
}

QStatus CdmAboutData::GetCountryOfProduction(char** country, const char* language)
{
    QStatus status = ER_OK;
    MsgArg* arg = NULL;
    status = GetField(CdmAboutKeys::COUNTRY_OF_PRODUCTION.c_str(), arg, language);
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: failed to get field.", __func__));
        return status;
    }
    status = arg->Get(GetFieldSignature(CdmAboutKeys::COUNTRY_OF_PRODUCTION.c_str()), country);
    return status;
}

QStatus CdmAboutData::SetCorporateBrand(const char* brand, const char* language)
{
    QStatus status = ER_OK;
    MsgArg arg;
    status = arg.Set(GetFieldSignature(CdmAboutKeys::CORPORATE_BRAND.c_str()), brand);
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: failed to set MsgArg.", __func__));
        return status;
    }
    status = SetField(CdmAboutKeys::CORPORATE_BRAND.c_str(), arg, language);
    return status;
}

QStatus CdmAboutData::GetCorporateBrand(char** brand, const char* language)
{
    QStatus status = ER_OK;
    MsgArg* arg = NULL;
    status = GetField(CdmAboutKeys::CORPORATE_BRAND.c_str(), arg, language);
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: failed to get field.", __func__));
        return status;
    }
    status = arg->Get(GetFieldSignature(CdmAboutKeys::CORPORATE_BRAND.c_str()), brand);
    return status;
}


QStatus CdmAboutData::SetProductBrand(const char* brand, const char* language)
{
    QStatus status = ER_OK;
    MsgArg arg;
    status = arg.Set(GetFieldSignature(CdmAboutKeys::PRODUCT_BRAND.c_str()), brand);
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: failed to set MsgArg.", __func__));
        return status;
    }
    status = SetField(CdmAboutKeys::PRODUCT_BRAND.c_str(), arg, language);
    return status;
}

QStatus CdmAboutData::GetProductBrand(char** brand, const char* language)
{
    QStatus status = ER_OK;
    MsgArg* arg = NULL;
    status = GetField(CdmAboutKeys::PRODUCT_BRAND.c_str(), arg, language);
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: failed to get field.", __func__));
        return status;
    }
    status = arg->Get(GetFieldSignature(CdmAboutKeys::PRODUCT_BRAND.c_str()), brand);
    return status;
}

QStatus CdmAboutData::SetLocation(const char* location, const char* language)
{
    QStatus status = ER_OK;
    MsgArg arg;
    status = arg.Set(GetFieldSignature(CdmAboutKeys::LOCATION.c_str()), location);
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: failed to set MsgArg.", __func__));
        return status;
    }
    status = SetField(CdmAboutKeys::LOCATION.c_str(), arg, language);
    return status;
}

QStatus CdmAboutData::GetLocation(char** location, const char* language)
{
    QStatus status = ER_OK;
    MsgArg* arg = NULL;
    status = GetField(CdmAboutKeys::LOCATION.c_str(), arg, language);
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: failed to get field.", __func__));
        return status;
    }
    status = arg->Get(GetFieldSignature(CdmAboutKeys::LOCATION.c_str()), location);
    return status;
}

QStatus CdmAboutData::SetDeviceTypeDescription(const DeviceTypeDescription *deviceTypes)
{
    QStatus status = ER_OK;

    const DeviceTypeDescription::DescriptionsType& descriptions = deviceTypes->GetDescriptions();
    const size_t elemSize = descriptions.size();
    size_t elemCount = 0;

    MsgArg* typeAndObjPath = new MsgArg[elemSize];
    for (DeviceTypeDescription::DescriptionsType::const_iterator itr = descriptions.begin(); itr != descriptions.end(); ++itr) {
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
    status = deviceTypeDescriptions.Set(GetFieldSignature(CdmAboutKeys::DEVICE_TYPE_DESCRIPTION.c_str()), elemSize, typeAndObjPath); // a(uo)
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: failed to set MsgArg.", __func__));
        delete[] typeAndObjPath;
        return status;
    }

    status = SetField(CdmAboutKeys::DEVICE_TYPE_DESCRIPTION.c_str(), deviceTypeDescriptions);

    delete[] typeAndObjPath;
    return status;
}

QStatus CdmAboutData::GetDeviceTypeDescription(DeviceTypeDescription **deviceTypes)
{
    QStatus status = ER_OK;
    MsgArg* arg = NULL;

    (*deviceTypes)->ResetDescriptions();

    status = GetField(CdmAboutKeys::DEVICE_TYPE_DESCRIPTION.c_str(), arg);
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: failed to get field.", __func__));
        return status;
    }
    MsgArg* elemArg = NULL;
    size_t elemSize = 0;
    status = arg->Get(GetFieldSignature(CdmAboutKeys::DEVICE_TYPE_DESCRIPTION.c_str()), &elemSize, &elemArg);
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: failed to get MsgArg.", __func__));
        return status;
    }

    for (size_t i = 0; i < elemSize; ++i) {
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


void CdmAboutData::InitializeCustomFieldDetails()
{
    SetNewFieldDetails(CdmAboutKeys::COUNTRY_OF_PRODUCTION.c_str(),   LOCALIZED, "s");
    SetNewFieldDetails(CdmAboutKeys::CORPORATE_BRAND.c_str(),         LOCALIZED, "s");
    SetNewFieldDetails(CdmAboutKeys::PRODUCT_BRAND.c_str(),           LOCALIZED, "s");
    SetNewFieldDetails(CdmAboutKeys::LOCATION.c_str(),                REQUIRED | LOCALIZED | ANNOUNCED, "s");
    SetNewFieldDetails(CdmAboutKeys::DEVICE_TYPE_DESCRIPTION.c_str(), REQUIRED | ANNOUNCED, "a(uo)");
}

} //namespace services
} //namespace ajn