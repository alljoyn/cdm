/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
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
#include <alljoyn/hae/interfaces/operation/ResourceSavingIntfControllerListener.h>
#include <alljoyn/hae/HaeProxyBusObject.h>
#include "ResourceSavingIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

HaeInterface* ResourceSavingIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, HaeProxyBusObject& haeProxyObject)
{
    return new ResourceSavingIntfControllerImpl(busAttachment, dynamic_cast<ResourceSavingIntfControllerListener&>(listener), haeProxyObject);
}

ResourceSavingIntfControllerImpl::ResourceSavingIntfControllerImpl(BusAttachment& busAttachment, ResourceSavingIntfControllerListener& listener, HaeProxyBusObject& haeProxyObject) :
    InterfaceController(haeProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

ResourceSavingIntfControllerImpl::~ResourceSavingIntfControllerImpl()
{
}

QStatus ResourceSavingIntfControllerImpl::Init()
{
    QStatus status = HaeInterface::Init();
    if (ER_OK != status) {
        QCC_LogError(status, ("%s: Interface init failed.", __func__));
        return status;
    }

    status = m_proxyObject.RegisterPropertiesChangedListener(GetInterfaceName().c_str(), NULL, 0, *this, NULL);
    if (ER_OK != status) {
        QCC_LogError(status, ("%s: RegisterPropertiesChangedListener failed.", __func__));
        return status;
    }

    return status;
}


QStatus ResourceSavingIntfControllerImpl::SetResourceSavingMode(const bool mode, void* context )
{
    QStatus status = ER_OK;
    MsgArg arg;
    arg.Set("b", mode);
    status = m_proxyObject.SetPropertyAsync(GetInterfaceName().c_str(), s_prop_ResourceSavingMode.c_str(), arg, this, (ProxyBusObject::Listener::SetPropertyCB)&ResourceSavingIntfControllerImpl::SetResourceSavingModePropertyCB, context);
    return status;

}

QStatus ResourceSavingIntfControllerImpl::GetResourceSavingMode( void* context )
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_ResourceSavingMode.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&ResourceSavingIntfControllerImpl::GetResourceSavingModePropertyCB, context);
    return status;
}

void ResourceSavingIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{

    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (!s_prop_ResourceSavingMode.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_BOOLEAN) {
                bool value = propValue->v_bool;
                m_interfaceListener.OnResourceSavingModeChanged(obj.GetPath(), value);
            }
        }
    }
}

void ResourceSavingIntfControllerImpl::SetResourceSavingModePropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    if (!obj) {
        return;
    }

    m_interfaceListener.OnResponseSetResourceSavingMode(status, obj->GetPath(), context);
}

void ResourceSavingIntfControllerImpl::GetResourceSavingModePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }

    bool resourcesavingmode;
    value.Get("b", &resourcesavingmode);

    m_interfaceListener.OnResponseGetResourceSavingMode(status, obj->GetPath(), resourcesavingmode, context);
}

} //namespace services
} //namespace ajn
