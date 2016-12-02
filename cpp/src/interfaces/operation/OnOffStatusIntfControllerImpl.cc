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
#include <alljoyn/cdm/interfaces/operation/OnOffStatusIntfControllerListener.h>
#include <alljoyn/cdm/CdmProxyBusObject.h>
#include "OnOffStatusIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* OnOffStatusIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject)
{
    return new OnOffStatusIntfControllerImpl(busAttachment, dynamic_cast<OnOffStatusIntfControllerListener&>(listener), cdmProxyObject);
}

OnOffStatusIntfControllerImpl::OnOffStatusIntfControllerImpl(BusAttachment& busAttachment, OnOffStatusIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject) :
    InterfaceController(cdmProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

OnOffStatusIntfControllerImpl::~OnOffStatusIntfControllerImpl()
{
}

QStatus OnOffStatusIntfControllerImpl::Init()
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

QStatus OnOffStatusIntfControllerImpl::GetIsOn(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_IsOn.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&OnOffStatusIntfControllerImpl::GetIsOnPropertyCB, context);
    return status;
}

void OnOffStatusIntfControllerImpl::GetIsOnPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }

    bool val;
    value.Get("b", &val);
    m_interfaceListener.OnResponseGetIsOn(status, obj->GetPath(), val, context);
}

void OnOffStatusIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (!s_prop_IsOn.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_BOOLEAN) {
                bool value = propValue->v_bool;
                m_interfaceListener.OnIsOnChanged(obj.GetPath(), value);
            }
        }
    }
}

} //namespace services
} //namespace ajn