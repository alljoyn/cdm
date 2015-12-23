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
#include "OnOffStatusCommands.h"
#include "ControllerSample.h"

OnOffStatusListener::OnOffStatusListener()
{
}

OnOffStatusListener::~OnOffStatusListener()
{
}

void OnOffStatusListener::OnOnOffChanged(const qcc::String& objectPath, const bool value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "OnOff: " << value << endl;
}

void OnOffStatusListener::OnResponseGetOnOff(QStatus status, const qcc::String& objectPath, const bool value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "OnOff: " << value << endl;
}

OnOffStatusCommands::OnOffStatusCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

OnOffStatusCommands::~OnOffStatusCommands()
{
}

void OnOffStatusCommands::Init()
{
    if (!m_intfController) {
        HaeInterface* haeInterface = m_sample->CreateInterface(ON_OFF_STATUS_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!haeInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<OnOffStatusIntfController*>(haeInterface);
    }

    RegisterCommand(&OnOffStatusCommands::OnCmdOnOffStatus, "onoff", "Current OnOff Status");

    PrintCommands();
}

void OnOffStatusCommands::OnCmdOnOffStatus(Commands* commands, std::string& cmd)
{
    OnOffStatusIntfController* intfController = static_cast<OnOffStatusCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetOnOff();
}

