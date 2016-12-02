/******************************************************************************
 *  * 
 *    Copyright (c) 2016 Open Connectivity Foundation and AllJoyn Open
 *    Source Project Contributors and others.
 *    
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0

 ******************************************************************************/

#include <qcc/Util.h>

#include <alljoyn/cdm/LogModule.h>
#include <alljoyn/cdm/CdmProxyBusObject.h>
#include <alljoyn/cdm/interfaces/operation/RepeatModeIntfControllerListener.h>

#include "RepeatModeIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* RepeatModeIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject)
{
    return new RepeatModeIntfControllerImpl(busAttachment, dynamic_cast<RepeatModeIntfControllerListener&>(listener), cdmProxyObject);
}

RepeatModeIntfControllerImpl::RepeatModeIntfControllerImpl(BusAttachment& busAttachment, RepeatModeIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject) :
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