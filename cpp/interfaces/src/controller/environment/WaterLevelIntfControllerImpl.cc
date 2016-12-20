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
#include <interfaces/controller/environment/WaterLevelIntfControllerListener.h>
#include <interfaces/controller/environment/WaterLevelIntfController.h>

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {
//======================================================================

typedef Ref<WaterLevelIntfControllerListener> MyInterfaceListener;


class WaterLevelIntfController::Impl : public InterfaceController
{
  public:

    Impl(
        WaterLevelIntfController& outer,
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

    QStatus GetSupplySource(void* context);
    QStatus GetCurrentLevel(void* context);
    QStatus GetMaxLevel(void* context);


    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);

    void GetSupplySourcePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetCurrentLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetMaxLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);



    // The outer facet
    WaterLevelIntfController& m_outer;

    // and inherit m_proxyObject from InterfaceController
    BusAttachment& m_busAttachment;
    MyInterfaceListener m_interfaceListener;
};

//======================================================================

QStatus WaterLevelIntfController::Impl::Init()
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




QStatus WaterLevelIntfController::Impl::GetSupplySource(void* context)
{
    auto status = m_proxyObject->GetPropertyAsync(GetInterfaceName(), s_prop_SupplySource.c_str(), this,
                (ProxyBusObject::Listener::GetPropertyCB)&WaterLevelIntfController::Impl::GetSupplySourcePropertyCB, context);
    return status;
}

QStatus WaterLevelIntfController::Impl::GetCurrentLevel(void* context)
{
    auto status = m_proxyObject->GetPropertyAsync(GetInterfaceName(), s_prop_CurrentLevel.c_str(), this,
                (ProxyBusObject::Listener::GetPropertyCB)&WaterLevelIntfController::Impl::GetCurrentLevelPropertyCB, context);
    return status;
}

QStatus WaterLevelIntfController::Impl::GetMaxLevel(void* context)
{
    auto status = m_proxyObject->GetPropertyAsync(GetInterfaceName(), s_prop_MaxLevel.c_str(), this,
                (ProxyBusObject::Listener::GetPropertyCB)&WaterLevelIntfController::Impl::GetMaxLevelPropertyCB, context);
    return status;
}





void WaterLevelIntfController::Impl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (s_prop_SupplySource == propNameStr) {
            WaterLevelInterface::SupplySource val;
            {
                CdmMsgCvt<WaterLevelInterface::SupplySource> converter;
                converter.get((*propValue), val);
            }
            m_interfaceListener->OnSupplySourceChanged(obj.GetPath(), val);
        } else if (s_prop_CurrentLevel == propNameStr) {
            uint8_t val;
            {
                CdmMsgCvt<uint8_t> converter;
                converter.get((*propValue), val);
            }
            m_interfaceListener->OnCurrentLevelChanged(obj.GetPath(), val);
        } else if (s_prop_MaxLevel == propNameStr) {
            uint8_t val;
            {
                CdmMsgCvt<uint8_t> converter;
                converter.get((*propValue), val);
            }
            m_interfaceListener->OnMaxLevelChanged(obj.GetPath(), val);
        } else {
            QCC_DbgTrace(("Unknown property change signal received"));
        }
    }
}

//======================================================================
// Callbacks


void WaterLevelIntfController::Impl::GetSupplySourcePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (obj) {
        WaterLevelInterface::SupplySource val;
        {
            CdmMsgCvt<WaterLevelInterface::SupplySource> converter;
            converter.get(value, val);
        }
        if (_QCC_DbgPrintCheck(DBG_GEN_MESSAGE, QCC_MODULE)) {
            auto s = CdmMsgCvt<WaterLevelInterface::SupplySource>().str(value);
            QCC_DbgPrintf(("%s: received property %s=%s", __func__, "SupplySource", s.c_str()));
        }
        m_interfaceListener->OnResponseGetSupplySource(status, obj->GetPath(), val, context);
    }
}




void WaterLevelIntfController::Impl::GetCurrentLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (obj) {
        uint8_t val;
        {
            CdmMsgCvt<uint8_t> converter;
            converter.get(value, val);
        }
        if (_QCC_DbgPrintCheck(DBG_GEN_MESSAGE, QCC_MODULE)) {
            auto s = CdmMsgCvt<uint8_t>().str(value);
            QCC_DbgPrintf(("%s: received property %s=%s", __func__, "CurrentLevel", s.c_str()));
        }
        m_interfaceListener->OnResponseGetCurrentLevel(status, obj->GetPath(), val, context);
    }
}




void WaterLevelIntfController::Impl::GetMaxLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (obj) {
        uint8_t val;
        {
            CdmMsgCvt<uint8_t> converter;
            converter.get(value, val);
        }
        if (_QCC_DbgPrintCheck(DBG_GEN_MESSAGE, QCC_MODULE)) {
            auto s = CdmMsgCvt<uint8_t>().str(value);
            QCC_DbgPrintf(("%s: received property %s=%s", __func__, "MaxLevel", s.c_str()));
        }
        m_interfaceListener->OnResponseGetMaxLevel(status, obj->GetPath(), val, context);
    }
}




//======================================================================
// Forward to the impl

WaterLevelIntfController::WaterLevelIntfController(
    BusAttachment& busAttachment,
    Ref<InterfaceControllerListener> listener,
    Ref<ProxyBusObject> cdmProxyObject
    )
  : m_impl(new Impl(*this, busAttachment, dynamic_pointer_cast<WaterLevelIntfControllerListener>(listener), cdmProxyObject))
{
}



WaterLevelIntfController::~WaterLevelIntfController()
{
    delete m_impl;
}



Ref<CdmInterface> WaterLevelIntfController::CreateInterface(BusAttachment& busAttachment, Ref<InterfaceControllerListener> listener, Ref<ProxyBusObject> cdmProxyObject)
{
    return mkRef<WaterLevelIntfController>(busAttachment, dynamic_pointer_cast<WaterLevelIntfControllerListener>(listener), cdmProxyObject);
}



QStatus WaterLevelIntfController::Init()
{
    // Call the superclass Init
    QStatus status = CdmInterface::Init();
    if (ER_OK != status) {
        QCC_LogError(status, ("%s: Interface init failed.", __func__));
        return status;
    }

    return m_impl->Init();
}



BusAttachment& WaterLevelIntfController::GetBusAttachment() const
{
    return m_impl->m_busAttachment;
}



QStatus WaterLevelIntfController::GetSupplySource(void* context)
{
    return m_impl->GetSupplySource(context);
}



QStatus WaterLevelIntfController::GetCurrentLevel(void* context)
{
    return m_impl->GetCurrentLevel(context);
}



QStatus WaterLevelIntfController::GetMaxLevel(void* context)
{
    return m_impl->GetMaxLevel(context);
}

//======================================================================
} //namespace services
} //namespace ajn