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

// This file is automatically generated. Do not edit it.

#include <alljoyn/cdm/common/LogModule.h>
#include <alljoyn/cdm/common/CdmTypes.h>
#include <alljoyn/cdm/controller/InterfaceController.h>
#include <interfaces/controller/operation/UnlockControlIntfControllerListener.h>
#include <interfaces/controller/operation/UnlockControlIntfController.h>

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {
//======================================================================

typedef Ref<UnlockControlIntfControllerListener> MyInterfaceListener;


class UnlockControlIntfController::Impl : public InterfaceController
{
  public:

    Impl(
        UnlockControlIntfController& outer,
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


    virtual QStatus Unlock(void* context);

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);


    void UnlockReplyHandler(Message& message, void* context);


    // The outer facet
    UnlockControlIntfController& m_outer;

    // and inherit m_proxyObject from InterfaceController
    BusAttachment& m_busAttachment;
    MyInterfaceListener m_interfaceListener;
};

//======================================================================

QStatus UnlockControlIntfController::Impl::Init()
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






QStatus UnlockControlIntfController::Impl::Unlock(void* context)
{
    // Method call
    static const size_t numInputs = 0;
    MsgArg* args = 0;

    auto status = m_proxyObject->MethodCallAsync(GetInterfaceName(), s_method_Unlock.c_str(), this,
                (MessageReceiver::ReplyHandler)&UnlockControlIntfController::Impl::UnlockReplyHandler,
                args, numInputs, context);
    return status;
}



void UnlockControlIntfController::Impl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        {
            QCC_DbgTrace(("Unknown property change signal received"));
        }
    }
}

//======================================================================
// Callbacks




void UnlockControlIntfController::Impl::UnlockReplyHandler(Message& message, void* context)
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

    m_interfaceListener->OnResponseUnlock(status, m_proxyObject->GetPath(), context, errorName, errorMessage.c_str());
}

//======================================================================
// Forward to the impl

UnlockControlIntfController::UnlockControlIntfController(
    BusAttachment& busAttachment,
    Ref<InterfaceControllerListener> listener,
    Ref<ProxyBusObject> cdmProxyObject
    )
  : m_impl(new Impl(*this, busAttachment, dynamic_pointer_cast<UnlockControlIntfControllerListener>(listener), cdmProxyObject))
{
}



UnlockControlIntfController::~UnlockControlIntfController()
{
    delete m_impl;
}



Ref<CdmInterface> UnlockControlIntfController::CreateInterface(BusAttachment& busAttachment, Ref<InterfaceControllerListener> listener, Ref<ProxyBusObject> cdmProxyObject)
{
    return mkRef<UnlockControlIntfController>(busAttachment, dynamic_pointer_cast<UnlockControlIntfControllerListener>(listener), cdmProxyObject);
}



QStatus UnlockControlIntfController::Init()
{
    // Call the superclass Init
    QStatus status = CdmInterface::Init();
    if (ER_OK != status) {
        QCC_LogError(status, ("%s: Interface init failed.", __func__));
        return status;
    }

    return m_impl->Init();
}



BusAttachment& UnlockControlIntfController::GetBusAttachment() const
{
    return m_impl->m_busAttachment;
}



QStatus UnlockControlIntfController::Unlock(void* context)
{
    return m_impl->Unlock(context);
}

//======================================================================
} //namespace services
} //namespace ajn