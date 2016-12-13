/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
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

#include "ConfigLoader.h"
#include <fstream>
#include <map>
#include <utility>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/CdmAboutData.h>
#include <alljoyn/cdm/interfaces/CdmInterface.h>
#include <qcc/String.h>
#include <qcc/StringSource.h>
#include <qcc/XmlElement.h>

using namespace std;
using namespace ajn;
using namespace qcc;
using namespace services;

const char* ConfigLoader::DEVICE_EMULATOR = "DeviceEmulator";
const char* ConfigLoader::ABOUT_DATA = "AboutData";
const char* ConfigLoader::INTERFACE_LIST = "InterfaceList";
const char* ConfigLoader::OBJECT = "Object";
const char* ConfigLoader::PATH = "path";
const char* ConfigLoader::INTERFACE = "Interface";
const char* ConfigLoader::NAME = "name";

static CdmInterfaceType GetCdmInterfaceType(const String& intfName)
{
    for (map<CdmInterfaceType, qcc::String>::const_iterator citr = InterfaceTypesMap.begin(); citr != InterfaceTypesMap.end(); ++citr) {
        if (citr->second == intfName) {
            return citr->first;
        }
    }

    return UNDEFINED_INTERFACE;
}

static bool ParseInterfaceList(const String xml, InterfaceList& list)
{
    StringSource source(xml);
    XmlParseContext context(source);
    QStatus status = XmlElement::Parse(context);
    if (status != ER_OK) {
        return false;
    }

    const XmlElement* intfList = context.GetRoot();
    vector<const XmlElement*> objects = intfList->GetChildren(ConfigLoader::OBJECT);
    for (vector<const XmlElement*>::const_iterator citr = objects.begin(); citr != objects.end(); ++citr) {
        const String& objPath = (*citr)->GetAttribute(ConfigLoader::PATH);
        String objXml = (*citr)->Generate();
        StringSource objSource(objXml);
        XmlParseContext objContext(objSource);
        status = XmlElement::Parse(objContext);
        if (status != ER_OK) {
            continue;
        }

        const XmlElement* object = objContext.GetRoot();
        vector<const XmlElement*> intfs = object->GetChildren(ConfigLoader::INTERFACE);
        for (vector<const XmlElement*>::const_iterator citr2 = intfs.begin(); citr2 != intfs.end(); ++citr2) {
            const String& intfName = (*citr2)->GetAttribute(ConfigLoader::NAME);
            CdmInterfaceType intfType = GetCdmInterfaceType(intfName);
            if (intfType == UNDEFINED_INTERFACE) {
                continue;
            }

            list.push_back(make_pair(intfType, (string)objPath.c_str()));
        }
    }

    return true;
}

static bool ParseXml(const String xml, CdmAboutData& data, InterfaceList& list)
{
    StringSource source(xml);
    XmlParseContext context(source);
    QStatus status = XmlElement::Parse(context);
    if (status != ER_OK) {
        return false;
    }

    const XmlElement* root = context.GetRoot();
    if (!root) {
        return false;
    } else if (root->GetName() != ConfigLoader::DEVICE_EMULATOR) {
        return false;
    }

    const XmlElement* aboutData = root->GetChild(ConfigLoader::ABOUT_DATA);
    if (!aboutData) {
        return false;
    }

    status = data.CreateFromXml(aboutData->Generate());
    if (status != ER_OK) {
        return false;
    }

    const XmlElement* intfList = root->GetChild(ConfigLoader::INTERFACE_LIST);
    if (!intfList) {
        return false;
    }

    return ParseInterfaceList(intfList->Generate(), list);
}

bool ConfigLoader::Load(CdmAboutData& data, InterfaceList& list)
{
    ifstream ifs(m_path.c_str());
    if (!ifs.is_open()) {
        return false;
    }

    string xml((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    if (!ParseXml(xml.c_str(), data, list)) {
        return false;
    }

    return true;
}