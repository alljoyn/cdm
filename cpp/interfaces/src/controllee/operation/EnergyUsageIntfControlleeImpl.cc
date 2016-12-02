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

#include <interfaces/controllee/operation/EnergyUsageIntfControllee.h>
#include <interfaces/controllee/operation/EnergyUsageIntfControlleeModel.h>


using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

/**
 * EnergyUsage Interface Controllee implementation class
 */
class EnergyUsageIntfControllee::Impl :
    public InterfaceReceiver,
    public EnergyUsageInterface
{

  public:
    static Impl* CreateInterface(BusAttachment& busAttachment, Ref<EnergyUsageIntfControlleeModel> model, CdmBusObject& cdmBusObject);

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
     * Emits a changed signal for the CumulativeEnergy property
     * @param[in] newValue new value of cumulative energy
     * @return ER_OK on success
     */
    QStatus EmitCumulativeEnergyChanged(const double newValue);

    /**
     * Emits a changed signal for the Precision property
     * @param[in] newValue new value of precision
     * @return ER_OK on success
     */
    QStatus EmitPrecisionChanged(const double newValue);

    /**
     * Emits a changed signal for the UpdateMinTime property
     * @param[in] newValue new value of update min time
     * @return ER_OK on success
     */
    QStatus EmitUpdateMinTimeChanged(const uint16_t newValue);

    /**
     * Handler of ResetCumulativeEnergy method
     * @param member
     * @param msg reference of alljoyn Message
     */
    void OnResetCumulativeEnergy(const InterfaceDescription::Member* member, Message& msg, CdmSideEffects& sideEffects);

  private:
    /**
     * Constructor of EnergyUsageIntfControllee::Impl
     */
    Impl(BusAttachment& busAttachment, Ref<EnergyUsageIntfControlleeModel> model, CdmBusObject& cdmBusObject);


    BusAttachment& m_busAttachment;
    Ref<EnergyUsageIntfControlleeModel> m_EnergyUsageModelInterface;

    MethodHandlers m_methodHandlers;
};

/*
 * Forwarding
 */
EnergyUsageIntfControllee::EnergyUsageIntfControllee(BusAttachment& busAttachment, Ref<InterfaceControlleeModel> model, CdmBusObject& cdmBusObject)
    : m_impl(Impl::CreateInterface(busAttachment, dynamic_pointer_cast<EnergyUsageIntfControlleeModel>(model), cdmBusObject))
{}


EnergyUsageIntfControllee::~EnergyUsageIntfControllee()
{
    delete m_impl;
}

const qcc::String& EnergyUsageIntfControllee::GetInterfaceName() const
{
    return m_impl->GetInterfaceName();
}

QStatus EnergyUsageIntfControllee::EmitCumulativeEnergyChanged(const double newValue)
{
    return (m_impl == nullptr) ? ER_FAIL : m_impl->EmitCumulativeEnergyChanged(newValue);
}

QStatus EnergyUsageIntfControllee::EmitPrecisionChanged(const double newValue)
{
    return (m_impl == nullptr) ? ER_FAIL : m_impl->EmitPrecisionChanged(newValue);
}

QStatus EnergyUsageIntfControllee::EmitUpdateMinTimeChanged(const uint16_t newValue)
{
    return (m_impl == nullptr) ? ER_FAIL : m_impl->EmitUpdateMinTimeChanged(newValue);
}


/*
 * Implementation
 */
 EnergyUsageIntfControllee::Impl* EnergyUsageIntfControllee::Impl::CreateInterface(
    BusAttachment& busAttachment,
    Ref<EnergyUsageIntfControlleeModel> model,
    CdmBusObject& cdmBusObject)
{
    EnergyUsageIntfControllee::Impl* interface = new EnergyUsageIntfControllee::Impl(busAttachment, model, cdmBusObject);

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

EnergyUsageIntfControllee::Impl::Impl(BusAttachment& busAttachment, Ref<EnergyUsageIntfControlleeModel> model, CdmBusObject& cdmBusObject) :
    InterfaceReceiver(cdmBusObject),
    m_busAttachment(busAttachment),
    m_EnergyUsageModelInterface(model),
    m_methodHandlers()
{}


QStatus EnergyUsageIntfControllee::Impl::Init()
{
    QStatus status = CdmInterface::Init();

    const InterfaceDescription::Member* ResetCumulativeEnergyMember = m_interfaceDescription->GetMember(s_method_ResetCumulativeEnergy.c_str());
    InterfaceReceiver::CdmMethodHandler ResetCumulativeEnergyHandler = static_cast<InterfaceReceiver::CdmMethodHandler>(&Impl::OnResetCumulativeEnergy);

    m_methodHandlers.push_back(make_pair(ResetCumulativeEnergyMember, ResetCumulativeEnergyHandler));

    return status;
}

QStatus EnergyUsageIntfControllee::Impl::OnGetProperty(const String& propName, MsgArg& msgarg)
{
    QStatus status;

    if (!(s_prop_Version.compare(propName))) {
        msgarg.typeId = ALLJOYN_UINT16;
        msgarg.v_uint16 = GetInterfaceVersion();
        return ER_OK;
    } else {
        if (!(s_prop_CumulativeEnergy.compare(propName))) {
            double value;
            status = m_EnergyUsageModelInterface->GetCumulativeEnergy(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            CdmMsgCvt<double> converter;
            converter.set(msgarg, value);
            return ER_OK;
        } else        if (!(s_prop_Precision.compare(propName))) {
            double value;
            status = m_EnergyUsageModelInterface->GetPrecision(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            CdmMsgCvt<double> converter;
            converter.set(msgarg, value);
            return ER_OK;
        } else        if (!(s_prop_UpdateMinTime.compare(propName))) {
            uint16_t value;
            status = m_EnergyUsageModelInterface->GetUpdateMinTime(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            CdmMsgCvt<uint16_t> converter;
            converter.set(msgarg, value);
            return ER_OK;
        } else {
            return ER_BUS_NO_SUCH_PROPERTY;
        }
    }
}

QStatus EnergyUsageIntfControllee::Impl::OnSetProperty(const String& propName, MsgArg& msgarg)
{
    QStatus status;

    if (!(s_prop_CumulativeEnergy.compare(propName))) {
        if (msgarg.Signature() != "d") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        return ER_BUS_PROPERTY_VALUE_NOT_SET;
    } else    if (!(s_prop_Precision.compare(propName))) {
        if (msgarg.Signature() != "d") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        return ER_BUS_PROPERTY_VALUE_NOT_SET;
    } else    if (!(s_prop_UpdateMinTime.compare(propName))) {
        if (msgarg.Signature() != "q") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        return ER_BUS_PROPERTY_VALUE_NOT_SET;
    } else {
        return ER_BUS_NO_SUCH_PROPERTY;
    }
}

void EnergyUsageIntfControllee::Impl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg, CdmSideEffects& sideEffects)
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

QStatus EnergyUsageIntfControllee::Impl::EmitCumulativeEnergyChanged(const double newValue)
{
    QStatus status = ER_OK;

    MsgArg val;
    CdmMsgCvt<double> converter;
    converter.set(val, newValue);
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_CumulativeEnergy.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);

    return status;
}
QStatus EnergyUsageIntfControllee::Impl::EmitPrecisionChanged(const double newValue)
{
    QStatus status = ER_OK;

    MsgArg val;
    CdmMsgCvt<double> converter;
    converter.set(val, newValue);
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_Precision.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);

    return status;
}
QStatus EnergyUsageIntfControllee::Impl::EmitUpdateMinTimeChanged(const uint16_t newValue)
{
    QStatus status = ER_OK;

    MsgArg val;
    CdmMsgCvt<uint16_t> converter;
    converter.set(val, newValue);
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_UpdateMinTime.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);

    return status;
}

void EnergyUsageIntfControllee::Impl::OnResetCumulativeEnergy(const InterfaceDescription::Member* member, Message& msg, CdmSideEffects& sideEffects) {
    QStatus status = ER_OK;
    const MsgArg* args = NULL;
    size_t numArgs = 0;

    msg->GetArgs(numArgs, args);


    ErrorCode errorCode = NOT_ERROR;
    status = m_EnergyUsageModelInterface->ResetCumulativeEnergy(errorCode, sideEffects);


    if (status == ER_OK) {
        m_busObject.ReplyMethodCall(msg, status);
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