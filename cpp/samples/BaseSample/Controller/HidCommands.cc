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
#include "HidCommands.h"
#include "ControllerSample.h"

HidListener::HidListener()
{
}

HidListener::~HidListener()
{
}

void HidListener::SupportedEventsPropertyChanged(const qcc::String& objectPath, const HidInterface::SupportedInputEvents& supportedEvents)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    for(HidInterface::SupportedInputEvents::const_iterator citer = supportedEvents.begin();
        citer != supportedEvents.end(); citer++) {
        cout << citer->type << " "
             << citer->code << " "
             << citer->min << " "
             << citer->max << endl;
    }
}

void HidListener::GetSupportedEventsPropertyCallback(QStatus status, const qcc::String& objectPath, const HidInterface::SupportedInputEvents& supportedEvents, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    for(HidInterface::SupportedInputEvents::const_iterator citer = supportedEvents.begin();
        citer != supportedEvents.end(); citer++) {
        cout << citer->type << " "
             << citer->code << " "
             << citer->min << " "
             << citer->max << endl;
    }
}

HidCommands::HidCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

HidCommands::~HidCommands()
{
}

void HidCommands::Init()
{
    if (!m_intfController) {
        HaeInterface* haeInterface = m_sample->CreateInterface(HID_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!haeInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<HidIntfController*>(haeInterface);
    }

    RegisterCommand(&HidCommands::OnCmdGetSupportedEvents, "gse", "get supported events");
    RegisterCommand(&HidCommands::OnCmdInjectEvents, "ie", "inject events (At present, mute key event is injected.)");
    PrintCommands();
}

void HidCommands::OnCmdGetSupportedEvents(Commands* commands, std::string& cmd)
{
    HidIntfController* intfController = static_cast<HidCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetSupportedEvents();
}

void HidCommands::OnCmdInjectEvents(Commands* commands, std::string& cmd)
{
    HidIntfController* intfController = static_cast<HidCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    HidIntfController::InputEvents events;
    HidIntfController::InputEvent event;
    event.type = 0x01;
    event.code = 0x71;
    event.value = 1;
    events.push_back(event);
    intfController->InjectEvents(events);
}
