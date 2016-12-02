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

#ifndef TEMPERATUREDISPLAYLISTENER_H_
#define TEMPERATUREDISPLAYLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/userinterfacesettings/TemperatureDisplayIntfControllee.h>
#include <alljoyn/cdm/interfaces/userinterfacesettings/TemperatureDisplayIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class TemperatureDisplayListener : public TemperatureDisplayIntfControlleeListener
{
  public:

    virtual QStatus OnSetDisplayTemperatureUnit(const uint8_t temperatureUnit);

    virtual QStatus OnGetDisplayTemperatureUnit(uint8_t& temperatureUnit);

    virtual QStatus OnGetSupportedDisplayTemperatureUnits(std::vector<uint8_t>& supportedDisplayTemperatureUnits);

};

class TemperatureDisplayCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    TemperatureDisplayCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~TemperatureDisplayCommands();

    virtual void Init();
    virtual void InitializeProperties();

    TemperatureDisplayIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetDisplayTemperatureUnit(Commands* commands, std::string& cmd);
    static void OnCmdSetDisplayTemperatureUnit(Commands* commands, std::string& cmd);

    static void OnCmdGetSupportedDisplayTemperatureUnits(Commands* commands, std::string& cmd);

  private:
    TemperatureDisplayIntfControllee* m_intfControllee;
    TemperatureDisplayListener m_listener;
};




#endif /* TEMPERATUREDISPLAYLISTENER_H_ */