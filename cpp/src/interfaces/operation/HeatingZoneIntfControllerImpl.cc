/******************************************************************************
 * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
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

#include <qcc/Util.h>

#include <alljoyn/cdm/LogModule.h>
#include <alljoyn/cdm/CdmProxyBusObject.h>
#include <alljoyn/cdm/interfaces/operation/HeatingZoneIntfControllerListener.h>

#include "HeatingZoneIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* HeatingZoneIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject)
{
    return new HeatingZoneIntfControllerImpl(busAttachment, dynamic_cast<HeatingZoneIntfControllerListener&>(listener), cdmProxyObject);
}

HeatingZoneIntfControllerImpl::HeatingZoneIntfControllerImpl(BusAttachment& busAttachment, HeatingZoneIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject) :
    InterfaceController(cdmProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

HeatingZoneIntfControllerImpl::~HeatingZoneIntfControllerImpl()
{
}

QStatus HeatingZoneIntfControllerImpl::Init()
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

void HeatingZoneIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (!s_prop_NumberOfHeatingZones.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_BYTE) {
                uint8_t numOfZones = propValue->v_byte;
                m_interfaceListener.NumberOfHeatingZonesPropertyChanged(obj.GetPath(), numOfZones);
            }
        }
        else if(!s_prop_MaxHeatingLevels.compare(propNameStr)) {
            if(propValue->typeId == ALLJOYN_BYTE_ARRAY) {
                uint8_t *vals;
                size_t numVals;
                propValue->Get("ay", &numVals, &vals);

                std::vector<uint8_t> maxHeatingLevels;
                for (size_t i = 0; i < numVals; ++i)
                    maxHeatingLevels.push_back(vals[i]);
                m_interfaceListener.MaxHeatingLevelsPropertyChanged(obj.GetPath(), maxHeatingLevels);
            }
        }
        else if (!s_prop_HeatingLevels.compare(propNameStr)) {
            if(propValue->typeId == ALLJOYN_BYTE_ARRAY) {
                uint8_t *vals;
                size_t numVals;
                propValue->Get("ay", &numVals, &vals);

                std::vector<uint8_t> heatingLevels;
                for (size_t i = 0; i < numVals; ++i)
                    heatingLevels.push_back(vals[i]);
                m_interfaceListener.HeatingLevelsPropertyChanged(obj.GetPath(), heatingLevels);
            }
        }
    }
}

QStatus HeatingZoneIntfControllerImpl::GetNumberOfHeatingZones(void* context)
{
    QStatus status = ER_OK;

    m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_NumberOfHeatingZones.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&HeatingZoneIntfControllerImpl::GetNumberOfHeatingZonesPropertyCB, context);

    return status;
}

QStatus HeatingZoneIntfControllerImpl::GetMaxHeatingLevels(void* context )
{
    QStatus status = ER_OK;

    m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_MaxHeatingLevels.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&HeatingZoneIntfControllerImpl::GetMaxHeatingLevelsPropertyCB, context);

    return status;
}

QStatus HeatingZoneIntfControllerImpl::GetHeatingLevels(void* context)
{
    QStatus status = ER_OK;

    m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_HeatingLevels.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&HeatingZoneIntfControllerImpl::GetHeatingLevelsPropertyCB, context);

    return status;
}

void HeatingZoneIntfControllerImpl::GetNumberOfHeatingZonesPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }

    uint8_t numOfZones;

    value.Get("y",&numOfZones);

    m_interfaceListener.OnGetNumberOfHeatingZonesPropertyCallback(status, obj->GetPath(), numOfZones, context);
}

void HeatingZoneIntfControllerImpl::GetMaxHeatingLevelsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    uint8_t *vals;
    size_t numVals;
    value.Get("ay", &numVals, &vals);

    std::vector<uint8_t> maxHeatingLevels;
    for (size_t i = 0; i < numVals; ++i) {
        maxHeatingLevels.push_back(vals[i]);
    }
    m_interfaceListener.OnGetMaxHeatingLevelsPropertyCallback(status, obj->GetPath(), maxHeatingLevels, context);

}

void HeatingZoneIntfControllerImpl::GetHeatingLevelsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    uint8_t *vals;
    size_t numVals;
    value.Get("ay", &numVals, &vals);

    std::vector<uint8_t> heatingLevels;
    for (size_t i = 0; i < numVals; ++i) {
        heatingLevels.push_back(vals[i]);
    }
    m_interfaceListener.OnGetHeatingLevelsPropertyCallback(status, obj->GetPath(), heatingLevels, context);
}


} //namespace services
} //namespace ajn