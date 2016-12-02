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

#include <interfaces/controllee/operation/AlertsIntfControllee.h>
#include <interfaces/controllee/operation/AlertsIntfControlleeModel.h>


using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

/**
 * Alerts Interface Controllee implementation class
 */
class AlertsIntfControllee::Impl :
    public InterfaceReceiver,
    public AlertsInterface
{

  public:
    static Impl* CreateInterface(BusAttachment& busAttachment, Ref<AlertsIntfControlleeModel> model, CdmBusObject& cdmBusObject);

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
     * Emits a changed signal for the Alerts property
     * @param[in] newValue new value of alerts
     * @return ER_OK on success
     */
    QStatus EmitAlertsChanged(const std::vector<AlertRecord> newValue);

    /**
     * Handler of GetAlertCodesDescription method
     * @param member
     * @param msg reference of alljoyn Message
     */
    void OnGetAlertCodesDescription(const InterfaceDescription::Member* member, Message& msg, CdmSideEffects& sideEffects);

    /**
     * Handler of AcknowledgeAlert method
     * @param member
     * @param msg reference of alljoyn Message
     */
    void OnAcknowledgeAlert(const InterfaceDescription::Member* member, Message& msg, CdmSideEffects& sideEffects);

    /**
     * Handler of AcknowledgeAllAlerts method
     * @param member
     * @param msg reference of alljoyn Message
     */
    void OnAcknowledgeAllAlerts(const InterfaceDescription::Member* member, Message& msg, CdmSideEffects& sideEffects);

  private:
    /**
     * Constructor of AlertsIntfControllee::Impl
     */
    Impl(BusAttachment& busAttachment, Ref<AlertsIntfControlleeModel> model, CdmBusObject& cdmBusObject);


    BusAttachment& m_busAttachment;
    Ref<AlertsIntfControlleeModel> m_AlertsModelInterface;

    MethodHandlers m_methodHandlers;
};

/*
 * Forwarding
 */
AlertsIntfControllee::AlertsIntfControllee(BusAttachment& busAttachment, Ref<InterfaceControlleeModel> model, CdmBusObject& cdmBusObject)
    : m_impl(Impl::CreateInterface(busAttachment, dynamic_pointer_cast<AlertsIntfControlleeModel>(model), cdmBusObject))
{}


AlertsIntfControllee::~AlertsIntfControllee()
{
    delete m_impl;
}

const qcc::String& AlertsIntfControllee::GetInterfaceName() const
{
    return m_impl->GetInterfaceName();
}

QStatus AlertsIntfControllee::EmitAlertsChanged(const std::vector<AlertRecord> newValue)
{
    return (m_impl == nullptr) ? ER_FAIL : m_impl->EmitAlertsChanged(newValue);
}


/*
 * Implementation
 */
 AlertsIntfControllee::Impl* AlertsIntfControllee::Impl::CreateInterface(
    BusAttachment& busAttachment,
    Ref<AlertsIntfControlleeModel> model,
    CdmBusObject& cdmBusObject)
{
    AlertsIntfControllee::Impl* interface = new AlertsIntfControllee::Impl(busAttachment, model, cdmBusObject);

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

AlertsIntfControllee::Impl::Impl(BusAttachment& busAttachment, Ref<AlertsIntfControlleeModel> model, CdmBusObject& cdmBusObject) :
    InterfaceReceiver(cdmBusObject),
    m_busAttachment(busAttachment),
    m_AlertsModelInterface(model),
    m_methodHandlers()
{}


QStatus AlertsIntfControllee::Impl::Init()
{
    QStatus status = CdmInterface::Init();

    const InterfaceDescription::Member* GetAlertCodesDescriptionMember = m_interfaceDescription->GetMember(s_method_GetAlertCodesDescription.c_str());
    InterfaceReceiver::CdmMethodHandler GetAlertCodesDescriptionHandler = static_cast<InterfaceReceiver::CdmMethodHandler>(&Impl::OnGetAlertCodesDescription);

    m_methodHandlers.push_back(make_pair(GetAlertCodesDescriptionMember, GetAlertCodesDescriptionHandler));

    const InterfaceDescription::Member* AcknowledgeAlertMember = m_interfaceDescription->GetMember(s_method_AcknowledgeAlert.c_str());
    InterfaceReceiver::CdmMethodHandler AcknowledgeAlertHandler = static_cast<InterfaceReceiver::CdmMethodHandler>(&Impl::OnAcknowledgeAlert);

    m_methodHandlers.push_back(make_pair(AcknowledgeAlertMember, AcknowledgeAlertHandler));

    const InterfaceDescription::Member* AcknowledgeAllAlertsMember = m_interfaceDescription->GetMember(s_method_AcknowledgeAllAlerts.c_str());
    InterfaceReceiver::CdmMethodHandler AcknowledgeAllAlertsHandler = static_cast<InterfaceReceiver::CdmMethodHandler>(&Impl::OnAcknowledgeAllAlerts);

    m_methodHandlers.push_back(make_pair(AcknowledgeAllAlertsMember, AcknowledgeAllAlertsHandler));

    return status;
}

QStatus AlertsIntfControllee::Impl::OnGetProperty(const String& propName, MsgArg& msgarg)
{
    QStatus status;

    if (!(s_prop_Version.compare(propName))) {
        msgarg.typeId = ALLJOYN_UINT16;
        msgarg.v_uint16 = GetInterfaceVersion();
        return ER_OK;
    } else {
        if (!(s_prop_Alerts.compare(propName))) {
            std::vector<AlertRecord> value;
            status = m_AlertsModelInterface->GetAlerts(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            {
                std::vector<MsgArg> array(value.size());
                for (auto& v : value) {
                    msgarg.Set("(yqb)", v.severity, v.alertCode, v.needAcknowledgement);
                }
                msgarg.Set("a(yqb)", array.size(), array.data());
                msgarg.Stabilize();
            }
            return ER_OK;
        } else {
            return ER_BUS_NO_SUCH_PROPERTY;
        }
    }
}

QStatus AlertsIntfControllee::Impl::OnSetProperty(const String& propName, MsgArg& msgarg)
{
    QStatus status;

    if (!(s_prop_Alerts.compare(propName))) {
        if (msgarg.Signature() != "a(yqb)") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        return ER_BUS_PROPERTY_VALUE_NOT_SET;
    } else {
        return ER_BUS_NO_SUCH_PROPERTY;
    }
}

void AlertsIntfControllee::Impl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg, CdmSideEffects& sideEffects)
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

QStatus AlertsIntfControllee::Impl::EmitAlertsChanged(const std::vector<AlertRecord> newValue)
{
    QStatus status = ER_OK;

    MsgArg val;
    {
        std::vector<MsgArg> array(newValue.size());
        for (auto& v : newValue) {
            val.Set("(yqb)", v.severity, v.alertCode, v.needAcknowledgement);
        }
        val.Set("a(yqb)", array.size(), array.data());
        val.Stabilize();
    }
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_Alerts.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);

    return status;
}

void AlertsIntfControllee::Impl::OnGetAlertCodesDescription(const InterfaceDescription::Member* member, Message& msg, CdmSideEffects& sideEffects) {
    QStatus status = ER_OK;
    const MsgArg* args = NULL;
    size_t numArgs = 0;

    msg->GetArgs(numArgs, args);

    qcc::String arg_languageTag;
    std::vector<AlertCodesDescriptor> arg_description;

    {
        CdmMsgCvt<qcc::String> cvt;
        cvt.get(args[0], arg_languageTag);
    }

    ErrorCode errorCode = NOT_ERROR;
    status = m_AlertsModelInterface->GetAlertCodesDescription(arg_languageTag, arg_description, errorCode, sideEffects);

    MsgArg reply;
    CdmMsgCvt<std::vector<AlertCodesDescriptor>> replyCvt;
    replyCvt.set(reply, arg_description);

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
void AlertsIntfControllee::Impl::OnAcknowledgeAlert(const InterfaceDescription::Member* member, Message& msg, CdmSideEffects& sideEffects) {
    QStatus status = ER_OK;
    const MsgArg* args = NULL;
    size_t numArgs = 0;

    msg->GetArgs(numArgs, args);

    uint16_t arg_alertCode;

    {
        CdmMsgCvt<uint16_t> cvt;
        cvt.get(args[0], arg_alertCode);
    }

    ErrorCode errorCode = NOT_ERROR;
    status = m_AlertsModelInterface->AcknowledgeAlert(arg_alertCode, errorCode, sideEffects);


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
void AlertsIntfControllee::Impl::OnAcknowledgeAllAlerts(const InterfaceDescription::Member* member, Message& msg, CdmSideEffects& sideEffects) {
    QStatus status = ER_OK;
    const MsgArg* args = NULL;
    size_t numArgs = 0;

    msg->GetArgs(numArgs, args);


    ErrorCode errorCode = NOT_ERROR;
    status = m_AlertsModelInterface->AcknowledgeAllAlerts(errorCode, sideEffects);


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
