/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

// This file is automatically generated. Do not edit it.

#include <alljoyn/cdm/common/LogModule.h>
#include <alljoyn/cdm/common/CdmTypes.h>
#include <alljoyn/cdm/controller/InterfaceController.h>
#include <interfaces/controller/environment/WindDirectionIntfControllerListener.h>
#include <interfaces/controller/environment/WindDirectionIntfController.h>

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {
//======================================================================

typedef Ref<WindDirectionIntfControllerListener> MyInterfaceListener;


class WindDirectionIntfController::Impl : public InterfaceController
{
  public:

    Impl(
        WindDirectionIntfController& outer,
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

    QStatus GetHorizontalDirection(void* context);
    QStatus SetHorizontalDirection(const uint16_t value, void* context);
    QStatus GetHorizontalMax(void* context);
    QStatus GetHorizontalAutoMode(void* context);
    QStatus SetHorizontalAutoMode(const WindDirectionInterface::AutoMode value, void* context);
    QStatus GetVerticalDirection(void* context);
    QStatus SetVerticalDirection(const uint16_t value, void* context);
    QStatus GetVerticalMax(void* context);
    QStatus GetVerticalAutoMode(void* context);
    QStatus SetVerticalAutoMode(const WindDirectionInterface::AutoMode value, void* context);


    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);

    void GetHorizontalDirectionPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetHorizontalDirectionPropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetHorizontalMaxPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetHorizontalAutoModePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetHorizontalAutoModePropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetVerticalDirectionPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetVerticalDirectionPropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetVerticalMaxPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetVerticalAutoModePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetVerticalAutoModePropertyCB(QStatus status, ProxyBusObject* obj, void* context);



    // The outer facet
    WindDirectionIntfController& m_outer;

    // and inherit m_proxyObject from InterfaceController
    BusAttachment& m_busAttachment;
    MyInterfaceListener m_interfaceListener;
};

//======================================================================

QStatus WindDirectionIntfController::Impl::Init()
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




QStatus WindDirectionIntfController::Impl::GetHorizontalDirection(void* context)
{
    auto status = m_proxyObject->GetPropertyAsync(GetInterfaceName(), s_prop_HorizontalDirection.c_str(), this,
                (ProxyBusObject::Listener::GetPropertyCB)&WindDirectionIntfController::Impl::GetHorizontalDirectionPropertyCB, context);
    return status;
}

QStatus WindDirectionIntfController::Impl::SetHorizontalDirection(const uint16_t value, void* context)
{
    MsgArg arg;
    {
        CdmMsgCvt<uint16_t> converter;
        converter.set(arg, value);
    }

    auto status = m_proxyObject->SetPropertyAsync(GetInterfaceName(), s_prop_HorizontalDirection.c_str(), arg, this,
                (ProxyBusObject::Listener::SetPropertyCB)&WindDirectionIntfController::Impl::SetHorizontalDirectionPropertyCB, context);
    return status;
}

QStatus WindDirectionIntfController::Impl::GetHorizontalMax(void* context)
{
    auto status = m_proxyObject->GetPropertyAsync(GetInterfaceName(), s_prop_HorizontalMax.c_str(), this,
                (ProxyBusObject::Listener::GetPropertyCB)&WindDirectionIntfController::Impl::GetHorizontalMaxPropertyCB, context);
    return status;
}

QStatus WindDirectionIntfController::Impl::GetHorizontalAutoMode(void* context)
{
    auto status = m_proxyObject->GetPropertyAsync(GetInterfaceName(), s_prop_HorizontalAutoMode.c_str(), this,
                (ProxyBusObject::Listener::GetPropertyCB)&WindDirectionIntfController::Impl::GetHorizontalAutoModePropertyCB, context);
    return status;
}

QStatus WindDirectionIntfController::Impl::SetHorizontalAutoMode(const WindDirectionInterface::AutoMode value, void* context)
{
    MsgArg arg;
    {
        CdmMsgCvt<WindDirectionInterface::AutoMode> converter;
        converter.set(arg, value);
    }

    auto status = m_proxyObject->SetPropertyAsync(GetInterfaceName(), s_prop_HorizontalAutoMode.c_str(), arg, this,
                (ProxyBusObject::Listener::SetPropertyCB)&WindDirectionIntfController::Impl::SetHorizontalAutoModePropertyCB, context);
    return status;
}

QStatus WindDirectionIntfController::Impl::GetVerticalDirection(void* context)
{
    auto status = m_proxyObject->GetPropertyAsync(GetInterfaceName(), s_prop_VerticalDirection.c_str(), this,
                (ProxyBusObject::Listener::GetPropertyCB)&WindDirectionIntfController::Impl::GetVerticalDirectionPropertyCB, context);
    return status;
}

QStatus WindDirectionIntfController::Impl::SetVerticalDirection(const uint16_t value, void* context)
{
    MsgArg arg;
    {
        CdmMsgCvt<uint16_t> converter;
        converter.set(arg, value);
    }

    auto status = m_proxyObject->SetPropertyAsync(GetInterfaceName(), s_prop_VerticalDirection.c_str(), arg, this,
                (ProxyBusObject::Listener::SetPropertyCB)&WindDirectionIntfController::Impl::SetVerticalDirectionPropertyCB, context);
    return status;
}

QStatus WindDirectionIntfController::Impl::GetVerticalMax(void* context)
{
    auto status = m_proxyObject->GetPropertyAsync(GetInterfaceName(), s_prop_VerticalMax.c_str(), this,
                (ProxyBusObject::Listener::GetPropertyCB)&WindDirectionIntfController::Impl::GetVerticalMaxPropertyCB, context);
    return status;
}

QStatus WindDirectionIntfController::Impl::GetVerticalAutoMode(void* context)
{
    auto status = m_proxyObject->GetPropertyAsync(GetInterfaceName(), s_prop_VerticalAutoMode.c_str(), this,
                (ProxyBusObject::Listener::GetPropertyCB)&WindDirectionIntfController::Impl::GetVerticalAutoModePropertyCB, context);
    return status;
}

QStatus WindDirectionIntfController::Impl::SetVerticalAutoMode(const WindDirectionInterface::AutoMode value, void* context)
{
    MsgArg arg;
    {
        CdmMsgCvt<WindDirectionInterface::AutoMode> converter;
        converter.set(arg, value);
    }

    auto status = m_proxyObject->SetPropertyAsync(GetInterfaceName(), s_prop_VerticalAutoMode.c_str(), arg, this,
                (ProxyBusObject::Listener::SetPropertyCB)&WindDirectionIntfController::Impl::SetVerticalAutoModePropertyCB, context);
    return status;
}





void WindDirectionIntfController::Impl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (s_prop_HorizontalDirection == propNameStr) {
            uint16_t val;
            {
                CdmMsgCvt<uint16_t> converter;
                converter.get((*propValue), val);
            }
            m_interfaceListener->OnHorizontalDirectionChanged(obj.GetPath(), val);
        } else if (s_prop_HorizontalMax == propNameStr) {
            uint16_t val;
            {
                CdmMsgCvt<uint16_t> converter;
                converter.get((*propValue), val);
            }
            m_interfaceListener->OnHorizontalMaxChanged(obj.GetPath(), val);
        } else if (s_prop_HorizontalAutoMode == propNameStr) {
            WindDirectionInterface::AutoMode val;
            {
                CdmMsgCvt<WindDirectionInterface::AutoMode> converter;
                converter.get((*propValue), val);
            }
            m_interfaceListener->OnHorizontalAutoModeChanged(obj.GetPath(), val);
        } else if (s_prop_VerticalDirection == propNameStr) {
            uint16_t val;
            {
                CdmMsgCvt<uint16_t> converter;
                converter.get((*propValue), val);
            }
            m_interfaceListener->OnVerticalDirectionChanged(obj.GetPath(), val);
        } else if (s_prop_VerticalMax == propNameStr) {
            uint16_t val;
            {
                CdmMsgCvt<uint16_t> converter;
                converter.get((*propValue), val);
            }
            m_interfaceListener->OnVerticalMaxChanged(obj.GetPath(), val);
        } else if (s_prop_VerticalAutoMode == propNameStr) {
            WindDirectionInterface::AutoMode val;
            {
                CdmMsgCvt<WindDirectionInterface::AutoMode> converter;
                converter.get((*propValue), val);
            }
            m_interfaceListener->OnVerticalAutoModeChanged(obj.GetPath(), val);
        } else {
            QCC_DbgTrace(("Unknown property change signal received"));
        }
    }
}

//======================================================================
// Callbacks


void WindDirectionIntfController::Impl::GetHorizontalDirectionPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (obj) {
        uint16_t val;
        {
            CdmMsgCvt<uint16_t> converter;
            converter.get(value, val);
        }
        if (_QCC_DbgPrintCheck(DBG_GEN_MESSAGE, QCC_MODULE)) {
            auto s = CdmMsgCvt<uint16_t>().str(value);
            QCC_DbgPrintf(("%s: received property %s=%s", __func__, "HorizontalDirection", s.c_str()));
        }
        m_interfaceListener->OnResponseGetHorizontalDirection(status, obj->GetPath(), val, context);
    }
}



void WindDirectionIntfController::Impl::SetHorizontalDirectionPropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    QCC_DbgPrintf(("%s: set completed", __func__));
    if (obj) {
        m_interfaceListener->OnResponseSetHorizontalDirection(status, obj->GetPath(), context);
    }
}

void WindDirectionIntfController::Impl::GetHorizontalMaxPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (obj) {
        uint16_t val;
        {
            CdmMsgCvt<uint16_t> converter;
            converter.get(value, val);
        }
        if (_QCC_DbgPrintCheck(DBG_GEN_MESSAGE, QCC_MODULE)) {
            auto s = CdmMsgCvt<uint16_t>().str(value);
            QCC_DbgPrintf(("%s: received property %s=%s", __func__, "HorizontalMax", s.c_str()));
        }
        m_interfaceListener->OnResponseGetHorizontalMax(status, obj->GetPath(), val, context);
    }
}




void WindDirectionIntfController::Impl::GetHorizontalAutoModePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (obj) {
        WindDirectionInterface::AutoMode val;
        {
            CdmMsgCvt<WindDirectionInterface::AutoMode> converter;
            converter.get(value, val);
        }
        if (_QCC_DbgPrintCheck(DBG_GEN_MESSAGE, QCC_MODULE)) {
            auto s = CdmMsgCvt<WindDirectionInterface::AutoMode>().str(value);
            QCC_DbgPrintf(("%s: received property %s=%s", __func__, "HorizontalAutoMode", s.c_str()));
        }
        m_interfaceListener->OnResponseGetHorizontalAutoMode(status, obj->GetPath(), val, context);
    }
}



void WindDirectionIntfController::Impl::SetHorizontalAutoModePropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    QCC_DbgPrintf(("%s: set completed", __func__));
    if (obj) {
        m_interfaceListener->OnResponseSetHorizontalAutoMode(status, obj->GetPath(), context);
    }
}

void WindDirectionIntfController::Impl::GetVerticalDirectionPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (obj) {
        uint16_t val;
        {
            CdmMsgCvt<uint16_t> converter;
            converter.get(value, val);
        }
        if (_QCC_DbgPrintCheck(DBG_GEN_MESSAGE, QCC_MODULE)) {
            auto s = CdmMsgCvt<uint16_t>().str(value);
            QCC_DbgPrintf(("%s: received property %s=%s", __func__, "VerticalDirection", s.c_str()));
        }
        m_interfaceListener->OnResponseGetVerticalDirection(status, obj->GetPath(), val, context);
    }
}



void WindDirectionIntfController::Impl::SetVerticalDirectionPropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    QCC_DbgPrintf(("%s: set completed", __func__));
    if (obj) {
        m_interfaceListener->OnResponseSetVerticalDirection(status, obj->GetPath(), context);
    }
}

void WindDirectionIntfController::Impl::GetVerticalMaxPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (obj) {
        uint16_t val;
        {
            CdmMsgCvt<uint16_t> converter;
            converter.get(value, val);
        }
        if (_QCC_DbgPrintCheck(DBG_GEN_MESSAGE, QCC_MODULE)) {
            auto s = CdmMsgCvt<uint16_t>().str(value);
            QCC_DbgPrintf(("%s: received property %s=%s", __func__, "VerticalMax", s.c_str()));
        }
        m_interfaceListener->OnResponseGetVerticalMax(status, obj->GetPath(), val, context);
    }
}




void WindDirectionIntfController::Impl::GetVerticalAutoModePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (obj) {
        WindDirectionInterface::AutoMode val;
        {
            CdmMsgCvt<WindDirectionInterface::AutoMode> converter;
            converter.get(value, val);
        }
        if (_QCC_DbgPrintCheck(DBG_GEN_MESSAGE, QCC_MODULE)) {
            auto s = CdmMsgCvt<WindDirectionInterface::AutoMode>().str(value);
            QCC_DbgPrintf(("%s: received property %s=%s", __func__, "VerticalAutoMode", s.c_str()));
        }
        m_interfaceListener->OnResponseGetVerticalAutoMode(status, obj->GetPath(), val, context);
    }
}



void WindDirectionIntfController::Impl::SetVerticalAutoModePropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    QCC_DbgPrintf(("%s: set completed", __func__));
    if (obj) {
        m_interfaceListener->OnResponseSetVerticalAutoMode(status, obj->GetPath(), context);
    }
}

//======================================================================
// Forward to the impl

WindDirectionIntfController::WindDirectionIntfController(
    BusAttachment& busAttachment,
    Ref<InterfaceControllerListener> listener,
    Ref<ProxyBusObject> cdmProxyObject
    )
  : m_impl(new Impl(*this, busAttachment, dynamic_pointer_cast<WindDirectionIntfControllerListener>(listener), cdmProxyObject))
{
}



WindDirectionIntfController::~WindDirectionIntfController()
{
    delete m_impl;
}



Ref<CdmInterface> WindDirectionIntfController::CreateInterface(BusAttachment& busAttachment, Ref<InterfaceControllerListener> listener, Ref<ProxyBusObject> cdmProxyObject)
{
    return mkRef<WindDirectionIntfController>(busAttachment, dynamic_pointer_cast<WindDirectionIntfControllerListener>(listener), cdmProxyObject);
}



QStatus WindDirectionIntfController::Init()
{
    // Call the superclass Init
    QStatus status = CdmInterface::Init();
    if (ER_OK != status) {
        QCC_LogError(status, ("%s: Interface init failed.", __func__));
        return status;
    }

    return m_impl->Init();
}



BusAttachment& WindDirectionIntfController::GetBusAttachment() const
{
    return m_impl->m_busAttachment;
}



QStatus WindDirectionIntfController::GetHorizontalDirection(void* context)
{
    return m_impl->GetHorizontalDirection(context);
}



QStatus WindDirectionIntfController::SetHorizontalDirection(const uint16_t value, void* context)
{
    return m_impl->SetHorizontalDirection(value, context);
}



QStatus WindDirectionIntfController::GetHorizontalMax(void* context)
{
    return m_impl->GetHorizontalMax(context);
}



QStatus WindDirectionIntfController::GetHorizontalAutoMode(void* context)
{
    return m_impl->GetHorizontalAutoMode(context);
}



QStatus WindDirectionIntfController::SetHorizontalAutoMode(const WindDirectionInterface::AutoMode value, void* context)
{
    return m_impl->SetHorizontalAutoMode(value, context);
}



QStatus WindDirectionIntfController::GetVerticalDirection(void* context)
{
    return m_impl->GetVerticalDirection(context);
}



QStatus WindDirectionIntfController::SetVerticalDirection(const uint16_t value, void* context)
{
    return m_impl->SetVerticalDirection(value, context);
}



QStatus WindDirectionIntfController::GetVerticalMax(void* context)
{
    return m_impl->GetVerticalMax(context);
}



QStatus WindDirectionIntfController::GetVerticalAutoMode(void* context)
{
    return m_impl->GetVerticalAutoMode(context);
}



QStatus WindDirectionIntfController::SetVerticalAutoMode(const WindDirectionInterface::AutoMode value, void* context)
{
    return m_impl->SetVerticalAutoMode(value, context);
}

//======================================================================
} //namespace services
} //namespace ajn
