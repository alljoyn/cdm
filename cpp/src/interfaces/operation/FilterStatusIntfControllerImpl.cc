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

#include <alljoyn/hae/LogModule.h>
#include <alljoyn/hae/HaeProxyBusObject.h>
#include <alljoyn/hae/interfaces/operation/FilterStatusIntfControllerListener.h>

#include "FilterStatusIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

HaeInterface* FilterStatusIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, HaeProxyBusObject& haeProxyObject)
{
    return new FilterStatusIntfControllerImpl(busAttachment, dynamic_cast<FilterStatusIntfControllerListener&>(listener), haeProxyObject);
}

FilterStatusIntfControllerImpl::FilterStatusIntfControllerImpl(BusAttachment& busAttachment, FilterStatusIntfControllerListener& listener, HaeProxyBusObject& haeProxyObject) :
    InterfaceController(haeProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

FilterStatusIntfControllerImpl::~FilterStatusIntfControllerImpl()
{
}

QStatus FilterStatusIntfControllerImpl::Init()
{
    QStatus status = HaeInterface::Init();
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

void FilterStatusIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (!s_prop_ExpectedLifeInDays.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_UINT16) {
                uint16_t value = propValue->v_uint16;
                m_interfaceListener.OnExpectedLifeInDaysChanged(obj.GetPath(), value);
            }
        } else if (!s_prop_IsCleanable.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_BOOLEAN) {
                bool isCleanable = propValue->v_bool;
                m_interfaceListener.OnIsCleanableChanged(obj.GetPath(), isCleanable);
            }
        } else if (!s_prop_OrderPercentage.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_BYTE) {
                uint8_t value = propValue->v_byte;
                m_interfaceListener.OnOrderPercentageChanged(obj.GetPath(), value);
            }
        } else if (!s_prop_LifeRemaining.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_BYTE) {
                uint8_t value = propValue->v_byte;
                m_interfaceListener.OnLifeRemainingChanged(obj.GetPath(), value);
            }
        }
    }
}

QStatus FilterStatusIntfControllerImpl::GetExpectedLifeInDays(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_ExpectedLifeInDays.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&FilterStatusIntfControllerImpl::GetExpectedLifeInDaysPropertyCB, context);
    return status;
}

QStatus FilterStatusIntfControllerImpl::GetIsCleanable(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_IsCleanable.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&FilterStatusIntfControllerImpl::GetIsCleanablePropertyCB, context);
    return status;
}

QStatus FilterStatusIntfControllerImpl::GetOrderPercentage(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_OrderPercentage.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&FilterStatusIntfControllerImpl::GetOrderPercentagePropertyCB, context);
    return status;
}

QStatus FilterStatusIntfControllerImpl::GetManufacturer(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_Manufacturer.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&FilterStatusIntfControllerImpl::GetManufacturerPropertyCB, context);
    return status;
}

QStatus FilterStatusIntfControllerImpl::GetPartNumber(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_PartNumber.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&FilterStatusIntfControllerImpl::GetPartNumberPropertyCB, context);
    return status;
}

QStatus FilterStatusIntfControllerImpl::GetUrl(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_Url.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&FilterStatusIntfControllerImpl::GetUrlPropertyCB, context);
    return status;
}

QStatus FilterStatusIntfControllerImpl::GetLifeRemaining(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_LifeRemaining.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&FilterStatusIntfControllerImpl::GetLifeRemainingPropertyCB, context);
    return status;
}

void FilterStatusIntfControllerImpl::GetExpectedLifeInDaysPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    uint16_t val;
    value.Get("q", &val);
    m_interfaceListener.OnResponseGetExpectedLifeInDays(status, obj->GetPath(), val, context);
}

void FilterStatusIntfControllerImpl::GetIsCleanablePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    bool isCleanable;
    value.Get("b", &isCleanable);
    m_interfaceListener.OnResponseGetIsCleanable(status, obj->GetPath(), isCleanable, context);
}

void FilterStatusIntfControllerImpl::GetOrderPercentagePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    uint8_t val;
    value.Get("y", &val);
    m_interfaceListener.OnResponseGetOrderPercentage(status, obj->GetPath(), val, context);
}

void FilterStatusIntfControllerImpl::GetManufacturerPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    const char* val = "";
    value.Get("s", &val);
    String manufacturer = String(val);
    m_interfaceListener.OnResponseGetManufacturer(status, obj->GetPath(), manufacturer, context);
}

void FilterStatusIntfControllerImpl::GetPartNumberPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    const char* val = "";
    value.Get("s", &val);
    String partNumber = String(val);
    m_interfaceListener.OnResponseGetPartNumber(status, obj->GetPath(), partNumber, context);
}

void FilterStatusIntfControllerImpl::GetUrlPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    const char* val = "";
    value.Get("s", &val);
    String url = String(val);
    m_interfaceListener.OnResponseGetUrl(status, obj->GetPath(), url, context);
}

void FilterStatusIntfControllerImpl::GetLifeRemainingPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    uint8_t val;
    value.Get("y", &val);
    m_interfaceListener.OnResponseGetLifeRemaining(status, obj->GetPath(), val, context);
}

} //namespace services
} //namespace ajn
