/******************************************************************************
 *  * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#include <qcc/Util.h>

#include <alljoyn/cdm/LogModule.h>
#include <alljoyn/cdm/interfaces/input/HidIntfControlleeListener.h>
#include <alljoyn/cdm/CdmBusObject.h>
#include "HidIntfControlleeImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* HidIntfControlleeImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject)
{
    return new HidIntfControlleeImpl(busAttachment, static_cast<HidIntfControlleeListener&>(listener), cdmBusObject);
}

HidIntfControlleeImpl::HidIntfControlleeImpl(BusAttachment& busAttachment, HidIntfControlleeListener& listener, CdmBusObject& cdmBusObject) :
    InterfaceControllee(cdmBusObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

HidIntfControlleeImpl::~HidIntfControlleeImpl()
{
}

QStatus HidIntfControlleeImpl::Init()
{
    QStatus status = CdmInterface::Init();

    const InterfaceDescription::Member* member = m_interfaceDescription->GetMember("InjectEvents");
    MessageReceiver::MethodHandler methodHandler = static_cast<MessageReceiver::MethodHandler>(&HidIntfControlleeImpl::OnInjectEvents);

    m_methodHandlers.push_back(make_pair(member, methodHandler));
    return status;
}

QStatus HidIntfControlleeImpl::SetSupportedEvents(const HidInterface::SupportedInputEvents& supportedEvents)
{
    bool diff = false;

    if (m_supportedEvents.size() != supportedEvents.size()) {
        diff = true;
    } else {
        HidInterface::SupportedInputEvents::const_iterator citer1 = m_supportedEvents.begin();
        HidInterface::SupportedInputEvents::const_iterator citer2 = supportedEvents.begin();

        while (citer1 != m_supportedEvents.end()) {
            if (citer1->type != citer2->type || citer1->code != citer2->code ||
                citer1->min != citer2->min || citer2->max != citer2->max) {
                diff = true;
                break;
            }

            citer1++;
            citer2++;
        }
    }

    if(diff) {
        MsgArg* args = new MsgArg[supportedEvents.size()];
        MsgArg val;
        HidInterface::SupportedInputEvents::const_iterator citer;
        int i=0;

        for(citer = supportedEvents.begin(); citer != supportedEvents.end(); citer++, i++) {
            args[i].Set("(qqii)", citer->type, citer->code, citer->min, citer->max);
            args[i].Stabilize();
        }

        val.typeId = ALLJOYN_ARRAY;
        val.v_array.SetElements("(qqii)", i, args);
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_SupportedEvents.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_supportedEvents = supportedEvents;
        delete[] args;
    }

    return ER_OK;
}

QStatus HidIntfControlleeImpl::OnGetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    if (!(s_prop_Version.compare(propName))) {
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = GetInterfaceVersion();
    } else {
        if (s_retrievingActualPropertyValue) {
            if (!(s_prop_SupportedEvents.compare(propName))) {
                HidInterface::SupportedInputEvents supportedEvents;
                status = m_interfaceListener.OnGetSupportedEvents(supportedEvents);
                if (status != ER_OK) {
                    supportedEvents = GetSupportedEvents();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetSupportedEvents(supportedEvents);
                }

                MsgArg* args = new MsgArg[supportedEvents.size()];
                HidInterface::SupportedInputEvents::const_iterator citer;
                int i=0;

                for(citer = supportedEvents.begin(); citer != supportedEvents.end(); citer++, i++) {
                    args[i].Set("(qqii)", citer->type, citer->code, citer->min, citer->max);
                    args[i].Stabilize();
                }

                val.Set("a(qqii)", i, args);
                val.Stabilize();
                delete[] args;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
        } else {
            if (!(s_prop_SupportedEvents.compare(propName))) {
                const HidInterface::SupportedInputEvents& supportedEvents = GetSupportedEvents();
                MsgArg* args = new MsgArg[supportedEvents.size()];
                HidInterface::SupportedInputEvents::const_iterator citer;
                int i=0;

                for(citer = supportedEvents.begin(); citer != supportedEvents.end(); citer++, i++) {
                    args[i].Set("(qqii)", citer->type, citer->code, citer->min, citer->max);
                    args[i].Stabilize();
                }

                val.Set("a(qqii)", i, args);
                val.Stabilize();
                delete[] args;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
        }
    }

    return status;
}

QStatus HidIntfControlleeImpl::OnSetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_BUS_NO_SUCH_PROPERTY;

    return status;
}

void HidIntfControlleeImpl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
{
    QStatus status = ER_OK;
    bool isFound = false;
    MethodHandlers::const_iterator it;
    for (it = m_methodHandlers.begin(); it != m_methodHandlers.end(); ++it) {
        if (it->first == member) {
            MessageReceiver::MethodHandler handler = it->second;
            (this->*handler)(member, msg);
            isFound = true;
            break;
        }
    }

    if (!isFound) {
        status = ER_BUS_METHOD_CALL_ABORTED;
        QCC_LogError(status, ("%s: could not find method handler.", __func__));
    }
}

void HidIntfControlleeImpl::OnInjectEvents(const InterfaceDescription::Member* member, Message& msg)
{
    const MsgArg* args = NULL;
    size_t numArgs = 0;

    msg->GetArgs(numArgs, args);

    if (numArgs == 1) {
        const MsgArg* elements = NULL;
        size_t numElements = 0;

        args->Get("a(qqi)", &numElements, &elements);

        HidInterface::InputEvent inputEvent;
        HidInterface::InputEvents inputEvents;
        for (size_t i=0; i<numElements; i++) {
            elements[i].Get("(qqi)", &inputEvent.type, &inputEvent.code, &inputEvent.value);

            inputEvents.push_back(inputEvent);
        }
        m_interfaceListener.OnInjectEvents(inputEvents);
    }
}


} //namespace services
} //namespace ajn