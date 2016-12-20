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
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <qcc/Debug.h>
#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/LogModule.h>
#include "DeviceManager.h"
#include <alljoyn/cdm/CdmProxyBusObject.h>
#include "AutoLock.h"

using namespace ajn;
using namespace services;

////////////////////////////////////////////////////////////////////////////////////////
// DeviceInfo

DeviceInfo::DeviceInfo()
{
}

DeviceInfo::DeviceInfo(const char* busName)
: m_busName(busName)
{
}

DeviceInfo::DeviceInfo(const char* busName, SessionId id, SessionPort port, const CdmAboutData& data, const AboutObjectDescription& description)
: m_busName(busName), m_sessionId(id), m_sessionPort(port), m_aboutData(data), m_aboutObjectDescription(description)
{
}

DeviceInfo::~DeviceInfo()
{
    for (CdmProxyObjectMap::const_iterator citer = m_cdmProxyObjectsMap.begin(); citer != m_cdmProxyObjectsMap.end(); ++citer) {
        CdmProxyBusObject* cdmProxyObject = citer->second;

        if (cdmProxyObject) {
            delete cdmProxyObject;
            cdmProxyObject = 0;
        }
    }
}

CdmProxyBusObject* DeviceInfo::GetCdmProxyBusObject(BusAttachment& bus, const qcc::String& objectPath)
{
    CdmProxyObjectMap::const_iterator citer = m_cdmProxyObjectsMap.find(objectPath);
    if (citer == m_cdmProxyObjectsMap.end()) {
        CdmProxyBusObject* cdmProxyObject = new CdmProxyBusObject(bus, m_busName, objectPath, m_sessionId);
        if (!cdmProxyObject) {
            QCC_LogError(ER_OUT_OF_MEMORY, ("%s: could not create CdmProxyBusObject class.", __func__));
            return NULL;
        } else {
            m_cdmProxyObjectsMap.insert(std::pair<qcc::String, CdmProxyBusObject*>(objectPath, cdmProxyObject));
            return cdmProxyObject;
        }
    } else {
        return citer->second;
    }
}

////////////////////////////////////////////////////////////////////////////////////////
// DeviceManager

void DeviceManager::Clear()
{
    AutoLock lock(m_mutex);
    m_deviceMap.clear();
}

QStatus DeviceManager::AddDeviceInfo(DeviceInfoPtr& info)
{
    if (m_deviceMap.find(info->GetSessionId()) != m_deviceMap.end()) {
        return ER_FAIL;
    }

    m_deviceMap.insert(std::pair<SessionId, DeviceInfoPtr>(info->GetSessionId(), info));

    return ER_OK;
}

QStatus DeviceManager::RemoveDeviceInfo(SessionId id)
{
    DeviceMap::iterator itr = m_deviceMap.find(id);
    if (itr == m_deviceMap.end()) {
        return ER_FAIL;
    }

    m_deviceMap.erase(id);

    return ER_OK;
}

QStatus DeviceManager::FindDeviceInfoBySessionId(SessionId id, DeviceInfoPtr& info)
{
    DeviceMap::iterator itr = m_deviceMap.find(id);
    if (itr == m_deviceMap.end()) {
        return ER_FAIL;
    }
    info = m_deviceMap[id];

    return ER_OK;
}

QStatus DeviceManager::FindDeviceInfoByBusName(const std::string busName, DeviceInfoPtr& info)
{
    DeviceMap::iterator itr;

    for (itr = m_deviceMap.begin(); itr != m_deviceMap.end(); ++itr) {
        if(itr->second->GetBusName() == busName) {
            break;
        }
    }

    if (itr == m_deviceMap.end()) {
        return ER_FAIL;
    }

    info = m_deviceMap[itr->first];
    return ER_OK;
}