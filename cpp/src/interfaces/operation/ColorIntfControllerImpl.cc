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
#include <alljoyn/cdm/interfaces/operation/ColorIntfControllerListener.h>

#include "ColorIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* ColorIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, ProxyBusObject& cdmProxyObject)
{
    return new ColorIntfControllerImpl(busAttachment, dynamic_cast<ColorIntfControllerListener&>(listener), cdmProxyObject);
}

ColorIntfControllerImpl::ColorIntfControllerImpl(BusAttachment& busAttachment, ColorIntfControllerListener& listener, ProxyBusObject& cdmProxyObject) :
    InterfaceController(cdmProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

ColorIntfControllerImpl::~ColorIntfControllerImpl()
{
}

QStatus ColorIntfControllerImpl::Init()
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

QStatus ColorIntfControllerImpl::GetHue(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_Hue.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&ColorIntfControllerImpl::GetHuePropertyCB, context);
    return status;
}

QStatus ColorIntfControllerImpl::SetHue(const double value, void* context)
{
    QStatus status = ER_OK;
    MsgArg arg;
    arg.Set("d", value);
    status = m_proxyObject.SetPropertyAsync(GetInterfaceName().c_str(), s_prop_Hue.c_str(), arg, this, (ProxyBusObject::Listener::SetPropertyCB)&ColorIntfControllerImpl::SetHuePropertyCB, context);
    return status;
}

QStatus ColorIntfControllerImpl::GetSaturation(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_Saturation.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&ColorIntfControllerImpl::GetSaturationPropertyCB, context);
    return status;
}

QStatus ColorIntfControllerImpl::SetSaturation(const double value, void* context)
{
    QStatus status = ER_OK;
    MsgArg arg;
    arg.Set("d", value);
    status = m_proxyObject.SetPropertyAsync(GetInterfaceName().c_str(), s_prop_Saturation.c_str(), arg, this, (ProxyBusObject::Listener::SetPropertyCB)&ColorIntfControllerImpl::SetSaturationPropertyCB, context);
    return status;
}

void ColorIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (!s_prop_Hue.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_DOUBLE) {
                m_interfaceListener.OnHueChanged(obj.GetPath(), propValue->v_double);
            }
        } else if (!s_prop_Saturation.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_DOUBLE) {
                m_interfaceListener.OnSaturationChanged(obj.GetPath(), propValue->v_double);
            }
        } else {
            QCC_DbgTrace(("Unknown property change signal received"));
        }
    }
}

void ColorIntfControllerImpl::GetHuePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    double val;
    value.Get("d", &val);
    m_interfaceListener.OnResponseGetHue(status, obj->GetPath(), val, context);
}

void ColorIntfControllerImpl::SetHuePropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    if(!obj) {
        return;
    }

    m_interfaceListener.OnResponseSetHue(status, obj->GetPath(), context);
}

void ColorIntfControllerImpl::GetSaturationPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    double val;
    value.Get("d", &val);
    m_interfaceListener.OnResponseGetSaturation(status, obj->GetPath(), val, context);
}

void ColorIntfControllerImpl::SetSaturationPropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    if(!obj) {
        return;
    }

    m_interfaceListener.OnResponseSetSaturation(status, obj->GetPath(), context);
}
} //namespace services
} //namespace ajn
