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

#include "HidListener.h"
#include "ControlleeSample.h"

// Integration of UInput functionalities
// Default activation status = OFF
// To activate it : scons BINDINGS=... UINPUT=on
#ifdef UINPUT
#include "UInput.h"
// To create the input device, we need a vendor ID, a product ID and a version
// In this sample, we are using LGE ID
// see : http://www.linux-usb.org/usb.ids
#define UINPUT_DEV_VENDOR_ID   0x043e // LG Electronics USA, Inc.
#define UINPUT_DEV_PRODUCT_ID  0xffff // unknown product
#define UINPUT_DEV_VERSION     0x01
#endif

using namespace std;

void HidListener::OnInjectEvents(HidInterface::InputEvents& inputEvents)
{
#ifdef UINPUT
    // we use UInput to inject each event in linux kernel
    for (HidInterface::InputEvents::iterator it = inputEvents.begin() ; it != inputEvents.end(); ++it) {
        HidInterface::InputEvent iev = *it;
        if(UInput::Instance().InjectEvent(iev.type, iev.code, iev.value) < 0) {
            cout << "event injection >> [type : " << iev.type << "] [code : " << iev.code << "] [value :" << iev.value << "] >> FAILURE" << endl;
            break;
        }
        else {
            cout << "event injection >> [type : " << iev.type << "] [code : " << iev.code << "] [value :" << iev.value << "] >> INJECTED" << endl;
        }
    }
#else
    cout << "HidListener::OnInjectEvents - inputEvents size : " << inputEvents.size() << endl;
#endif
}

QStatus HidListener::OnGetSupportedEvents(HidInterface::SupportedInputEvents& supportedEvents)
{
    cout << "HidListener::OnGetSupportedEvents()" << endl;
    return ER_OK;
}

/////////////////////////////////////////////////////////////////////////////////////
ControlleeCommands* HidCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new HidCommands(sample, objectPath);
}

HidCommands::HidCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

HidCommands::~HidCommands()
{
}

void HidCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(HID_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }
        m_intfControllee = static_cast<HidIntfControllee*>(cdmInterface);

        RegisterCommand(&HidCommands::OnCmdGetSupportedEvents, "gse", "get supported events");
    } else {
        PrintCommands();
    }
}

void HidCommands::InitializeProperties()
{
    if (m_intfControllee) {
        HidInterface::SupportedInputEvents supportedEvents;
        HidInterface::SupportedInputEvent supportedEvent;
        // synchronization event (required to synchronize other events)
        supportedEvent.type = 0x00; // EV_SYN
        supportedEvent.code = 0; //SYN_REPORT
        supportedEvent.min = 0;
        supportedEvent.max = 0;
        supportedEvents.push_back(supportedEvent);
        // all numeric keys
        for(uint16_t code = 0x200; code <= 0x209; code++) { // KEY_NUMERIC_0 to KEY_NUMERIC_9
            supportedEvent.type = 0x01; // EV_KEY
            supportedEvent.code = code;
            supportedEvent.min = 0; // release state
            supportedEvent.max = 1; // press state
            supportedEvents.push_back(supportedEvent);
        }
        // all volume keys
        for(uint16_t code = 0x71; code <= 0x73; code++) { // KEY_MUTE to KEY_VOLUMEUP
            supportedEvent.type = 0x01; // EV_KEY
            supportedEvent.code = code;
            supportedEvent.min = 0; // release state
            supportedEvent.max = 1; // press state
            supportedEvents.push_back(supportedEvent);
        }
        m_intfControllee->SetSupportedEvents(supportedEvents);

#ifdef UINPUT
        // Initialize the UInput instance (to create the input device on system)
        UInput::Instance().Init(UINPUT_DEV_VENDOR_ID, UINPUT_DEV_PRODUCT_ID, UINPUT_DEV_VERSION, supportedEvents);
#endif
    }
}
void HidCommands::OnCmdGetSupportedEvents(Commands* commands, std::string& cmd)
{
    HidIntfControllee* intfControllee = static_cast<HidCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    const HidInterface::SupportedInputEvents& events = intfControllee->GetSupportedEvents();
    for (HidInterface::SupportedInputEvents::const_iterator citer = events.begin();
            citer != events.end(); citer++) {
        cout << "type : " << (int)citer->type << endl;
        cout << "code : " << (int)citer->code<< endl;
        cout << "min  : " << (int)citer->min << endl;
        cout << "max  : " << (int)citer->max << endl;
    }

}