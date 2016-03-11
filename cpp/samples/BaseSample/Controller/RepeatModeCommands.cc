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

#include <cstdlib>
#include <alljoyn/hae/interfaces/HaeInterfaceTypes.h>
#include "RepeatModeCommands.h"
#include "ControllerSample.h"

RepeatModeListener::RepeatModeListener()
{
}

RepeatModeListener::~RepeatModeListener()
{
}

void RepeatModeListener::OnResponseGetRepeatMode(QStatus status, const qcc::String& objectPath, const bool repeatMode, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "repeatMode: " << repeatMode << endl;
}

void RepeatModeListener::OnResponseSetRepeatMode(QStatus status, const qcc::String& objectPath, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
}

void RepeatModeListener::OnRepeatModeChanged(const qcc::String& objectPath, const bool value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "value: " << value << endl;
}



RepeatModeCommands::RepeatModeCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

RepeatModeCommands::~RepeatModeCommands()
{
}

void RepeatModeCommands::Init()
{
    if (!m_intfController) {
        HaeInterface* haeInterface = m_sample->CreateInterface(REPEAT_MODE_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!haeInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<RepeatModeIntfController*>(haeInterface);
    }

    RegisterCommand(&RepeatModeCommands::OnCmdGetRepeatMode, "grm", "get repeat mode");
    RegisterCommand(&RepeatModeCommands::OnCmdSetRepeatMode, "srm", "set repeat mode");
    PrintCommands();
}

void RepeatModeCommands::OnCmdGetRepeatMode(Commands* commands, std::string& cmd)
{
    RepeatModeIntfController* intfController = static_cast<RepeatModeCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetRepeatMode();
}

void RepeatModeCommands::OnCmdSetRepeatMode(Commands* commands, std::string& cmd)
{
    RepeatModeIntfController* intfController = static_cast<RepeatModeCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }
    bool repeatMode = atoi(cmd.c_str());

    intfController->SetRepeatMode(repeatMode);
}
