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

#include "ResourceSavingListener.h"
#include "ControlleeSample.h"

using namespace std;

QStatus ResourceSavingListener::OnSetResourceSavingMode(const bool& mode)
{
    cout << "ResourceSavingListener::OnSetResourceSavingMode() - ResourceSavingMode : " << mode << endl;
    return ER_OK;
}

QStatus ResourceSavingListener::OnGetResourceSavingMode(bool& mode)
{
    cout << "ResourceSavingListener::OnGetResourceSavingMode() - ResourceSavingMode : " << mode << endl;
    return ER_OK;
}
///////////////////////////////////////////////////////////////////////////////////

ControlleeCommands* ResourceSavingCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new ResourceSavingCommands(sample, objectPath);
}

ResourceSavingCommands::ResourceSavingCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

ResourceSavingCommands::~ResourceSavingCommands()
{
}

void ResourceSavingCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(RESOURCE_SAVING_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<ResourceSavingIntfControllee*>(cdmInterface);

        RegisterCommand(&ResourceSavingCommands::OnCmdGetResourceSavingMode, "grm", "get resource saving mode");
        RegisterCommand(&ResourceSavingCommands::OnCmdSetResourceSavingMode, "srm", "set resource saving mode(use 'srm <0/1>'");

    } else {
        PrintCommands();
    }
}

void ResourceSavingCommands::OnCmdGetResourceSavingMode(Commands* commands, std::string& cmd)
{
    ResourceSavingIntfControllee* intfControllee = static_cast<ResourceSavingCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << intfControllee->GetResourceSavingMode() << endl;
}

void ResourceSavingCommands::OnCmdSetResourceSavingMode(Commands* commands, std::string& cmd)
{
    ResourceSavingIntfControllee* intfControllee = static_cast<ResourceSavingCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int mode = strtol(cmd.c_str(), NULL, 10);
    if (mode == 0 || mode == 1) {
        intfControllee->SetResourceSavingMode(mode);
    } else {
        cout << "Input argument is wrong." << endl;
        return;
    }
}