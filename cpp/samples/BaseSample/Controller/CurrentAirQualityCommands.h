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

#ifndef CURRENTAIRQUALITYCOMMANDS_H_
#define CURRENTAIRQUALITYCOMMANDS_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/environment/CurrentAirQualityIntfController.h>
#include <alljoyn/cdm/interfaces/environment/CurrentAirQualityIntfControllerListener.h>

class ControllerSample;

using namespace ajn;
using namespace services;

class CurrentAirQualityListener : public CurrentAirQualityIntfControllerListener {
  public:
    CurrentAirQualityListener();
    virtual ~CurrentAirQualityListener();

    virtual void OnResponseGetContaminantType(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context);
    virtual void OnResponseGetCurrentValue(QStatus status, const qcc::String& objectPath, const double value, void* context);
    virtual void OnResponseGetMinValue(QStatus status, const qcc::String& objectPath, const double value, void* context);
    virtual void OnResponseGetMaxValue(QStatus status, const qcc::String& objectPath, const double value, void* context);
    virtual void OnResponseGetPrecision(QStatus status, const qcc::String& objectPath, const double value, void* context);
    virtual void OnResponseGetUpdateMinTime(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context);

    virtual void OnContaminantTypeChanged(const qcc::String& objectPath, const uint8_t value);
    virtual void OnCurrentValueChanged(const qcc::String& objectPath, const double value);
    virtual void OnMaxValueChanged(const qcc::String& objectPath, const  double value);
    virtual void OnMinValueChanged(const qcc::String& objectPath, const double value);
    virtual void OnPrecisionChanged(const qcc::String& objectPath, const double value);
    virtual void OnUpdateMinTimeChanged(const qcc::String& objectPath, const uint16_t value);
};

class CurrentAirQualityCommands : public InterfaceCommands
{
  public:
    CurrentAirQualityCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~CurrentAirQualityCommands();

    virtual void Init();

    CurrentAirQualityIntfController* GetInterface() { return m_intfController; }

    static void OnCmdGetContaminantType(Commands* commands, std::string& cmd);
    static void OnCmdGetCurrentValue(Commands* commands, std::string& cmd);
    static void OnCmdGetMaxValue(Commands* commands, std::string& cmd);
    static void OnCmdGetMinValue(Commands* commands, std::string& cmd);
    static void OnCmdGetPrecision(Commands* commands, std::string& cmd);
    static void OnCmdGetUpdateMinTime(Commands* commands, std::string& cmd);

  private:
    CurrentAirQualityIntfController* m_intfController;
    CurrentAirQualityListener m_listener;
};

#endif /* CURRENTAIRQUALITYCOMMANDS_H_ */