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

#ifndef FILTERSTATUSLISTENER_H_
#define FILTERSTATUSLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/FilterStatusIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/FilterStatusIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class FilterStatusListener : public FilterStatusIntfControlleeListener
{
  public:
    virtual QStatus OnGetExpectedLifeInDays(uint16_t& value);
    virtual QStatus OnGetIsCleanable(bool& isCleanable);
    virtual QStatus OnGetOrderPercentage(uint8_t& value);
    virtual QStatus OnGetManufacturer(qcc::String& manufacturer);
    virtual QStatus OnGetPartNumber(qcc::String& partNumber);
    virtual QStatus OnGetUrl(qcc::String& url);
    virtual QStatus OnGetLifeRemaining(uint8_t& value);
};

class FilterStatusCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    FilterStatusCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~FilterStatusCommands();

    virtual void Init();
    virtual void InitializeProperties();

    FilterStatusIntfControllee* GetInterface() { return m_intfControllee; }

    static void OnCmdGetExpectedLifeInDays(Commands* commands, std::string& cmd);
    static void OnCmdSetExpectedLifeInDays(Commands* commands, std::string& cmd);
    static void OnCmdGetIsCleanable(Commands* commands, std::string& cmd);
    static void OnCmdSetIsCleanable(Commands* commands, std::string& cmd);
    static void OnCmdGetOrderPercentage(Commands* commands, std::string& cmd);
    static void OnCmdSetOrderPercentage(Commands* commands, std::string& cmd);
    static void OnCmdGetManufacturer(Commands* commands, std::string& cmd);
    static void OnCmdGetPartNumber(Commands* commands, std::string& cmd);
    static void OnCmdGetUrl(Commands* commands, std::string& cmd);
    static void OnCmdGetLifeRemaining(Commands* commands, std::string& cmd);
    static void OnCmdSetLifeRemaining(Commands* commands, std::string& cmd);

  private:
    FilterStatusIntfControllee* m_intfControllee;
    FilterStatusListener m_listener;
};

#endif /* FILTERSTATUSLISTENER_H_ */