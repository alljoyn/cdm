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
#include <alljoyn/cdm/interfaces/operation/RobotCleaningCyclePhaseIntfControllerListener.h>

#include "RobotCleaningCyclePhaseIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* RobotCleaningCyclePhaseIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject)
{
    return new RobotCleaningCyclePhaseIntfControllerImpl(busAttachment, dynamic_cast<RobotCleaningCyclePhaseIntfControllerListener&>(listener), cdmProxyObject);
}

RobotCleaningCyclePhaseIntfControllerImpl::RobotCleaningCyclePhaseIntfControllerImpl(BusAttachment& busAttachment, RobotCleaningCyclePhaseIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject) :
    InterfaceController(cdmProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

RobotCleaningCyclePhaseIntfControllerImpl::~RobotCleaningCyclePhaseIntfControllerImpl()
{
}

QStatus RobotCleaningCyclePhaseIntfControllerImpl::Init()
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

void RobotCleaningCyclePhaseIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; i++) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (!s_prop_CyclePhase.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_BYTE) {
                uint8_t cyclePhase = propValue->v_byte;
                m_interfaceListener.OnCyclePhaseChanged(obj.GetPath(), cyclePhase);
            }
        } else if (!s_prop_SupportedCyclePhases.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_BYTE_ARRAY) {
                SupportedCyclePhases supportedCyclePhases;
                uint8_t *vals;
                size_t numVals;
                propValue->Get("ay", &numVals, &vals);

                for(size_t i = 0; i < numVals; i++)
                {
                    supportedCyclePhases.push_back(vals[i]);
                }

                m_interfaceListener.OnSupportedCyclePhasesChanged(obj.GetPath(), supportedCyclePhases);
            }
        }
    }
}

QStatus RobotCleaningCyclePhaseIntfControllerImpl::GetCyclePhase(void* context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_CyclePhase.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&RobotCleaningCyclePhaseIntfControllerImpl::GetCyclePhasePropertyCB, context);

    return status;
}

QStatus RobotCleaningCyclePhaseIntfControllerImpl::GetSupportedCyclePhases(void* context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_SupportedCyclePhases.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&RobotCleaningCyclePhaseIntfControllerImpl::GetSupportedCyclePhasesPropertyCB, context);

    return status;
}

QStatus RobotCleaningCyclePhaseIntfControllerImpl::GetVendorPhasesDescription(const qcc::String& languageTag, void* context)
{
    QStatus status = ER_OK;

    MsgArg args[1];
    args[0].Set("s", languageTag.c_str());

    status = m_proxyObject.MethodCallAsync(GetInterfaceName().c_str(), s_method_GetVendorPhasesDescription.c_str(), this, (MessageReceiver::ReplyHandler)&RobotCleaningCyclePhaseIntfControllerImpl::GetVendorPhasesDescriptionReplyHandler, args, 1, context);

    return status;
}

void RobotCleaningCyclePhaseIntfControllerImpl::GetCyclePhasePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }

    uint8_t cyclePhase;
    value.Get("y", &cyclePhase);

    m_interfaceListener.OnResponseGetCyclePhase(status, obj->GetPath(), cyclePhase, context);
}

void RobotCleaningCyclePhaseIntfControllerImpl::GetSupportedCyclePhasesPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }

    SupportedCyclePhases supportedCyclePhases;

    uint8_t *vals;
    size_t numVals;
    value.Get("ay", &numVals, &vals);

    if (numVals > 0)
    {
        for(size_t i = 0; i < numVals; i++)
        {
            supportedCyclePhases.push_back(vals[i]);
        }
    }

    m_interfaceListener.OnResponseGetSupportedCyclePhases(status, obj->GetPath(), supportedCyclePhases, context);
}

void RobotCleaningCyclePhaseIntfControllerImpl::GetVendorPhasesDescriptionReplyHandler(Message& message, void* context)
{
    RobotCleaningCyclePhaseInterface::CyclePhaseDescriptors phasesDescription;
    String errorMessage;
    const char* errorName = message->GetErrorName(&errorMessage);
    QStatus status = ER_OK;
    if (message->GetType() != MESSAGE_METHOD_RET) {
        status = ER_FAIL;
    } else {
        size_t numArgs;
        const MsgArg* args;
        message->GetArgs(numArgs, args);

        if (!args[0].HasSignature("a(yss)")) {
            return;
        }

        MsgArg* entries;
        size_t numEntries;
        RobotCleaningCyclePhaseInterface::CyclePhaseDescriptor descriptor;

        args[0].Get("a(yss)", &numEntries, &entries);
        for (size_t i = 0; i < numEntries; i++) {
            uint8_t phase;
            const char* name, *description;
            entries[i].Get("(yss)", &phase, &name, &description);
            descriptor.phase = phase;
            descriptor.name = String(name);
            descriptor.description = String(description);
            phasesDescription.push_back(descriptor);
        }
    }
    m_interfaceListener.OnResponseGetVendorPhasesDescription(status, m_proxyObject.GetPath(), phasesDescription, context,
                                                             errorName, errorMessage.c_str());
}

} //namespace services
} //namespace ajn