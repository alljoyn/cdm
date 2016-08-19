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
#include <alljoyn/cdm/CdmProxyBusObject.h>
#include <alljoyn/cdm/interfaces/operation/RapidModeIntfControllerListener.h>

#include "RapidModeIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* RapidModeIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject)
{
    return new RapidModeIntfControllerImpl(busAttachment, dynamic_cast<RapidModeIntfControllerListener&>(listener), cdmProxyObject);
}

RapidModeIntfControllerImpl::RapidModeIntfControllerImpl(BusAttachment& busAttachment, RapidModeIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject) :
    InterfaceController(cdmProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

RapidModeIntfControllerImpl::~RapidModeIntfControllerImpl()
{
}

QStatus RapidModeIntfControllerImpl::Init()
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

void RapidModeIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i)
    {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (!s_prop_RapidMode.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_BOOLEAN) {
                bool rapidMode = propValue->v_bool;
                m_interfaceListener.RapidModePropertyChanged(obj.GetPath(), rapidMode);
            }
        }
    }
}

QStatus RapidModeIntfControllerImpl::GetRapidMode(void* context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_RapidMode.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&RapidModeIntfControllerImpl::GetRapidModePropertyCB, context);

    return status;
}

QStatus RapidModeIntfControllerImpl::SetRapidMode(const bool rapidMode, void* context)
{
    QStatus status = ER_OK;

    MsgArg arg;
    arg.Set("b", rapidMode);
    status = m_proxyObject.SetPropertyAsync(GetInterfaceName().c_str(), s_prop_RapidMode.c_str(), arg, this, (ProxyBusObject::Listener::SetPropertyCB)&RapidModeIntfControllerImpl::SetRapidModePropertyCB, context);

    return status;
}


void RapidModeIntfControllerImpl::SetRapidModePropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    if(!obj){
        return;
    }

    m_interfaceListener.OnSetRapidModePropertyCallback(status, obj->GetPath(), context);
}
void RapidModeIntfControllerImpl::GetRapidModePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if(!obj) {
        return;
    }
    bool rapidMode;

    value.Get("b", &rapidMode);

    m_interfaceListener.OnGetRapidModePropertyCallback(status, obj->GetPath(), rapidMode, context);
}

} //namespace services
} //namespace ajn
