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

#include <qcc/Util.h>

#include <alljoyn/cdm/LogModule.h>
#include <alljoyn/cdm/CdmBusObject.h>
#include <alljoyn/cdm/interfaces/operation/RobotCleaningCyclePhaseIntfControlleeListener.h>

#include "RobotCleaningCyclePhaseIntfControlleeImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* RobotCleaningCyclePhaseIntfControlleeImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject)
{
    return new RobotCleaningCyclePhaseIntfControlleeImpl(busAttachment, dynamic_cast<RobotCleaningCyclePhaseIntfControlleeListener&>(listener), cdmBusObject);
}

RobotCleaningCyclePhaseIntfControlleeImpl::RobotCleaningCyclePhaseIntfControlleeImpl(BusAttachment& busAttachment, RobotCleaningCyclePhaseIntfControlleeListener& listener, CdmBusObject& cdmBusObject) :
    InterfaceControllee(cdmBusObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

RobotCleaningCyclePhaseIntfControlleeImpl::~RobotCleaningCyclePhaseIntfControlleeImpl()
{
}

QStatus RobotCleaningCyclePhaseIntfControlleeImpl::Init()
{
    QStatus status = CdmInterface::Init();

    const InterfaceDescription::Member* member = m_interfaceDescription->GetMember(s_method_GetVendorPhasesDescription.c_str());
    MessageReceiver::MethodHandler methodHandler = static_cast<MessageReceiver::MethodHandler>(&RobotCleaningCyclePhaseIntfControlleeImpl::OnGetVendorPhasesDescription);

    m_methodHandlers.push_back(make_pair(member, methodHandler));
    return status;
}

QStatus RobotCleaningCyclePhaseIntfControlleeImpl::OnGetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    if (!(s_prop_Version.compare(propName))) {
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = GetInterfaceVersion();
    } else {
        if (s_retrievingActualPropertyValue) {
            if (!(s_prop_CyclePhase.compare(propName))) {
                uint8_t cyclePhase;
                status = m_interfaceListener.OnGetCyclePhase(cyclePhase);
                if (status != ER_OK) {
                    cyclePhase = GetCyclePhase();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetCyclePhase(cyclePhase);
                }
                val.typeId = ALLJOYN_BYTE;
                val.v_byte = cyclePhase;
            } else if (!(s_prop_SupportedCyclePhases.compare(propName))) {
                SupportedCyclePhases supportedCyclePhases;
                status = m_interfaceListener.OnGetSupportedCyclePhases(supportedCyclePhases);
                if (status != ER_OK) {
                    supportedCyclePhases = GetSupportedCyclePhases();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetSupportedCyclePhases(supportedCyclePhases);
                }

                MsgArg arg(ALLJOYN_ARRAY);
                size_t numElements = supportedCyclePhases.size();
                uint8_t* temp = new uint8_t[numElements];
                for (size_t i = 0; i < numElements; i++)
                {
                    temp[i] =  supportedCyclePhases[i];
                }
                arg.Set("ay", numElements, temp);

                val = arg;
                delete[] temp;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
        } else {
            if (!(s_prop_CyclePhase.compare(propName))) {
                uint8_t cyclePhase = GetCyclePhase();
                val.typeId = ALLJOYN_BYTE;
                val.v_byte = cyclePhase;
            } else if (!(s_prop_SupportedCyclePhases.compare(propName))) {
                const SupportedCyclePhases& supportedCyclePhases = GetSupportedCyclePhases();

                MsgArg arg(ALLJOYN_ARRAY);
                size_t numElements = supportedCyclePhases.size();
                uint8_t* temp = new uint8_t[numElements];
                for (size_t i = 0; i < numElements; i++)
                {
                    temp[i] =  supportedCyclePhases[i];
                }
                arg.Set("ay", numElements, temp);

                val = arg;
                delete[] temp;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
        }
    }

    return status;
}

QStatus RobotCleaningCyclePhaseIntfControlleeImpl::OnSetProperty(const String& propName, MsgArg& val)
{
    return ER_BUS_NO_SUCH_PROPERTY;
}

void RobotCleaningCyclePhaseIntfControlleeImpl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
{
    QStatus status = ER_OK;
    bool isFound = false;
    MethodHandlers::const_iterator it;
    for (it = m_methodHandlers.begin(); it != m_methodHandlers.end(); ++it) {
        if (it->first == member) {
            MessageReceiver::MethodHandler handler = it->second;
            (this->*handler)(member, msg);
            isFound = true;
            break;
        }
    }

    if (!isFound) {
        status = ER_BUS_METHOD_CALL_ABORTED;
        QCC_LogError(status, ("%s: could not find method handler.", __func__));
        m_busObject.ReplyMethodCall(msg, status);
    }
}

QStatus RobotCleaningCyclePhaseIntfControlleeImpl::SetCyclePhase(const uint8_t cyclePhase)
{
    if (cyclePhase < MIN_ROBOT_CLEANING_VENDOR_DEFINED_CYCLE_PHASE
        && (cyclePhase < MIN_ROBOT_CLEANING_STANDARD_CYCLE_PHASE
            || cyclePhase > MAX_ROBOT_CLEANING_STANDARD_CYCLE_PHASE)) {
        QCC_LogError(ER_INVALID_DATA, ("%s: Out of range.", __func__));
        return ER_INVALID_DATA;
    } else {
        size_t i = 0;

        for (i = 0; i < m_supportedCyclePhases.size(); i++) {
            if (cyclePhase == m_supportedCyclePhases[i]) {
                break;
            }
        }
        if (i == m_supportedCyclePhases.size()) {
            QCC_LogError(ER_INVALID_DATA, ("%s: CyclePhase is not exist in SupportedCyclePhases.", __func__));
            return ER_INVALID_DATA;
        }
    }

    if (m_cyclePhase != cyclePhase) {
        MsgArg val;
        val.typeId = ALLJOYN_BYTE;
        val.v_byte = cyclePhase;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_CyclePhase.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_cyclePhase = cyclePhase;
    }
    return ER_OK;
}

QStatus RobotCleaningCyclePhaseIntfControlleeImpl::SetSupportedCyclePhases(const SupportedCyclePhases& supportedCyclePhases)
{
    bool diff = false;

    for (size_t i=0 ; i < supportedCyclePhases.size() ; i++) {
        if (supportedCyclePhases[i] < MIN_ROBOT_CLEANING_VENDOR_DEFINED_CYCLE_PHASE
            && (supportedCyclePhases[i] < MIN_ROBOT_CLEANING_STANDARD_CYCLE_PHASE
                || supportedCyclePhases[i] > MAX_ROBOT_CLEANING_STANDARD_CYCLE_PHASE)) {
            QCC_LogError(ER_INVALID_DATA, ("%s: Unknown CyclePhase is included.", __func__));
            return ER_INVALID_DATA;
        }
    }

    if (m_supportedCyclePhases.size() != supportedCyclePhases.size()) {
        diff = true;
    } else {
        for (size_t i = 0; i < m_supportedCyclePhases.size(); i++)
        {
            if (m_supportedCyclePhases[i] != supportedCyclePhases[i])
            {
                diff = true;
                break;
            }
        }
    }

    if (diff) {
        MsgArg arg(ALLJOYN_ARRAY);
        size_t numElements = supportedCyclePhases.size();
        uint8_t* temp = new uint8_t[numElements];
        for (size_t i = 0; i < numElements; i++)
        {
            temp[i] =  supportedCyclePhases[i];
        }
        arg.Set("ay", numElements, temp);

        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_SupportedCyclePhases.c_str(), arg, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_supportedCyclePhases = supportedCyclePhases;
        delete[] temp;
    }

    return ER_OK;
}

void RobotCleaningCyclePhaseIntfControlleeImpl::OnGetVendorPhasesDescription(const InterfaceDescription::Member* member, Message& msg)
{
    QStatus status = ER_OK;
    const MsgArg* args = NULL;
    size_t numArgs = 0;

    msg->GetArgs(numArgs, args);

    if (numArgs == 1) {
        String languageTag = String(args[0].v_string.str);
        ErrorCode errorCode = NOT_ERROR;
        RobotCleaningCyclePhaseInterface::CyclePhaseDescriptors phasesDescription;

        status = m_interfaceListener.OnGetVendorPhasesDescription(languageTag, phasesDescription, errorCode);
        if (status == ER_OK) {
            int numReturned = phasesDescription.size();
            RobotCleaningCyclePhaseInterface::CyclePhaseDescriptors::const_iterator citer;
            MsgArg* args = new MsgArg[numReturned];
            MsgArg retArgs[1];
            int i = 0;

            for (citer = phasesDescription.begin(); citer != phasesDescription.end(); citer++, i++) {
                status = args[i].Set("(yss)", citer->phase, citer->name.c_str(), citer->description.c_str());
                args[i].Stabilize();
            }
            status = retArgs[0].Set("a(yss)", i, args);

            status = m_busObject.ReplyMethodCall(msg, retArgs, ArraySize(retArgs));
            delete[] args;
        } else {
            if (errorCode == NOT_ERROR) {
                QCC_LogError(status, ("%s: status is not ER_OK, but errorCode was not set.", __func__));
                m_busObject.ReplyMethodCall(msg, status);
            } else {
                m_busObject.ReplyMethodCall(msg, CdmInterface::GetInterfaceErrorName(errorCode).c_str(),
                                            CdmInterface::GetInterfaceErrorMessage(errorCode).c_str());
            }
        }
    } else {
        m_busObject.ReplyMethodCall(msg, ER_INVALID_DATA);
    }
}

} //namespace services
} //namespace ajn