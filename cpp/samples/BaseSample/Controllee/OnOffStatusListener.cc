/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
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

#include "OnOffStatusListener.h"
#include "ControlleeSample.h"

using namespace std;

QStatus OnOffStatusListener::OnGetIsOn(bool& value)
{
    cout << "OnOffStatusListener::OnGetIsOn() - OnOff : " << value << endl;
    return ER_OK;
}

///////////////////////////////////////////////////////////////////////////////////

ControlleeCommands* OnOffStatusCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new OnOffStatusCommands(sample, objectPath);
}

OnOffStatusCommands::OnOffStatusCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

OnOffStatusCommands::~OnOffStatusCommands()
{
}

void OnOffStatusCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(ON_OFF_STATUS_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<OnOffStatusIntfControllee*>(cdmInterface);

        RegisterCommand(&OnOffStatusCommands::OnCmdGetIsOnStatus, "gos", "get on/off status");
        RegisterCommand(&OnOffStatusCommands::OnCmdSetIsOnStatus, "sos", "set on/off status(use 'sos <0/1>'");

    } else {
        PrintCommands();
    }
}

void OnOffStatusCommands::OnCmdGetIsOnStatus(Commands* commands, std::string& cmd)
{
    OnOffStatusIntfControllee* intfControllee = static_cast<OnOffStatusCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << intfControllee->GetIsOn() << endl;
}

void OnOffStatusCommands::OnCmdSetIsOnStatus(Commands* commands, std::string& cmd)
{
    OnOffStatusIntfControllee* intfControllee = static_cast<OnOffStatusCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int status = strtol(cmd.c_str(), NULL, 10);
    if (status == 0 || status == 1) {
        intfControllee->SetIsOn(status);
    } else {
        cout << "Input argument is wrong." << endl;
        return;
    }
}