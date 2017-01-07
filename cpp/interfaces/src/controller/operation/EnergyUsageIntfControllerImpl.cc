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
#include <interfaces/controller/operation/EnergyUsageIntfControllerListener.h>
#include <interfaces/controller/operation/EnergyUsageIntfController.h>

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {
//======================================================================

typedef Ref<EnergyUsageIntfControllerListener> MyInterfaceListener;


class EnergyUsageIntfController::Impl : public InterfaceController
{
  public:

    Impl(
        EnergyUsageIntfController& outer,
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

    QStatus GetCumulativeEnergy(void* context);
    QStatus GetPrecision(void* context);
    QStatus GetUpdateMinTime(void* context);

    virtual QStatus ResetCumulativeEnergy(void* context);

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);

    void GetCumulativeEnergyPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetPrecisionPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetUpdateMinTimePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    void ResetCumulativeEnergyReplyHandler(Message& message, void* context);


    // The outer facet
    EnergyUsageIntfController& m_outer;

    // and inherit m_proxyObject from InterfaceController
    BusAttachment& m_busAttachment;
    MyInterfaceListener m_interfaceListener;
};

//======================================================================

QStatus EnergyUsageIntfController::Impl::Init()
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




QStatus EnergyUsageIntfController::Impl::GetCumulativeEnergy(void* context)
{
    auto status = m_proxyObject->GetPropertyAsync(GetInterfaceName(), s_prop_CumulativeEnergy.c_str(), this,
                (ProxyBusObject::Listener::GetPropertyCB)&EnergyUsageIntfController::Impl::GetCumulativeEnergyPropertyCB, context);
    return status;
}

QStatus EnergyUsageIntfController::Impl::GetPrecision(void* context)
{
    auto status = m_proxyObject->GetPropertyAsync(GetInterfaceName(), s_prop_Precision.c_str(), this,
                (ProxyBusObject::Listener::GetPropertyCB)&EnergyUsageIntfController::Impl::GetPrecisionPropertyCB, context);
    return status;
}

QStatus EnergyUsageIntfController::Impl::GetUpdateMinTime(void* context)
{
    auto status = m_proxyObject->GetPropertyAsync(GetInterfaceName(), s_prop_UpdateMinTime.c_str(), this,
                (ProxyBusObject::Listener::GetPropertyCB)&EnergyUsageIntfController::Impl::GetUpdateMinTimePropertyCB, context);
    return status;
}



QStatus EnergyUsageIntfController::Impl::ResetCumulativeEnergy(void* context)
{
    // Method call
    static const size_t numInputs = 0;
    MsgArg* args = 0;

    auto status = m_proxyObject->MethodCallAsync(GetInterfaceName(), s_method_ResetCumulativeEnergy.c_str(), this,
                (MessageReceiver::ReplyHandler)&EnergyUsageIntfController::Impl::ResetCumulativeEnergyReplyHandler,
                args, numInputs, context);
    return status;
}



void EnergyUsageIntfController::Impl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (s_prop_CumulativeEnergy == propNameStr) {
            double val;
            {
                CdmMsgCvt<double> converter;
                converter.get((*propValue), val);
            }
            m_interfaceListener->OnCumulativeEnergyChanged(obj.GetPath(), val);
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


void EnergyUsageIntfController::Impl::GetCumulativeEnergyPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (obj) {
        double val;
        {
            CdmMsgCvt<double> converter;
            converter.get(value, val);
        }
        if (_QCC_DbgPrintCheck(DBG_GEN_MESSAGE, QCC_MODULE)) {
            auto s = CdmMsgCvt<double>().str(value);
            QCC_DbgPrintf(("%s: received property %s=%s", __func__, "CumulativeEnergy", s.c_str()));
        }
        m_interfaceListener->OnResponseGetCumulativeEnergy(status, obj->GetPath(), val, context);
    }
}




void EnergyUsageIntfController::Impl::GetPrecisionPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
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




void EnergyUsageIntfController::Impl::GetUpdateMinTimePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
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






void EnergyUsageIntfController::Impl::ResetCumulativeEnergyReplyHandler(Message& message, void* context)
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

    m_interfaceListener->OnResponseResetCumulativeEnergy(status, m_proxyObject->GetPath(), context, errorName, errorMessage.c_str());
}

//======================================================================
// Forward to the impl

EnergyUsageIntfController::EnergyUsageIntfController(
    BusAttachment& busAttachment,
    Ref<InterfaceControllerListener> listener,
    Ref<ProxyBusObject> cdmProxyObject
    )
  : m_impl(new Impl(*this, busAttachment, dynamic_pointer_cast<EnergyUsageIntfControllerListener>(listener), cdmProxyObject))
{
}



EnergyUsageIntfController::~EnergyUsageIntfController()
{
    delete m_impl;
}



Ref<CdmInterface> EnergyUsageIntfController::CreateInterface(BusAttachment& busAttachment, Ref<InterfaceControllerListener> listener, Ref<ProxyBusObject> cdmProxyObject)
{
    return mkRef<EnergyUsageIntfController>(busAttachment, dynamic_pointer_cast<EnergyUsageIntfControllerListener>(listener), cdmProxyObject);
}



QStatus EnergyUsageIntfController::Init()
{
    // Call the superclass Init
    QStatus status = CdmInterface::Init();
    if (ER_OK != status) {
        QCC_LogError(status, ("%s: Interface init failed.", __func__));
        return status;
    }

    return m_impl->Init();
}



BusAttachment& EnergyUsageIntfController::GetBusAttachment() const
{
    return m_impl->m_busAttachment;
}



QStatus EnergyUsageIntfController::GetCumulativeEnergy(void* context)
{
    return m_impl->GetCumulativeEnergy(context);
}



QStatus EnergyUsageIntfController::GetPrecision(void* context)
{
    return m_impl->GetPrecision(context);
}



QStatus EnergyUsageIntfController::GetUpdateMinTime(void* context)
{
    return m_impl->GetUpdateMinTime(context);
}



QStatus EnergyUsageIntfController::ResetCumulativeEnergy(void* context)
{
    return m_impl->ResetCumulativeEnergy(context);
}

//======================================================================
} //namespace services
} //namespace ajn
