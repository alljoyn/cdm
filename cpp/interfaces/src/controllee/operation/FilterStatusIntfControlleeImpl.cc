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

#include <alljoyn/BusAttachment.h>

#include <alljoyn/cdm/common/LogModule.h>
#include <alljoyn/cdm/util/CdmMsgCvt.h>

#include <alljoyn/cdm/controllee/CdmBusObject.h>
#include <alljoyn/cdm/controllee/InterfaceReceiver.h>
#include <alljoyn/cdm/controllee/InterfaceControlleeModel.h>

#include <interfaces/controllee/operation/FilterStatusIntfControllee.h>
#include <interfaces/controllee/operation/FilterStatusIntfControlleeModel.h>


using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

/**
 * FilterStatus Interface Controllee implementation class
 */
class FilterStatusIntfControllee::Impl :
    public InterfaceReceiver,
    public FilterStatusInterface
{

  public:
    static Impl* CreateInterface(BusAttachment& busAttachment, Ref<FilterStatusIntfControlleeModel> model, CdmBusObject& cdmBusObject);

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
    void OnMethodHandler(const InterfaceDescription::Member* member, Message& msg, CdmSideEffects& sideEffects) override;

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
     * Emits a changed signal for the ExpectedLifeInDays property
     * @param[in] newValue new value of expected life in days
     * @return ER_OK on success
     */
    QStatus EmitExpectedLifeInDaysChanged(const uint16_t newValue);

    /**
     * Emits a changed signal for the IsCleanable property
     * @param[in] newValue new value of is cleanable
     * @return ER_OK on success
     */
    QStatus EmitIsCleanableChanged(const bool newValue);

    /**
     * Emits a changed signal for the OrderPercentage property
     * @param[in] newValue new value of order percentage
     * @return ER_OK on success
     */
    QStatus EmitOrderPercentageChanged(const uint8_t newValue);

    /**
     * Emits a changed signal for the LifeRemaining property
     * @param[in] newValue new value of life remaining
     * @return ER_OK on success
     */
    QStatus EmitLifeRemainingChanged(const uint8_t newValue);

  private:
    /**
     * Constructor of FilterStatusIntfControllee::Impl
     */
    Impl(BusAttachment& busAttachment, Ref<FilterStatusIntfControlleeModel> model, CdmBusObject& cdmBusObject);


    BusAttachment& m_busAttachment;
    Ref<FilterStatusIntfControlleeModel> m_FilterStatusModelInterface;

    MethodHandlers m_methodHandlers;
};

/*
 * Forwarding
 */
FilterStatusIntfControllee::FilterStatusIntfControllee(BusAttachment& busAttachment, Ref<InterfaceControlleeModel> model, CdmBusObject& cdmBusObject)
    : m_impl(Impl::CreateInterface(busAttachment, dynamic_pointer_cast<FilterStatusIntfControlleeModel>(model), cdmBusObject))
{}


FilterStatusIntfControllee::~FilterStatusIntfControllee()
{
    delete m_impl;
}

const qcc::String& FilterStatusIntfControllee::GetInterfaceName() const
{
    return m_impl->GetInterfaceName();
}

QStatus FilterStatusIntfControllee::EmitExpectedLifeInDaysChanged(const uint16_t newValue)
{
    return (m_impl == nullptr) ? ER_FAIL : m_impl->EmitExpectedLifeInDaysChanged(newValue);
}

QStatus FilterStatusIntfControllee::EmitIsCleanableChanged(const bool newValue)
{
    return (m_impl == nullptr) ? ER_FAIL : m_impl->EmitIsCleanableChanged(newValue);
}

QStatus FilterStatusIntfControllee::EmitOrderPercentageChanged(const uint8_t newValue)
{
    return (m_impl == nullptr) ? ER_FAIL : m_impl->EmitOrderPercentageChanged(newValue);
}

QStatus FilterStatusIntfControllee::EmitLifeRemainingChanged(const uint8_t newValue)
{
    return (m_impl == nullptr) ? ER_FAIL : m_impl->EmitLifeRemainingChanged(newValue);
}


/*
 * Implementation
 */
 FilterStatusIntfControllee::Impl* FilterStatusIntfControllee::Impl::CreateInterface(
    BusAttachment& busAttachment,
    Ref<FilterStatusIntfControlleeModel> model,
    CdmBusObject& cdmBusObject)
{
    FilterStatusIntfControllee::Impl* interface = new FilterStatusIntfControllee::Impl(busAttachment, model, cdmBusObject);

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

FilterStatusIntfControllee::Impl::Impl(BusAttachment& busAttachment, Ref<FilterStatusIntfControlleeModel> model, CdmBusObject& cdmBusObject) :
    InterfaceReceiver(cdmBusObject),
    m_busAttachment(busAttachment),
    m_FilterStatusModelInterface(model),
    m_methodHandlers()
{}


QStatus FilterStatusIntfControllee::Impl::Init()
{
    QStatus status = CdmInterface::Init();

    return status;
}

QStatus FilterStatusIntfControllee::Impl::OnGetProperty(const String& propName, MsgArg& msgarg)
{
    QStatus status;

    if (!(s_prop_Version.compare(propName))) {
        msgarg.typeId = ALLJOYN_UINT16;
        msgarg.v_uint16 = GetInterfaceVersion();
        return ER_OK;
    } else {
        if (!(s_prop_ExpectedLifeInDays.compare(propName))) {
            uint16_t value;
            status = m_FilterStatusModelInterface->GetExpectedLifeInDays(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            CdmMsgCvt<uint16_t> converter;
            converter.set(msgarg, value);
            return ER_OK;
        } else        if (!(s_prop_IsCleanable.compare(propName))) {
            bool value;
            status = m_FilterStatusModelInterface->GetIsCleanable(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            CdmMsgCvt<bool> converter;
            converter.set(msgarg, value);
            return ER_OK;
        } else        if (!(s_prop_OrderPercentage.compare(propName))) {
            uint8_t value;
            status = m_FilterStatusModelInterface->GetOrderPercentage(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            CdmMsgCvt<uint8_t> converter;
            converter.set(msgarg, value);
            return ER_OK;
        } else        if (!(s_prop_Manufacturer.compare(propName))) {
            qcc::String value;
            status = m_FilterStatusModelInterface->GetManufacturer(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            CdmMsgCvt<qcc::String> converter;
            converter.set(msgarg, value);
            return ER_OK;
        } else        if (!(s_prop_PartNumber.compare(propName))) {
            qcc::String value;
            status = m_FilterStatusModelInterface->GetPartNumber(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            CdmMsgCvt<qcc::String> converter;
            converter.set(msgarg, value);
            return ER_OK;
        } else        if (!(s_prop_Url.compare(propName))) {
            qcc::String value;
            status = m_FilterStatusModelInterface->GetUrl(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            CdmMsgCvt<qcc::String> converter;
            converter.set(msgarg, value);
            return ER_OK;
        } else        if (!(s_prop_LifeRemaining.compare(propName))) {
            uint8_t value;
            status = m_FilterStatusModelInterface->GetLifeRemaining(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            CdmMsgCvt<uint8_t> converter;
            converter.set(msgarg, value);
            return ER_OK;
        } else {
            return ER_BUS_NO_SUCH_PROPERTY;
        }
    }
}

QStatus FilterStatusIntfControllee::Impl::OnSetProperty(const String& propName, MsgArg& msgarg)
{
    QStatus status;

    if (!(s_prop_ExpectedLifeInDays.compare(propName))) {
        if (msgarg.Signature() != "q") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        return ER_BUS_PROPERTY_VALUE_NOT_SET;
    } else    if (!(s_prop_IsCleanable.compare(propName))) {
        if (msgarg.Signature() != "b") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        return ER_BUS_PROPERTY_VALUE_NOT_SET;
    } else    if (!(s_prop_OrderPercentage.compare(propName))) {
        if (msgarg.Signature() != "y") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        return ER_BUS_PROPERTY_VALUE_NOT_SET;
    } else    if (!(s_prop_Manufacturer.compare(propName))) {
        if (msgarg.Signature() != "s") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        return ER_BUS_PROPERTY_VALUE_NOT_SET;
    } else    if (!(s_prop_PartNumber.compare(propName))) {
        if (msgarg.Signature() != "s") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        return ER_BUS_PROPERTY_VALUE_NOT_SET;
    } else    if (!(s_prop_Url.compare(propName))) {
        if (msgarg.Signature() != "s") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        return ER_BUS_PROPERTY_VALUE_NOT_SET;
    } else    if (!(s_prop_LifeRemaining.compare(propName))) {
        if (msgarg.Signature() != "y") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        return ER_BUS_PROPERTY_VALUE_NOT_SET;
    } else {
        return ER_BUS_NO_SUCH_PROPERTY;
    }
}

void FilterStatusIntfControllee::Impl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg, CdmSideEffects& sideEffects)
{
    QStatus status = ER_OK;
    bool isFound = false;
    MethodHandlers::const_iterator it;
    for (it = m_methodHandlers.begin(); it != m_methodHandlers.end(); ++it) {
        if (it->first == member) {
            InterfaceReceiver::CdmMethodHandler handler = it->second;
            (this->*handler)(member, msg, sideEffects);
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

QStatus FilterStatusIntfControllee::Impl::EmitExpectedLifeInDaysChanged(const uint16_t newValue)
{
    QStatus status = ER_OK;

    MsgArg val;
    CdmMsgCvt<uint16_t> converter;
    converter.set(val, newValue);
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_ExpectedLifeInDays.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);

    return status;
}
QStatus FilterStatusIntfControllee::Impl::EmitIsCleanableChanged(const bool newValue)
{
    QStatus status = ER_OK;

    MsgArg val;
    CdmMsgCvt<bool> converter;
    converter.set(val, newValue);
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_IsCleanable.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);

    return status;
}
QStatus FilterStatusIntfControllee::Impl::EmitOrderPercentageChanged(const uint8_t newValue)
{
    QStatus status = ER_OK;

    MsgArg val;
    CdmMsgCvt<uint8_t> converter;
    converter.set(val, newValue);
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_OrderPercentage.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);

    return status;
}
QStatus FilterStatusIntfControllee::Impl::EmitLifeRemainingChanged(const uint8_t newValue)
{
    QStatus status = ER_OK;

    MsgArg val;
    CdmMsgCvt<uint8_t> converter;
    converter.set(val, newValue);
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_LifeRemaining.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);

    return status;
}


} //namespace services
} //namespace ajn
