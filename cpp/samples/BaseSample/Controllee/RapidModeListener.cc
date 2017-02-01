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

#include <iostream>
#include "RapidModeListener.h"
#include "ControlleeSample.h"

using namespace std;


QStatus RapidModeListener::OnGetRapidMode(bool& rapidMode)
{
    cout << "RapidModeListener::OnGetRapidMode()" << endl;
    return ER_OK;
}

QStatus RapidModeListener::OnSetRapidMode(const bool& rapidMode)
{
    cout << "RapidModeListener::OnSetRapidMode()" << endl;
    return ER_OK;
}

ControlleeCommands* RapidModeCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new RapidModeCommands(sample, objectPath);
}

RapidModeCommands::RapidModeCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

RapidModeCommands::~RapidModeCommands()
{
}

void RapidModeCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(RAPID_MODE_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<RapidModeIntfControllee*>(cdmInterface);

        RegisterCommand(&RapidModeCommands::OnCmdGetRapidMode, "grm", "get rapid mode");
        RegisterCommand(&RapidModeCommands::OnCmdSetRapidMode, "srm", "set rapid mode (use 'srm <0/1>'");
    } else {
        PrintCommands();
    }
}

void RapidModeCommands::OnCmdGetRapidMode(Commands* commands, std::string& cmd)
{
    RapidModeIntfControllee* intfControllee = static_cast<RapidModeCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << intfControllee->GetRapidMode() << endl;

}
void RapidModeCommands::OnCmdSetRapidMode(Commands* commands, std::string& cmd)
{
    RapidModeIntfControllee* intfControllee = static_cast<RapidModeCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int rapidMode = strtol(cmd.c_str(), NULL, 10);
    if(rapidMode != 0 && rapidMode != 1)
    {
        cout << "input argument is wrong" << endl;
        return;
    }
    intfControllee->SetRapidMode((bool)rapidMode);

}