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

#include <interfaces/controllee/operation/HvacFanModeIntfControllee.h>
#include <interfaces/controllee/operation/HvacFanModeIntfControlleeModel.h>

#include "../CdmInterfaceValidation.h"


using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

/**
 * HvacFanMode Interface Controllee implementation class
 */
class HvacFanModeIntfControllee::Impl :
    public InterfaceReceiver,
    public HvacFanModeInterface
{

  public:
    static Impl* CreateInterface(BusAttachment& busAttachment, Ref<HvacFanModeIntfControlleeModel> model, CdmBusObject& cdmBusObject, CdmControllee& cdmControllee);

    /**
     * Initialize interface
     * @return status
     */
    QStatus Init() override;

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
     * Emits a changed signal for the Mode property
     * @param[in] newValue new value of mode
     * @return ER_OK on success
     */
    QStatus EmitModeChanged(const HvacFanModeInterface::Mode newValue);

    /**
     * Emits a changed signal for the SupportedModes property
     * @param[in] newValue new value of supported modes
     * @return ER_OK on success
     */
    QStatus EmitSupportedModesChanged(const std::vector<HvacFanModeInterface::Mode>& newValue);

  private:
    /**
     * Constructor of HvacFanModeIntfControllee::Impl
     */
    Impl(BusAttachment& busAttachment, Ref<HvacFanModeIntfControlleeModel> model, CdmBusObject& cdmBusObject, CdmControllee& cdmControllee);

    QStatus ValidateMode(HvacFanModeInterface::Mode value);

    BusAttachment& m_busAttachment;
    CdmControllee& m_cdmControllee;
    MethodHandlers m_methodHandlers;

    Ref<HvacFanModeIntfControlleeModel> m_HvacFanModeModelInterface;
};

/*
 * Forwarding
 */
HvacFanModeIntfControllee::HvacFanModeIntfControllee(BusAttachment& busAttachment, Ref<InterfaceControlleeModel> model, CdmBusObject& cdmBusObject, CdmControllee& cdmControllee)
    : m_impl(Impl::CreateInterface(busAttachment, dynamic_pointer_cast<HvacFanModeIntfControlleeModel>(model), cdmBusObject, cdmControllee))
{}


HvacFanModeIntfControllee::~HvacFanModeIntfControllee()
{
    delete m_impl;
}

const qcc::String& HvacFanModeIntfControllee::GetInterfaceName() const
{
    return m_impl->GetInterfaceName();
}

QStatus HvacFanModeIntfControllee::EmitModeChanged(const HvacFanModeInterface::Mode newValue)
{
    return (m_impl == nullptr) ? ER_FAIL : m_impl->EmitModeChanged(newValue);
}

QStatus HvacFanModeIntfControllee::EmitSupportedModesChanged(const std::vector<HvacFanModeInterface::Mode>& newValue)
{
    return (m_impl == nullptr) ? ER_FAIL : m_impl->EmitSupportedModesChanged(newValue);
}


/*
 * Implementation
 */
 HvacFanModeIntfControllee::Impl* HvacFanModeIntfControllee::Impl::CreateInterface(
    BusAttachment& busAttachment,
    Ref<HvacFanModeIntfControlleeModel> model,
    CdmBusObject& cdmBusObject,
    CdmControllee& cdmControllee)
{
    HvacFanModeIntfControllee::Impl* interface = new HvacFanModeIntfControllee::Impl(busAttachment, model, cdmBusObject, cdmControllee);

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

HvacFanModeIntfControllee::Impl::Impl(BusAttachment& busAttachment, Ref<HvacFanModeIntfControlleeModel> model, CdmBusObject& cdmBusObject, CdmControllee& cdmControllee) :
    InterfaceReceiver(cdmBusObject),
    m_busAttachment(busAttachment),
    m_cdmControllee(cdmControllee),
    m_methodHandlers(),
    m_HvacFanModeModelInterface(model)
{
    ignore_unused(m_cdmControllee);
}


QStatus HvacFanModeIntfControllee::Impl::Init()
{
    QStatus status = CdmInterface::Init();

    return status;
}

QStatus HvacFanModeIntfControllee::Impl::OnGetProperty(const String& propName, MsgArg& msgarg)
{
    if (!(s_prop_Version.compare(propName))) {
        msgarg.typeId = ALLJOYN_UINT16;
        msgarg.v_uint16 = GetInterfaceVersion();
        return ER_OK;
    } else {
        if (!(s_prop_Mode.compare(propName))) {
            HvacFanModeInterface::Mode value;
            auto status = m_HvacFanModeModelInterface->GetMode(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            {
                CdmMsgCvt<HvacFanModeInterface::Mode> converter;
                converter.set(msgarg, value);
            }
            return ER_OK;
        } else        if (!(s_prop_SupportedModes.compare(propName))) {
            std::vector<HvacFanModeInterface::Mode> value;
            auto status = m_HvacFanModeModelInterface->GetSupportedModes(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            {
                CdmMsgCvt<std::vector<HvacFanModeInterface::Mode>> converter;
                converter.set(msgarg, value);
            }
            return ER_OK;
        } else {
            return ER_BUS_NO_SUCH_PROPERTY;
        }
    }
}

QStatus HvacFanModeIntfControllee::Impl::OnSetProperty(const String& propName, MsgArg& msgarg)
{
    if (!(s_prop_Mode.compare(propName))) {
        if (msgarg.Signature() != "q") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }
        HvacFanModeInterface::Mode value;
        {
            CdmMsgCvt<HvacFanModeInterface::Mode> converter;
            converter.get(msgarg, value);
        }

        HvacFanModeInterface::Mode validValue = value;

        if (ValidateMode(validValue) != ER_OK)
            return ER_INVALID_DATA;

        QStatus status = m_HvacFanModeModelInterface->SetMode(validValue);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: failed to set property value", __func__));
            return ER_BUS_PROPERTY_VALUE_NOT_SET;
        }

        if (m_cdmControllee.EmitChangedSignalOnSetProperty())
            EmitModeChanged(validValue);

        return ER_OK;
    } else    if (!(s_prop_SupportedModes.compare(propName))) {
        if (msgarg.Signature() != "aq") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }
        return ER_BUS_PROPERTY_VALUE_NOT_SET;
    } else {
        return ER_BUS_NO_SUCH_PROPERTY;
    }
}

void HvacFanModeIntfControllee::Impl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
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

QStatus HvacFanModeIntfControllee::Impl::EmitModeChanged(const HvacFanModeInterface::Mode newValue)
{
    QStatus status = ER_OK;

    MsgArg val;
    {
        CdmMsgCvt<HvacFanModeInterface::Mode> converter;
        converter.set(val, newValue);
    }
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_Mode.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);

    return status;
}

QStatus HvacFanModeIntfControllee::Impl::EmitSupportedModesChanged(const std::vector<HvacFanModeInterface::Mode>& newValue)
{
    QStatus status = ER_OK;

    MsgArg val;
    {
        CdmMsgCvt<std::vector<HvacFanModeInterface::Mode>> converter;
        converter.set(val, newValue);
    }
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_SupportedModes.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);

    return status;
}


QStatus HvacFanModeIntfControllee::Impl::ValidateMode(HvacFanModeInterface::Mode value)
{
    switch (value)
    {
        case HvacFanModeInterface::MODE_AUTO:
        case HvacFanModeInterface::MODE_CIRCULATION:
        case HvacFanModeInterface::MODE_CONTINUOUS:
            break;
        default:
            return ER_INVALID_DATA;
    }
    return ER_OK;
}

} //namespace services
} //namespace ajn
