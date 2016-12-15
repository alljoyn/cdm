/******************************************************************************
 *  *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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
#include <interfaces/controller/userinterfacesettings/TemperatureDisplayIntfControllerListener.h>
#include <interfaces/controller/userinterfacesettings/TemperatureDisplayIntfController.h>

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {
//======================================================================

typedef Ref<TemperatureDisplayIntfControllerListener> MyInterfaceListener;


class TemperatureDisplayIntfController::Impl : public InterfaceController
{
  public:

    Impl(
        TemperatureDisplayIntfController& outer,
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

    QStatus GetDisplayTemperatureUnit(void* context);
    QStatus SetDisplayTemperatureUnit(const uint8_t value, void* context);
    QStatus GetSupportedDisplayTemperatureUnits(void* context);


    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);

    void GetDisplayTemperatureUnitPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetDisplayTemperatureUnitPropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetSupportedDisplayTemperatureUnitsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);



    // The outer facet
    TemperatureDisplayIntfController& m_outer;

    // and inherit m_proxyObject from InterfaceController
    BusAttachment& m_busAttachment;
    MyInterfaceListener m_interfaceListener;
};

//======================================================================

QStatus TemperatureDisplayIntfController::Impl::Init()
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




QStatus TemperatureDisplayIntfController::Impl::GetDisplayTemperatureUnit(void* context)
{
    auto status = m_proxyObject->GetPropertyAsync(GetInterfaceName(), s_prop_DisplayTemperatureUnit.c_str(), this,
                (ProxyBusObject::Listener::GetPropertyCB)&TemperatureDisplayIntfController::Impl::GetDisplayTemperatureUnitPropertyCB, context);
    return status;
}

QStatus TemperatureDisplayIntfController::Impl::SetDisplayTemperatureUnit(const uint8_t value, void* context)
{
    MsgArg arg;
    {
        CdmMsgCvt<uint8_t> converter;
        converter.set(arg, value);
    }

    auto status = m_proxyObject->SetPropertyAsync(GetInterfaceName(), s_prop_DisplayTemperatureUnit.c_str(), arg, this,
                (ProxyBusObject::Listener::SetPropertyCB)&TemperatureDisplayIntfController::Impl::SetDisplayTemperatureUnitPropertyCB, context);
    return status;
}

QStatus TemperatureDisplayIntfController::Impl::GetSupportedDisplayTemperatureUnits(void* context)
{
    auto status = m_proxyObject->GetPropertyAsync(GetInterfaceName(), s_prop_SupportedDisplayTemperatureUnits.c_str(), this,
                (ProxyBusObject::Listener::GetPropertyCB)&TemperatureDisplayIntfController::Impl::GetSupportedDisplayTemperatureUnitsPropertyCB, context);
    return status;
}





void TemperatureDisplayIntfController::Impl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (s_prop_DisplayTemperatureUnit == propNameStr) {
            uint8_t val;
            {
                CdmMsgCvt<uint8_t> converter;
                converter.get((*propValue), val);
            }
            m_interfaceListener->OnDisplayTemperatureUnitChanged(obj.GetPath(), val);
        } else if (s_prop_SupportedDisplayTemperatureUnits == propNameStr) {
            std::vector<uint8_t> val;
            {
                CdmMsgCvt<std::vector<uint8_t>> converter;
                converter.get((*propValue), val);
            }
            m_interfaceListener->OnSupportedDisplayTemperatureUnitsChanged(obj.GetPath(), val);
        } else {
            QCC_DbgTrace(("Unknown property change signal received"));
        }
    }
}

//======================================================================
// Callbacks


void TemperatureDisplayIntfController::Impl::GetDisplayTemperatureUnitPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (obj) {
        uint8_t val;
        {
            CdmMsgCvt<uint8_t> converter;
            converter.get(value, val);
        }
        if (_QCC_DbgPrintCheck(DBG_GEN_MESSAGE, QCC_MODULE)) {
            auto s = CdmMsgCvt<uint8_t>().str(value);
            QCC_DbgPrintf(("%s: received property %s=%s", __func__, "DisplayTemperatureUnit", s.c_str()));
        }
        m_interfaceListener->OnResponseGetDisplayTemperatureUnit(status, obj->GetPath(), val, context);
    }
}



void TemperatureDisplayIntfController::Impl::SetDisplayTemperatureUnitPropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    QCC_DbgPrintf(("%s: set completed", __func__));
    if (obj) {
        m_interfaceListener->OnResponseSetDisplayTemperatureUnit(status, obj->GetPath(), context);
    }
}

void TemperatureDisplayIntfController::Impl::GetSupportedDisplayTemperatureUnitsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (obj) {
        std::vector<uint8_t> val;
        {
            CdmMsgCvt<std::vector<uint8_t>> converter;
            converter.get(value, val);
        }
        if (_QCC_DbgPrintCheck(DBG_GEN_MESSAGE, QCC_MODULE)) {
            auto s = CdmMsgCvt<std::vector<uint8_t>>().str(value);
            QCC_DbgPrintf(("%s: received property %s=%s", __func__, "SupportedDisplayTemperatureUnits", s.c_str()));
        }
        m_interfaceListener->OnResponseGetSupportedDisplayTemperatureUnits(status, obj->GetPath(), val, context);
    }
}




//======================================================================
// Forward to the impl

TemperatureDisplayIntfController::TemperatureDisplayIntfController(
    BusAttachment& busAttachment,
    Ref<InterfaceControllerListener> listener,
    Ref<ProxyBusObject> cdmProxyObject
    )
  : m_impl(new Impl(*this, busAttachment, dynamic_pointer_cast<TemperatureDisplayIntfControllerListener>(listener), cdmProxyObject))
{
}



TemperatureDisplayIntfController::~TemperatureDisplayIntfController()
{
    delete m_impl;
}



Ref<CdmInterface> TemperatureDisplayIntfController::CreateInterface(BusAttachment& busAttachment, Ref<InterfaceControllerListener> listener, Ref<ProxyBusObject> cdmProxyObject)
{
    return mkRef<TemperatureDisplayIntfController>(busAttachment, dynamic_pointer_cast<TemperatureDisplayIntfControllerListener>(listener), cdmProxyObject);
}



QStatus TemperatureDisplayIntfController::Init()
{
    // Call the superclass Init
    QStatus status = CdmInterface::Init();
    if (ER_OK != status) {
        QCC_LogError(status, ("%s: Interface init failed.", __func__));
        return status;
    }

    return m_impl->Init();
}



BusAttachment& TemperatureDisplayIntfController::GetBusAttachment() const
{
    return m_impl->m_busAttachment;
}



QStatus TemperatureDisplayIntfController::GetDisplayTemperatureUnit(void* context)
{
    return m_impl->GetDisplayTemperatureUnit(context);
}



QStatus TemperatureDisplayIntfController::SetDisplayTemperatureUnit(const uint8_t value, void* context)
{
    return m_impl->SetDisplayTemperatureUnit(value, context);
}



QStatus TemperatureDisplayIntfController::GetSupportedDisplayTemperatureUnits(void* context)
{
    return m_impl->GetSupportedDisplayTemperatureUnits(context);
}

//======================================================================
} //namespace services
} //namespace ajn