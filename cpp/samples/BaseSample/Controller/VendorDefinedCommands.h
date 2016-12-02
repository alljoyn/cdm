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

#ifndef VENDORDEFINEDCOMMANDS_H_
#define VENDORDEFINEDCOMMANDS_H_

#include "InterfaceCommands.h"
#include "VendorDefinedIntfController.h"
#include "VendorDefinedIntfControllerListener.h"

class ControllerSample;

using namespace ajn;
using namespace services;

class VendorDefinedListener : public VendorDefinedIntfControllerListener {
  public:
    VendorDefinedListener();
    virtual ~VendorDefinedListener();
    virtual void OnResponseSetTestProperty(QStatus status, const qcc::String& objectPath, void* context);
    virtual void OnResponseGetTestProperty(QStatus status, const qcc::String& objectPath, int32_t property, void* context);
    virtual void OnResponseTestMethod(QStatus status, const qcc::String& objectPath,
            void* context, const char* errorName, const char* errorMessage);

    /*
     * TODO: define functions that receives the PropertyChanged and other signals
     */
    virtual void OnTestPropertyChanged(const qcc::String& objectPath, const int32_t property);
    virtual void OnTestSignal(const qcc::String& objectPath);
};

class VendorDefinedCommands : public InterfaceCommands
{
  public:
    VendorDefinedCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath);
    virtual ~VendorDefinedCommands();

    virtual void Init();

    VendorDefinedIntfController* GetInterface() { return m_intfController; }
    static void OnCmdGetTestProperty(Commands* commands, std::string& cmd);
    static void OnCmdSetTestProperty(Commands* commands, std::string& cmd);
    static void OnCmdTestMethod(Commands* commands, std::string& cmd);

  private:
    VendorDefinedIntfController* m_intfController;
    VendorDefinedListener m_listener;
};

#endif /* VENDORDEFINEDCOMMANDS_H_ */