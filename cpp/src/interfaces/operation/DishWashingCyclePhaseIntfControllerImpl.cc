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
#include <alljoyn/cdm/interfaces/operation/DishWashingCyclePhaseIntfControllerListener.h>

#include "DishWashingCyclePhaseIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* DishWashingCyclePhaseIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject)
{
    return new DishWashingCyclePhaseIntfControllerImpl(busAttachment, dynamic_cast<DishWashingCyclePhaseIntfControllerListener&>(listener), cdmProxyObject);
}

DishWashingCyclePhaseIntfControllerImpl::DishWashingCyclePhaseIntfControllerImpl(BusAttachment& busAttachment, DishWashingCyclePhaseIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject) :
    InterfaceController(cdmProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

DishWashingCyclePhaseIntfControllerImpl::~DishWashingCyclePhaseIntfControllerImpl()
{
}

QStatus DishWashingCyclePhaseIntfControllerImpl::Init()
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

void DishWashingCyclePhaseIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (!s_prop_CyclePhase.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_BYTE) {
                DishWashingCyclePhaseInterface::DishWashingCyclePhase cyclePhase = (DishWashingCyclePhaseInterface::DishWashingCyclePhase)propValue->v_byte;
                m_interfaceListener.OnCyclePhasePropertyChanged(obj.GetPath(), cyclePhase);
            }
        } else if (!s_prop_SupportedCyclePhases.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_BYTE_ARRAY) {
                DishWashingCyclePhaseInterface::SupportedCyclePhases supportedCyclePhases;
                uint8_t *vals;
                size_t numVals;
                propValue->Get("ay", &numVals, &vals);

                for (size_t i = 0; i < numVals; ++i)
                    supportedCyclePhases.push_back((DishWashingCyclePhaseInterface::DishWashingCyclePhase)vals[i]);
                m_interfaceListener.OnSupportedCyclePhasesPropertyChanged(obj.GetPath(), supportedCyclePhases);
            }
        }
    }
}

QStatus DishWashingCyclePhaseIntfControllerImpl::GetCyclePhase(void* context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(),s_prop_CyclePhase.c_str(),this,(ProxyBusObject::Listener::GetPropertyCB)&DishWashingCyclePhaseIntfControllerImpl::GetCyclePhasePropertyCB,context);

    return status;

}

QStatus DishWashingCyclePhaseIntfControllerImpl::GetSupportedCyclePhases(void* context )
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(),s_prop_SupportedCyclePhases.c_str(),this,(ProxyBusObject::Listener::GetPropertyCB)&DishWashingCyclePhaseIntfControllerImpl::GetSupportedCyclePhasesPropertyCB,context);

    return status;
}

QStatus DishWashingCyclePhaseIntfControllerImpl::GetCyclePhasesDescriptions(const qcc::String& language, void* context)
{
    QStatus status = ER_OK;

    MsgArg args[1];
    args[0].typeId = ALLJOYN_STRING;
    args[0].v_string.str = language.c_str();
    args[0].v_string.len = language.size();

    status = m_proxyObject.MethodCallAsync(GetInterfaceName().c_str(), s_method_GetVendorPhasesDescription.c_str(), this, (MessageReceiver::ReplyHandler)&DishWashingCyclePhaseIntfControllerImpl::GetCyclePhasesDescriptionReplyHandler, args, 1, context);

    return status;
}

void DishWashingCyclePhaseIntfControllerImpl::GetCyclePhasePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if(!obj) {
        return;
    }

    uint8_t cyclePhase;
    value.Get("y", &cyclePhase);

    m_interfaceListener.OnResponseGetCyclePhase(status, obj->GetPath(), (DishWashingCyclePhase)cyclePhase, context);
}
void DishWashingCyclePhaseIntfControllerImpl::GetSupportedCyclePhasesPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if(!obj) {
        return;
    }
    uint8_t *vals;
    size_t numVals;
    value.Get("ay", &numVals, &vals);

    SupportedCyclePhases cyclePhases;
    for (size_t i = 0; i < numVals; ++i)
        cyclePhases.push_back((DishWashingCyclePhase)vals[i]);

    m_interfaceListener.OnResponseGetSupportedCyclePhases(status, obj->GetPath(), cyclePhases, context);

}

void DishWashingCyclePhaseIntfControllerImpl::GetCyclePhasesDescriptionReplyHandler(Message& message, void* context)
{
    DishWashingCyclePhaseInterface::CyclePhaseDescriptions descriptions;
    qcc::String errorMessage;
    const char* errorName = message->GetErrorName(&errorMessage);
    QStatus status = ER_OK;
    if (message->GetType() != MESSAGE_METHOD_RET)
    {
        status = ER_FAIL;
    }
    else
    {
        size_t numArgs;
        const MsgArg* args;
        message->GetArgs(numArgs, args);

        if (!args[0].HasSignature("a(yss)"))
        {
            return;
        }

        MsgArg* entries;
        size_t numEntries;
        DishWashingCyclePhaseInterface::DishWashingPhaseDescriptor desc;

        args[0].Get("a(yss)", &numEntries, &entries);
        for (size_t i = 0; i < numEntries; ++i)
        {
            const char* phaseName, *phaseDesc;
            uint8_t phase;
            entries[i].Get("(yss)", &phase, &phaseName, &phaseDesc);
            desc.phase = (DishWashingCyclePhase)phase;
            desc.name = String(phaseName);
            desc.description = String(phaseDesc);
            descriptions.push_back(desc);
        }
    }
    m_interfaceListener.OnResponseGetCyclePhasesDescriptions(status, m_proxyObject.GetPath(), descriptions, context, errorName, errorMessage.c_str());
}

} //namespace services
} //namespace ajn