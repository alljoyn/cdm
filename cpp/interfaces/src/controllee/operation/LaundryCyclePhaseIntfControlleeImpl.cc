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

#include <alljoyn/BusAttachment.h>

#include <alljoyn/cdm/common/LogModule.h>
#include <alljoyn/cdm/util/CdmMsgCvt.h>

#include <alljoyn/cdm/controllee/CdmBusObject.h>
#include <alljoyn/cdm/controllee/InterfaceReceiver.h>
#include <alljoyn/cdm/controllee/InterfaceControlleeModel.h>

#include <interfaces/controllee/operation/LaundryCyclePhaseIntfControllee.h>
#include <interfaces/controllee/operation/LaundryCyclePhaseIntfControlleeModel.h>

#include <interfaces/controllee/CdmInterfaceValidation.h>


using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

/**
 * LaundryCyclePhase Interface Controllee implementation class
 */
class LaundryCyclePhaseIntfControllee::Impl :
    public InterfaceReceiver,
    public LaundryCyclePhaseInterface
{

  public:
    static Impl* CreateInterface(BusAttachment& busAttachment, Ref<LaundryCyclePhaseIntfControlleeModel> model, CdmBusObject& cdmBusObject, CdmControllee& cdmControllee);

    /**
     * Initialize interface
     * @return status
     */
    QStatus Init() override;

    /**
     * override the interfaces GetInterfaceName method
     * @return
     */
    const qcc::String& GetInterfaceName() const override { return InterfaceName; }

    /**
     * a callback function for getting property.
     * @param[in] propName   Identifies the property to get
     * @param[out] val   Returns the property value. The type of this value is the actual value type.
     * @return status
     */
    QStatus OnGetProperty(const qcc::String& propName, MsgArg& val) override;

    /**
     * a callback function for setting property.
     * @param[in] propName  Identifies the property to set
     * @param[in] val       The property value to set. The type of this value is the actual value type.
     */
    QStatus OnSetProperty(const qcc::String& propName, MsgArg& val) override;

    /**
     * method handler
     * @param[in] member    Method interface member entry.
     * @param[in] message   The received method call message.
     */
    void OnMethodHandler(const InterfaceDescription::Member* member, Message& msg) override;

    /**
     * Get method handlers
     * @return MethodHandlers
     */
    const MethodHandlers& GetMethodHanders() const override { return m_methodHandlers; }

    /**
     * Get bus attachment
     * @return bus attachment
     */
    BusAttachment& GetBusAttachment() const override { return m_busAttachment; }

    /**
     * Emits a changed signal for the CyclePhase property
     * @param[in] newValue new value of cycle phase
     * @return ER_OK on success
     */
    QStatus EmitCyclePhaseChanged(const uint8_t newValue);

    /**
     * Emits a changed signal for the SupportedCyclePhases property
     * @param[in] newValue new value of supported cycle phases
     * @return ER_OK on success
     */
    QStatus EmitSupportedCyclePhasesChanged(const std::vector<uint8_t>& newValue);

    /**
     * Handler of GetVendorPhasesDescription method
     * @param member
     * @param msg reference of alljoyn Message
     */
    void OnGetVendorPhasesDescription(const InterfaceDescription::Member* member, Message& msg);

  private:
    /**
     * Constructor of LaundryCyclePhaseIntfControllee::Impl
     */
    Impl(BusAttachment& busAttachment, Ref<LaundryCyclePhaseIntfControlleeModel> model, CdmBusObject& cdmBusObject, CdmControllee& cdmControllee);

    BusAttachment& m_busAttachment;
    CdmControllee& m_cdmControllee;
    MethodHandlers m_methodHandlers;

    Ref<LaundryCyclePhaseIntfControlleeModel> m_LaundryCyclePhaseModelInterface;
    qcc::String InterfaceName;
};

/*
 * Forwarding
 */
LaundryCyclePhaseIntfControllee::LaundryCyclePhaseIntfControllee(BusAttachment& busAttachment, Ref<InterfaceControlleeModel> model, CdmBusObject& cdmBusObject, CdmControllee& cdmControllee)
    : m_impl(Impl::CreateInterface(busAttachment, dynamic_pointer_cast<LaundryCyclePhaseIntfControlleeModel>(model), cdmBusObject, cdmControllee))
{}


LaundryCyclePhaseIntfControllee::~LaundryCyclePhaseIntfControllee()
{
    delete m_impl;
}

const qcc::String& LaundryCyclePhaseIntfControllee::GetInterfaceName() const
{
    return m_impl->GetInterfaceName();
}

QStatus LaundryCyclePhaseIntfControllee::EmitCyclePhaseChanged(const uint8_t newValue)
{
    return (m_impl == nullptr) ? ER_FAIL : m_impl->EmitCyclePhaseChanged(newValue);
}

QStatus LaundryCyclePhaseIntfControllee::EmitSupportedCyclePhasesChanged(const std::vector<uint8_t>& newValue)
{
    return (m_impl == nullptr) ? ER_FAIL : m_impl->EmitSupportedCyclePhasesChanged(newValue);
}


/*
 * Implementation
 */
 LaundryCyclePhaseIntfControllee::Impl* LaundryCyclePhaseIntfControllee::Impl::CreateInterface(
    BusAttachment& busAttachment,
    Ref<LaundryCyclePhaseIntfControlleeModel> model,
    CdmBusObject& cdmBusObject,
    CdmControllee& cdmControllee)
{
    LaundryCyclePhaseIntfControllee::Impl* interface = new LaundryCyclePhaseIntfControllee::Impl(busAttachment, model, cdmBusObject, cdmControllee);

    QStatus status = interface->Init();
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: could not initialize interface", __func__));
        goto ERROR_CLEANUP;
    }

    status = cdmBusObject.RegisterInterface(interface);
    if (status != ER_OK) {
        goto ERROR_CLEANUP;
    }

    return interface;

ERROR_CLEANUP:
    delete interface;
    return nullptr;
}

LaundryCyclePhaseIntfControllee::Impl::Impl(BusAttachment& busAttachment, Ref<LaundryCyclePhaseIntfControlleeModel> model, CdmBusObject& cdmBusObject, CdmControllee& cdmControllee) :
    InterfaceReceiver(cdmBusObject),
    m_busAttachment(busAttachment),
    m_cdmControllee(cdmControllee),
    m_methodHandlers(),
    m_LaundryCyclePhaseModelInterface(model),
    InterfaceName(LaundryCyclePhaseInterface::INTERFACE_NAME)
{
    ignore_unused(m_cdmControllee);
}


QStatus LaundryCyclePhaseIntfControllee::Impl::Init()
{
    QStatus status = CdmInterface::Init();

    const InterfaceDescription::Member* GetVendorPhasesDescriptionMember = m_interfaceDescription->GetMember(s_method_GetVendorPhasesDescription.c_str());
    InterfaceReceiver::CdmMethodHandler GetVendorPhasesDescriptionHandler = static_cast<InterfaceReceiver::CdmMethodHandler>(&Impl::OnGetVendorPhasesDescription);

    m_methodHandlers.push_back(make_pair(GetVendorPhasesDescriptionMember, GetVendorPhasesDescriptionHandler));

    return status;
}

QStatus LaundryCyclePhaseIntfControllee::Impl::OnGetProperty(const String& propName, MsgArg& msgarg)
{
    if (!(s_prop_Version.compare(propName))) {
        msgarg.typeId = ALLJOYN_UINT16;
        msgarg.v_uint16 = GetInterfaceVersion();
        return ER_OK;
    } else {
        if (!(s_prop_CyclePhase.compare(propName))) {
            uint8_t value;
            auto status = m_LaundryCyclePhaseModelInterface->GetCyclePhase(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            {
                CdmMsgCvt<uint8_t> converter;
                converter.set(msgarg, value);
            }
            return ER_OK;
        } else        if (!(s_prop_SupportedCyclePhases.compare(propName))) {
            std::vector<uint8_t> value;
            auto status = m_LaundryCyclePhaseModelInterface->GetSupportedCyclePhases(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            {
                CdmMsgCvt<std::vector<uint8_t>> converter;
                converter.set(msgarg, value);
            }
            return ER_OK;
        } else {
            return ER_BUS_NO_SUCH_PROPERTY;
        }
    }
}

QStatus LaundryCyclePhaseIntfControllee::Impl::OnSetProperty(const String& propName, MsgArg& msgarg)
{
    if (!(s_prop_CyclePhase.compare(propName))) {
        if (msgarg.Signature() != "y") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }
        return ER_BUS_PROPERTY_VALUE_NOT_SET;
    } else    if (!(s_prop_SupportedCyclePhases.compare(propName))) {
        if (msgarg.Signature() != "ay") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }
        return ER_BUS_PROPERTY_VALUE_NOT_SET;
    } else {
        return ER_BUS_NO_SUCH_PROPERTY;
    }
}

void LaundryCyclePhaseIntfControllee::Impl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
{
    bool isFound = false;
    MethodHandlers::const_iterator it;
    for (it = m_methodHandlers.begin(); it != m_methodHandlers.end(); ++it) {
        if (it->first == member) {
            InterfaceReceiver::CdmMethodHandler handler = it->second;
            (this->*handler)(member, msg);
            isFound = true;
            break;
        }
    }

    if (!isFound) {
        auto status = ER_BUS_METHOD_CALL_ABORTED;
        QCC_LogError(status, ("%s: could not find method handler.", __func__));
        m_busObject.ReplyMethodCall(msg, status);
    }
}

QStatus LaundryCyclePhaseIntfControllee::Impl::EmitCyclePhaseChanged(const uint8_t newValue)
{
    QStatus status = ER_OK;

    MsgArg val;
    {
        CdmMsgCvt<uint8_t> converter;
        converter.set(val, newValue);
    }
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_CyclePhase.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);

    return status;
}

QStatus LaundryCyclePhaseIntfControllee::Impl::EmitSupportedCyclePhasesChanged(const std::vector<uint8_t>& newValue)
{
    QStatus status = ER_OK;

    MsgArg val;
    {
        CdmMsgCvt<std::vector<uint8_t>> converter;
        converter.set(val, newValue);
    }
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_SupportedCyclePhases.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);

    return status;
}

void LaundryCyclePhaseIntfControllee::Impl::OnGetVendorPhasesDescription(const InterfaceDescription::Member* member, Message& msg) {
    const MsgArg* args = NULL;
    size_t numArgs = 0;

    msg->GetArgs(numArgs, args);

    qcc::String arg_languageTag;
    std::vector<LaundryCyclePhaseInterface::CyclePhaseDescriptor> arg_phasesDescription;

    {
        CdmMsgCvt<qcc::String> cvt;
        cvt.get(args[0], arg_languageTag);
    }

    ErrorCode errorCode = NOT_ERROR;
    auto status = m_LaundryCyclePhaseModelInterface->GetVendorPhasesDescription(arg_languageTag, arg_phasesDescription, errorCode, m_cdmControllee);

    // TODO this only allows one output arg
    MsgArg reply;
    CdmMsgCvt<std::vector<LaundryCyclePhaseInterface::CyclePhaseDescriptor>> replyCvt;
    replyCvt.set(reply, arg_phasesDescription);

    if (status == ER_OK) {
        m_busObject.ReplyMethodCall(msg, &reply, 1);
    } else {
        if (errorCode == NOT_ERROR) {
            QCC_LogError(status, ("%s: status is not ER_OK, but errorCode was not set.", __func__));
            m_busObject.ReplyMethodCall(msg, status);
        } else {
                m_busObject.ReplyMethodCall(msg, CdmInterface::GetInterfaceErrorName(errorCode).c_str(),
                        CdmInterface::GetInterfaceErrorMessage(errorCode).c_str());
        }
    }
}

} //namespace services
} //namespace ajn
