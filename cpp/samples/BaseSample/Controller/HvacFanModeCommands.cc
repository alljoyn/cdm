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
#include <alljoyn/cdm/interfaces/CdmInterfaceTypes.h>
#include "HvacFanModeCommands.h"
#include "ControllerSample.h"

HvacFanModeListener::HvacFanModeListener()
{
}

HvacFanModeListener::~HvacFanModeListener()
{
}

void HvacFanModeListener::OnResponseSetMode(QStatus status, const qcc::String& objectPath, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
}

void HvacFanModeListener::OnResponseGetMode(QStatus status, const qcc::String& objectPath, const Mode value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "Mode: " << value << endl;
}

void HvacFanModeListener::OnResponseGetSupportedModes(QStatus status, const qcc::String& objectPath, const std::vector<Mode>& value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "SupportedModes: ";
    for( int i=0 ;  i < (int)value.size() ; i++)
    {
        cout << value[i] << " ";
    }
    cout << endl;
}

void HvacFanModeListener::OnModeChanged(const qcc::String& objectPath, const Mode value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "Mode: " << value << endl;
}

void HvacFanModeListener::OnSupportedModesChanged(const qcc::String& objectPath, const std::vector<Mode>& value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;

    for( int i=0 ;  i < (int)value.size() ; i++)
    {
        cout << value[i] << " ";
    }
    cout << endl;

}

HvacFanModeCommands::HvacFanModeCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

HvacFanModeCommands::~HvacFanModeCommands()
{
}

void HvacFanModeCommands::Init()
{
    if (!m_intfController) {
        m_intfController = m_sample->GetController()->CreateInterface<HvacFanModeIntfController>(m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!m_intfController) {
            cout << "Interface creation failed." << endl;
            return;
        }


    }

    RegisterCommand(&HvacFanModeCommands::OnCmdGetMode, "getmode", "Get Mode");
    RegisterCommand(&HvacFanModeCommands::OnCmdSetMode, "setmode", "Set Mode");
    RegisterCommand(&HvacFanModeCommands::OnCmdGetSupportedModes, "getsm", "Get SupportedModes");

    PrintCommands();
}

void HvacFanModeCommands::OnCmdGetMode(Commands* commands, std::string& cmd)
{
    HvacFanModeIntfController* intfController = static_cast<HvacFanModeCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetMode();
}

void HvacFanModeCommands::OnCmdSetMode(Commands* commands, std::string& cmd)
{
    HvacFanModeIntfController* intfController = static_cast<HvacFanModeCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int mode = strtol(cmd.c_str(), NULL, 10);
    if (mode < 0 || mode > 6) {
        cout << "Input argument is wrong." << endl;
        return;
    }
    intfController->SetMode((HvacFanModeInterface::Mode)mode);
}

void HvacFanModeCommands::OnCmdGetSupportedModes(Commands* commands, std::string& cmd)
{
    HvacFanModeIntfController* intfController = static_cast<HvacFanModeCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetSupportedModes();
}
