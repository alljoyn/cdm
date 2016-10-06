/******************************************************************************
 *  * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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
#include <alljoyn/cdm/interfaces/operation/SpinSpeedLevelIntfControllerListener.h>

#include "SpinSpeedLevelIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* SpinSpeedLevelIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject)
{
    return new SpinSpeedLevelIntfControllerImpl(busAttachment, dynamic_cast<SpinSpeedLevelIntfControllerListener&>(listener), cdmProxyObject);
}

SpinSpeedLevelIntfControllerImpl::SpinSpeedLevelIntfControllerImpl(BusAttachment& busAttachment, SpinSpeedLevelIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject) :
    InterfaceController(cdmProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

SpinSpeedLevelIntfControllerImpl::~SpinSpeedLevelIntfControllerImpl()
{
}

QStatus SpinSpeedLevelIntfControllerImpl::Init()
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

void SpinSpeedLevelIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (!s_prop_MaxLevel.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_BYTE) {
                uint8_t level = propValue->v_byte;
                m_interfaceListener.MaxLevelPropertyChanged(obj.GetPath(), level);
            }
        } else if (!s_prop_TargetLevel.compare(propNameStr)){
            if(propValue->typeId == ALLJOYN_BYTE) {
                uint8_t level = propValue->v_byte;
                m_interfaceListener.TargetLevelPropertyChanged(obj.GetPath(), level);
            }
        } else if(!s_prop_SelectableLevels.compare(propNameStr)) {
            uint8_t *vals;
            size_t numVals;
            std::vector<uint8_t> levels;
            propValue->Get("ay", &numVals, &vals);

            cout << "Selectable Levels: " << endl;
            for (size_t i = 0; i < numVals; ++i) {
                levels.push_back(vals[i]);
            }
            m_interfaceListener.SelectableLevelsPropertyChanged(obj.GetPath(), levels);
        }
    }
}
QStatus SpinSpeedLevelIntfControllerImpl::GetMaxLevel(void* context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_MaxLevel.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&SpinSpeedLevelIntfControllerImpl::GetMaxLevelPropertyCB,context);

    return status;
}

QStatus SpinSpeedLevelIntfControllerImpl::GetTargetLevel(void* context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_TargetLevel.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&SpinSpeedLevelIntfControllerImpl::GetTargetLevelPropertyCB,context);

    return status;
}
QStatus SpinSpeedLevelIntfControllerImpl::SetTargetLevel(const uint8_t targetLevel, void* context)
{
    QStatus status = ER_OK;

    MsgArg arg;
    arg.Set("y", targetLevel);

    status = m_proxyObject.SetPropertyAsync(GetInterfaceName().c_str(), s_prop_TargetLevel.c_str(), arg, this, (ProxyBusObject::Listener::SetPropertyCB)&SpinSpeedLevelIntfControllerImpl::SetTargetLevelPropertyCB,context);

    return status;
}
QStatus SpinSpeedLevelIntfControllerImpl::GetSelectableLevels(void* context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_SelectableLevels.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&SpinSpeedLevelIntfControllerImpl::GetSelectableLevelsPropertyCB,context);

    return status;
}

void SpinSpeedLevelIntfControllerImpl::GetMaxLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if(!obj) {
        return;
    }

    uint8_t maxLevel;
    cout << "# SoilLevelIntfControllerImpl::GetMaxLevelPropertyCB" << endl;
    value.Get("y", &maxLevel);

    m_interfaceListener.GetMaxLevelPropertyCallback(status,obj->GetPath(),maxLevel,context);
}
void SpinSpeedLevelIntfControllerImpl::GetTargetLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if(!obj) {
        return;
    }

    uint8_t targetLevel;
    value.Get("y", &targetLevel);

    m_interfaceListener.GetTargetLevelPropertyCallback(status,obj->GetPath(),targetLevel,context);
}
void SpinSpeedLevelIntfControllerImpl::SetTargetLevelPropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    if(!obj){
        return;
    }
    m_interfaceListener.SetTargetLevelPropertyCallback(status,obj->GetPath(),context);
}
void SpinSpeedLevelIntfControllerImpl::GetSelectableLevelsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{

    if(!obj){
        return;
    }

    uint8_t *vals;
    size_t numVals;
    std::vector<uint8_t> levels;
    value.Get("ay", &numVals, &vals);

    cout << "Selectable Levels: " << endl;
    for (size_t i = 0; i < numVals; ++i) {
        levels.push_back(vals[i]);
    }

    m_interfaceListener.GetSelectableLevelsPropertyCallback(status,obj->GetPath(), levels, context);
}


} //namespace services
} //namespace ajn