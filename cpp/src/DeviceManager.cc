/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
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

#include <qcc/Debug.h>
#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/hae/LogModule.h>
#include "DeviceManager.h"
#include "HaeProxyBusObject.h"
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

DeviceInfo::DeviceInfo(const char* busName, SessionId id, SessionPort port, const HaeAboutData& data, const AboutObjectDescription& description)
: m_busName(busName), m_sessionId(id), m_sessionPort(port), m_aboutData(data), m_aboutObjectDescription(description)
{
}

DeviceInfo::~DeviceInfo()
{
    for (HaeProxyObjectMap::const_iterator citer = m_haeProxyObjectsMap.begin(); citer != m_haeProxyObjectsMap.end(); ++citer) {
        HaeProxyBusObject* haeProxyObject = citer->second;

        if (haeProxyObject) {
            delete haeProxyObject;
            haeProxyObject = 0;
        }
    }
}

HaeProxyBusObject* DeviceInfo::GetHaeProxyBusObject(BusAttachment& bus, const qcc::String& objectPath)
{
    HaeProxyObjectMap::const_iterator citer = m_haeProxyObjectsMap.find(objectPath);
    if (citer == m_haeProxyObjectsMap.end()) {
        HaeProxyBusObject* haeProxyObject = new HaeProxyBusObject(bus, m_busName, objectPath, m_sessionId);
        if (!haeProxyObject) {
            QCC_LogError(ER_OUT_OF_MEMORY, ("%s: could not create HaeBusObject cHaeProxyBusObjectlass.", __func__));
            return NULL;
        } else {
            m_haeProxyObjectsMap.insert(std::pair<qcc::String, HaeProxyBusObject*>(objectPath, haeProxyObject));
            return haeProxyObject;
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
