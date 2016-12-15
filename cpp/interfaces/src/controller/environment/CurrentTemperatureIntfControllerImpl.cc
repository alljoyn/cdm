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
#include <interfaces/controller/environment/CurrentTemperatureIntfControllerListener.h>
#include <interfaces/controller/environment/CurrentTemperatureIntfController.h>

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {
//======================================================================

typedef Ref<CurrentTemperatureIntfControllerListener> MyInterfaceListener;


class CurrentTemperatureIntfController::Impl : public InterfaceController
{
  public:

    Impl(
        CurrentTemperatureIntfController& outer,
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

    QStatus GetCurrentValue(void* context);
    QStatus GetPrecision(void* context);
    QStatus GetUpdateMinTime(void* context);


    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);

    void GetCurrentValuePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetPrecisionPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetUpdateMinTimePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);



    // The outer facet
    CurrentTemperatureIntfController& m_outer;

    // and inherit m_proxyObject from InterfaceController
    BusAttachment& m_busAttachment;
    MyInterfaceListener m_interfaceListener;
};

//======================================================================

QStatus CurrentTemperatureIntfController::Impl::Init()
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




QStatus CurrentTemperatureIntfController::Impl::GetCurrentValue(void* context)
{
    auto status = m_proxyObject->GetPropertyAsync(GetInterfaceName(), s_prop_CurrentValue.c_str(), this,
                (ProxyBusObject::Listener::GetPropertyCB)&CurrentTemperatureIntfController::Impl::GetCurrentValuePropertyCB, context);
    return status;
}

QStatus CurrentTemperatureIntfController::Impl::GetPrecision(void* context)
{
    auto status = m_proxyObject->GetPropertyAsync(GetInterfaceName(), s_prop_Precision.c_str(), this,
                (ProxyBusObject::Listener::GetPropertyCB)&CurrentTemperatureIntfController::Impl::GetPrecisionPropertyCB, context);
    return status;
}

QStatus CurrentTemperatureIntfController::Impl::GetUpdateMinTime(void* context)
{
    auto status = m_proxyObject->GetPropertyAsync(GetInterfaceName(), s_prop_UpdateMinTime.c_str(), this,
                (ProxyBusObject::Listener::GetPropertyCB)&CurrentTemperatureIntfController::Impl::GetUpdateMinTimePropertyCB, context);
    return status;
}





void CurrentTemperatureIntfController::Impl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (s_prop_CurrentValue == propNameStr) {
            double val;
            {
                CdmMsgCvt<double> converter;
                converter.get((*propValue), val);
            }
            m_interfaceListener->OnCurrentValueChanged(obj.GetPath(), val);
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


void CurrentTemperatureIntfController::Impl::GetCurrentValuePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (obj) {
        double val;
        {
            CdmMsgCvt<double> converter;
            converter.get(value, val);
        }
        if (_QCC_DbgPrintCheck(DBG_GEN_MESSAGE, QCC_MODULE)) {
            auto s = CdmMsgCvt<double>().str(value);
            QCC_DbgPrintf(("%s: received property %s=%s", __func__, "CurrentValue", s.c_str()));
        }
        m_interfaceListener->OnResponseGetCurrentValue(status, obj->GetPath(), val, context);
    }
}




void CurrentTemperatureIntfController::Impl::GetPrecisionPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
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




void CurrentTemperatureIntfController::Impl::GetUpdateMinTimePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
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

CurrentTemperatureIntfController::CurrentTemperatureIntfController(
    BusAttachment& busAttachment,
    Ref<InterfaceControllerListener> listener,
    Ref<ProxyBusObject> cdmProxyObject
    )
  : m_impl(new Impl(*this, busAttachment, dynamic_pointer_cast<CurrentTemperatureIntfControllerListener>(listener), cdmProxyObject))
{
}



CurrentTemperatureIntfController::~CurrentTemperatureIntfController()
{
    delete m_impl;
}



Ref<CdmInterface> CurrentTemperatureIntfController::CreateInterface(BusAttachment& busAttachment, Ref<InterfaceControllerListener> listener, Ref<ProxyBusObject> cdmProxyObject)
{
    return mkRef<CurrentTemperatureIntfController>(busAttachment, dynamic_pointer_cast<CurrentTemperatureIntfControllerListener>(listener), cdmProxyObject);
}



QStatus CurrentTemperatureIntfController::Init()
{
    // Call the superclass Init
    QStatus status = CdmInterface::Init();
    if (ER_OK != status) {
        QCC_LogError(status, ("%s: Interface init failed.", __func__));
        return status;
    }

    return m_impl->Init();
}



BusAttachment& CurrentTemperatureIntfController::GetBusAttachment() const
{
    return m_impl->m_busAttachment;
}



QStatus CurrentTemperatureIntfController::GetCurrentValue(void* context)
{
    return m_impl->GetCurrentValue(context);
}



QStatus CurrentTemperatureIntfController::GetPrecision(void* context)
{
    return m_impl->GetPrecision(context);
}



QStatus CurrentTemperatureIntfController::GetUpdateMinTime(void* context)
{
    return m_impl->GetUpdateMinTime(context);
}

//======================================================================
} //namespace services
} //namespace ajn