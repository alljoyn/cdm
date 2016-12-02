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
#include "DeviceManager.h"
#include "../common/AutoLock.h"

using namespace ajn;
using namespace services;

void DeviceManager::Clear()
{
    AutoLock lock(m_mutex);
    m_deviceMap.clear();
}

QStatus DeviceManager::AddDeviceInfo(Ref<DeviceInfo> info)
{
    if (m_deviceMap.find(info->GetSessionId()) != m_deviceMap.end()) {
        return ER_FAIL;
    }

    m_deviceMap.insert(std::pair<SessionId, Ref<DeviceInfo>>(info->GetSessionId(), info));

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

QStatus DeviceManager::FindDeviceInfoBySessionId(SessionId id, Ref<DeviceInfo> info)
{
    DeviceMap::iterator itr = m_deviceMap.find(id);
    if (itr == m_deviceMap.end()) {
        return ER_FAIL;
    }
    info = m_deviceMap[id];

    return ER_OK;
}

QStatus DeviceManager::FindDeviceInfoByBusName(const std::string busName, Ref<DeviceInfo> info)
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
