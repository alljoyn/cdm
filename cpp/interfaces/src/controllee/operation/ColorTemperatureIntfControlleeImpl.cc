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

#include <interfaces/controllee/operation/ColorTemperatureIntfControllee.h>
#include <interfaces/controllee/operation/ColorTemperatureIntfControlleeModel.h>


using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

/**
 * ColorTemperature Interface Controllee implementation class
 */
class ColorTemperatureIntfControllee::Impl :
    public InterfaceReceiver,
    public ColorTemperatureInterface
{

  public:
    static Impl* CreateInterface(BusAttachment& busAttachment, Ref<ColorTemperatureIntfControlleeModel> model, CdmBusObject& cdmBusObject);

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
     * Emits a changed signal for the Temperature property
     * @param[in] newValue new value of temperature
     * @return ER_OK on success
     */
    QStatus EmitTemperatureChanged(const double newValue);

  private:
    /**
     * Constructor of ColorTemperatureIntfControllee::Impl
     */
    Impl(BusAttachment& busAttachment, Ref<ColorTemperatureIntfControlleeModel> model, CdmBusObject& cdmBusObject);


    BusAttachment& m_busAttachment;
    Ref<ColorTemperatureIntfControlleeModel> m_ColorTemperatureModelInterface;

    MethodHandlers m_methodHandlers;
};

/*
 * Forwarding
 */
ColorTemperatureIntfControllee::ColorTemperatureIntfControllee(BusAttachment& busAttachment, Ref<InterfaceControlleeModel> model, CdmBusObject& cdmBusObject)
    : m_impl(Impl::CreateInterface(busAttachment, dynamic_pointer_cast<ColorTemperatureIntfControlleeModel>(model), cdmBusObject))
{}


ColorTemperatureIntfControllee::~ColorTemperatureIntfControllee()
{
    delete m_impl;
}

const qcc::String& ColorTemperatureIntfControllee::GetInterfaceName() const
{
    return m_impl->GetInterfaceName();
}

QStatus ColorTemperatureIntfControllee::EmitTemperatureChanged(const double newValue)
{
    return (m_impl == nullptr) ? ER_FAIL : m_impl->EmitTemperatureChanged(newValue);
}


/*
 * Implementation
 */
 ColorTemperatureIntfControllee::Impl* ColorTemperatureIntfControllee::Impl::CreateInterface(
    BusAttachment& busAttachment,
    Ref<ColorTemperatureIntfControlleeModel> model,
    CdmBusObject& cdmBusObject)
{
    ColorTemperatureIntfControllee::Impl* interface = new ColorTemperatureIntfControllee::Impl(busAttachment, model, cdmBusObject);

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

ColorTemperatureIntfControllee::Impl::Impl(BusAttachment& busAttachment, Ref<ColorTemperatureIntfControlleeModel> model, CdmBusObject& cdmBusObject) :
    InterfaceReceiver(cdmBusObject),
    m_busAttachment(busAttachment),
    m_ColorTemperatureModelInterface(model),
    m_methodHandlers()
{}


QStatus ColorTemperatureIntfControllee::Impl::Init()
{
    QStatus status = CdmInterface::Init();

    return status;
}

QStatus ColorTemperatureIntfControllee::Impl::OnGetProperty(const String& propName, MsgArg& msgarg)
{
    QStatus status;

    if (!(s_prop_Version.compare(propName))) {
        msgarg.typeId = ALLJOYN_UINT16;
        msgarg.v_uint16 = GetInterfaceVersion();
        return ER_OK;
    } else {
        if (!(s_prop_Temperature.compare(propName))) {
            double value;
            status = m_ColorTemperatureModelInterface->GetTemperature(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            CdmMsgCvt<double> converter;
            converter.set(msgarg, value);
            return ER_OK;
        } else        if (!(s_prop_MinTemperature.compare(propName))) {
            double value;
            status = m_ColorTemperatureModelInterface->GetMinTemperature(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            CdmMsgCvt<double> converter;
            converter.set(msgarg, value);
            return ER_OK;
        } else        if (!(s_prop_MaxTemperature.compare(propName))) {
            double value;
            status = m_ColorTemperatureModelInterface->GetMaxTemperature(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            CdmMsgCvt<double> converter;
            converter.set(msgarg, value);
            return ER_OK;
        } else {
            return ER_BUS_NO_SUCH_PROPERTY;
        }
    }
}

QStatus ColorTemperatureIntfControllee::Impl::OnSetProperty(const String& propName, MsgArg& msgarg)
{
    QStatus status;

    if (!(s_prop_Temperature.compare(propName))) {
        if (msgarg.Signature() != "d") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        double value;
        CdmMsgCvt<double> converter;
        converter.get(msgarg, value);

        if (value < 0.0)
            return ER_BUS_PROPERTY_VALUE_NOT_SET;

        status = m_ColorTemperatureModelInterface->SetTemperature(value);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: failed to set property value", __func__));
            return ER_BUS_PROPERTY_VALUE_NOT_SET;
        }

        EmitTemperatureChanged(value);

        return ER_OK;
    } else    if (!(s_prop_MinTemperature.compare(propName))) {
        if (msgarg.Signature() != "d") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        return ER_BUS_PROPERTY_VALUE_NOT_SET;
    } else    if (!(s_prop_MaxTemperature.compare(propName))) {
        if (msgarg.Signature() != "d") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        return ER_BUS_PROPERTY_VALUE_NOT_SET;
    } else {
        return ER_BUS_NO_SUCH_PROPERTY;
    }
}

void ColorTemperatureIntfControllee::Impl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg, CdmSideEffects& sideEffects)
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

QStatus ColorTemperatureIntfControllee::Impl::EmitTemperatureChanged(const double newValue)
{
    QStatus status = ER_OK;

    MsgArg val;
    CdmMsgCvt<double> converter;
    converter.set(val, newValue);
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_Temperature.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);

    return status;
}


} //namespace services
} //namespace ajn
