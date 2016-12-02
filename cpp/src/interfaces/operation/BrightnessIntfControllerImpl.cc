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
#include <alljoyn/cdm/interfaces/operation/BrightnessIntfControllerListener.h>

#include "BrightnessIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* BrightnessIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, ProxyBusObject& cdmProxyObject)
{
    return new BrightnessIntfControllerImpl(busAttachment, dynamic_cast<BrightnessIntfControllerListener&>(listener), cdmProxyObject);
}

BrightnessIntfControllerImpl::BrightnessIntfControllerImpl(BusAttachment& busAttachment, BrightnessIntfControllerListener& listener, ProxyBusObject& cdmProxyObject) :
    InterfaceController(cdmProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

BrightnessIntfControllerImpl::~BrightnessIntfControllerImpl()
{
}

QStatus BrightnessIntfControllerImpl::Init()
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

QStatus BrightnessIntfControllerImpl::GetBrightness(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_Brightness.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&BrightnessIntfControllerImpl::GetBrightnessPropertyCB, context);
    return status;
}

QStatus BrightnessIntfControllerImpl::SetBrightness(const double value, void* context)
{
    QStatus status = ER_OK;
    MsgArg arg;
    arg.Set("d", value);
    status = m_proxyObject.SetPropertyAsync(GetInterfaceName().c_str(), s_prop_Brightness.c_str(), arg, this, (ProxyBusObject::Listener::SetPropertyCB)&BrightnessIntfControllerImpl::SetBrightnessPropertyCB, context);
    return status;
}

void BrightnessIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (!s_prop_Brightness.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_DOUBLE) {
                m_interfaceListener.OnBrightnessChanged(obj.GetPath(), propValue->v_double);
            }
        } else {
            QCC_DbgTrace(("Unknown property change signal received"));
        }
    }
}

void BrightnessIntfControllerImpl::GetBrightnessPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    double val;
    value.Get("d", &val);
    m_interfaceListener.OnResponseGetBrightness(status, obj->GetPath(), val, context);
}

void BrightnessIntfControllerImpl::SetBrightnessPropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    if(!obj) {
        return;
    }

    m_interfaceListener.OnResponseSetBrightness(status, obj->GetPath(), context);
}
} //namespace services
} //namespace ajn
