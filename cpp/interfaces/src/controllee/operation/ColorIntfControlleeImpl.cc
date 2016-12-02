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

#include <interfaces/controllee/operation/ColorIntfControllee.h>
#include <interfaces/controllee/operation/ColorIntfControlleeModel.h>


using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

/**
 * Color Interface Controllee implementation class
 */
class ColorIntfControllee::Impl :
    public InterfaceReceiver,
    public ColorInterface
{

  public:
    static Impl* CreateInterface(BusAttachment& busAttachment, Ref<ColorIntfControlleeModel> model, CdmBusObject& cdmBusObject);

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
     * Emits a changed signal for the Hue property
     * @param[in] newValue new value of hue
     * @return ER_OK on success
     */
    QStatus EmitHueChanged(const double newValue);

    /**
     * Emits a changed signal for the Saturation property
     * @param[in] newValue new value of saturation
     * @return ER_OK on success
     */
    QStatus EmitSaturationChanged(const double newValue);

  private:
    /**
     * Constructor of ColorIntfControllee::Impl
     */
    Impl(BusAttachment& busAttachment, Ref<ColorIntfControlleeModel> model, CdmBusObject& cdmBusObject);


    BusAttachment& m_busAttachment;
    Ref<ColorIntfControlleeModel> m_ColorModelInterface;

    MethodHandlers m_methodHandlers;
};

/*
 * Forwarding
 */
ColorIntfControllee::ColorIntfControllee(BusAttachment& busAttachment, Ref<InterfaceControlleeModel> model, CdmBusObject& cdmBusObject)
    : m_impl(Impl::CreateInterface(busAttachment, dynamic_pointer_cast<ColorIntfControlleeModel>(model), cdmBusObject))
{}


ColorIntfControllee::~ColorIntfControllee()
{
    delete m_impl;
}

const qcc::String& ColorIntfControllee::GetInterfaceName() const
{
    return m_impl->GetInterfaceName();
}

QStatus ColorIntfControllee::EmitHueChanged(const double newValue)
{
    return (m_impl == nullptr) ? ER_FAIL : m_impl->EmitHueChanged(newValue);
}

QStatus ColorIntfControllee::EmitSaturationChanged(const double newValue)
{
    return (m_impl == nullptr) ? ER_FAIL : m_impl->EmitSaturationChanged(newValue);
}


/*
 * Implementation
 */
 ColorIntfControllee::Impl* ColorIntfControllee::Impl::CreateInterface(
    BusAttachment& busAttachment,
    Ref<ColorIntfControlleeModel> model,
    CdmBusObject& cdmBusObject)
{
    ColorIntfControllee::Impl* interface = new ColorIntfControllee::Impl(busAttachment, model, cdmBusObject);

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

ColorIntfControllee::Impl::Impl(BusAttachment& busAttachment, Ref<ColorIntfControlleeModel> model, CdmBusObject& cdmBusObject) :
    InterfaceReceiver(cdmBusObject),
    m_busAttachment(busAttachment),
    m_ColorModelInterface(model),
    m_methodHandlers()
{}


QStatus ColorIntfControllee::Impl::Init()
{
    QStatus status = CdmInterface::Init();

    return status;
}

QStatus ColorIntfControllee::Impl::OnGetProperty(const String& propName, MsgArg& msgarg)
{
    QStatus status;

    if (!(s_prop_Version.compare(propName))) {
        msgarg.typeId = ALLJOYN_UINT16;
        msgarg.v_uint16 = GetInterfaceVersion();
        return ER_OK;
    } else {
        if (!(s_prop_Hue.compare(propName))) {
            double value;
            status = m_ColorModelInterface->GetHue(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            CdmMsgCvt<double> converter;
            converter.set(msgarg, value);
            return ER_OK;
        } else        if (!(s_prop_Saturation.compare(propName))) {
            double value;
            status = m_ColorModelInterface->GetSaturation(value);
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

QStatus ColorIntfControllee::Impl::OnSetProperty(const String& propName, MsgArg& msgarg)
{
    QStatus status;

    if (!(s_prop_Hue.compare(propName))) {
        if (msgarg.Signature() != "d") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        double value;
        CdmMsgCvt<double> converter;
        converter.get(msgarg, value);

        if (value > 360.0)
            return ER_BUS_PROPERTY_VALUE_NOT_SET;

        if (value < 0.0)
            return ER_BUS_PROPERTY_VALUE_NOT_SET;

        status = m_ColorModelInterface->SetHue(value);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: failed to set property value", __func__));
            return ER_BUS_PROPERTY_VALUE_NOT_SET;
        }

        EmitHueChanged(value);

        return ER_OK;
    } else    if (!(s_prop_Saturation.compare(propName))) {
        if (msgarg.Signature() != "d") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        double value;
        CdmMsgCvt<double> converter;
        converter.get(msgarg, value);

        if (value > 1.0)
            return ER_BUS_PROPERTY_VALUE_NOT_SET;

        if (value < 0.0)
            return ER_BUS_PROPERTY_VALUE_NOT_SET;

        status = m_ColorModelInterface->SetSaturation(value);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: failed to set property value", __func__));
            return ER_BUS_PROPERTY_VALUE_NOT_SET;
        }

        EmitSaturationChanged(value);

        return ER_OK;
    } else {
        return ER_BUS_NO_SUCH_PROPERTY;
    }
}

void ColorIntfControllee::Impl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg, CdmSideEffects& sideEffects)
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

QStatus ColorIntfControllee::Impl::EmitHueChanged(const double newValue)
{
    QStatus status = ER_OK;

    MsgArg val;
    CdmMsgCvt<double> converter;
    converter.set(val, newValue);
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_Hue.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);

    return status;
}
QStatus ColorIntfControllee::Impl::EmitSaturationChanged(const double newValue)
{
    QStatus status = ER_OK;

    MsgArg val;
    CdmMsgCvt<double> converter;
    converter.set(val, newValue);
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_Saturation.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);

    return status;
}


} //namespace services
} //namespace ajn