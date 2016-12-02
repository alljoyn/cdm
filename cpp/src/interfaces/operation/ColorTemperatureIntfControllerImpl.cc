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
#include <alljoyn/cdm/interfaces/operation/ColorTemperatureIntfControllerListener.h>

#include "ColorTemperatureIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* ColorTemperatureIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, ProxyBusObject& cdmProxyObject)
{
    return new ColorTemperatureIntfControllerImpl(busAttachment, dynamic_cast<ColorTemperatureIntfControllerListener&>(listener), cdmProxyObject);
}

ColorTemperatureIntfControllerImpl::ColorTemperatureIntfControllerImpl(BusAttachment& busAttachment, ColorTemperatureIntfControllerListener& listener, ProxyBusObject& cdmProxyObject) :
    InterfaceController(cdmProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

ColorTemperatureIntfControllerImpl::~ColorTemperatureIntfControllerImpl()
{
}

QStatus ColorTemperatureIntfControllerImpl::Init()
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

QStatus ColorTemperatureIntfControllerImpl::GetTemperature(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_Temperature.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&ColorTemperatureIntfControllerImpl::GetTemperaturePropertyCB, context);
    return status;
}

QStatus ColorTemperatureIntfControllerImpl::SetTemperature(const double value, void* context)
{
    QStatus status = ER_OK;
    MsgArg arg;
    arg.Set("d", value);
    status = m_proxyObject.SetPropertyAsync(GetInterfaceName().c_str(), s_prop_Temperature.c_str(), arg, this, (ProxyBusObject::Listener::SetPropertyCB)&ColorTemperatureIntfControllerImpl::SetTemperaturePropertyCB, context);
    return status;
}

QStatus ColorTemperatureIntfControllerImpl::GetMinTemperature(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_MinTemperature.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&ColorTemperatureIntfControllerImpl::GetMinTemperaturePropertyCB, context);
    return status;
}

QStatus ColorTemperatureIntfControllerImpl::GetMaxTemperature(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_MaxTemperature.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&ColorTemperatureIntfControllerImpl::GetMaxTemperaturePropertyCB, context);
    return status;
}

void ColorTemperatureIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (!s_prop_Temperature.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_DOUBLE) {
                m_interfaceListener.OnTemperatureChanged(obj.GetPath(), propValue->v_double);
            }
        } else if (!s_prop_MinTemperature.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_DOUBLE) {
                m_interfaceListener.OnMinTemperatureChanged(obj.GetPath(), propValue->v_double);
            }
        } else if (!s_prop_MaxTemperature.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_DOUBLE) {
                m_interfaceListener.OnMaxTemperatureChanged(obj.GetPath(), propValue->v_double);
            }
        } else {
            QCC_DbgTrace(("Unknown property change signal received"));
        }
    }
}

void ColorTemperatureIntfControllerImpl::GetTemperaturePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    double val;
    value.Get("d", &val);
    m_interfaceListener.OnResponseGetTemperature(status, obj->GetPath(), val, context);
}

void ColorTemperatureIntfControllerImpl::SetTemperaturePropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    if(!obj) {
        return;
    }

    m_interfaceListener.OnResponseSetTemperature(status, obj->GetPath(), context);
}

void ColorTemperatureIntfControllerImpl::GetMinTemperaturePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    double val;
    value.Get("d", &val);
    m_interfaceListener.OnResponseGetMinTemperature(status, obj->GetPath(), val, context);
}

void ColorTemperatureIntfControllerImpl::GetMaxTemperaturePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    double val;
    value.Get("d", &val);
    m_interfaceListener.OnResponseGetMaxTemperature(status, obj->GetPath(), val, context);
}
} //namespace services
} //namespace ajn
