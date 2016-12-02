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
#include <alljoyn/cdm/interfaces/operation/AirRecirculationModeIntfControllerListener.h>

#include "AirRecirculationModeIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* AirRecirculationModeIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject)
{
    return new AirRecirculationModeIntfControllerImpl(busAttachment, dynamic_cast<AirRecirculationModeIntfControllerListener&>(listener), cdmProxyObject);
}

AirRecirculationModeIntfControllerImpl::AirRecirculationModeIntfControllerImpl(BusAttachment& busAttachment, AirRecirculationModeIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject) :
    InterfaceController(cdmProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

AirRecirculationModeIntfControllerImpl::~AirRecirculationModeIntfControllerImpl()
{
}

QStatus AirRecirculationModeIntfControllerImpl::Init()
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

void AirRecirculationModeIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (!s_prop_IsRecirculating.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_BOOLEAN) {
                bool isRecirculating = propValue->v_bool;
                m_interfaceListener.OnIsRecirculatingChanged(obj.GetPath(), isRecirculating);
            }
        }
    }
}

QStatus AirRecirculationModeIntfControllerImpl::SetIsRecirculating(const bool isRecirculating, void* context)
{
    QStatus status = ER_OK;

    MsgArg arg;
    arg.Set("b", isRecirculating);
    status = m_proxyObject.SetPropertyAsync(GetInterfaceName().c_str(), s_prop_IsRecirculating.c_str(), arg, this, (ProxyBusObject::Listener::SetPropertyCB)&AirRecirculationModeIntfControllerImpl::SetIsRecirculatingPropertyCB, context);

    return status;
}

QStatus AirRecirculationModeIntfControllerImpl::GetIsRecirculating(void* context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_IsRecirculating.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&AirRecirculationModeIntfControllerImpl::GetIsRecirculatingPropertyCB, context);

    return status;
}

void AirRecirculationModeIntfControllerImpl::SetIsRecirculatingPropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    if(!obj) {
        return;
    }

    m_interfaceListener.OnResponseSetIsRecirculating(status, obj->GetPath(), context);
}

void AirRecirculationModeIntfControllerImpl::GetIsRecirculatingPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }

    bool isRecirculating;
    value.Get("b", &isRecirculating);

    m_interfaceListener.OnResponseGetIsRecirculating(status, obj->GetPath(), isRecirculating, context);
}

} //namespace services
} //namespace ajn