/******************************************************************************
 *  * 
 *    Copyright (c) 2016 Open Connectivity Foundation and AllJoyn Open
 *    Source Project Contributors and others.
 *    
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0

 ******************************************************************************/


#ifndef DEVICEMANAGER_H_
#define DEVICEMANAGER_H_

#include <qcc/Mutex.h>
#include <alljoyn/cdm/DeviceInfo.h>

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