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
#include <interfaces/controller/operation/CurrentPowerIntfControllerListener.h>
#include <interfaces/controller/operation/CurrentPowerIntfController.h>

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {
//======================================================================

typedef Ref<CurrentPowerIntfControllerListener> MyInterfaceListener;


class CurrentPowerIntfController::Impl : public InterfaceController
{
  public:

    Impl(
        CurrentPowerIntfController& outer,
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

    QStatus GetCurrentPower(void* context);
    QStatus GetPrecision(void* context);
    QStatus GetUpdateMinTime(void* context);


    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);

    void GetCurrentPowerPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetPrecisionPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetUpdateMinTimePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);



    // The outer facet
    CurrentPowerIntfController& m_outer;

    // and inherit m_proxyObject from InterfaceController
    BusAttachment& m_busAttachment;
    MyInterfaceListener m_interfaceListener;
};

//======================================================================

QStatus CurrentPowerIntfController::Impl::Init()
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




QStatus CurrentPowerIntfController::Impl::GetCurrentPower(void* context)
{
    auto status = m_proxyObject->GetPropertyAsync(GetInterfaceName(), s_prop_CurrentPower.c_str(), this,
                (ProxyBusObject::Listener::GetPropertyCB)&CurrentPowerIntfController::Impl::GetCurrentPowerPropertyCB, context);
    return status;
}

QStatus CurrentPowerIntfController::Impl::GetPrecision(void* context)
{
    auto status = m_proxyObject->GetPropertyAsync(GetInterfaceName(), s_prop_Precision.c_str(), this,
                (ProxyBusObject::Listener::GetPropertyCB)&CurrentPowerIntfController::Impl::GetPrecisionPropertyCB, context);
    return status;
}

QStatus CurrentPowerIntfController::Impl::GetUpdateMinTime(void* context)
{
    auto status = m_proxyObject->GetPropertyAsync(GetInterfaceName(), s_prop_UpdateMinTime.c_str(), this,
                (ProxyBusObject::Listener::GetPropertyCB)&CurrentPowerIntfController::Impl::GetUpdateMinTimePropertyCB, context);
    return status;
}





void CurrentPowerIntfController::Impl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (s_prop_CurrentPower == propNameStr) {
            double val;
            {
                CdmMsgCvt<double> converter;
                converter.get((*propValue), val);
            }
            m_interfaceListener->OnCurrentPowerChanged(obj.GetPath(), val);
        } else if (s_prop_Precision == propNameStr) {
            double val;
            {
                CdmMsgCvt<double> converter;
                converter.get((*propValue), val);
            }
            m_interfaceListener->OnPrecisionChanged(obj.GetPath(), val);
        } else if (s_prop_UpdateMinTime == propNameStr) {
            uint16_t val;
            {
                CdmMsgCvt<uint16_t> converter;
                converter.get((*propValue), val);
            }
            m_interfaceListener->OnUpdateMinTimeChanged(obj.GetPath(), val);
        } else {
            QCC_DbgTrace(("Unknown property change signal received"));
        }
    }
}

//======================================================================
// Callbacks


void CurrentPowerIntfController::Impl::GetCurrentPowerPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (obj) {
        double val;
        {
            CdmMsgCvt<double> converter;
            converter.get(value, val);
        }
        if (_QCC_DbgPrintCheck(DBG_GEN_MESSAGE, QCC_MODULE)) {
            auto s = CdmMsgCvt<double>().str(value);
            QCC_DbgPrintf(("%s: received property %s=%s", __func__, "CurrentPower", s.c_str()));
        }
        m_interfaceListener->OnResponseGetCurrentPower(status, obj->GetPath(), val, context);
    }
}




void CurrentPowerIntfController::Impl::GetPrecisionPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (obj) {
        double val;
        {
            CdmMsgCvt<double> converter;
            converter.get(value, val);
        }
        if (_QCC_DbgPrintCheck(DBG_GEN_MESSAGE, QCC_MODULE)) {
            auto s = CdmMsgCvt<double>().str(value);
            QCC_DbgPrintf(("%s: received property %s=%s", __func__, "Precision", s.c_str()));
        }
        m_interfaceListener->OnResponseGetPrecision(status, obj->GetPath(), val, context);
    }
}




void CurrentPowerIntfController::Impl::GetUpdateMinTimePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (obj) {
        uint16_t val;
        {
            CdmMsgCvt<uint16_t> converter;
            converter.get(value, val);
        }
        if (_QCC_DbgPrintCheck(DBG_GEN_MESSAGE, QCC_MODULE)) {
            auto s = CdmMsgCvt<uint16_t>().str(value);
            QCC_DbgPrintf(("%s: received property %s=%s", __func__, "UpdateMinTime", s.c_str()));
        }
        m_interfaceListener->OnResponseGetUpdateMinTime(status, obj->GetPath(), val, context);
    }
}




//======================================================================
// Forward to the impl

CurrentPowerIntfController::CurrentPowerIntfController(
    BusAttachment& busAttachment,
    Ref<InterfaceControllerListener> listener,
    Ref<ProxyBusObject> cdmProxyObject
    )
  : m_impl(new Impl(*this, busAttachment, dynamic_pointer_cast<CurrentPowerIntfControllerListener>(listener), cdmProxyObject))
{
}



CurrentPowerIntfController::~CurrentPowerIntfController()
{
    delete m_impl;
}



Ref<CdmInterface> CurrentPowerIntfController::CreateInterface(BusAttachment& busAttachment, Ref<InterfaceControllerListener> listener, Ref<ProxyBusObject> cdmProxyObject)
{
    return mkRef<CurrentPowerIntfController>(busAttachment, dynamic_pointer_cast<CurrentPowerIntfControllerListener>(listener), cdmProxyObject);
}



QStatus CurrentPowerIntfController::Init()
{
    // Call the superclass Init
    QStatus status = CdmInterface::Init();
    if (ER_OK != status) {
        QCC_LogError(status, ("%s: Interface init failed.", __func__));
        return status;
    }

    return m_impl->Init();
}



BusAttachment& CurrentPowerIntfController::GetBusAttachment() const
{
    return m_impl->m_busAttachment;
}



QStatus CurrentPowerIntfController::GetCurrentPower(void* context)
{
    return m_impl->GetCurrentPower(context);
}



QStatus CurrentPowerIntfController::GetPrecision(void* context)
{
    return m_impl->GetPrecision(context);
}



QStatus CurrentPowerIntfController::GetUpdateMinTime(void* context)
{
    return m_impl->GetUpdateMinTime(context);
}

//======================================================================
} //namespace services
} //namespace ajn
