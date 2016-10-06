/******************************************************************************
 *  *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
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
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include "AirRecirculationModeListener.h"
#include "ControlleeSample.h"

using namespace std;

QStatus AirRecirculationModeListener::OnSetIsRecirculating(const bool& isRecirculating)
{
    cout << "AirRecirculationModeListener::OnSetIsRecirculating() - isRecirculating : " << isRecirculating << endl;
    return ER_OK;
}

QStatus AirRecirculationModeListener::OnGetIsRecirculating(bool& isRecirculating)
{
    cout << "AirRecirculationModeListener::OnGetIsRecirculating()" << endl;
    return ER_OK;
}
////////////////////////////////////////////////////////////////////////////////

ControlleeCommands* AirRecirculationModeCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new AirRecirculationModeCommands(sample, objectPath);
}

AirRecirculationModeCommands::AirRecirculationModeCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

AirRecirculationModeCommands::~AirRecirculationModeCommands()
{
}

void AirRecirculationModeCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(AIR_RECIRCULATION_MODE_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<AirRecirculationModeIntfControllee*>(cdmInterface);

        RegisterCommand(&AirRecirculationModeCommands::OnCmdGetIsRecirculating, "gir", "get is recirculating");
        RegisterCommand(&AirRecirculationModeCommands::OnCmdSetIsRecirculating, "sir", "set is recirculating (use 'sir <0/1>'");
    } else {
        PrintCommands();
    }
}

void AirRecirculationModeCommands::OnCmdGetIsRecirculating(Commands* commands, std::string& cmd)
{
    AirRecirculationModeIntfControllee* intfControllee = static_cast<AirRecirculationModeCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << intfControllee->GetIsRecirculating() << endl;
}

void AirRecirculationModeCommands::OnCmdSetIsRecirculating(Commands* commands, std::string& cmd)
{
    AirRecirculationModeIntfControllee* intfControllee = static_cast<AirRecirculationModeCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int isRecirculating = strtol(cmd.c_str(), NULL, 10);
    if (isRecirculating == 0 || isRecirculating == 1) {
        intfControllee->SetIsRecirculating(isRecirculating);
    } else {
        cout << "Input argument is wrong." << endl;
        return;
    }
}