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
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

// This file is automatically generated. Do not edit it.

#include <alljoyn/cdm/common/LogModule.h>
#include <alljoyn/cdm/common/CdmTypes.h>
#include <alljoyn/cdm/controller/InterfaceController.h>
#include <interfaces/controller/operation/ClimateControlModeIntfControllerListener.h>
#include <interfaces/controller/operation/ClimateControlModeIntfController.h>

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {
//======================================================================

typedef Ref<ClimateControlModeIntfControllerListener> MyInterfaceListener;


class ClimateControlModeIntfController::Impl : public InterfaceController
{
  public:

    Impl(
        ClimateControlModeIntfController& outer,
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

    QStatus GetMode(void* context);
    QStatus SetMode(const ClimateControlModeInterface::Mode value, void* context);
    QStatus GetSupportedModes(void* context);
    QStatus GetOperationalState(void* context);


    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);

    void GetModePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetModePropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetSupportedModesPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetOperationalStatePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);



    // The outer facet
    ClimateControlModeIntfController& m_outer;

    // and inherit m_proxyObject from InterfaceController
    BusAttachment& m_busAttachment;
    MyInterfaceListener m_interfaceListener;
};

//======================================================================

QStatus ClimateControlModeIntfController::Impl::Init()
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




QStatus ClimateControlModeIntfController::Impl::GetMode(void* context)
{
    auto status = m_proxyObject->GetPropertyAsync(GetInterfaceName(), s_prop_Mode.c_str(), this,
                (ProxyBusObject::Listener::GetPropertyCB)&ClimateControlModeIntfController::Impl::GetModePropertyCB, context);
    return status;
}

QStatus ClimateControlModeIntfController::Impl::SetMode(const ClimateControlModeInterface::Mode value, void* context)
{
    MsgArg arg;
    {
        CdmMsgCvt<ClimateControlModeInterface::Mode> converter;
        converter.set(arg, value);
    }

    auto status = m_proxyObject->SetPropertyAsync(GetInterfaceName(), s_prop_Mode.c_str(), arg, this,
                (ProxyBusObject::Listener::SetPropertyCB)&ClimateControlModeIntfController::Impl::SetModePropertyCB, context);
    return status;
}

QStatus ClimateControlModeIntfController::Impl::GetSupportedModes(void* context)
{
    auto status = m_proxyObject->GetPropertyAsync(GetInterfaceName(), s_prop_SupportedModes.c_str(), this,
                (ProxyBusObject::Listener::GetPropertyCB)&ClimateControlModeIntfController::Impl::GetSupportedModesPropertyCB, context);
    return status;
}

QStatus ClimateControlModeIntfController::Impl::GetOperationalState(void* context)
{
    auto status = m_proxyObject->GetPropertyAsync(GetInterfaceName(), s_prop_OperationalState.c_str(), this,
                (ProxyBusObject::Listener::GetPropertyCB)&ClimateControlModeIntfController::Impl::GetOperationalStatePropertyCB, context);
    return status;
}





void ClimateControlModeIntfController::Impl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (s_prop_Mode == propNameStr) {
            ClimateControlModeInterface::Mode val;
            {
                CdmMsgCvt<ClimateControlModeInterface::Mode> converter;
                converter.get((*propValue), val);
            }
            m_interfaceListener->OnModeChanged(obj.GetPath(), val);
        } else if (s_prop_SupportedModes == propNameStr) {
            std::vector<ClimateControlModeInterface::Mode> val;
            {
                CdmMsgCvt<std::vector<ClimateControlModeInterface::Mode>> converter;
                converter.get((*propValue), val);
            }
            m_interfaceListener->OnSupportedModesChanged(obj.GetPath(), val);
        } else if (s_prop_OperationalState == propNameStr) {
            ClimateControlModeInterface::OperationalState val;
            {
                CdmMsgCvt<ClimateControlModeInterface::OperationalState> converter;
                converter.get((*propValue), val);
            }
            m_interfaceListener->OnOperationalStateChanged(obj.GetPath(), val);
        } else {
            QCC_DbgTrace(("Unknown property change signal received"));
        }
    }
}

//======================================================================
// Callbacks


void ClimateControlModeIntfController::Impl::GetModePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (obj) {
        ClimateControlModeInterface::Mode val;
        {
            CdmMsgCvt<ClimateControlModeInterface::Mode> converter;
            converter.get(value, val);
        }
        if (_QCC_DbgPrintCheck(DBG_GEN_MESSAGE, QCC_MODULE)) {
            auto s = CdmMsgCvt<ClimateControlModeInterface::Mode>().str(value);
            QCC_DbgPrintf(("%s: received property %s=%s", __func__, "Mode", s.c_str()));
        }
        m_interfaceListener->OnResponseGetMode(status, obj->GetPath(), val, context);
    }
}



void ClimateControlModeIntfController::Impl::SetModePropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    QCC_DbgPrintf(("%s: set completed", __func__));
    if (obj) {
        m_interfaceListener->OnResponseSetMode(status, obj->GetPath(), context);
    }
}

void ClimateControlModeIntfController::Impl::GetSupportedModesPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (obj) {
        std::vector<ClimateControlModeInterface::Mode> val;
        {
            CdmMsgCvt<std::vector<ClimateControlModeInterface::Mode>> converter;
            converter.get(value, val);
        }
        if (_QCC_DbgPrintCheck(DBG_GEN_MESSAGE, QCC_MODULE)) {
            auto s = CdmMsgCvt<std::vector<ClimateControlModeInterface::Mode>>().str(value);
            QCC_DbgPrintf(("%s: received property %s=%s", __func__, "SupportedModes", s.c_str()));
        }
        m_interfaceListener->OnResponseGetSupportedModes(status, obj->GetPath(), val, context);
    }
}




void ClimateControlModeIntfController::Impl::GetOperationalStatePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (obj) {
        ClimateControlModeInterface::OperationalState val;
        {
            CdmMsgCvt<ClimateControlModeInterface::OperationalState> converter;
            converter.get(value, val);
        }
        if (_QCC_DbgPrintCheck(DBG_GEN_MESSAGE, QCC_MODULE)) {
            auto s = CdmMsgCvt<ClimateControlModeInterface::OperationalState>().str(value);
            QCC_DbgPrintf(("%s: received property %s=%s", __func__, "OperationalState", s.c_str()));
        }
        m_interfaceListener->OnResponseGetOperationalState(status, obj->GetPath(), val, context);
    }
}




//======================================================================
// Forward to the impl

ClimateControlModeIntfController::ClimateControlModeIntfController(
    BusAttachment& busAttachment,
    Ref<InterfaceControllerListener> listener,
    Ref<ProxyBusObject> cdmProxyObject
    )
  : m_impl(new Impl(*this, busAttachment, dynamic_pointer_cast<ClimateControlModeIntfControllerListener>(listener), cdmProxyObject))
{
}



ClimateControlModeIntfController::~ClimateControlModeIntfController()
{
    delete m_impl;
}



Ref<CdmInterface> ClimateControlModeIntfController::CreateInterface(BusAttachment& busAttachment, Ref<InterfaceControllerListener> listener, Ref<ProxyBusObject> cdmProxyObject)
{
    return mkRef<ClimateControlModeIntfController>(busAttachment, dynamic_pointer_cast<ClimateControlModeIntfControllerListener>(listener), cdmProxyObject);
}



QStatus ClimateControlModeIntfController::Init()
{
    // Call the superclass Init
    QStatus status = CdmInterface::Init();
    if (ER_OK != status) {
        QCC_LogError(status, ("%s: Interface init failed.", __func__));
        return status;
    }

    return m_impl->Init();
}



BusAttachment& ClimateControlModeIntfController::GetBusAttachment() const
{
    return m_impl->m_busAttachment;
}



QStatus ClimateControlModeIntfController::GetMode(void* context)
{
    return m_impl->GetMode(context);
}



QStatus ClimateControlModeIntfController::SetMode(const ClimateControlModeInterface::Mode value, void* context)
{
    return m_impl->SetMode(value, context);
}



QStatus ClimateControlModeIntfController::GetSupportedModes(void* context)
{
    return m_impl->GetSupportedModes(context);
}



QStatus ClimateControlModeIntfController::GetOperationalState(void* context)
{
    return m_impl->GetOperationalState(context);
}

//======================================================================
} //namespace services
} //namespace ajn