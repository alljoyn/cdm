/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <iostream>
#include "ClosedStatusListener.h"
#include "ControlleeSample.h"


using namespace std;


QStatus ClosedStatusListener::OnGetIsClosed(bool& isClosed)
{
    cout << "ClosedStatusListener::OnGetIsClosed()" << endl;
    return ER_OK;
}

ControlleeCommands* ClosedStatusCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new ClosedStatusCommands(sample, objectPath);
}

ClosedStatusCommands::ClosedStatusCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

ClosedStatusCommands::~ClosedStatusCommands()
{
}

void ClosedStatusCommands::Init()
{
    if (!m_intfControllee) {
        HaeInterface* haeInterface = m_sample->CreateInterface(CLOSED_STATUS_INTERFACE, m_objectPath, m_listener);
        if (!haeInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<ClosedStatusIntfControllee*>(haeInterface);

        RegisterCommand(&ClosedStatusCommands::OnCmdGetClosedStatus, "gic", "get is closed");
        RegisterCommand(&ClosedStatusCommands::OnCmdSetClosedStatus, "sic", "set is closed (use 'sic <0/1>'");
    } else {
        PrintCommands();
    }
}

void ClosedStatusCommands::OnCmdGetClosedStatus(Commands* commands, std::string& cmd)
{
    ClosedStatusIntfControllee* intfControllee = static_cast<ClosedStatusCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << intfControllee->GetIsClosed() << endl;

}
void ClosedStatusCommands::OnCmdSetClosedStatus(Commands* commands, std::string& cmd)
{
    ClosedStatusIntfControllee* intfControllee = static_cast<ClosedStatusCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int isClosed = strtol(cmd.c_str(), NULL, 10);
    if(isClosed != 0 && isClosed != 1)
    {
        cout << "input argument is wrong" << endl;
        return;
    }
    intfControllee->SetIsClosed((bool)isClosed);

}