/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
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
#ifdef UINPUT
#include "UInput.h"

#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

UInput UInput::m_instance = UInput();

// ------------------------------------------------------------------------------------
// Singleton
// ------------------------------------------------------------------------------------
UInput::UInput()
{
    m_deviceFD = -1;
}

UInput::~UInput()
{

}

UInput& UInput::Instance()
{
    return m_instance;
}

// ------------------------------------------------------------------------------------
// Singleton life cycle
// ------------------------------------------------------------------------------------
void UInput::Init(uint16_t vendorId, uint16_t productId, uint16_t version, HidInterface::SupportedInputEvents supportedEvents)
{
    m_supportedEvents = supportedEvents;

    // open the device that represents the interface between
    // the application and the kernel input subsystem
    // named as /dev/input/uinput (or /dev/uinput on some systems)
    m_deviceFD = open("/dev/input/uinput", O_WRONLY | O_NDELAY);
    if (m_deviceFD == -1) {
        // not find with first name => try with second one
        m_deviceFD = open("/dev/uinput", O_WRONLY | O_NDELAY);
    }

    if (m_deviceFD == -1) {
        // unable to open the device
        // uinput is not available on the system or you haven't root privilege
        cout << "!!!! FAILURE !!!!" << endl;
        cout << "UInput::Init > unable to open uinput device" << endl;
        cout << "- uinput kernel module must be available on your system: please check that /dev/input/uinput or /dev/uinput are present" << endl;
        cout << "- check that permission on /dev/input/uinput or /dev/uinput are correctly set, by default only root can use uinput" << endl;
        return;
    }

    std::map<uint16_t, unsigned long> eventTypesToIoctlRequest;
    eventTypesToIoctlRequest[EV_KEY] = UI_SET_KEYBIT;
    eventTypesToIoctlRequest[EV_REL] = UI_SET_RELBIT;
    eventTypesToIoctlRequest[EV_ABS] = UI_SET_ABSBIT;
    eventTypesToIoctlRequest[EV_SW]  = UI_SET_SWBIT;
    eventTypesToIoctlRequest[EV_MSC] = UI_SET_MSCBIT;
    eventTypesToIoctlRequest[EV_LED] = UI_SET_LEDBIT;
    eventTypesToIoctlRequest[EV_SND] = UI_SET_SNDBIT;
    eventTypesToIoctlRequest[EV_FF]  = UI_SET_FFBIT;

    // we have to enable each supported events
    std::vector<uint16_t> enabledTypes;
    for(HidInterface::SupportedInputEvents::const_iterator citer = m_supportedEvents.begin();
        citer != m_supportedEvents.end(); citer++) {

        // enable event type
        if(std::find(enabledTypes.begin(), enabledTypes.end(), citer->type) != enabledTypes.end()) {
            // event type already enabled => nothing to do
        }
        else {
            // new event type => enable it
            enabledTypes.push_back(citer->type);
            if(ioctl(m_deviceFD, UI_SET_EVBIT, citer->type) < 0) {
                cout << "UInput::Init > unable to enable event type : " << citer->type << endl;
            }
        }

        // enable event code
        if(eventTypesToIoctlRequest.find(citer->type) != eventTypesToIoctlRequest.end()) {
            if(ioctl(m_deviceFD, eventTypesToIoctlRequest[citer->type], citer->code) < 0) {
                cout << "UInput::Init > unable to enable event code : [type : " << citer->type << "] [code :" << citer->code << "]" << endl;
            }
        }
    }
    eventTypesToIoctlRequest.clear();

    // now, basic features have been enabled, we need to finish the configuration
    // by using the struct uinput_user_dev from linux/uinput.h
    struct uinput_user_dev uidev;
    memset(&uidev, 0, sizeof(uidev));
    // name is the given name of the input device we will create
    snprintf(uidev.name, UINPUT_MAX_NAME_SIZE, "uinput-cdm-controllee");
    // id is a linux internal structure that describes the device bustype
    uidev.id.bustype = BUS_USB;
    uidev.id.vendor = vendorId;
    uidev.id.product = productId;
    uidev.id.version = version;

    // we write this structure in the uinput file descriptor
    if(write(m_deviceFD, &uidev, sizeof(uidev)) < 0) {
        cout << "UInput::Init > unable to write in the uinput file descriptor" << endl;
    }

    // last step is to request the creation of the device via the UI_DEV_CREATE ioctl request on the file descriptor
    if(ioctl(m_deviceFD, UI_DEV_CREATE) < 0) {
        cout << "UInput::Init > unable to create the input device" << endl;
    }
}

void UInput::Release()
{
    if (m_deviceFD != -1) {
        // destroy the device used for the injections
        ioctl(m_deviceFD, UI_DEV_DESTROY);
        // close the file descriptor
        close(m_deviceFD);
        m_deviceFD = -1;
    }
}

// ------------------------------------------------------------------------------------
// Singleton methods
// ------------------------------------------------------------------------------------
int UInput::InjectEvent(uint16_t type, uint16_t code, int32_t value)
{
    if(m_deviceFD != -1) {
        // check if the event is supported
        bool eventSupported = false;
        HidInterface::SupportedInputEvents::const_iterator event;
        for(event = m_supportedEvents.begin(); event != m_supportedEvents.end(); event++) {
            if(event->type == type && event->code == code) {
                eventSupported = true;
                break;
            }
        }
        if(eventSupported) {
            if(value < event->min || value > event->max) {
                cout << "UInput::InjectEvent > event value out of range" << endl;
                return -1;
            }
        }
        else {
            cout << "UInput::InjectEvent > event not supported" << endl;
            return -1;
        }

        // everything is fine => inject the event
        struct input_event ev;
        memset(&ev, 0, sizeof(ev));
        gettimeofday(&ev.time, NULL);
        ev.type = type;
        ev.code = code;
        ev.value = value;
        return write(m_deviceFD, &ev, sizeof(ev));
    }
    cout << "UInput::InjectEvent > bad file descriptor (UInput instance initialized ?)" << endl;
    return -1;
}
// ------------------------------------------------------------------------------------
#endif