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

#include <interfaces/controllee/operation/HvacFanModeIntfControllee.h>
#include <interfaces/controllee/operation/HvacFanModeIntfControlleeModel.h>


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
    static Impl* CreateInterface(BusAttachment& busAttachment, Ref<HvacFanModeIntfControlleeModel> model, CdmBusObject& cdmBusObject);

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
     * Emits a changed signal for the Mode property
     * @param[in] newValue new value of mode
     * @return ER_OK on success
     */
    QStatus EmitModeChanged(const Mode newValue);

    /**
     * Emits a changed signal for the SupportedModes property
     * @param[in] newValue new value of supported modes
     * @return ER_OK on success
     */
    QStatus EmitSupportedModesChanged(const std::vector<Mode> newValue);

  private:
    /**
     * Constructor of HvacFanModeIntfControllee::Impl
     */
    Impl(BusAttachment& busAttachment, Ref<HvacFanModeIntfControlleeModel> model, CdmBusObject& cdmBusObject);


    BusAttachment& m_busAttachment;
    Ref<HvacFanModeIntfControlleeModel> m_HvacFanModeModelInterface;

    MethodHandlers m_methodHandlers;
};

/*
 * Forwarding
 */
HvacFanModeIntfControllee::HvacFanModeIntfControllee(BusAttachment& busAttachment, Ref<InterfaceControlleeModel> model, CdmBusObject& cdmBusObject)
    : m_impl(Impl::CreateInterface(busAttachment, dynamic_pointer_cast<HvacFanModeIntfControlleeModel>(model), cdmBusObject))
{}


HvacFanModeIntfControllee::~HvacFanModeIntfControllee()
{
    delete m_impl;
}

const qcc::String& HvacFanModeIntfControllee::GetInterfaceName() const
{
    return m_impl->GetInterfaceName();
}

QStatus HvacFanModeIntfControllee::EmitModeChanged(const Mode newValue)
{
    return (m_impl == nullptr) ? ER_FAIL : m_impl->EmitModeChanged(newValue);
}

QStatus HvacFanModeIntfControllee::EmitSupportedModesChanged(const std::vector<Mode> newValue)
{
    return (m_impl == nullptr) ? ER_FAIL : m_impl->EmitSupportedModesChanged(newValue);
}


/*
 * Implementation
 */
 HvacFanModeIntfControllee::Impl* HvacFanModeIntfControllee::Impl::CreateInterface(
    BusAttachment& busAttachment,
    Ref<HvacFanModeIntfControlleeModel> model,
    CdmBusObject& cdmBusObject)
{
    HvacFanModeIntfControllee::Impl* interface = new HvacFanModeIntfControllee::Impl(busAttachment, model, cdmBusObject);

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

HvacFanModeIntfControllee::Impl::Impl(BusAttachment& busAttachment, Ref<HvacFanModeIntfControlleeModel> model, CdmBusObject& cdmBusObject) :
    InterfaceReceiver(cdmBusObject),
    m_busAttachment(busAttachment),
    m_HvacFanModeModelInterface(model),
    m_methodHandlers()
{}


QStatus HvacFanModeIntfControllee::Impl::Init()
{
    QStatus status = CdmInterface::Init();

    return status;
}

QStatus HvacFanModeIntfControllee::Impl::OnGetProperty(const String& propName, MsgArg& msgarg)
{
    QStatus status;

    if (!(s_prop_Version.compare(propName))) {
        msgarg.typeId = ALLJOYN_UINT16;
        msgarg.v_uint16 = GetInterfaceVersion();
        return ER_OK;
    } else {
        if (!(s_prop_Mode.compare(propName))) {
            Mode value;
            status = m_HvacFanModeModelInterface->GetMode(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            CdmMsgCvt<Mode> converter;
            converter.set(msgarg, value);
            return ER_OK;
        } else        if (!(s_prop_SupportedModes.compare(propName))) {
            std::vector<Mode> value;
            status = m_HvacFanModeModelInterface->GetSupportedModes(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            CdmMsgCvt<std::vector<Mode>> converter;
            converter.set(msgarg, value);
            return ER_OK;
        } else {
            return ER_BUS_NO_SUCH_PROPERTY;
        }
    }
}

QStatus HvacFanModeIntfControllee::Impl::OnSetProperty(const String& propName, MsgArg& msgarg)
{
    QStatus status;

    if (!(s_prop_Mode.compare(propName))) {
        if (msgarg.Signature() != "q") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        Mode value;
        CdmMsgCvt<Mode> converter;
        converter.get(msgarg, value);

        status = m_HvacFanModeModelInterface->SetMode(value);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: failed to set property value", __func__));
            return ER_BUS_PROPERTY_VALUE_NOT_SET;
        }

        EmitModeChanged(value);

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

void HvacFanModeIntfControllee::Impl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg, CdmSideEffects& sideEffects)
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

QStatus HvacFanModeIntfControllee::Impl::EmitModeChanged(const Mode newValue)
{
    QStatus status = ER_OK;

    MsgArg val;
    CdmMsgCvt<Mode> converter;
    converter.set(val, newValue);
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_Mode.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);

    return status;
}
QStatus HvacFanModeIntfControllee::Impl::EmitSupportedModesChanged(const std::vector<Mode> newValue)
{
    QStatus status = ER_OK;

    MsgArg val;
    CdmMsgCvt<std::vector<Mode>> converter;
    converter.set(val, newValue);
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_SupportedModes.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);

    return status;
}


} //namespace services
} //namespace ajn
