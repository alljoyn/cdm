/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <alljoyn/cdm/LogModule.h>
#include <alljoyn/cdm/interfaces/userinterfacesettings/TemperatureDisplayIntfControllerListener.h>

#include "TemperatureDisplayIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* TemperatureDisplayIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, ProxyBusObject& cdmProxyObject)
{
    return new TemperatureDisplayIntfControllerImpl(busAttachment, dynamic_cast<TemperatureDisplayIntfControllerListener&>(listener), cdmProxyObject);
}

TemperatureDisplayIntfControllerImpl::TemperatureDisplayIntfControllerImpl(BusAttachment& busAttachment, TemperatureDisplayIntfControllerListener& listener, ProxyBusObject& cdmProxyObject) :
    InterfaceController(cdmProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

TemperatureDisplayIntfControllerImpl::~TemperatureDisplayIntfControllerImpl()
{
}

QStatus TemperatureDisplayIntfControllerImpl::Init()
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

QStatus TemperatureDisplayIntfControllerImpl::GetDisplayTemperatureUnit(void* context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_DisplayTemperatureUnit.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&TemperatureDisplayIntfControllerImpl::GetDisplayTemperatureUnitPropertyCB,context);

    return status;

}

QStatus TemperatureDisplayIntfControllerImpl::SetDisplayTemperatureUnit(const uint8_t temperatureUnit, void* context)
{
    QStatus status = ER_OK;

    MsgArg arg;
    arg.Set("y", temperatureUnit);

    status = m_proxyObject.SetPropertyAsync(GetInterfaceName().c_str(), s_prop_DisplayTemperatureUnit.c_str(), arg, this, (ProxyBusObject::Listener::SetPropertyCB)&TemperatureDisplayIntfControllerImpl::SetDisplayTemperatureUnitPropertyCB,context);

    return status;
}
QStatus TemperatureDisplayIntfControllerImpl::GetSupportedDisplayTemperatureUnits(void* context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_SupportedDisplayTemperatureUnits.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&TemperatureDisplayIntfControllerImpl::GetSupportedDisplayTemperatureUnitsPropertyCB,context);

    return status;
}
void TemperatureDisplayIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (!s_prop_DisplayTemperatureUnit.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_BYTE) {
                uint8_t temperatureUnit = propValue->v_byte;
                m_interfaceListener.OnDisplayTemperatureUnitChanged(obj.GetPath(), temperatureUnit);
            }
        } else if(!s_prop_SupportedDisplayTemperatureUnits.compare(propNameStr)) {
            uint8_t *vals;
            size_t numVals;
            std::vector<uint8_t> supportedTemperatureUnits;
            propValue->Get("ay", &numVals, &vals);

            cout << "Selectable Levels: " << endl;
            for (size_t i = 0; i < numVals; ++i) {
                supportedTemperatureUnits.push_back(vals[i]);
            }
            m_interfaceListener.OnSupportedDisplayTemperatureUnitsChanged(obj.GetPath(), supportedTemperatureUnits);
        }
    }
}

void TemperatureDisplayIntfControllerImpl::GetDisplayTemperatureUnitPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if(!obj) {
        return;
    }

    uint8_t temperatureUnit;
    value.Get("y", &temperatureUnit);

    m_interfaceListener.OnResponseGetDisplayTemperatureUnit(status, obj->GetPath(), temperatureUnit, context);
}
void TemperatureDisplayIntfControllerImpl::SetDisplayTemperatureUnitPropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    if(!obj){
        return;
    }
    m_interfaceListener.OnResponseSetDisplayTemperatureUnit(status, obj->GetPath(), context);

}
void TemperatureDisplayIntfControllerImpl::GetSupportedDisplayTemperatureUnitsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if(!obj){
        return;
    }

    uint8_t *vals;
    size_t numVals;
    std::vector<uint8_t> supportedTemperatureUnits;
    value.Get("ay", &numVals, &vals);

    cout << "Supported temperature units: " << endl;
    for (size_t i = 0; i < numVals; ++i) {
        supportedTemperatureUnits.push_back(vals[i]);
    }

    m_interfaceListener.OnResponseGetSupportedDisplayTemperatureUnits(status, obj->GetPath(), supportedTemperatureUnits, context);
}

} //namespace services
} //namespace ajn