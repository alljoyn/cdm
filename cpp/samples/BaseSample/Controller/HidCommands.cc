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
#include <map>
#include <alljoyn/cdm/interfaces/CdmInterfaceTypes.h>
#include "HidCommands.h"
#include "ControllerSample.h"

// Integration of UInput functionalities
// Default activation status = OFF
// To activate it : scons BINDINGS=... UINPUT=on
#ifdef UINPUT
#include "UInput.h"
#endif

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
        m_intfController = m_sample->GetController()->CreateInterface<HidIntfController>(m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!m_intfController) {
            cout << "Interface creation failed." << endl;
            return;
        }


    }

    RegisterCommand(&HidCommands::OnCmdGetSupportedEvents, "gse", "get supported events");
    RegisterCommand(&HidCommands::OnCmdInjectGenericEvent, "ige", "inject generic event (use 'ige <type> <code> <value>')");
    RegisterCommand(&HidCommands::OnCmdInjectKeyEvent,     "ike", "inject key event (use 'ike <key code>')");

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

#ifdef UINPUT
    // for available event types and code
    // see event types : https://git.kernel.org/cgit/linux/kernel/git/stable/linux-stable.git/tree/include/uapi/linux/input-event-codes.h

    // check type
    if(type < EV_SYN || type > EV_MAX) {
        cout << "Input argument 'type' out of range. (0x00 <= type <= 0x1f)" << endl;
        return;
    }

    // check code
    std::map<uint16_t, uint16_t> codeMinByTypes;
    std::map<uint16_t, uint16_t> codeMaxByTypes;
    codeMinByTypes[EV_SYN] = SYN_REPORT;
    codeMaxByTypes[EV_SYN] = SYN_MAX;
    codeMinByTypes[EV_KEY] = KEY_RESERVED;
    codeMaxByTypes[EV_KEY] = KEY_MAX;
    codeMinByTypes[EV_REL] = REL_X;
    codeMaxByTypes[EV_REL] = REL_MAX;
    codeMinByTypes[EV_ABS] = ABS_X;
    codeMaxByTypes[EV_ABS] = ABS_MAX;
    codeMinByTypes[EV_MSC] = MSC_SERIAL;
    codeMaxByTypes[EV_MSC] = MSC_MAX;
    codeMinByTypes[EV_SW]  = SW_LID;
    codeMaxByTypes[EV_SW]  = SW_MAX;
    codeMinByTypes[EV_LED] = LED_NUML;
    codeMaxByTypes[EV_LED] = LED_MAX;
    codeMinByTypes[EV_SND] = SND_CLICK;
    codeMaxByTypes[EV_SND] = SND_MAX;
    codeMinByTypes[EV_REP] = REP_DELAY;
    codeMaxByTypes[EV_REP] = REP_MAX;

    if(codeMinByTypes.find(type) != codeMinByTypes.end() &&
       codeMaxByTypes.find(type) != codeMaxByTypes.end()) {
        if (code < codeMinByTypes[type] || code > codeMaxByTypes[type]) {
            cout << "Input argument 'code' out of range. min = " << codeMinByTypes[type] << "  max = " << codeMaxByTypes[type] << endl;
            return;
        }
    }
    else {
        if(code < 0 || code > UINT16_MAX) {
            cout << "Input argument 'code' out of range. min = 0x0000  max = 0xffff" << endl;
            return;
        }
    }
    codeMinByTypes.clear();
    codeMaxByTypes.clear();

    //check value
    if( type == EV_SYN || type == EV_KEY) {
        if (value != 0 &&  value != 1) {
            cout << "Input argument 'value' out of range. (syn value = 0 or 1)" << endl;
            return;
        }
    }
    else {
        if(value < INT32_MIN || value > INT32_MAX) {
            cout << "Input argument 'value' out of range." << endl;
            return;
        }
    }
#else
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
#endif

    // type, code and value checked => inject event
    HidIntfController::InputEvents events;
    HidIntfController::InputEvent event;
    event.type = type;
    event.code = code;
    event.value = value;
    events.push_back(event);
    intfController->InjectEvents(events);
}

void HidCommands::OnCmdInjectKeyEvent(Commands* commands, std::string& cmd)
{
    HidIntfController* intfController = static_cast<HidCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int keyCode = strtol(cmd.c_str(), NULL, 0);

#ifdef UINPUT
    if(keyCode < KEY_RESERVED || keyCode > KEY_MAX) {
        cout << "Input argument 'key code' out of range. (0 <= key code <= 0x2ff)" << endl;
        return;
    }
#else
    if(keyCode < 0 || keyCode > UINT16_MAX) {
        cout << "Input argument 'key code' out of range. min = 0x0000  max = 0xffff" << endl;
        return;
    }
#endif

    HidIntfController::InputEvents events;
    HidIntfController::InputEvent event;
    // press key
    event.type = 0x01; // EV_KEY;
    event.code = keyCode;
    event.value = 1;
    events.push_back(event);
    // release key
    event.type = 0x01; // EV_KEY;
    event.code = keyCode;
    event.value = 0;
    events.push_back(event);
    //sync
    event.type = 0x00; // EV_SYN;
    event.code = 0; // SYN_REPORT;
    event.value = 0;
    events.push_back(event);
    intfController->InjectEvents(events);
}
