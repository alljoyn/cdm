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

// This file is automatically generated. Do not edit it.

#include <alljoyn/cdm/common/LogModule.h>
#include <alljoyn/cdm/common/CdmTypes.h>
#include <alljoyn/cdm/controller/InterfaceController.h>
#include <interfaces/controller/operation/RobotCleaningCyclePhaseIntfControllerListener.h>
#include <interfaces/controller/operation/RobotCleaningCyclePhaseIntfController.h>

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {
//======================================================================

typedef Ref<RobotCleaningCyclePhaseIntfControllerListener> MyInterfaceListener;


class RobotCleaningCyclePhaseIntfController::Impl : public InterfaceController
{
  public:

    Impl(
        RobotCleaningCyclePhaseIntfController& outer,
        BusAttachment& busAttachment,
        MyInterfaceListener listener,
        Ref<ProxyBusObject> proxyBusObject
        )
      : InterfaceController(proxyBusObject),
        m_outer(outer),
        m_busAttachment(busAttachment),
        m_interfaceListener(listener)
    {
    }

    QStatus Init();

    const char* GetInterfaceName() const
    {
        return INTERFACE_NAME;
    }

    QStatus GetCyclePhase(void* context);
    QStatus GetSupportedCyclePhases(void* context);

    virtual QStatus GetVendorPhasesDescription(const qcc::String& languageTag, void* context);

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);

    void GetCyclePhasePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetSupportedCyclePhasesPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    void GetVendorPhasesDescriptionReplyHandler(Message& message, void* context);


    // The outer facet
    RobotCleaningCyclePhaseIntfController& m_outer;

    // and inherit m_proxyObject from InterfaceController
    BusAttachment& m_busAttachment;
    MyInterfaceListener m_interfaceListener;
};

//======================================================================

QStatus RobotCleaningCyclePhaseIntfController::Impl::Init()
{
    auto status = m_proxyObject->RegisterPropertiesChangedListener(GetInterfaceName(), NULL, 0, *this, NULL);

    if (ER_OK != status) {
        QCC_LogError(status, ("%s: RegisterPropertiesChangedListener failed.", __func__));
    }

    const InterfaceDescription* intf = m_outer.GetInterfaceDescription();
    if (intf) {
    } else {
        status = ER_FAIL;
        QCC_LogError(status, ("%s: The interface description does not exist.", __func__));
    }

    return status;
}




QStatus RobotCleaningCyclePhaseIntfController::Impl::GetCyclePhase(void* context)
{
    auto status = m_proxyObject->GetPropertyAsync(GetInterfaceName(), s_prop_CyclePhase.c_str(), this,
                (ProxyBusObject::Listener::GetPropertyCB)&RobotCleaningCyclePhaseIntfController::Impl::GetCyclePhasePropertyCB, context);
    return status;
}

QStatus RobotCleaningCyclePhaseIntfController::Impl::GetSupportedCyclePhases(void* context)
{
    auto status = m_proxyObject->GetPropertyAsync(GetInterfaceName(), s_prop_SupportedCyclePhases.c_str(), this,
                (ProxyBusObject::Listener::GetPropertyCB)&RobotCleaningCyclePhaseIntfController::Impl::GetSupportedCyclePhasesPropertyCB, context);
    return status;
}



QStatus RobotCleaningCyclePhaseIntfController::Impl::GetVendorPhasesDescription(const qcc::String& languageTag, void* context)
{
    // Method call
    static const size_t numInputs = 1;
    MsgArg args[numInputs];

    {
        CdmMsgCvt<qcc::String> converter;
        converter.set(args[0], languageTag);
    }

    auto status = m_proxyObject->MethodCallAsync(GetInterfaceName(), s_method_GetVendorPhasesDescription.c_str(), this,
                (MessageReceiver::ReplyHandler)&RobotCleaningCyclePhaseIntfController::Impl::GetVendorPhasesDescriptionReplyHandler,
                args, numInputs, context);
    return status;
}



void RobotCleaningCyclePhaseIntfController::Impl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (s_prop_CyclePhase == propNameStr) {
            uint8_t val;
            {
                CdmMsgCvt<uint8_t> converter;
                converter.get((*propValue), val);
            }
            m_interfaceListener->OnCyclePhaseChanged(obj.GetPath(), val);
        } else if (s_prop_SupportedCyclePhases == propNameStr) {
            std::vector<uint8_t> val;
            {
                CdmMsgCvt<std::vector<uint8_t>> converter;
                converter.get((*propValue), val);
            }
            m_interfaceListener->OnSupportedCyclePhasesChanged(obj.GetPath(), val);
        } else {
            QCC_DbgTrace(("Unknown property change signal received"));
        }
    }
}

//======================================================================
// Callbacks


void RobotCleaningCyclePhaseIntfController::Impl::GetCyclePhasePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (obj) {
        uint8_t val;
        {
            CdmMsgCvt<uint8_t> converter;
            converter.get(value, val);
        }
        if (_QCC_DbgPrintCheck(DBG_GEN_MESSAGE, QCC_MODULE)) {
            auto s = CdmMsgCvt<uint8_t>().str(value);
            QCC_DbgPrintf(("%s: received property %s=%s", __func__, "CyclePhase", s.c_str()));
        }
        m_interfaceListener->OnResponseGetCyclePhase(status, obj->GetPath(), val, context);
    }
}




void RobotCleaningCyclePhaseIntfController::Impl::GetSupportedCyclePhasesPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (obj) {
        std::vector<uint8_t> val;
        {
            CdmMsgCvt<std::vector<uint8_t>> converter;
            converter.get(value, val);
        }
        if (_QCC_DbgPrintCheck(DBG_GEN_MESSAGE, QCC_MODULE)) {
            auto s = CdmMsgCvt<std::vector<uint8_t>>().str(value);
            QCC_DbgPrintf(("%s: received property %s=%s", __func__, "SupportedCyclePhases", s.c_str()));
        }
        m_interfaceListener->OnResponseGetSupportedCyclePhases(status, obj->GetPath(), val, context);
    }
}






void RobotCleaningCyclePhaseIntfController::Impl::GetVendorPhasesDescriptionReplyHandler(Message& message, void* context)
{
    qcc::String errorMessage;
    const char* errorName = message->GetErrorName(&errorMessage);
    QStatus status = ER_OK;
    size_t numArgs = 0;
    const MsgArg* args = 0;

    std::vector<RobotCleaningCyclePhaseInterface::CyclePhaseDescriptor> arg_phasesDescription;

    if (message->GetType() == MESSAGE_METHOD_RET) {
        message->GetArgs(numArgs, args);
        CdmMsgCvt<std::vector<RobotCleaningCyclePhaseInterface::CyclePhaseDescriptor>> cvt_phasesDescription;
        cvt_phasesDescription.get(args[0], arg_phasesDescription);

        if (_QCC_DbgPrintCheck(DBG_GEN_MESSAGE, QCC_MODULE)) {
            auto s = cvt_phasesDescription.str(args[0]);
            QCC_DbgPrintf(("%s: received reply with %s=%s", __func__, "phasesDescription", s.c_str()));
        }
    } else {
        status = ER_FAIL;
    }

    m_interfaceListener->OnResponseGetVendorPhasesDescription(status, m_proxyObject->GetPath(), arg_phasesDescription, context, errorName, errorMessage.c_str());
}

//======================================================================
// Forward to the impl

RobotCleaningCyclePhaseIntfController::RobotCleaningCyclePhaseIntfController(
    BusAttachment& busAttachment,
    Ref<InterfaceControllerListener> listener,
    Ref<ProxyBusObject> cdmProxyObject
    )
  : m_impl(new Impl(*this, busAttachment, dynamic_pointer_cast<RobotCleaningCyclePhaseIntfControllerListener>(listener), cdmProxyObject))
{
}



RobotCleaningCyclePhaseIntfController::~RobotCleaningCyclePhaseIntfController()
{
    delete m_impl;
}



Ref<CdmInterface> RobotCleaningCyclePhaseIntfController::CreateInterface(BusAttachment& busAttachment, Ref<InterfaceControllerListener> listener, Ref<ProxyBusObject> cdmProxyObject)
{
    return mkRef<RobotCleaningCyclePhaseIntfController>(busAttachment, dynamic_pointer_cast<RobotCleaningCyclePhaseIntfControllerListener>(listener), cdmProxyObject);
}



QStatus RobotCleaningCyclePhaseIntfController::Init()
{
    // Call the superclass Init
    QStatus status = CdmInterface::Init();
    if (ER_OK != status) {
        QCC_LogError(status, ("%s: Interface init failed.", __func__));
        return status;
    }

    return m_impl->Init();
}



BusAttachment& RobotCleaningCyclePhaseIntfController::GetBusAttachment() const
{
    return m_impl->m_busAttachment;
}



QStatus RobotCleaningCyclePhaseIntfController::GetCyclePhase(void* context)
{
    return m_impl->GetCyclePhase(context);
}



QStatus RobotCleaningCyclePhaseIntfController::GetSupportedCyclePhases(void* context)
{
    return m_impl->GetSupportedCyclePhases(context);
}



QStatus RobotCleaningCyclePhaseIntfController::GetVendorPhasesDescription(const qcc::String& languageTag, void* context)
{
    return m_impl->GetVendorPhasesDescription(languageTag, context);
}

//======================================================================
} //namespace services
} //namespace ajn
