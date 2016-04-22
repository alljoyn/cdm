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

#include <sstream>
#include <assert.h>
#include <alljoyn/hae/LogModule.h>
#include <alljoyn/hae/HaeAboutData.h>
#include <alljoyn/hae/DeviceTypeDescription.h>
#include <HaeAboutKeys.h>
#include <qcc/StringSource.h>
#include <qcc/XmlElement.h>

using ajn::services::HaeAboutKeys;

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

QStatus HaeAboutData::CreateFromXml(const char* aboutDataXml)
{
    return CreateFromXml(qcc::String(aboutDataXml));
}

QStatus HaeAboutData::CreateFromXml(const qcc::String& aboutDataXml)
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

QStatus HaeAboutData::SetCountryOfProduction(const char* country, const char* language)
{
    QStatus status = ER_OK;
    MsgArg arg;
    status = arg.Set(GetFieldSignature(HaeAboutKeys::COUNTRY_OF_PRODUCTION.c_str()), country);
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: failed to set MsgArg.", __func__));
        return status;
    }
    status = SetField(HaeAboutKeys::COUNTRY_OF_PRODUCTION.c_str(), arg, language);
    return status;
}

QStatus HaeAboutData::GetCountryOfProduction(char** country, const char* language)
{
    QStatus status = ER_OK;
    MsgArg* arg = NULL;
    status = GetField(HaeAboutKeys::COUNTRY_OF_PRODUCTION.c_str(), arg, language);
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: failed to get field.", __func__));
        return status;
    }
    status = arg->Get(GetFieldSignature(HaeAboutKeys::COUNTRY_OF_PRODUCTION.c_str()), country);
    return status;
}

QStatus HaeAboutData::SetCorporateBrand(const char* brand, const char* language)
{
    QStatus status = ER_OK;
    MsgArg arg;
    status = arg.Set(GetFieldSignature(HaeAboutKeys::CORPORATE_BRAND.c_str()), brand);
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: failed to set MsgArg.", __func__));
        return status;
    }
    status = SetField(HaeAboutKeys::CORPORATE_BRAND.c_str(), arg, language);
    return status;
}

QStatus HaeAboutData::GetCorporateBrand(char** brand, const char* language)
{
    QStatus status = ER_OK;
    MsgArg* arg = NULL;
    status = GetField(HaeAboutKeys::CORPORATE_BRAND.c_str(), arg, language);
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: failed to get field.", __func__));
        return status;
    }
    status = arg->Get(GetFieldSignature(HaeAboutKeys::CORPORATE_BRAND.c_str()), brand);
    return status;
}


QStatus HaeAboutData::SetProductBrand(const char* brand, const char* language)
{
    QStatus status = ER_OK;
    MsgArg arg;
    status = arg.Set(GetFieldSignature(HaeAboutKeys::PRODUCT_BRAND.c_str()), brand);
    if (status != ER_OK) {
        return status;
    }
    status = SetField(HaeAboutKeys::PRODUCT_BRAND.c_str(), arg, language);
    return status;
}

QStatus HaeAboutData::GetProductBrand(char** brand, const char* language)
{
    QStatus status = ER_OK;
    MsgArg* arg = NULL;
    status = GetField(HaeAboutKeys::PRODUCT_BRAND.c_str(), arg, language);
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: failed to get field.", __func__));
        return status;
    }
    status = arg->Get(GetFieldSignature(HaeAboutKeys::PRODUCT_BRAND.c_str()), brand);
    return status;
}

QStatus HaeAboutData::SetLocation(const char* location, const char* language)
{
    QStatus status = ER_OK;
    MsgArg arg;
    status = arg.Set(GetFieldSignature(HaeAboutKeys::LOCATION.c_str()), location);
    if (status != ER_OK) {
        return status;
    }
    status = SetField(HaeAboutKeys::LOCATION.c_str(), arg, language);
    return status;
}

QStatus HaeAboutData::GetLocation(char** location, const char* language)
{
    QStatus status = ER_OK;
    MsgArg* arg = NULL;
    status = GetField(HaeAboutKeys::LOCATION.c_str(), arg, language);
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: failed to get field.", __func__));
        return status;
    }
    status = arg->Get(GetFieldSignature(HaeAboutKeys::LOCATION.c_str()), location);
    return status;
}

QStatus HaeAboutData::SetDeviceTypeDescription(const DeviceTypeDescription *deviceTypes)
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
    status = deviceTypeDescriptions.Set(GetFieldSignature(HaeAboutKeys::DEVICE_TYPE_DESCRIPTION.c_str()), elemSize, typeAndObjPath); // a(uo)
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: failed to set MsgArg.", __func__));
        delete[] typeAndObjPath;
        return status;
    }

    status = SetField(HaeAboutKeys::DEVICE_TYPE_DESCRIPTION.c_str(), deviceTypeDescriptions);

    delete[] typeAndObjPath;
    return status;
}

QStatus HaeAboutData::GetDeviceTypeDescription(DeviceTypeDescription **deviceTypes)
{
    QStatus status = ER_OK;
    MsgArg* arg = NULL;

    (*deviceTypes)->ResetDescriptions();

    status = GetField(HaeAboutKeys::DEVICE_TYPE_DESCRIPTION.c_str(), arg);
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: failed to get field.", __func__));
        return status;
    }
    MsgArg* elemArg = NULL;
    size_t elemSize = 0;
    status = arg->Get(GetFieldSignature(HaeAboutKeys::DEVICE_TYPE_DESCRIPTION.c_str()), &elemSize, &elemArg);
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


void HaeAboutData::InitializeCustomFieldDetails()
{
    SetNewFieldDetails(HaeAboutKeys::COUNTRY_OF_PRODUCTION.c_str(),   LOCALIZED, "s");
    SetNewFieldDetails(HaeAboutKeys::CORPORATE_BRAND.c_str(),         LOCALIZED, "s");
    SetNewFieldDetails(HaeAboutKeys::PRODUCT_BRAND.c_str(),           LOCALIZED, "s");
    SetNewFieldDetails(HaeAboutKeys::LOCATION.c_str(),                REQUIRED | LOCALIZED | ANNOUNCED, "s");
    SetNewFieldDetails(HaeAboutKeys::DEVICE_TYPE_DESCRIPTION.c_str(), REQUIRED | ANNOUNCED, "a(uo)");
}

} //namespace services
} //namespace ajn
