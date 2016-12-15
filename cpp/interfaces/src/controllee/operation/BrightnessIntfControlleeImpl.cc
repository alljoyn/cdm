/******************************************************************************
 *  *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

// This file is automatically generated. Do not edit it.

#include <alljoyn/BusAttachment.h>

#include <alljoyn/cdm/common/LogModule.h>
#include <alljoyn/cdm/util/CdmMsgCvt.h>

#include <alljoyn/cdm/controllee/CdmBusObject.h>
#include <alljoyn/cdm/controllee/InterfaceReceiver.h>
#include <alljoyn/cdm/controllee/InterfaceControlleeModel.h>

#include <interfaces/controllee/operation/BrightnessIntfControllee.h>
#include <interfaces/controllee/operation/BrightnessIntfControlleeModel.h>


using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

/**
 * Brightness Interface Controllee implementation class
 */
class BrightnessIntfControllee::Impl :
    public InterfaceReceiver,
    public BrightnessInterface
{

  public:
    static Impl* CreateInterface(BusAttachment& busAttachment, Ref<BrightnessIntfControlleeModel> model, CdmBusObject& cdmBusObject);

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
    void OnMethodHandler(const InterfaceDescription::Member* member, Message& msg, CdmControllee& controllee) override;

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
     * Emits a changed signal for the Brightness property
     * @param[in] newValue new value of brightness
     * @return ER_OK on success
     */
    QStatus EmitBrightnessChanged(const double newValue);

  private:
    /**
     * Constructor of BrightnessIntfControllee::Impl
     */
    Impl(BusAttachment& busAttachment, Ref<BrightnessIntfControlleeModel> model, CdmBusObject& cdmBusObject);


    BusAttachment& m_busAttachment;
    Ref<BrightnessIntfControlleeModel> m_BrightnessModelInterface;

    MethodHandlers m_methodHandlers;
};

/*
 * Forwarding
 */
BrightnessIntfControllee::BrightnessIntfControllee(BusAttachment& busAttachment, Ref<InterfaceControlleeModel> model, CdmBusObject& cdmBusObject)
    : m_impl(Impl::CreateInterface(busAttachment, dynamic_pointer_cast<BrightnessIntfControlleeModel>(model), cdmBusObject))
{}


BrightnessIntfControllee::~BrightnessIntfControllee()
{
    delete m_impl;
}

const qcc::String& BrightnessIntfControllee::GetInterfaceName() const
{
    return m_impl->GetInterfaceName();
}

QStatus BrightnessIntfControllee::EmitBrightnessChanged(const double newValue)
{
    return (m_impl == nullptr) ? ER_FAIL : m_impl->EmitBrightnessChanged(newValue);
}


/*
 * Implementation
 */
 BrightnessIntfControllee::Impl* BrightnessIntfControllee::Impl::CreateInterface(
    BusAttachment& busAttachment,
    Ref<BrightnessIntfControlleeModel> model,
    CdmBusObject& cdmBusObject)
{
    BrightnessIntfControllee::Impl* interface = new BrightnessIntfControllee::Impl(busAttachment, model, cdmBusObject);

    QStatus status = interface->Init();
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: could not initialize interface", __func__));
        goto ERROR;
    }

    status = cdmBusObject.RegisterInterface(interface);
    if (status != ER_OK) {
        goto ERROR;
    }

    return interface;

ERROR:
    delete interface;
    return nullptr;
}

BrightnessIntfControllee::Impl::Impl(BusAttachment& busAttachment, Ref<BrightnessIntfControlleeModel> model, CdmBusObject& cdmBusObject) :
    InterfaceReceiver(cdmBusObject),
    m_busAttachment(busAttachment),
    m_BrightnessModelInterface(model),
    m_methodHandlers()
{}


QStatus BrightnessIntfControllee::Impl::Init()
{
    QStatus status = CdmInterface::Init();

    return status;
}

QStatus BrightnessIntfControllee::Impl::OnGetProperty(const String& propName, MsgArg& msgarg)
{
    if (!(s_prop_Version.compare(propName))) {
        msgarg.typeId = ALLJOYN_UINT16;
        msgarg.v_uint16 = GetInterfaceVersion();
        return ER_OK;
    } else {
        if (!(s_prop_Brightness.compare(propName))) {
            double value;
            auto status = m_BrightnessModelInterface->GetBrightness(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            {
                CdmMsgCvt<double> converter;
                converter.set(msgarg, value);
            }
            return ER_OK;
        } else {
            return ER_BUS_NO_SUCH_PROPERTY;
        }
    }
}

QStatus BrightnessIntfControllee::Impl::OnSetProperty(const String& propName, MsgArg& msgarg)
{
    if (!(s_prop_Brightness.compare(propName))) {
        if (msgarg.Signature() != "d") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        double value;
        {
            CdmMsgCvt<double> converter;
            converter.get(msgarg, value);
        }

        if (value > 1.0)
            return ER_BUS_PROPERTY_VALUE_NOT_SET;

        if (value < 0.0)
            return ER_BUS_PROPERTY_VALUE_NOT_SET;

        QStatus status;
        status = m_BrightnessModelInterface->SetBrightness(value);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: failed to set property value", __func__));
            return ER_BUS_PROPERTY_VALUE_NOT_SET;
        }

        EmitBrightnessChanged(value);

        return ER_OK;
    } else {
        return ER_BUS_NO_SUCH_PROPERTY;
    }
}

void BrightnessIntfControllee::Impl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg, CdmControllee& controllee)
{
    bool isFound = false;
    MethodHandlers::const_iterator it;
    for (it = m_methodHandlers.begin(); it != m_methodHandlers.end(); ++it) {
        if (it->first == member) {
            InterfaceReceiver::CdmMethodHandler handler = it->second;
            (this->*handler)(member, msg, controllee);
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

QStatus BrightnessIntfControllee::Impl::EmitBrightnessChanged(const double newValue)
{
    QStatus status = ER_OK;

    MsgArg val;
    {
        CdmMsgCvt<double> converter;
        converter.set(val, newValue);
    }
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_Brightness.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);

    return status;
}


} //namespace services
} //namespace ajn