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
#include <alljoyn/cdm/interfaces/operation/ClosedStatusIntfControllerListener.h>

#include "ClosedStatusIntfControllerImpl.h"


using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* ClosedStatusIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject)
{
    return new ClosedStatusIntfControllerImpl(busAttachment, dynamic_cast<ClosedStatusIntfControllerListener&>(listener), cdmProxyObject);
}

ClosedStatusIntfControllerImpl::ClosedStatusIntfControllerImpl(BusAttachment& busAttachment, ClosedStatusIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject) :
    InterfaceController(cdmProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

ClosedStatusIntfControllerImpl::~ClosedStatusIntfControllerImpl()
{
}

QStatus ClosedStatusIntfControllerImpl::Init()
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

void ClosedStatusIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (!s_prop_IsClosed.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_BOOLEAN) {
                uint8_t volume = propValue->v_bool;
                m_interfaceListener.IsClosedPropertyChanged(obj.GetPath(), volume);
            }
        }
    }
}

QStatus ClosedStatusIntfControllerImpl::GetIsClosed(void* context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_IsClosed.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&ClosedStatusIntfControllerImpl::GetIsClosedPropertyCB, context);

    return status;
}

void ClosedStatusIntfControllerImpl::GetIsClosedPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj)
    {
        return;
    }

    bool isClosed;
    value.Get("b", &isClosed);

    m_interfaceListener.GetIsClosedPropertyCallback(status, obj->GetPath(), isClosed, context);
}


} //namespace services
} //namespace ajn