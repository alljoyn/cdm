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
#include <interfaces/controller/operation/CycleControlIntfControllerListener.h>
#include <interfaces/controller/operation/CycleControlIntfController.h>

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {
//======================================================================

typedef Ref<CycleControlIntfControllerListener> MyInterfaceListener;


class CycleControlIntfController::Impl : public InterfaceController
{
  public:

    Impl(
        CycleControlIntfController& outer,
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
        return m_outer.GetInterfaceName().c_str();
    }

    QStatus GetOperationalState(void* context);
    QStatus GetSupportedOperationalStates(void* context);
    QStatus GetSupportedOperationalCommands(void* context);

    virtual QStatus ExecuteOperationalCommand(const CycleControlInterface::OperationalCommands command, void* context);

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);

    void GetOperationalStatePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetSupportedOperationalStatesPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetSupportedOperationalCommandsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    void ExecuteOperationalCommandReplyHandler(Message& message, void* context);


    // The outer facet
    CycleControlIntfController& m_outer;

    // and inherit m_proxyObject from InterfaceController
    BusAttachment& m_busAttachment;
    MyInterfaceListener m_interfaceListener;
};

//======================================================================

QStatus CycleControlIntfController::Impl::Init()
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




QStatus CycleControlIntfController::Impl::GetOperationalState(void* context)
{
    auto status = m_proxyObject->GetPropertyAsync(GetInterfaceName(), s_prop_OperationalState.c_str(), this,
                (ProxyBusObject::Listener::GetPropertyCB)&CycleControlIntfController::Impl::GetOperationalStatePropertyCB, context);
    return status;
}

QStatus CycleControlIntfController::Impl::GetSupportedOperationalStates(void* context)
{
    auto status = m_proxyObject->GetPropertyAsync(GetInterfaceName(), s_prop_SupportedOperationalStates.c_str(), this,
                (ProxyBusObject::Listener::GetPropertyCB)&CycleControlIntfController::Impl::GetSupportedOperationalStatesPropertyCB, context);
    return status;
}

QStatus CycleControlIntfController::Impl::GetSupportedOperationalCommands(void* context)
{
    auto status = m_proxyObject->GetPropertyAsync(GetInterfaceName(), s_prop_SupportedOperationalCommands.c_str(), this,
                (ProxyBusObject::Listener::GetPropertyCB)&CycleControlIntfController::Impl::GetSupportedOperationalCommandsPropertyCB, context);
    return status;
}



QStatus CycleControlIntfController::Impl::ExecuteOperationalCommand(const CycleControlInterface::OperationalCommands command, void* context)
{
    // Method call
    static const size_t numInputs = 1;
    MsgArg args[numInputs];

    {
        CdmMsgCvt<CycleControlInterface::OperationalCommands> converter;
        converter.set(args[0], command);
    }

    auto status = m_proxyObject->MethodCallAsync(GetInterfaceName(), s_method_ExecuteOperationalCommand.c_str(), this,
                (MessageReceiver::ReplyHandler)&CycleControlIntfController::Impl::ExecuteOperationalCommandReplyHandler,
                args, numInputs, context);
    return status;
}



void CycleControlIntfController::Impl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (s_prop_OperationalState == propNameStr) {
            CycleControlInterface::OperationalState val;
            {
                CdmMsgCvt<CycleControlInterface::OperationalState> converter;
                converter.get((*propValue), val);
            }
            m_interfaceListener->OnOperationalStateChanged(obj.GetPath(), val);
        } else if (s_prop_SupportedOperationalStates == propNameStr) {
            std::vector<CycleControlInterface::OperationalState> val;
            {
                CdmMsgCvt<std::vector<CycleControlInterface::OperationalState>> converter;
                converter.get((*propValue), val);
            }
            m_interfaceListener->OnSupportedOperationalStatesChanged(obj.GetPath(), val);
        } else if (s_prop_SupportedOperationalCommands == propNameStr) {
            std::vector<CycleControlInterface::OperationalCommands> val;
            {
                CdmMsgCvt<std::vector<CycleControlInterface::OperationalCommands>> converter;
                converter.get((*propValue), val);
            }
            m_interfaceListener->OnSupportedOperationalCommandsChanged(obj.GetPath(), val);
        } else {
            QCC_DbgTrace(("Unknown property change signal received"));
        }
    }
}

//======================================================================
// Callbacks


void CycleControlIntfController::Impl::GetOperationalStatePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (obj) {
        CycleControlInterface::OperationalState val;
        {
            CdmMsgCvt<CycleControlInterface::OperationalState> converter;
            converter.get(value, val);
        }
        if (_QCC_DbgPrintCheck(DBG_GEN_MESSAGE, QCC_MODULE)) {
            auto s = CdmMsgCvt<CycleControlInterface::OperationalState>().str(value);
            QCC_DbgPrintf(("%s: received property %s=%s", __func__, "OperationalState", s.c_str()));
        }
        m_interfaceListener->OnResponseGetOperationalState(status, obj->GetPath(), val, context);
    }
}




void CycleControlIntfController::Impl::GetSupportedOperationalStatesPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (obj) {
        std::vector<CycleControlInterface::OperationalState> val;
        {
            CdmMsgCvt<std::vector<CycleControlInterface::OperationalState>> converter;
            converter.get(value, val);
        }
        if (_QCC_DbgPrintCheck(DBG_GEN_MESSAGE, QCC_MODULE)) {
            auto s = CdmMsgCvt<std::vector<CycleControlInterface::OperationalState>>().str(value);
            QCC_DbgPrintf(("%s: received property %s=%s", __func__, "SupportedOperationalStates", s.c_str()));
        }
        m_interfaceListener->OnResponseGetSupportedOperationalStates(status, obj->GetPath(), val, context);
    }
}




void CycleControlIntfController::Impl::GetSupportedOperationalCommandsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (obj) {
        std::vector<CycleControlInterface::OperationalCommands> val;
        {
            CdmMsgCvt<std::vector<CycleControlInterface::OperationalCommands>> converter;
            converter.get(value, val);
        }
        if (_QCC_DbgPrintCheck(DBG_GEN_MESSAGE, QCC_MODULE)) {
            auto s = CdmMsgCvt<std::vector<CycleControlInterface::OperationalCommands>>().str(value);
            QCC_DbgPrintf(("%s: received property %s=%s", __func__, "SupportedOperationalCommands", s.c_str()));
        }
        m_interfaceListener->OnResponseGetSupportedOperationalCommands(status, obj->GetPath(), val, context);
    }
}






void CycleControlIntfController::Impl::ExecuteOperationalCommandReplyHandler(Message& message, void* context)
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

    m_interfaceListener->OnResponseExecuteOperationalCommand(status, m_proxyObject->GetPath(), context, errorName, errorMessage.c_str());
}

//======================================================================
// Forward to the impl

CycleControlIntfController::CycleControlIntfController(
    BusAttachment& busAttachment,
    Ref<InterfaceControllerListener> listener,
    Ref<ProxyBusObject> cdmProxyObject
    )
  : m_impl(new Impl(*this, busAttachment, dynamic_pointer_cast<CycleControlIntfControllerListener>(listener), cdmProxyObject))
{
}



CycleControlIntfController::~CycleControlIntfController()
{
    delete m_impl;
}



Ref<CdmInterface> CycleControlIntfController::CreateInterface(BusAttachment& busAttachment, Ref<InterfaceControllerListener> listener, Ref<ProxyBusObject> cdmProxyObject)
{
    return mkRef<CycleControlIntfController>(busAttachment, dynamic_pointer_cast<CycleControlIntfControllerListener>(listener), cdmProxyObject);
}



QStatus CycleControlIntfController::Init()
{
    // Call the superclass Init
    QStatus status = CdmInterface::Init();
    if (ER_OK != status) {
        QCC_LogError(status, ("%s: Interface init failed.", __func__));
        return status;
    }

    return m_impl->Init();
}



BusAttachment& CycleControlIntfController::GetBusAttachment() const
{
    return m_impl->m_busAttachment;
}



QStatus CycleControlIntfController::GetOperationalState(void* context)
{
    return m_impl->GetOperationalState(context);
}



QStatus CycleControlIntfController::GetSupportedOperationalStates(void* context)
{
    return m_impl->GetSupportedOperationalStates(context);
}



QStatus CycleControlIntfController::GetSupportedOperationalCommands(void* context)
{
    return m_impl->GetSupportedOperationalCommands(context);
}



QStatus CycleControlIntfController::ExecuteOperationalCommand(const CycleControlInterface::OperationalCommands command, void* context)
{
    return m_impl->ExecuteOperationalCommand(command, context);
}

//======================================================================
} //namespace services
} //namespace ajn