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


#ifndef DEVICELISTENER_H_
#define DEVICELISTENER_H_

#include <map>
#include <alljoyn/Session.h>
#include <alljoyn/cdm/DeviceInfo.h>

namespace ajn {
namespace services {

/**
 * Abstract base class implemented by User Application Developers. \n
 * The callbacks defined in this class allow the User Application
 * to be informed about some Cdm Controller operations.
 */
class DeviceListener {
  public:
    /**
     * Destructor of DeviceListener
     */
    virtual ~DeviceListener() { }

    /**
     * Added device in the network
     * @param[in] busname bus name
     * @param[in] port port
     * @param[in] data CDM About data
     * @param[in] description About object description
     */
    virtual void OnDeviceAdded(const char* busname, SessionPort port, const CdmAboutData& data,
                               const AboutObjectDescription& description) = 0;

    /**
     * Removed device in the network
     * @param[in] busname bus name
     */
    virtual void OnDeviceRemoved(const char* busname) = 0;

    /**
     * Device session joined
     * @param[in] info device info pointer
     */
    virtual void OnDeviceSessionJoined(const DeviceInfoPtr& info) = 0;

    /**
     * Device session lost
     * @param[in] sessionId session id
     */
    virtual void OnDeviceSessionLost(SessionId sessionId) = 0;
};

}  // services
}  // ajn

#endif  // DEVICEMANAGER_H_