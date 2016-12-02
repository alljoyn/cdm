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

#include "VendorDefinedCommands.h"
#include "ControllerSample.h"
#include "VendorDefinedIntfControllerImpl.h"

#include <climits>

using namespace ajn;
using namespace services;

VendorDefinedListener::VendorDefinedListener()
{
}

VendorDefinedListener::~VendorDefinedListener()
{
}

void VendorDefinedListener::OnResponseSetTestProperty(QStatus status, const qcc::String& objectPath, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
}

void VendorDefinedListener::OnResponseGetTestProperty(QStatus status, const qcc::String& objectPath, int32_t property, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "property: " << property << endl;
}

void VendorDefinedListener::OnResponseTestMethod(QStatus status, const qcc::String& objectPath,
        void* context, const char* errorName, const char* errorMessage)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    if (ER_OK != status) {
        cout << "error name : " << errorName << endl;
        cout << "error message : " << errorMessage << endl;
    }
}

void VendorDefinedListener::OnTestPropertyChanged(const qcc::String& objectPath, const int32_t property)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "property: " << property << endl;
}

void VendorDefinedListener::OnTestSignal(const qcc::String& objectPath)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

VendorDefinedCommands::VendorDefinedCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

VendorDefinedCommands::~VendorDefinedCommands()
{

}

void VendorDefinedCommands::Init()
{
    if (!m_intfController) {

        CdmInterfaceType vendorDefinedIntfType = m_sample->RegisterVendorDefinedInterface("com.foo.bar.test", static_cast<CreateIntfControllerFptr>(&VendorDefinedIntfControllerImpl::CreateInterface));

        CdmInterface* cdmInterface = m_sample->CreateInterface(vendorDefinedIntfType, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<VendorDefinedIntfController*>(cdmInterface);
    }

    RegisterCommand(&VendorDefinedCommands::OnCmdGetTestProperty, "gp", "get property");
    RegisterCommand(&VendorDefinedCommands::OnCmdSetTestProperty, "sp", "set property (use 'sp <property>'");
    RegisterCommand(&VendorDefinedCommands::OnCmdTestMethod, "tm", "call TestMethod (use 'tm <arg1>'");

    PrintCommands();
}

void VendorDefinedCommands::OnCmdGetTestProperty(Commands* commands, std::string& cmd)
{
    VendorDefinedIntfController* intfController = static_cast<VendorDefinedCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetTestProperty();
}

void VendorDefinedCommands::OnCmdSetTestProperty(Commands* commands, std::string& cmd)
{
    VendorDefinedIntfController* intfController = static_cast<VendorDefinedCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int32_t property = strtol(cmd.c_str(), NULL, 10);
    if (INT_MIN > property || property > INT_MAX) {
        cout << "Input argument is wrong." << endl;
        return;
    }
    intfController->SetTestProperty((int32_t)property);
}

void VendorDefinedCommands::OnCmdTestMethod(Commands* commands, std::string& cmd)
{
    VendorDefinedIntfController* intfController = static_cast<VendorDefinedCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int32_t arg1 = strtol(cmd.c_str(), NULL, 10);
    if (INT_MIN > arg1 || arg1 > INT_MAX) {
        cout << "Input argument is wrong." << endl;
        return;
    }

    intfController->TestMethod(arg1);
}