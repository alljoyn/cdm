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
#include <interfaces/controller/operation/RapidModeIntfControllerListener.h>
#include <interfaces/controller/operation/RapidModeIntfController.h>

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {
//======================================================================

typedef Ref<RapidModeIntfControllerListener> MyInterfaceListener;


class RapidModeIntfController::Impl : public InterfaceController
{
  public:

    Impl(
        RapidModeIntfController& outer,
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

    QStatus GetRapidMode(void* context);
    QStatus SetRapidMode(const bool value, void* context);


    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);

    void GetRapidModePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetRapidModePropertyCB(QStatus status, ProxyBusObject* obj, void* context);



    // The outer facet
    RapidModeIntfController& m_outer;

    // and inherit m_proxyObject from InterfaceController
    BusAttachment& m_busAttachment;
    MyInterfaceListener m_interfaceListener;
};

//======================================================================

QStatus RapidModeIntfController::Impl::Init()
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




QStatus RapidModeIntfController::Impl::GetRapidMode(void* context)
{
    auto status = m_proxyObject->GetPropertyAsync(GetInterfaceName(), s_prop_RapidMode.c_str(), this,
                (ProxyBusObject::Listener::GetPropertyCB)&RapidModeIntfController::Impl::GetRapidModePropertyCB, context);
    return status;
}

QStatus RapidModeIntfController::Impl::SetRapidMode(const bool value, void* context)
{
    MsgArg arg;
    {
        CdmMsgCvt<bool> converter;
        converter.set(arg, value);
    }

    auto status = m_proxyObject->SetPropertyAsync(GetInterfaceName(), s_prop_RapidMode.c_str(), arg, this,
                (ProxyBusObject::Listener::SetPropertyCB)&RapidModeIntfController::Impl::SetRapidModePropertyCB, context);
    return status;
}





void RapidModeIntfController::Impl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (s_prop_RapidMode == propNameStr) {
            bool val;
            {
                CdmMsgCvt<bool> converter;
                converter.get((*propValue), val);
            }
            m_interfaceListener->OnRapidModeChanged(obj.GetPath(), val);
        } else {
            QCC_DbgTrace(("Unknown property change signal received"));
        }
    }
}

//======================================================================
// Callbacks


void RapidModeIntfController::Impl::GetRapidModePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (obj) {
        bool val;
        {
            CdmMsgCvt<bool> converter;
            converter.get(value, val);
        }
        if (_QCC_DbgPrintCheck(DBG_GEN_MESSAGE, QCC_MODULE)) {
            auto s = CdmMsgCvt<bool>().str(value);
            QCC_DbgPrintf(("%s: received property %s=%s", __func__, "RapidMode", s.c_str()));
        }
        m_interfaceListener->OnResponseGetRapidMode(status, obj->GetPath(), val, context);
    }
}



void RapidModeIntfController::Impl::SetRapidModePropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    QCC_DbgPrintf(("%s: set completed", __func__));
    if (obj) {
        m_interfaceListener->OnResponseSetRapidMode(status, obj->GetPath(), context);
    }
}

//======================================================================
// Forward to the impl

RapidModeIntfController::RapidModeIntfController(
    BusAttachment& busAttachment,
    Ref<InterfaceControllerListener> listener,
    Ref<ProxyBusObject> cdmProxyObject
    )
  : m_impl(new Impl(*this, busAttachment, dynamic_pointer_cast<RapidModeIntfControllerListener>(listener), cdmProxyObject))
{
}



RapidModeIntfController::~RapidModeIntfController()
{
    delete m_impl;
}



Ref<CdmInterface> RapidModeIntfController::CreateInterface(BusAttachment& busAttachment, Ref<InterfaceControllerListener> listener, Ref<ProxyBusObject> cdmProxyObject)
{
    return mkRef<RapidModeIntfController>(busAttachment, dynamic_pointer_cast<RapidModeIntfControllerListener>(listener), cdmProxyObject);
}



QStatus RapidModeIntfController::Init()
{
    // Call the superclass Init
    QStatus status = CdmInterface::Init();
    if (ER_OK != status) {
        QCC_LogError(status, ("%s: Interface init failed.", __func__));
        return status;
    }

    return m_impl->Init();
}



BusAttachment& RapidModeIntfController::GetBusAttachment() const
{
    return m_impl->m_busAttachment;
}



QStatus RapidModeIntfController::GetRapidMode(void* context)
{
    return m_impl->GetRapidMode(context);
}



QStatus RapidModeIntfController::SetRapidMode(const bool value, void* context)
{
    return m_impl->SetRapidMode(value, context);
}

//======================================================================
} //namespace services
} //namespace ajn
