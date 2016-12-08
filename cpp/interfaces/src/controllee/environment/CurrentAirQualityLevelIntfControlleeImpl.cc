/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

// This file is automatically generated. Do not edit it.

#include <alljoyn/BusAttachment.h>

#include <alljoyn/cdm/common/LogModule.h>
#include <alljoyn/cdm/util/CdmMsgCvt.h>

#include <alljoyn/cdm/controllee/CdmBusObject.h>
#include <alljoyn/cdm/controllee/InterfaceReceiver.h>
#include <alljoyn/cdm/controllee/InterfaceControlleeModel.h>

#include <interfaces/controllee/environment/CurrentAirQualityLevelIntfControllee.h>
#include <interfaces/controllee/environment/CurrentAirQualityLevelIntfControlleeModel.h>


using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

/**
 * CurrentAirQualityLevel Interface Controllee implementation class
 */
class CurrentAirQualityLevelIntfControllee::Impl :
    public InterfaceReceiver,
    public CurrentAirQualityLevelInterface
{

  public:
    static Impl* CreateInterface(BusAttachment& busAttachment, Ref<CurrentAirQualityLevelIntfControlleeModel> model, CdmBusObject& cdmBusObject);

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
     * Emits a changed signal for the ContaminantType property
     * @param[in] newValue new value of contaminant type
     * @return ER_OK on success
     */
    QStatus EmitContaminantTypeChanged(const CurrentAirQualityLevelInterface::ContaminantType newValue);

    /**
     * Emits a changed signal for the CurrentLevel property
     * @param[in] newValue new value of current level
     * @return ER_OK on success
     */
    QStatus EmitCurrentLevelChanged(const uint8_t newValue);

    /**
     * Emits a changed signal for the MaxLevel property
     * @param[in] newValue new value of max level
     * @return ER_OK on success
     */
    QStatus EmitMaxLevelChanged(const uint8_t newValue);

  private:
    /**
     * Constructor of CurrentAirQualityLevelIntfControllee::Impl
     */
    Impl(BusAttachment& busAttachment, Ref<CurrentAirQualityLevelIntfControlleeModel> model, CdmBusObject& cdmBusObject);


    BusAttachment& m_busAttachment;
    Ref<CurrentAirQualityLevelIntfControlleeModel> m_CurrentAirQualityLevelModelInterface;

    MethodHandlers m_methodHandlers;
};

/*
 * Forwarding
 */
CurrentAirQualityLevelIntfControllee::CurrentAirQualityLevelIntfControllee(BusAttachment& busAttachment, Ref<InterfaceControlleeModel> model, CdmBusObject& cdmBusObject)
    : m_impl(Impl::CreateInterface(busAttachment, dynamic_pointer_cast<CurrentAirQualityLevelIntfControlleeModel>(model), cdmBusObject))
{}


CurrentAirQualityLevelIntfControllee::~CurrentAirQualityLevelIntfControllee()
{
    delete m_impl;
}

const qcc::String& CurrentAirQualityLevelIntfControllee::GetInterfaceName() const
{
    return m_impl->GetInterfaceName();
}

QStatus CurrentAirQualityLevelIntfControllee::EmitContaminantTypeChanged(const CurrentAirQualityLevelInterface::ContaminantType newValue)
{
    return (m_impl == nullptr) ? ER_FAIL : m_impl->EmitContaminantTypeChanged(newValue);
}

QStatus CurrentAirQualityLevelIntfControllee::EmitCurrentLevelChanged(const uint8_t newValue)
{
    return (m_impl == nullptr) ? ER_FAIL : m_impl->EmitCurrentLevelChanged(newValue);
}

QStatus CurrentAirQualityLevelIntfControllee::EmitMaxLevelChanged(const uint8_t newValue)
{
    return (m_impl == nullptr) ? ER_FAIL : m_impl->EmitMaxLevelChanged(newValue);
}


/*
 * Implementation
 */
 CurrentAirQualityLevelIntfControllee::Impl* CurrentAirQualityLevelIntfControllee::Impl::CreateInterface(
    BusAttachment& busAttachment,
    Ref<CurrentAirQualityLevelIntfControlleeModel> model,
    CdmBusObject& cdmBusObject)
{
    CurrentAirQualityLevelIntfControllee::Impl* interface = new CurrentAirQualityLevelIntfControllee::Impl(busAttachment, model, cdmBusObject);

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

CurrentAirQualityLevelIntfControllee::Impl::Impl(BusAttachment& busAttachment, Ref<CurrentAirQualityLevelIntfControlleeModel> model, CdmBusObject& cdmBusObject) :
    InterfaceReceiver(cdmBusObject),
    m_busAttachment(busAttachment),
    m_CurrentAirQualityLevelModelInterface(model),
    m_methodHandlers()
{}


QStatus CurrentAirQualityLevelIntfControllee::Impl::Init()
{
    QStatus status = CdmInterface::Init();

    return status;
}

QStatus CurrentAirQualityLevelIntfControllee::Impl::OnGetProperty(const String& propName, MsgArg& msgarg)
{
    if (!(s_prop_Version.compare(propName))) {
        msgarg.typeId = ALLJOYN_UINT16;
        msgarg.v_uint16 = GetInterfaceVersion();
        return ER_OK;
    } else {
        if (!(s_prop_ContaminantType.compare(propName))) {
            CurrentAirQualityLevelInterface::ContaminantType value;
            auto status = m_CurrentAirQualityLevelModelInterface->GetContaminantType(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            {
                CdmMsgCvt<CurrentAirQualityLevelInterface::ContaminantType> converter;
                converter.set(msgarg, value);
            }
            return ER_OK;
        } else        if (!(s_prop_CurrentLevel.compare(propName))) {
            uint8_t value;
            auto status = m_CurrentAirQualityLevelModelInterface->GetCurrentLevel(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            {
                CdmMsgCvt<uint8_t> converter;
                converter.set(msgarg, value);
            }
            return ER_OK;
        } else        if (!(s_prop_MaxLevel.compare(propName))) {
            uint8_t value;
            auto status = m_CurrentAirQualityLevelModelInterface->GetMaxLevel(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            {
                CdmMsgCvt<uint8_t> converter;
                converter.set(msgarg, value);
            }
            return ER_OK;
        } else {
            return ER_BUS_NO_SUCH_PROPERTY;
        }
    }
}

QStatus CurrentAirQualityLevelIntfControllee::Impl::OnSetProperty(const String& propName, MsgArg& msgarg)
{
    if (!(s_prop_ContaminantType.compare(propName))) {
        if (msgarg.Signature() != "y") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        return ER_BUS_PROPERTY_VALUE_NOT_SET;
    } else    if (!(s_prop_CurrentLevel.compare(propName))) {
        if (msgarg.Signature() != "y") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        return ER_BUS_PROPERTY_VALUE_NOT_SET;
    } else    if (!(s_prop_MaxLevel.compare(propName))) {
        if (msgarg.Signature() != "y") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        return ER_BUS_PROPERTY_VALUE_NOT_SET;
    } else {
        return ER_BUS_NO_SUCH_PROPERTY;
    }
}

void CurrentAirQualityLevelIntfControllee::Impl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg, CdmControllee& controllee)
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

QStatus CurrentAirQualityLevelIntfControllee::Impl::EmitContaminantTypeChanged(const CurrentAirQualityLevelInterface::ContaminantType newValue)
{
    QStatus status = ER_OK;

    MsgArg val;
    {
        CdmMsgCvt<CurrentAirQualityLevelInterface::ContaminantType> converter;
        converter.set(val, newValue);
    }
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_ContaminantType.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);

    return status;
}
QStatus CurrentAirQualityLevelIntfControllee::Impl::EmitCurrentLevelChanged(const uint8_t newValue)
{
    QStatus status = ER_OK;

    MsgArg val;
    {
        CdmMsgCvt<uint8_t> converter;
        converter.set(val, newValue);
    }
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_CurrentLevel.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);

    return status;
}
QStatus CurrentAirQualityLevelIntfControllee::Impl::EmitMaxLevelChanged(const uint8_t newValue)
{
    QStatus status = ER_OK;

    MsgArg val;
    {
        CdmMsgCvt<uint8_t> converter;
        converter.set(val, newValue);
    }
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_MaxLevel.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);

    return status;
}


} //namespace services
} //namespace ajn
