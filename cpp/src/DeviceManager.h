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


#ifndef DEVICEMANAGER_H_
#define DEVICEMANAGER_H_

#include <qcc/Mutex.h>
#include <alljoyn/hae/DeviceInfo.h>

namespace ajn {
namespace services {

class DeviceManager {
  public:
    void Clear();
    QStatus AddDeviceInfo(DeviceInfoPtr& info);
    QStatus RemoveDeviceInfo(SessionId id);
    QStatus FindDeviceInfoBySessionId(SessionId, DeviceInfoPtr& info);
    QStatus FindDeviceInfoByBusName(const std::string busName, DeviceInfoPtr& info);

  private:
    qcc::Mutex m_mutex;
    DeviceMap m_deviceMap;
};

}  // services
}  // ajn

#endif  // DEVICEMANAGER_H_
