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

#include <qcc/Util.h>

#include <alljoyn/cdm/LogModule.h>
#include <alljoyn/cdm/interfaces/environment/WindDirectionIntfControllerListener.h>
#include "WindDirectionIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* WindDirectionIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, ProxyBusObject& cdmProxyObject)
{
    return new WindDirectionIntfControllerImpl(busAttachment, dynamic_cast<WindDirectionIntfControllerListener&>(listener), cdmProxyObject);
}

WindDirectionIntfControllerImpl::WindDirectionIntfControllerImpl(BusAttachment& busAttachment, WindDirectionIntfControllerListener& listener, ProxyBusObject& cdmProxyObject) :
    InterfaceController(cdmProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

WindDirectionIntfControllerImpl::~WindDirectionIntfControllerImpl()
{
}

QStatus WindDirectionIntfControllerImpl::Init()
{
    QStatus status = CdmInterface::Init();
    if (ER_OK != status) {
        QCC_LogError(status, ("%s: Interface init failed.", __func__));
        return status;
    }

    status = m_proxyObject.RegisterPropertiesChangedListener(GetInterfaceName().c_str(), NULL, 0, *this, NULL);
    if (ER_OK != status) {
        QCC_LogError(status, ("%s: RegisterPropertiesChangedListener failed.", __func__));
    }

    return status;
}

QStatus WindDirectionIntfControllerImpl::GetHorizontalDirection(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_HorizontalDirection.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&WindDirectionIntfControllerImpl::GetHorizontalDirectionPropertyCB, context);
    return status;
}

QStatus WindDirectionIntfControllerImpl::SetHorizontalDirection(const uint16_t value, void* context)
{
    QStatus status = ER_OK;
    MsgArg arg;
    arg.Set("q", value);
    status = m_proxyObject.SetPropertyAsync(GetInterfaceName().c_str(), s_prop_HorizontalDirection.c_str(), arg, this, (ProxyBusObject::Listener::SetPropertyCB)&WindDirectionIntfControllerImpl::SetHorizontalDirectionPropertyCB, context);
    return status;
}

QStatus WindDirectionIntfControllerImpl::GetHorizontalMax(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_HorizontalMax.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&WindDirectionIntfControllerImpl::GetHorizontalMaxPropertyCB, context);
    return status;
}

QStatus WindDirectionIntfControllerImpl::GetHorizontalAutoMode(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_HorizontalAutoMode.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&WindDirectionIntfControllerImpl::GetHorizontalAutoModePropertyCB, context);
    return status;
}

QStatus WindDirectionIntfControllerImpl::SetHorizontalAutoMode(const AutoMode value, void* context)
{
    QStatus status = ER_OK;
    MsgArg arg;
    arg.Set("y", value);
    status = m_proxyObject.SetPropertyAsync(GetInterfaceName().c_str(), s_prop_HorizontalAutoMode.c_str(), arg, this, (ProxyBusObject::Listener::SetPropertyCB)&WindDirectionIntfControllerImpl::SetHorizontalAutoModePropertyCB, context);
    return status;
}

QStatus WindDirectionIntfControllerImpl::GetVerticalDirection(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_VerticalDirection.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&WindDirectionIntfControllerImpl::GetVerticalDirectionPropertyCB, context);
    return status;
}


QStatus WindDirectionIntfControllerImpl::SetVerticalDirection(const uint16_t value, void* context)
{
    QStatus status = ER_OK;
    MsgArg arg;
    arg.Set("q", value);
    status = m_proxyObject.SetPropertyAsync(GetInterfaceName().c_str(), s_prop_VerticalDirection.c_str(), arg, this, (ProxyBusObject::Listener::SetPropertyCB)&WindDirectionIntfControllerImpl::SetVerticalDirectionPropertyCB, context);
    return status;
}

QStatus WindDirectionIntfControllerImpl::GetVerticalMax(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_VerticalMax.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&WindDirectionIntfControllerImpl::GetVerticalMaxPropertyCB, context);
    return status;
}

QStatus WindDirectionIntfControllerImpl::GetVerticalAutoMode(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_VerticalAutoMode.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&WindDirectionIntfControllerImpl::GetVerticalAutoModePropertyCB, context);
    return status;
}

QStatus WindDirectionIntfControllerImpl::SetVerticalAutoMode(const AutoMode value, void* context)
{
    QStatus status = ER_OK;
    MsgArg arg;
    arg.Set("y", value);
    status = m_proxyObject.SetPropertyAsync(GetInterfaceName().c_str(), s_prop_VerticalAutoMode.c_str(), arg, this, (ProxyBusObject::Listener::SetPropertyCB)&WindDirectionIntfControllerImpl::SetVerticalAutoModePropertyCB, context);
    return status;
}

void WindDirectionIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (!s_prop_HorizontalDirection.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_UINT16) {
                uint16_t value = propValue->v_uint16;
                m_interfaceListener.OnHorizontalDirectionChanged(obj.GetPath(), value);
            }
        } else if (!s_prop_HorizontalMax.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_UINT16) {
                uint16_t value = propValue->v_uint16;
                m_interfaceListener.OnHorizontalMaxChanged(obj.GetPath(), value);
            }
        } else if (!s_prop_HorizontalAutoMode.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_BYTE) {
                uint8_t value = propValue->v_byte;
                m_interfaceListener.OnHorizontalAutoModeChanged(obj.GetPath(), (AutoMode)value);
            }
        } else if (!s_prop_VerticalDirection.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_UINT16) {
                uint16_t value = propValue->v_uint16;
                m_interfaceListener.OnVerticalDirectionChanged(obj.GetPath(), value);
            }
        } else if (!s_prop_VerticalMax.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_UINT16) {
                uint16_t value = propValue->v_uint16;
                m_interfaceListener.OnVerticalMaxChanged(obj.GetPath(), value);
            }
        } else if (!s_prop_VerticalAutoMode.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_BYTE) {
                uint8_t value = propValue->v_byte;
                m_interfaceListener.OnVerticalAutoModeChanged(obj.GetPath(), (AutoMode)value);
            }
        }
    }
}

void WindDirectionIntfControllerImpl::GetHorizontalDirectionPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    uint16_t val;
    value.Get("q", &val);
    m_interfaceListener.OnResponseGetHorizontalDirection(status, obj->GetPath(), val, context);
}

void WindDirectionIntfControllerImpl::SetHorizontalDirectionPropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    if (!obj) {
        return;
    }
    m_interfaceListener.OnResponseSetHorizontalDirection(status, obj->GetPath(), context);
}

void WindDirectionIntfControllerImpl::GetHorizontalMaxPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    uint16_t val;
    value.Get("q", &val);
    m_interfaceListener.OnResponseGetHorizontalMax(status, obj->GetPath(), val, context);
}
void WindDirectionIntfControllerImpl::GetHorizontalAutoModePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    uint8_t val;
    value.Get("y", &val);
    m_interfaceListener.OnResponseGetHorizontalAutoMode(status, obj->GetPath(), (AutoMode)val, context);
}

void WindDirectionIntfControllerImpl::SetHorizontalAutoModePropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    if (!obj) {
        return;
    }
    m_interfaceListener.OnResponseSetHorizontalAutoMode(status, obj->GetPath(), context);
}


void WindDirectionIntfControllerImpl::GetVerticalDirectionPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    uint16_t val;
    value.Get("q", &val);
    m_interfaceListener.OnResponseGetVerticalDirection(status, obj->GetPath(), val, context);
}

void WindDirectionIntfControllerImpl::SetVerticalDirectionPropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    if (!obj) {
        return;
    }
    m_interfaceListener.OnResponseSetVerticalDirection(status, obj->GetPath(), context);
}

void WindDirectionIntfControllerImpl::GetVerticalMaxPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    uint16_t val;
    value.Get("q", &val);
    m_interfaceListener.OnResponseGetVerticalMax(status, obj->GetPath(), val, context);
}
void WindDirectionIntfControllerImpl::GetVerticalAutoModePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    uint8_t val;
    value.Get("y", &val);
    m_interfaceListener.OnResponseGetVerticalAutoMode(status, obj->GetPath(), (AutoMode)val, context);
}

void WindDirectionIntfControllerImpl::SetVerticalAutoModePropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    if (!obj) {
        return;
    }
    m_interfaceListener.OnResponseSetVerticalAutoMode(status, obj->GetPath(), context);
}


} //namespace services
} //namespace ajn
