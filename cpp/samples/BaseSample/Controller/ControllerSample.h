/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF), AllJoyn Open Source
 *    Project (AJOSP) Contributors and others.
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

#ifndef CONTROLLERSAMPLE_H_
#define CONTROLLERSAMPLE_H_

#include <map>
#include <string>
#include <alljoyn/Session.h>
#include <alljoyn/AboutObjectDescription.h>
#include <alljoyn/cdm/CdmController.h>
#include <alljoyn/cdm/CdmAboutData.h>
#include <alljoyn/cdm/DeviceListener.h>
#include <alljoyn/cdm/DeviceInfo.h>
#include "BaseSample.h"

class Commands;

using namespace std;
using namespace ajn;
using namespace services;

class FoundDeviceInfo {
  public:
    std::string busName;
    std::string deviceName;
    SessionPort sessionPort;
    SessionId sessionId;
    CdmAboutData aboutData;
    AboutObjectDescription aboutObjectDescription;

    FoundDeviceInfo() { }
    FoundDeviceInfo(const char* name, SessionPort port, CdmAboutData& data, AboutObjectDescription& description) : busName(name), sessionPort(port), sessionId(0), aboutData(data), aboutObjectDescription(description)
    {
        MsgArg* arg;
        data.GetField("DeviceName", arg, "en");
        const char* bus_name;
        arg->Get("s", &bus_name);

        deviceName = bus_name;
    }
};
typedef std::map<std::string, FoundDeviceInfo> FoundDeviceMap;

class ControllerSample : public BaseSample
                       , public DeviceListener
{
  public:
    ControllerSample(BusAttachment* bus);
    virtual ~ControllerSample();
    QStatus Init();
    void Deinit();

    virtual void OnDeviceAdded(const char* busname,
                                SessionPort port,
                                const CdmAboutData& data,
                               const AboutObjectDescription& description);
    virtual void OnDeviceRemoved(const char* busname);
    virtual void OnDeviceSessionJoined(const DeviceInfoPtr& info);
    virtual void OnDeviceSessionLost(SessionId sessionId);

    CdmController* GetController() { return m_controller; }
    FoundDeviceMap& GetDeviceMap() { return m_deviceList; }
    FoundDeviceInfo* GetFoundDeviceInfo(int index);

    CdmInterface* CreateInterface(const CdmInterfaceType type, const std::string& busName, const qcc::String& objectPath,
                                  const SessionId& sessionId, InterfaceControllerListener& listener);

    void DropDeviceSession();

    const CdmInterfaceType RegisterVendorDefinedInterface(const qcc::String& interfaceName, CreateIntfControllerFptr createIntfController);

  private:
    BusAttachment* m_bus;
    FoundDeviceMap m_deviceList;
    CdmController* m_controller;
    Commands* m_rootCommands;
    SessionId m_lastSession;
};


#endif // CONTROLLERSAMPLE_H_