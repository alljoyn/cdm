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
#ifndef DEVICEEMULATOR_H_
#define DEVICEEMULATOR_H_

#include <iostream>
#include <qcc/Log.h>
#include <qcc/String.h>
#include <alljoyn/Init.h>
#include <alljoyn/version.h>
#include <alljoyn/cdm/CdmAboutData.h>
#include "ConfigLoader.h"
#include "VirtualDevice.h"

using namespace std;
using namespace qcc;

namespace ajn {

class BusAttachment;

namespace services {

class DeviceEmulator
{
private:
    CdmAboutData m_aboutData;
    BusAttachment* m_bus;
    ConfigLoader m_configLoader;
    VirtualDevice* m_virtualDevice;
public:
    DeviceEmulator(const string& configPath);
    ~DeviceEmulator();

    void InitCommandsFactory();
    void Startup();
    void Shutdown();
};

}
}


#endif  //DEVICEEMULATOR_H_