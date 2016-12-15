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
#include <interfaces/controller/environment/TargetTemperatureLevelIntfControllerListener.h>
#include <interfaces/controller/environment/TargetTemperatureLevelIntfController.h>

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {
//======================================================================

typedef Ref<TargetTemperatureLevelIntfControllerListener> MyInterfaceListener;


class TargetTemperatureLevelIntfController::Impl : public InterfaceController
{
  public:

    Impl(
        TargetTemperatureLevelIntfController& outer,
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

    QStatus GetMaxLevel(void* context);
    QStatus GetTargetLevel(void* context);
    QStatus SetTargetLevel(const uint8_t value, void* context);
    QStatus GetSelectableTemperatureLevels(void* context);


    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);

    void GetMaxLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetTargetLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetTargetLevelPropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetSelectableTemperatureLevelsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);



    // The outer facet
    TargetTemperatureLevelIntfController& m_outer;

    // and inherit m_proxyObject from InterfaceController
    BusAttachment& m_busAttachment;
    MyInterfaceListener m_interfaceListener;
};

//======================================================================

QStatus TargetTemperatureLevelIntfController::Impl::Init()
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




QStatus TargetTemperatureLevelIntfController::Impl::GetMaxLevel(void* context)
{
    auto status = m_proxyObject->GetPropertyAsync(GetInterfaceName(), s_prop_MaxLevel.c_str(), this,
                (ProxyBusObject::Listener::GetPropertyCB)&TargetTemperatureLevelIntfController::Impl::GetMaxLevelPropertyCB, context);
    return status;
}

QStatus TargetTemperatureLevelIntfController::Impl::GetTargetLevel(void* context)
{
    auto status = m_proxyObject->GetPropertyAsync(GetInterfaceName(), s_prop_TargetLevel.c_str(), this,
                (ProxyBusObject::Listener::GetPropertyCB)&TargetTemperatureLevelIntfController::Impl::GetTargetLevelPropertyCB, context);
    return status;
}

QStatus TargetTemperatureLevelIntfController::Impl::SetTargetLevel(const uint8_t value, void* context)
{
    MsgArg arg;
    {
        CdmMsgCvt<uint8_t> converter;
        converter.set(arg, value);
    }

    auto status = m_proxyObject->SetPropertyAsync(GetInterfaceName(), s_prop_TargetLevel.c_str(), arg, this,
                (ProxyBusObject::Listener::SetPropertyCB)&TargetTemperatureLevelIntfController::Impl::SetTargetLevelPropertyCB, context);
    return status;
}

QStatus TargetTemperatureLevelIntfController::Impl::GetSelectableTemperatureLevels(void* context)
{
    auto status = m_proxyObject->GetPropertyAsync(GetInterfaceName(), s_prop_SelectableTemperatureLevels.c_str(), this,
                (ProxyBusObject::Listener::GetPropertyCB)&TargetTemperatureLevelIntfController::Impl::GetSelectableTemperatureLevelsPropertyCB, context);
    return status;
}





void TargetTemperatureLevelIntfController::Impl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (s_prop_MaxLevel == propNameStr) {
            uint8_t val;
            {
                CdmMsgCvt<uint8_t> converter;
                converter.get((*propValue), val);
            }
            m_interfaceListener->OnMaxLevelChanged(obj.GetPath(), val);
        } else if (s_prop_TargetLevel == propNameStr) {
            uint8_t val;
            {
                CdmMsgCvt<uint8_t> converter;
                converter.get((*propValue), val);
            }
            m_interfaceListener->OnTargetLevelChanged(obj.GetPath(), val);
        } else if (s_prop_SelectableTemperatureLevels == propNameStr) {
            std::vector<uint8_t> val;
            {
                CdmMsgCvt<std::vector<uint8_t>> converter;
                converter.get((*propValue), val);
            }
            m_interfaceListener->OnSelectableTemperatureLevelsChanged(obj.GetPath(), val);
        } else {
            QCC_DbgTrace(("Unknown property change signal received"));
        }
    }
}

//======================================================================
// Callbacks


void TargetTemperatureLevelIntfController::Impl::GetMaxLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
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




void TargetTemperatureLevelIntfController::Impl::GetTargetLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (obj) {
        uint8_t val;
        {
            CdmMsgCvt<uint8_t> converter;
            converter.get(value, val);
        }
        if (_QCC_DbgPrintCheck(DBG_GEN_MESSAGE, QCC_MODULE)) {
            auto s = CdmMsgCvt<uint8_t>().str(value);
            QCC_DbgPrintf(("%s: received property %s=%s", __func__, "TargetLevel", s.c_str()));
        }
        m_interfaceListener->OnResponseGetTargetLevel(status, obj->GetPath(), val, context);
    }
}



void TargetTemperatureLevelIntfController::Impl::SetTargetLevelPropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    QCC_DbgPrintf(("%s: set completed", __func__));
    if (obj) {
        m_interfaceListener->OnResponseSetTargetLevel(status, obj->GetPath(), context);
    }
}

void TargetTemperatureLevelIntfController::Impl::GetSelectableTemperatureLevelsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (obj) {
        std::vector<uint8_t> val;
        {
            CdmMsgCvt<std::vector<uint8_t>> converter;
            converter.get(value, val);
        }
        if (_QCC_DbgPrintCheck(DBG_GEN_MESSAGE, QCC_MODULE)) {
            auto s = CdmMsgCvt<std::vector<uint8_t>>().str(value);
            QCC_DbgPrintf(("%s: received property %s=%s", __func__, "SelectableTemperatureLevels", s.c_str()));
        }
        m_interfaceListener->OnResponseGetSelectableTemperatureLevels(status, obj->GetPath(), val, context);
    }
}




//======================================================================
// Forward to the impl

TargetTemperatureLevelIntfController::TargetTemperatureLevelIntfController(
    BusAttachment& busAttachment,
    Ref<InterfaceControllerListener> listener,
    Ref<ProxyBusObject> cdmProxyObject
    )
  : m_impl(new Impl(*this, busAttachment, dynamic_pointer_cast<TargetTemperatureLevelIntfControllerListener>(listener), cdmProxyObject))
{
}



TargetTemperatureLevelIntfController::~TargetTemperatureLevelIntfController()
{
    delete m_impl;
}



Ref<CdmInterface> TargetTemperatureLevelIntfController::CreateInterface(BusAttachment& busAttachment, Ref<InterfaceControllerListener> listener, Ref<ProxyBusObject> cdmProxyObject)
{
    return mkRef<TargetTemperatureLevelIntfController>(busAttachment, dynamic_pointer_cast<TargetTemperatureLevelIntfControllerListener>(listener), cdmProxyObject);
}



QStatus TargetTemperatureLevelIntfController::Init()
{
    // Call the superclass Init
    QStatus status = CdmInterface::Init();
    if (ER_OK != status) {
        QCC_LogError(status, ("%s: Interface init failed.", __func__));
        return status;
    }

    return m_impl->Init();
}



BusAttachment& TargetTemperatureLevelIntfController::GetBusAttachment() const
{
    return m_impl->m_busAttachment;
}



QStatus TargetTemperatureLevelIntfController::GetMaxLevel(void* context)
{
    return m_impl->GetMaxLevel(context);
}



QStatus TargetTemperatureLevelIntfController::GetTargetLevel(void* context)
{
    return m_impl->GetTargetLevel(context);
}



QStatus TargetTemperatureLevelIntfController::SetTargetLevel(const uint8_t value, void* context)
{
    return m_impl->SetTargetLevel(value, context);
}



QStatus TargetTemperatureLevelIntfController::GetSelectableTemperatureLevels(void* context)
{
    return m_impl->GetSelectableTemperatureLevels(context);
}

//======================================================================
} //namespace services
} //namespace ajn