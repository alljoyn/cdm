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

#include <interfaces/controllee/operation/CycleControlIntfControllee.h>
#include <interfaces/controllee/operation/CycleControlIntfControlleeModel.h>


using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

/**
 * CycleControl Interface Controllee implementation class
 */
class CycleControlIntfControllee::Impl :
    public InterfaceReceiver,
    public CycleControlInterface
{

  public:
    static Impl* CreateInterface(BusAttachment& busAttachment, Ref<CycleControlIntfControlleeModel> model, CdmBusObject& cdmBusObject);

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
     * Emits a changed signal for the OperationalState property
     * @param[in] newValue new value of operational state
     * @return ER_OK on success
     */
    QStatus EmitOperationalStateChanged(const OperationalState newValue);

    /**
     * Handler of ExecuteOperationalCommand method
     * @param member
     * @param msg reference of alljoyn Message
     */
    void OnExecuteOperationalCommand(const InterfaceDescription::Member* member, Message& msg, CdmSideEffects& sideEffects);

  private:
    /**
     * Constructor of CycleControlIntfControllee::Impl
     */
    Impl(BusAttachment& busAttachment, Ref<CycleControlIntfControlleeModel> model, CdmBusObject& cdmBusObject);


    BusAttachment& m_busAttachment;
    Ref<CycleControlIntfControlleeModel> m_CycleControlModelInterface;

    MethodHandlers m_methodHandlers;
};

/*
 * Forwarding
 */
CycleControlIntfControllee::CycleControlIntfControllee(BusAttachment& busAttachment, Ref<InterfaceControlleeModel> model, CdmBusObject& cdmBusObject)
    : m_impl(Impl::CreateInterface(busAttachment, dynamic_pointer_cast<CycleControlIntfControlleeModel>(model), cdmBusObject))
{}


CycleControlIntfControllee::~CycleControlIntfControllee()
{
    delete m_impl;
}

const qcc::String& CycleControlIntfControllee::GetInterfaceName() const
{
    return m_impl->GetInterfaceName();
}

QStatus CycleControlIntfControllee::EmitOperationalStateChanged(const OperationalState newValue)
{
    return (m_impl == nullptr) ? ER_FAIL : m_impl->EmitOperationalStateChanged(newValue);
}


/*
 * Implementation
 */
 CycleControlIntfControllee::Impl* CycleControlIntfControllee::Impl::CreateInterface(
    BusAttachment& busAttachment,
    Ref<CycleControlIntfControlleeModel> model,
    CdmBusObject& cdmBusObject)
{
    CycleControlIntfControllee::Impl* interface = new CycleControlIntfControllee::Impl(busAttachment, model, cdmBusObject);

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

CycleControlIntfControllee::Impl::Impl(BusAttachment& busAttachment, Ref<CycleControlIntfControlleeModel> model, CdmBusObject& cdmBusObject) :
    InterfaceReceiver(cdmBusObject),
    m_busAttachment(busAttachment),
    m_CycleControlModelInterface(model),
    m_methodHandlers()
{}


QStatus CycleControlIntfControllee::Impl::Init()
{
    QStatus status = CdmInterface::Init();

    const InterfaceDescription::Member* ExecuteOperationalCommandMember = m_interfaceDescription->GetMember(s_method_ExecuteOperationalCommand.c_str());
    InterfaceReceiver::CdmMethodHandler ExecuteOperationalCommandHandler = static_cast<InterfaceReceiver::CdmMethodHandler>(&Impl::OnExecuteOperationalCommand);

    m_methodHandlers.push_back(make_pair(ExecuteOperationalCommandMember, ExecuteOperationalCommandHandler));

    return status;
}

QStatus CycleControlIntfControllee::Impl::OnGetProperty(const String& propName, MsgArg& msgarg)
{
    QStatus status;

    if (!(s_prop_Version.compare(propName))) {
        msgarg.typeId = ALLJOYN_UINT16;
        msgarg.v_uint16 = GetInterfaceVersion();
        return ER_OK;
    } else {
        if (!(s_prop_OperationalState.compare(propName))) {
            OperationalState value;
            status = m_CycleControlModelInterface->GetOperationalState(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            CdmMsgCvt<OperationalState> converter;
            converter.set(msgarg, value);
            return ER_OK;
        } else        if (!(s_prop_SupportedOperationalStates.compare(propName))) {
            std::vector<OperationalState> value;
            status = m_CycleControlModelInterface->GetSupportedOperationalStates(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            CdmMsgCvt<std::vector<OperationalState>> converter;
            converter.set(msgarg, value);
            return ER_OK;
        } else        if (!(s_prop_SupportedOperationalCommands.compare(propName))) {
            std::vector<OperationalCommands> value;
            status = m_CycleControlModelInterface->GetSupportedOperationalCommands(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            CdmMsgCvt<std::vector<OperationalCommands>> converter;
            converter.set(msgarg, value);
            return ER_OK;
        } else {
            return ER_BUS_NO_SUCH_PROPERTY;
        }
    }
}

QStatus CycleControlIntfControllee::Impl::OnSetProperty(const String& propName, MsgArg& msgarg)
{
    QStatus status;

    if (!(s_prop_OperationalState.compare(propName))) {
        if (msgarg.Signature() != "y") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        return ER_BUS_PROPERTY_VALUE_NOT_SET;
    } else    if (!(s_prop_SupportedOperationalStates.compare(propName))) {
        if (msgarg.Signature() != "ay") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        return ER_BUS_PROPERTY_VALUE_NOT_SET;
    } else    if (!(s_prop_SupportedOperationalCommands.compare(propName))) {
        if (msgarg.Signature() != "ay") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        return ER_BUS_PROPERTY_VALUE_NOT_SET;
    } else {
        return ER_BUS_NO_SUCH_PROPERTY;
    }
}

void CycleControlIntfControllee::Impl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg, CdmSideEffects& sideEffects)
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

QStatus CycleControlIntfControllee::Impl::EmitOperationalStateChanged(const OperationalState newValue)
{
    QStatus status = ER_OK;

    MsgArg val;
    CdmMsgCvt<OperationalState> converter;
    converter.set(val, newValue);
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_OperationalState.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);

    return status;
}

void CycleControlIntfControllee::Impl::OnExecuteOperationalCommand(const InterfaceDescription::Member* member, Message& msg, CdmSideEffects& sideEffects) {
    QStatus status = ER_OK;
    const MsgArg* args = NULL;
    size_t numArgs = 0;

    msg->GetArgs(numArgs, args);

    OperationalCommands arg_command;

    {
        CdmMsgCvt<OperationalCommands> cvt;
        cvt.get(args[0], arg_command);
    }

    ErrorCode errorCode = NOT_ERROR;
    status = m_CycleControlModelInterface->ExecuteOperationalCommand(arg_command, errorCode, sideEffects);


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
