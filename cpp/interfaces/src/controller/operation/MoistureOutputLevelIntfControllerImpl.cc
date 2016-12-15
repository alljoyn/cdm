/******************************************************************************
 * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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
#include <interfaces/controller/operation/MoistureOutputLevelIntfControllerListener.h>
#include <interfaces/controller/operation/MoistureOutputLevelIntfController.h>

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {
//======================================================================

typedef Ref<MoistureOutputLevelIntfControllerListener> MyInterfaceListener;


class MoistureOutputLevelIntfController::Impl : public InterfaceController
{
  public:

    Impl(
        MoistureOutputLevelIntfController& outer,
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

    QStatus GetMoistureOutputLevel(void* context);
    QStatus SetMoistureOutputLevel(const uint8_t value, void* context);
    QStatus GetMaxMoistureOutputLevel(void* context);
    QStatus GetAutoMode(void* context);
    QStatus SetAutoMode(const MoistureOutputLevelInterface::AutoMode value, void* context);


    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);

    void GetMoistureOutputLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetMoistureOutputLevelPropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetMaxMoistureOutputLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetAutoModePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetAutoModePropertyCB(QStatus status, ProxyBusObject* obj, void* context);



    // The outer facet
    MoistureOutputLevelIntfController& m_outer;

    // and inherit m_proxyObject from InterfaceController
    BusAttachment& m_busAttachment;
    MyInterfaceListener m_interfaceListener;
};

//======================================================================

QStatus MoistureOutputLevelIntfController::Impl::Init()
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




QStatus MoistureOutputLevelIntfController::Impl::GetMoistureOutputLevel(void* context)
{
    auto status = m_proxyObject->GetPropertyAsync(GetInterfaceName(), s_prop_MoistureOutputLevel.c_str(), this,
                (ProxyBusObject::Listener::GetPropertyCB)&MoistureOutputLevelIntfController::Impl::GetMoistureOutputLevelPropertyCB, context);
    return status;
}

QStatus MoistureOutputLevelIntfController::Impl::SetMoistureOutputLevel(const uint8_t value, void* context)
{
    MsgArg arg;
    {
        CdmMsgCvt<uint8_t> converter;
        converter.set(arg, value);
    }

    auto status = m_proxyObject->SetPropertyAsync(GetInterfaceName(), s_prop_MoistureOutputLevel.c_str(), arg, this,
                (ProxyBusObject::Listener::SetPropertyCB)&MoistureOutputLevelIntfController::Impl::SetMoistureOutputLevelPropertyCB, context);
    return status;
}

QStatus MoistureOutputLevelIntfController::Impl::GetMaxMoistureOutputLevel(void* context)
{
    auto status = m_proxyObject->GetPropertyAsync(GetInterfaceName(), s_prop_MaxMoistureOutputLevel.c_str(), this,
                (ProxyBusObject::Listener::GetPropertyCB)&MoistureOutputLevelIntfController::Impl::GetMaxMoistureOutputLevelPropertyCB, context);
    return status;
}

QStatus MoistureOutputLevelIntfController::Impl::GetAutoMode(void* context)
{
    auto status = m_proxyObject->GetPropertyAsync(GetInterfaceName(), s_prop_AutoMode.c_str(), this,
                (ProxyBusObject::Listener::GetPropertyCB)&MoistureOutputLevelIntfController::Impl::GetAutoModePropertyCB, context);
    return status;
}

QStatus MoistureOutputLevelIntfController::Impl::SetAutoMode(const MoistureOutputLevelInterface::AutoMode value, void* context)
{
    MsgArg arg;
    {
        CdmMsgCvt<MoistureOutputLevelInterface::AutoMode> converter;
        converter.set(arg, value);
    }

    auto status = m_proxyObject->SetPropertyAsync(GetInterfaceName(), s_prop_AutoMode.c_str(), arg, this,
                (ProxyBusObject::Listener::SetPropertyCB)&MoistureOutputLevelIntfController::Impl::SetAutoModePropertyCB, context);
    return status;
}





void MoistureOutputLevelIntfController::Impl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (s_prop_MoistureOutputLevel == propNameStr) {
            uint8_t val;
            {
                CdmMsgCvt<uint8_t> converter;
                converter.get((*propValue), val);
            }
            m_interfaceListener->OnMoistureOutputLevelChanged(obj.GetPath(), val);
        } else if (s_prop_MaxMoistureOutputLevel == propNameStr) {
            uint8_t val;
            {
                CdmMsgCvt<uint8_t> converter;
                converter.get((*propValue), val);
            }
            m_interfaceListener->OnMaxMoistureOutputLevelChanged(obj.GetPath(), val);
        } else if (s_prop_AutoMode == propNameStr) {
            MoistureOutputLevelInterface::AutoMode val;
            {
                CdmMsgCvt<MoistureOutputLevelInterface::AutoMode> converter;
                converter.get((*propValue), val);
            }
            m_interfaceListener->OnAutoModeChanged(obj.GetPath(), val);
        } else {
            QCC_DbgTrace(("Unknown property change signal received"));
        }
    }
}

//======================================================================
// Callbacks


void MoistureOutputLevelIntfController::Impl::GetMoistureOutputLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (obj) {
        uint8_t val;
        {
            CdmMsgCvt<uint8_t> converter;
            converter.get(value, val);
        }
        if (_QCC_DbgPrintCheck(DBG_GEN_MESSAGE, QCC_MODULE)) {
            auto s = CdmMsgCvt<uint8_t>().str(value);
            QCC_DbgPrintf(("%s: received property %s=%s", __func__, "MoistureOutputLevel", s.c_str()));
        }
        m_interfaceListener->OnResponseGetMoistureOutputLevel(status, obj->GetPath(), val, context);
    }
}



void MoistureOutputLevelIntfController::Impl::SetMoistureOutputLevelPropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    QCC_DbgPrintf(("%s: set completed", __func__));
    if (obj) {
        m_interfaceListener->OnResponseSetMoistureOutputLevel(status, obj->GetPath(), context);
    }
}

void MoistureOutputLevelIntfController::Impl::GetMaxMoistureOutputLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (obj) {
        uint8_t val;
        {
            CdmMsgCvt<uint8_t> converter;
            converter.get(value, val);
        }
        if (_QCC_DbgPrintCheck(DBG_GEN_MESSAGE, QCC_MODULE)) {
            auto s = CdmMsgCvt<uint8_t>().str(value);
            QCC_DbgPrintf(("%s: received property %s=%s", __func__, "MaxMoistureOutputLevel", s.c_str()));
        }
        m_interfaceListener->OnResponseGetMaxMoistureOutputLevel(status, obj->GetPath(), val, context);
    }
}




void MoistureOutputLevelIntfController::Impl::GetAutoModePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (obj) {
        MoistureOutputLevelInterface::AutoMode val;
        {
            CdmMsgCvt<MoistureOutputLevelInterface::AutoMode> converter;
            converter.get(value, val);
        }
        if (_QCC_DbgPrintCheck(DBG_GEN_MESSAGE, QCC_MODULE)) {
            auto s = CdmMsgCvt<MoistureOutputLevelInterface::AutoMode>().str(value);
            QCC_DbgPrintf(("%s: received property %s=%s", __func__, "AutoMode", s.c_str()));
        }
        m_interfaceListener->OnResponseGetAutoMode(status, obj->GetPath(), val, context);
    }
}



void MoistureOutputLevelIntfController::Impl::SetAutoModePropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    QCC_DbgPrintf(("%s: set completed", __func__));
    if (obj) {
        m_interfaceListener->OnResponseSetAutoMode(status, obj->GetPath(), context);
    }
}

//======================================================================
// Forward to the impl

MoistureOutputLevelIntfController::MoistureOutputLevelIntfController(
    BusAttachment& busAttachment,
    Ref<InterfaceControllerListener> listener,
    Ref<ProxyBusObject> cdmProxyObject
    )
  : m_impl(new Impl(*this, busAttachment, dynamic_pointer_cast<MoistureOutputLevelIntfControllerListener>(listener), cdmProxyObject))
{
}



MoistureOutputLevelIntfController::~MoistureOutputLevelIntfController()
{
    delete m_impl;
}



Ref<CdmInterface> MoistureOutputLevelIntfController::CreateInterface(BusAttachment& busAttachment, Ref<InterfaceControllerListener> listener, Ref<ProxyBusObject> cdmProxyObject)
{
    return mkRef<MoistureOutputLevelIntfController>(busAttachment, dynamic_pointer_cast<MoistureOutputLevelIntfControllerListener>(listener), cdmProxyObject);
}



QStatus MoistureOutputLevelIntfController::Init()
{
    // Call the superclass Init
    QStatus status = CdmInterface::Init();
    if (ER_OK != status) {
        QCC_LogError(status, ("%s: Interface init failed.", __func__));
        return status;
    }

    return m_impl->Init();
}



BusAttachment& MoistureOutputLevelIntfController::GetBusAttachment() const
{
    return m_impl->m_busAttachment;
}



QStatus MoistureOutputLevelIntfController::GetMoistureOutputLevel(void* context)
{
    return m_impl->GetMoistureOutputLevel(context);
}



QStatus MoistureOutputLevelIntfController::SetMoistureOutputLevel(const uint8_t value, void* context)
{
    return m_impl->SetMoistureOutputLevel(value, context);
}



QStatus MoistureOutputLevelIntfController::GetMaxMoistureOutputLevel(void* context)
{
    return m_impl->GetMaxMoistureOutputLevel(context);
}



QStatus MoistureOutputLevelIntfController::GetAutoMode(void* context)
{
    return m_impl->GetAutoMode(context);
}



QStatus MoistureOutputLevelIntfController::SetAutoMode(const MoistureOutputLevelInterface::AutoMode value, void* context)
{
    return m_impl->SetAutoMode(value, context);
}

//======================================================================
} //namespace services
} //namespace ajn