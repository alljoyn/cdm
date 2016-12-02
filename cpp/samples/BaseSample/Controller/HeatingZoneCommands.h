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

#ifndef HEATINGZONECOMMANDS_H_
#define HEATINGZONECOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/HeatingZoneIntfController.h>
#include <alljoyn/cdm/interfaces/operation/HeatingZoneIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class HeatingZoneListener : public HeatingZoneIntfControllerListener{
  public:
    HeatingZoneListener();
    virtual ~HeatingZoneListener();

    virtual void OnGetNumberOfHeatingZonesPropertyCallback(QStatus status, const qcc::String& objectPath, const uint8_t numberOfZones, void* context);
    virtual void OnGetMaxHeatingLevelsPropertyCallback(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& maxHeatingLevels, void* context);
    virtual void OnGetHeatingLevelsPropertyCallback(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& heatingLevels, void* context);
    virtual void NumberOfHeatingZonesPropertyChanged(const qcc::String& objectPath, const uint8_t numberOfHeatingZones);
    virtual void MaxHeatingLevelsPropertyChanged(const qcc::String& objectPath, const std::vector<uint8_t>& maxHeatingLevels);
    virtual void HeatingLevelsPropertyChanged(const qcc::String& objectPath, const std::vector<uint8_t>& heatingLevels);
};

class HeatingZoneCommands : public InterfaceCommands
{
  public:
    HeatingZoneCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~HeatingZoneCommands();

    virtual void Init();

    HeatingZoneIntfController* GetInterface() { return m_intfController; }
    static void OnCmdGetNumberOfHeatingZones(Commands* commands, std::string& cmd);

    static void OnCmdGetMaxHeatingLevels(Commands* commands, std::string& cmd);

    static void OnCmdGetHeatingLevels(Commands* commands, std::string& cmd);
  private:
    HeatingZoneIntfController* m_intfController;
    HeatingZoneListener m_listener;
};


#endif /* HEATINGZONECOMMANDS_H_ */