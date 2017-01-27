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

// This file is automatically generated. Do not edit it.

#include <alljoyn/cdm/common/LogModule.h>
#include <alljoyn/cdm/common/CdmTypes.h>
#include <alljoyn/cdm/controller/InterfaceController.h>
#include <interfaces/controller/input/HidIntfControllerListener.h>
#include <interfaces/controller/input/HidIntfController.h>

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {
//======================================================================

typedef Ref<HidIntfControllerListener> MyInterfaceListener;


class HidIntfController::Impl : public InterfaceController
{
  public:

    Impl(
        HidIntfController& outer,
        BusAttachment& busAttachment,
        MyInterfaceListener listener,
        Ref<ProxyBusObject> proxyBusObject
        )
      : InterfaceController(proxyBusObject),
        m_outer(outer),
        m_busAttachment(busAttachment),
        m_interfaceListener(listener)
    {
    }

    QStatus Init();

    const char* GetInterfaceName() const
    {
        return INTERFACE_NAME;
    }

    QStatus GetSupportedEvents(void* context);

    virtual QStatus InjectEvents(const std::vector<HidInterface::InputEvent>& inputEvents, void* context);

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);

    void GetSupportedEventsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    void InjectEventsReplyHandler(Message& message, void* context);


    // The outer facet
    HidIntfController& m_outer;

    // and inherit m_proxyObject from InterfaceController
    BusAttachment& m_busAttachment;
    MyInterfaceListener m_interfaceListener;
};

//======================================================================

QStatus HidIntfController::Impl::Init()
{
    auto status = m_proxyObject->RegisterPropertiesChangedListener(GetInterfaceName(), NULL, 0, *this, NULL);

    if (ER_OK != status) {
        QCC_LogError(status, ("%s: RegisterPropertiesChangedListener failed.", __func__));
    }

    const InterfaceDescription* intf = m_outer.GetInterfaceDescription();
    if (intf) {
    } else {
        status = ER_FAIL;
        QCC_LogError(status, ("%s: The interface description does not exist.", __func__));
    }

    return status;
}




QStatus HidIntfController::Impl::GetSupportedEvents(void* context)
{
    auto status = m_proxyObject->GetPropertyAsync(GetInterfaceName(), s_prop_SupportedEvents.c_str(), this,
                (ProxyBusObject::Listener::GetPropertyCB)&HidIntfController::Impl::GetSupportedEventsPropertyCB, context);
    return status;
}



QStatus HidIntfController::Impl::InjectEvents(const std::vector<HidInterface::InputEvent>& inputEvents, void* context)
{
    // Method call
    static const size_t numInputs = 1;
    MsgArg args[numInputs];

    {
        CdmMsgCvt<std::vector<HidInterface::InputEvent>> converter;
        converter.set(args[0], inputEvents);
    }

    auto status = m_proxyObject->MethodCallAsync(GetInterfaceName(), s_method_InjectEvents.c_str(), this,
                (MessageReceiver::ReplyHandler)&HidIntfController::Impl::InjectEventsReplyHandler,
                args, numInputs, context);
    return status;
}



void HidIntfController::Impl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (s_prop_SupportedEvents == propNameStr) {
            std::vector<HidInterface::SupportedInputEvent> val;
            {
                CdmMsgCvt<std::vector<HidInterface::SupportedInputEvent>> converter;
                converter.get((*propValue), val);
            }
            m_interfaceListener->OnSupportedEventsChanged(obj.GetPath(), val);
        } else {
            QCC_DbgTrace(("Unknown property change signal received"));
        }
    }
}

//======================================================================
// Callbacks


void HidIntfController::Impl::GetSupportedEventsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (obj) {
        std::vector<HidInterface::SupportedInputEvent> val;
        {
            CdmMsgCvt<std::vector<HidInterface::SupportedInputEvent>> converter;
            converter.get(value, val);
        }
        if (_QCC_DbgPrintCheck(DBG_GEN_MESSAGE, QCC_MODULE)) {
            auto s = CdmMsgCvt<std::vector<HidInterface::SupportedInputEvent>>().str(value);
            QCC_DbgPrintf(("%s: received property %s=%s", __func__, "SupportedEvents", s.c_str()));
        }
        m_interfaceListener->OnResponseGetSupportedEvents(status, obj->GetPath(), val, context);
    }
}






void HidIntfController::Impl::InjectEventsReplyHandler(Message& message, void* context)
{
    qcc::String errorMessage;
    const char* errorName = message->GetErrorName(&errorMessage);
    QStatus status = ER_OK;
    size_t numArgs = 0;
    const MsgArg* args = 0;


    if (message->GetType() == MESSAGE_METHOD_RET) {
        message->GetArgs(numArgs, args);
    } else {
        status = ER_FAIL;
    }

    m_interfaceListener->OnResponseInjectEvents(status, m_proxyObject->GetPath(), context, errorName, errorMessage.c_str());
}

//======================================================================
// Forward to the impl

HidIntfController::HidIntfController(
    BusAttachment& busAttachment,
    Ref<InterfaceControllerListener> listener,
    Ref<ProxyBusObject> cdmProxyObject
    )
  : m_impl(new Impl(*this, busAttachment, dynamic_pointer_cast<HidIntfControllerListener>(listener), cdmProxyObject))
{
}



HidIntfController::~HidIntfController()
{
    delete m_impl;
}



Ref<CdmInterface> HidIntfController::CreateInterface(BusAttachment& busAttachment, Ref<InterfaceControllerListener> listener, Ref<ProxyBusObject> cdmProxyObject)
{
    return mkRef<HidIntfController>(busAttachment, dynamic_pointer_cast<HidIntfControllerListener>(listener), cdmProxyObject);
}



QStatus HidIntfController::Init()
{
    // Call the superclass Init
    QStatus status = CdmInterface::Init();
    if (ER_OK != status) {
        QCC_LogError(status, ("%s: Interface init failed.", __func__));
        return status;
    }

    return m_impl->Init();
}



BusAttachment& HidIntfController::GetBusAttachment() const
{
    return m_impl->m_busAttachment;
}



QStatus HidIntfController::GetSupportedEvents(void* context)
{
    return m_impl->GetSupportedEvents(context);
}



QStatus HidIntfController::InjectEvents(const std::vector<HidInterface::InputEvent>& inputEvents, void* context)
{
    return m_impl->InjectEvents(inputEvents, context);
}

//======================================================================
} //namespace services
} //namespace ajn
