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
#include <alljoyn/cdm/interfaces/operation/PlugInUnitsIntfControllerListener.h>

#include "PlugInUnitsIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* PlugInUnitsIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject)
{
    return new PlugInUnitsIntfControllerImpl(busAttachment, dynamic_cast<PlugInUnitsIntfControllerListener&>(listener), cdmProxyObject);
}

PlugInUnitsIntfControllerImpl::PlugInUnitsIntfControllerImpl(BusAttachment& busAttachment, PlugInUnitsIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject) :
    InterfaceController(cdmProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

PlugInUnitsIntfControllerImpl::~PlugInUnitsIntfControllerImpl()
{
}

QStatus PlugInUnitsIntfControllerImpl::Init()
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

void PlugInUnitsIntfControllerImpl::GetPlugInUnitsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if(!obj) {
        return;
    }
    MsgArg* unitEntries;
    size_t numUnitEntries;

    PlugInUnitsInterface::PlugInUnits units;
    PlugInUnitsInterface::PlugInInfo info;
    value.Get("a(oub)", &numUnitEntries, &unitEntries);
    for (size_t i = 0; i < numUnitEntries; ++i)
    {
        char* objPath = NULL;
        unitEntries[i].Get("(oub)", &objPath, &info.deviceId, &info.pluggedIn);
        info.objectPath = objPath;
        units.push_back(info);
    }
    m_interfaceListener.OnResponseGetPlugInUnits(status, obj->GetPath(), units, context);
}

void PlugInUnitsIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (!s_prop_PlugInUnits.compare(propNameStr)) {
            if (!propValue[0].HasSignature("a(oub)"))
            {
                return;
            }

            MsgArg* unitEntries;
            size_t numUnitEntries;

            PlugInUnitsInterface::PlugInUnits units;
            PlugInUnitsInterface::PlugInInfo info;
            propValue[0].Get("a(oub)", &numUnitEntries, &unitEntries);
            for (size_t i = 0; i < numUnitEntries; ++i)
            {
                char* objPath = NULL;
                unitEntries[i].Get("(oub)", &objPath, &info.deviceId, &info.pluggedIn);
                info.objectPath = objPath;
                units.push_back(info);
            }
            m_interfaceListener.OnPlugInUnitsPropertyChanged(obj.GetPath(), units);
        }
    }
}

QStatus PlugInUnitsIntfControllerImpl::GetPlugInUnits(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(),s_prop_PlugInUnits.c_str(),this,(ProxyBusObject::Listener::GetPropertyCB)&PlugInUnitsIntfControllerImpl::GetPlugInUnitsPropertyCB,context);

    return status;
}

} //namespace services
} //namespace ajn