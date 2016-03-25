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
#include <sstream>
#include <alljoyn/hae/interfaces/HaeInterfaceTypes.h>
#include "HidCommands.h"
#include "ControllerSample.h"

using namespace std;

HidListener::HidListener()
{
}

HidListener::~HidListener()
{
}

void HidListener::OnResponseGetSupportedEvents(QStatus status, const qcc::String& objectPath, const HidInterface::SupportedInputEvents& supportedEvents, void* context)
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

void HidListener::OnSupportedEventsChanged(const qcc::String& objectPath, const HidInterface::SupportedInputEvents& supportedEvents)
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
    RegisterCommand(&HidCommands::OnCmdInjectGenericEvent, "ige", "inject generic event (use 'ige <type> <code> <value>')");

    // event types and codes are defined in <linux/input.h>
    // see : https://git.kernel.org/cgit/linux/kernel/git/stable/linux-stable.git/tree/include/uapi/linux/input-event-codes.h
    // arguments (type, code, value) could be set as decimal or hexadecimal formats
    //
    // ie :
    // - to simulate/inject a press action on the ENTER key > command = 'ige 1 28 1' or 'ige 0x01 28 1'
    // - to simulate/inject a push action (press + release) on the MUTE key > command = 'ike 113' or 'ike 0x71'

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

void HidCommands::OnCmdInjectGenericEvent(Commands* commands, std::string& cmd)
{
    HidIntfController* intfController = static_cast<HidCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    // split command to get event TYPE, CODE and VALUE
    std::string buf;
    std::stringstream ss(cmd);
    std::vector<std::string> cmd_args;
    while (ss >> buf) {
        cmd_args.push_back(buf);
    }

    if(cmd_args.size() != 3) {
        cout << "Input arguments size is wrong." << endl;
        return;
    }

    long int type = strtol(cmd_args[0].c_str(), NULL, 0);
    long int code = strtol(cmd_args[1].c_str(), NULL, 0);
    long int value = strtol(cmd_args[2].c_str(), NULL, 0);

    // check type
    if(type < 0 || type > UINT16_MAX) {
        cout << "Input argument 'type' out of range. (0x0000 <= type <= 0xffff)" << endl;
        return;
    }

    // check code
    if(code < 0 || code > UINT16_MAX) {
        cout << "Input argument 'code' out of range. min = 0x0000  max = 0xffff" << endl;
        return;
    }
    //check value
    if(value < INT32_MIN || value > INT32_MAX) {
        cout << "Input argument 'value' out of range." << endl;
        return;
    }

    // type, code and value checked => inject event
    HidIntfController::InputEvents events;
    HidIntfController::InputEvent event;
    event.type = type;
    event.code = code;
    event.value = value;
    events.push_back(event);
    intfController->InjectEvents(events);
}
