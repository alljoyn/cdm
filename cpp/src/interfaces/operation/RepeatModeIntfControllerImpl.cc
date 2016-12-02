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
#include <alljoyn/cdm/interfaces/operation/RepeatModeIntfControllerListener.h>

#include "RepeatModeIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* RepeatModeIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, ProxyBusObject& cdmProxyObject)
{
    return new RepeatModeIntfControllerImpl(busAttachment, dynamic_cast<RepeatModeIntfControllerListener&>(listener), cdmProxyObject);
}

RepeatModeIntfControllerImpl::RepeatModeIntfControllerImpl(BusAttachment& busAttachment, RepeatModeIntfControllerListener& listener, ProxyBusObject& cdmProxyObject) :
    InterfaceController(cdmProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

RepeatModeIntfControllerImpl::~RepeatModeIntfControllerImpl()
{
}

QStatus RepeatModeIntfControllerImpl::Init()
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

QStatus RepeatModeIntfControllerImpl::GetRepeatMode(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_RepeatMode.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&RepeatModeIntfControllerImpl::GetRepeatModePropertyCB, context);
    return status;
}

QStatus RepeatModeIntfControllerImpl::SetRepeatMode(const bool value, void* context)
{
    QStatus status = ER_OK;
    MsgArg arg;
    arg.Set("b", value);
    status = m_proxyObject.SetPropertyAsync(GetInterfaceName().c_str(), s_prop_RepeatMode.c_str(), arg, this, (ProxyBusObject::Listener::SetPropertyCB)&RepeatModeIntfControllerImpl::SetRepeatModePropertyCB, context);
    return status;
}

void RepeatModeIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (!s_prop_RepeatMode.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_BOOLEAN) {
                bool repeatMode = propValue->v_bool;
                m_interfaceListener.OnRepeatModeChanged(obj.GetPath(), repeatMode);
            }
        }
    }
}

void RepeatModeIntfControllerImpl::GetRepeatModePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }

    bool val;
    value.Get("b", &val);
    m_interfaceListener.OnResponseGetRepeatMode(status, obj->GetPath(), val, context);
}

void RepeatModeIntfControllerImpl::SetRepeatModePropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    if (!obj) {
        return;
    }
    m_interfaceListener.OnResponseSetRepeatMode(status, obj->GetPath(), context);
}

} //namespace services
} //namespace ajn
