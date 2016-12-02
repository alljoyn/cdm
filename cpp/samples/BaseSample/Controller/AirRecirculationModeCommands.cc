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

#include "AirRecirculationModeCommands.h"
#include "ControllerSample.h"

AirRecirculationModeListener::AirRecirculationModeListener()
{
}

AirRecirculationModeListener::~AirRecirculationModeListener()
{
}

void AirRecirculationModeListener::OnResponseSetIsRecirculating(QStatus status, const qcc::String& objectPath, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
}

void AirRecirculationModeListener::OnResponseGetIsRecirculating(QStatus status, const qcc::String& objectPath, const bool isRecirculating, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "isRecirculating: " << isRecirculating << endl;
}

void AirRecirculationModeListener::OnIsRecirculatingChanged(const qcc::String& objectPath, const bool isRecirculating)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "isRecirculating: " << isRecirculating << endl;
}

AirRecirculationModeCommands::AirRecirculationModeCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

AirRecirculationModeCommands::~AirRecirculationModeCommands()
{

}

void AirRecirculationModeCommands::Init()
{
    if (!m_intfController) {
        m_intfController = m_sample->GetController()->CreateInterface<AirRecirculationModeIntfController>(m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!m_intfController) {
            cout << "Interface creation failed." << endl;
            return;
        }
    }

    RegisterCommand(&AirRecirculationModeCommands::OnCmdGetIsRecirculating, "gir", "get is recirculating");
    RegisterCommand(&AirRecirculationModeCommands::OnCmdSetIsRecirculating, "sir", "set is recirculating (use 'sir <0/1>'");
    PrintCommands();
}

void AirRecirculationModeCommands::OnCmdGetIsRecirculating(Commands* commands, std::string& cmd)
{
    AirRecirculationModeIntfController* intfController = static_cast<AirRecirculationModeCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetIsRecirculating();
}

void AirRecirculationModeCommands::OnCmdSetIsRecirculating(Commands* commands, std::string& cmd)
{
    AirRecirculationModeIntfController* intfController = static_cast<AirRecirculationModeCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int isRecirculating = strtol(cmd.c_str(), NULL, 10);
    if (isRecirculating == 0 || isRecirculating == 1) {
        intfController->SetIsRecirculating(isRecirculating);
    } else {
        cout << "Input argument is wrong." << endl;
        return;
    }
}
