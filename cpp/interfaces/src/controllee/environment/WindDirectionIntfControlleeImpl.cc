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

#include <interfaces/controllee/environment/WindDirectionIntfControllee.h>
#include <interfaces/controllee/environment/WindDirectionIntfControlleeModel.h>


using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

/**
 * WindDirection Interface Controllee implementation class
 */
class WindDirectionIntfControllee::Impl :
    public InterfaceReceiver,
    public WindDirectionInterface
{

  public:
    static Impl* CreateInterface(BusAttachment& busAttachment, Ref<WindDirectionIntfControlleeModel> model, CdmBusObject& cdmBusObject);

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
     * Emits a changed signal for the HorizontalDirection property
     * @param[in] newValue new value of horizontal direction
     * @return ER_OK on success
     */
    QStatus EmitHorizontalDirectionChanged(const uint16_t newValue);

    /**
     * Emits a changed signal for the HorizontalMax property
     * @param[in] newValue new value of horizontal max
     * @return ER_OK on success
     */
    QStatus EmitHorizontalMaxChanged(const uint16_t newValue);

    /**
     * Emits a changed signal for the HorizontalAutoMode property
     * @param[in] newValue new value of horizontal auto mode
     * @return ER_OK on success
     */
    QStatus EmitHorizontalAutoModeChanged(const WindDirectionInterface::AutoMode newValue);

    /**
     * Emits a changed signal for the VerticalDirection property
     * @param[in] newValue new value of vertical direction
     * @return ER_OK on success
     */
    QStatus EmitVerticalDirectionChanged(const uint16_t newValue);

    /**
     * Emits a changed signal for the VerticalMax property
     * @param[in] newValue new value of vertical max
     * @return ER_OK on success
     */
    QStatus EmitVerticalMaxChanged(const uint16_t newValue);

    /**
     * Emits a changed signal for the VerticalAutoMode property
     * @param[in] newValue new value of vertical auto mode
     * @return ER_OK on success
     */
    QStatus EmitVerticalAutoModeChanged(const WindDirectionInterface::AutoMode newValue);

  private:
    /**
     * Constructor of WindDirectionIntfControllee::Impl
     */
    Impl(BusAttachment& busAttachment, Ref<WindDirectionIntfControlleeModel> model, CdmBusObject& cdmBusObject);


    BusAttachment& m_busAttachment;
    Ref<WindDirectionIntfControlleeModel> m_WindDirectionModelInterface;

    MethodHandlers m_methodHandlers;
};

/*
 * Forwarding
 */
WindDirectionIntfControllee::WindDirectionIntfControllee(BusAttachment& busAttachment, Ref<InterfaceControlleeModel> model, CdmBusObject& cdmBusObject)
    : m_impl(Impl::CreateInterface(busAttachment, dynamic_pointer_cast<WindDirectionIntfControlleeModel>(model), cdmBusObject))
{}


WindDirectionIntfControllee::~WindDirectionIntfControllee()
{
    delete m_impl;
}

const qcc::String& WindDirectionIntfControllee::GetInterfaceName() const
{
    return m_impl->GetInterfaceName();
}

QStatus WindDirectionIntfControllee::EmitHorizontalDirectionChanged(const uint16_t newValue)
{
    return (m_impl == nullptr) ? ER_FAIL : m_impl->EmitHorizontalDirectionChanged(newValue);
}

QStatus WindDirectionIntfControllee::EmitHorizontalMaxChanged(const uint16_t newValue)
{
    return (m_impl == nullptr) ? ER_FAIL : m_impl->EmitHorizontalMaxChanged(newValue);
}

QStatus WindDirectionIntfControllee::EmitHorizontalAutoModeChanged(const WindDirectionInterface::AutoMode newValue)
{
    return (m_impl == nullptr) ? ER_FAIL : m_impl->EmitHorizontalAutoModeChanged(newValue);
}

QStatus WindDirectionIntfControllee::EmitVerticalDirectionChanged(const uint16_t newValue)
{
    return (m_impl == nullptr) ? ER_FAIL : m_impl->EmitVerticalDirectionChanged(newValue);
}

QStatus WindDirectionIntfControllee::EmitVerticalMaxChanged(const uint16_t newValue)
{
    return (m_impl == nullptr) ? ER_FAIL : m_impl->EmitVerticalMaxChanged(newValue);
}

QStatus WindDirectionIntfControllee::EmitVerticalAutoModeChanged(const WindDirectionInterface::AutoMode newValue)
{
    return (m_impl == nullptr) ? ER_FAIL : m_impl->EmitVerticalAutoModeChanged(newValue);
}


/*
 * Implementation
 */
 WindDirectionIntfControllee::Impl* WindDirectionIntfControllee::Impl::CreateInterface(
    BusAttachment& busAttachment,
    Ref<WindDirectionIntfControlleeModel> model,
    CdmBusObject& cdmBusObject)
{
    WindDirectionIntfControllee::Impl* interface = new WindDirectionIntfControllee::Impl(busAttachment, model, cdmBusObject);

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

WindDirectionIntfControllee::Impl::Impl(BusAttachment& busAttachment, Ref<WindDirectionIntfControlleeModel> model, CdmBusObject& cdmBusObject) :
    InterfaceReceiver(cdmBusObject),
    m_busAttachment(busAttachment),
    m_WindDirectionModelInterface(model),
    m_methodHandlers()
{}


QStatus WindDirectionIntfControllee::Impl::Init()
{
    QStatus status = CdmInterface::Init();

    return status;
}

QStatus WindDirectionIntfControllee::Impl::OnGetProperty(const String& propName, MsgArg& msgarg)
{
    if (!(s_prop_Version.compare(propName))) {
        msgarg.typeId = ALLJOYN_UINT16;
        msgarg.v_uint16 = GetInterfaceVersion();
        return ER_OK;
    } else {
        if (!(s_prop_HorizontalDirection.compare(propName))) {
            uint16_t value;
            auto status = m_WindDirectionModelInterface->GetHorizontalDirection(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            {
                CdmMsgCvt<uint16_t> converter;
                converter.set(msgarg, value);
            }
            return ER_OK;
        } else        if (!(s_prop_HorizontalMax.compare(propName))) {
            uint16_t value;
            auto status = m_WindDirectionModelInterface->GetHorizontalMax(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            {
                CdmMsgCvt<uint16_t> converter;
                converter.set(msgarg, value);
            }
            return ER_OK;
        } else        if (!(s_prop_HorizontalAutoMode.compare(propName))) {
            WindDirectionInterface::AutoMode value;
            auto status = m_WindDirectionModelInterface->GetHorizontalAutoMode(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            {
                CdmMsgCvt<WindDirectionInterface::AutoMode> converter;
                converter.set(msgarg, value);
            }
            return ER_OK;
        } else        if (!(s_prop_VerticalDirection.compare(propName))) {
            uint16_t value;
            auto status = m_WindDirectionModelInterface->GetVerticalDirection(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            {
                CdmMsgCvt<uint16_t> converter;
                converter.set(msgarg, value);
            }
            return ER_OK;
        } else        if (!(s_prop_VerticalMax.compare(propName))) {
            uint16_t value;
            auto status = m_WindDirectionModelInterface->GetVerticalMax(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            {
                CdmMsgCvt<uint16_t> converter;
                converter.set(msgarg, value);
            }
            return ER_OK;
        } else        if (!(s_prop_VerticalAutoMode.compare(propName))) {
            WindDirectionInterface::AutoMode value;
            auto status = m_WindDirectionModelInterface->GetVerticalAutoMode(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            {
                CdmMsgCvt<WindDirectionInterface::AutoMode> converter;
                converter.set(msgarg, value);
            }
            return ER_OK;
        } else {
            return ER_BUS_NO_SUCH_PROPERTY;
        }
    }
}

QStatus WindDirectionIntfControllee::Impl::OnSetProperty(const String& propName, MsgArg& msgarg)
{
    if (!(s_prop_HorizontalDirection.compare(propName))) {
        if (msgarg.Signature() != "q") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        uint16_t value;
        {
            CdmMsgCvt<uint16_t> converter;
            converter.get(msgarg, value);
        }

        QStatus status;
        status = m_WindDirectionModelInterface->SetHorizontalDirection(value);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: failed to set property value", __func__));
            return ER_BUS_PROPERTY_VALUE_NOT_SET;
        }

        EmitHorizontalDirectionChanged(value);

        return ER_OK;
    } else    if (!(s_prop_HorizontalMax.compare(propName))) {
        if (msgarg.Signature() != "q") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        return ER_BUS_PROPERTY_VALUE_NOT_SET;
    } else    if (!(s_prop_HorizontalAutoMode.compare(propName))) {
        if (msgarg.Signature() != "y") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        WindDirectionInterface::AutoMode value;
        {
            CdmMsgCvt<WindDirectionInterface::AutoMode> converter;
            converter.get(msgarg, value);
        }

        QStatus status;
        status = m_WindDirectionModelInterface->SetHorizontalAutoMode(value);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: failed to set property value", __func__));
            return ER_BUS_PROPERTY_VALUE_NOT_SET;
        }

        EmitHorizontalAutoModeChanged(value);

        return ER_OK;
    } else    if (!(s_prop_VerticalDirection.compare(propName))) {
        if (msgarg.Signature() != "q") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        uint16_t value;
        {
            CdmMsgCvt<uint16_t> converter;
            converter.get(msgarg, value);
        }

        QStatus status;
        status = m_WindDirectionModelInterface->SetVerticalDirection(value);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: failed to set property value", __func__));
            return ER_BUS_PROPERTY_VALUE_NOT_SET;
        }

        EmitVerticalDirectionChanged(value);

        return ER_OK;
    } else    if (!(s_prop_VerticalMax.compare(propName))) {
        if (msgarg.Signature() != "q") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        return ER_BUS_PROPERTY_VALUE_NOT_SET;
    } else    if (!(s_prop_VerticalAutoMode.compare(propName))) {
        if (msgarg.Signature() != "y") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        WindDirectionInterface::AutoMode value;
        {
            CdmMsgCvt<WindDirectionInterface::AutoMode> converter;
            converter.get(msgarg, value);
        }

        QStatus status;
        status = m_WindDirectionModelInterface->SetVerticalAutoMode(value);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: failed to set property value", __func__));
            return ER_BUS_PROPERTY_VALUE_NOT_SET;
        }

        EmitVerticalAutoModeChanged(value);

        return ER_OK;
    } else {
        return ER_BUS_NO_SUCH_PROPERTY;
    }
}

void WindDirectionIntfControllee::Impl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg, CdmControllee& controllee)
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

QStatus WindDirectionIntfControllee::Impl::EmitHorizontalDirectionChanged(const uint16_t newValue)
{
    QStatus status = ER_OK;

    MsgArg val;
    {
        CdmMsgCvt<uint16_t> converter;
        converter.set(val, newValue);
    }
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_HorizontalDirection.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);

    return status;
}
QStatus WindDirectionIntfControllee::Impl::EmitHorizontalMaxChanged(const uint16_t newValue)
{
    QStatus status = ER_OK;

    MsgArg val;
    {
        CdmMsgCvt<uint16_t> converter;
        converter.set(val, newValue);
    }
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_HorizontalMax.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);

    return status;
}
QStatus WindDirectionIntfControllee::Impl::EmitHorizontalAutoModeChanged(const WindDirectionInterface::AutoMode newValue)
{
    QStatus status = ER_OK;

    MsgArg val;
    {
        CdmMsgCvt<WindDirectionInterface::AutoMode> converter;
        converter.set(val, newValue);
    }
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_HorizontalAutoMode.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);

    return status;
}
QStatus WindDirectionIntfControllee::Impl::EmitVerticalDirectionChanged(const uint16_t newValue)
{
    QStatus status = ER_OK;

    MsgArg val;
    {
        CdmMsgCvt<uint16_t> converter;
        converter.set(val, newValue);
    }
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_VerticalDirection.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);

    return status;
}
QStatus WindDirectionIntfControllee::Impl::EmitVerticalMaxChanged(const uint16_t newValue)
{
    QStatus status = ER_OK;

    MsgArg val;
    {
        CdmMsgCvt<uint16_t> converter;
        converter.set(val, newValue);
    }
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_VerticalMax.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);

    return status;
}
QStatus WindDirectionIntfControllee::Impl::EmitVerticalAutoModeChanged(const WindDirectionInterface::AutoMode newValue)
{
    QStatus status = ER_OK;

    MsgArg val;
    {
        CdmMsgCvt<WindDirectionInterface::AutoMode> converter;
        converter.set(val, newValue);
    }
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_VerticalAutoMode.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);

    return status;
}


} //namespace services
} //namespace ajn