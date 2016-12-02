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
#ifndef VIRTUALDEVICE_H_
#define VIRTUALDEVICE_H_

#include "ControlleeSample.h"
#include "ConfigLoader.h"

namespace ajn {

class BusAttachment;

namespace services {

class VirtualDevice : public ControlleeSample
{
private:
    InterfaceList* m_interfaceList;

public:
    VirtualDevice(BusAttachment* bus, CdmAboutData* aboutData, InterfaceList* list);
    virtual ~VirtualDevice();

    void InitSample();
    void CreateInterfaces();
    void SetInitialProperty();
    InterfaceList* GetInterfaceList();
};

}
}

#endif  // VIRTUALDEVICE_H_