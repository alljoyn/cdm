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

#include <interfaces/controllee/operation/TimerIntfControllee.h>
#include <interfaces/controllee/operation/TimerIntfControlleeModel.h>


using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

/**
 * Timer Interface Controllee implementation class
 */
class TimerIntfControllee::Impl :
    public InterfaceReceiver,
    public TimerInterface
{

  public:
    static Impl* CreateInterface(BusAttachment& busAttachment, Ref<TimerIntfControlleeModel> model, CdmBusObject& cdmBusObject);

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
     * Emits a changed signal for the TargetTimeToStart property
     * @param[in] newValue new value of target time to start
     * @return ER_OK on success
     */
    QStatus EmitTargetTimeToStartChanged(const int32_t newValue);

    /**
     * Emits a changed signal for the TargetTimeToStop property
     * @param[in] newValue new value of target time to stop
     * @return ER_OK on success
     */
    QStatus EmitTargetTimeToStopChanged(const int32_t newValue);

    /**
     * Emits a changed signal for the TargetDuration property
     * @param[in] newValue new value of target duration
     * @return ER_OK on success
     */
    QStatus EmitTargetDurationChanged(const int32_t newValue);

    /**
     * Handler of SetTargetTimeToStart method
     * @param member
     * @param msg reference of alljoyn Message
     */
    void OnSetTargetTimeToStart(const InterfaceDescription::Member* member, Message& msg, CdmControllee& controllee);

    /**
     * Handler of SetTargetTimeToStop method
     * @param member
     * @param msg reference of alljoyn Message
     */
    void OnSetTargetTimeToStop(const InterfaceDescription::Member* member, Message& msg, CdmControllee& controllee);

  private:
    /**
     * Constructor of TimerIntfControllee::Impl
     */
    Impl(BusAttachment& busAttachment, Ref<TimerIntfControlleeModel> model, CdmBusObject& cdmBusObject);


    BusAttachment& m_busAttachment;
    Ref<TimerIntfControlleeModel> m_TimerModelInterface;

    MethodHandlers m_methodHandlers;
};

/*
 * Forwarding
 */
TimerIntfControllee::TimerIntfControllee(BusAttachment& busAttachment, Ref<InterfaceControlleeModel> model, CdmBusObject& cdmBusObject)
    : m_impl(Impl::CreateInterface(busAttachment, dynamic_pointer_cast<TimerIntfControlleeModel>(model), cdmBusObject))
{}


TimerIntfControllee::~TimerIntfControllee()
{
    delete m_impl;
}

const qcc::String& TimerIntfControllee::GetInterfaceName() const
{
    return m_impl->GetInterfaceName();
}

QStatus TimerIntfControllee::EmitTargetTimeToStartChanged(const int32_t newValue)
{
    return (m_impl == nullptr) ? ER_FAIL : m_impl->EmitTargetTimeToStartChanged(newValue);
}

QStatus TimerIntfControllee::EmitTargetTimeToStopChanged(const int32_t newValue)
{
    return (m_impl == nullptr) ? ER_FAIL : m_impl->EmitTargetTimeToStopChanged(newValue);
}

QStatus TimerIntfControllee::EmitTargetDurationChanged(const int32_t newValue)
{
    return (m_impl == nullptr) ? ER_FAIL : m_impl->EmitTargetDurationChanged(newValue);
}


/*
 * Implementation
 */
 TimerIntfControllee::Impl* TimerIntfControllee::Impl::CreateInterface(
    BusAttachment& busAttachment,
    Ref<TimerIntfControlleeModel> model,
    CdmBusObject& cdmBusObject)
{
    TimerIntfControllee::Impl* interface = new TimerIntfControllee::Impl(busAttachment, model, cdmBusObject);

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

TimerIntfControllee::Impl::Impl(BusAttachment& busAttachment, Ref<TimerIntfControlleeModel> model, CdmBusObject& cdmBusObject) :
    InterfaceReceiver(cdmBusObject),
    m_busAttachment(busAttachment),
    m_TimerModelInterface(model),
    m_methodHandlers()
{}


QStatus TimerIntfControllee::Impl::Init()
{
    QStatus status = CdmInterface::Init();

    const InterfaceDescription::Member* SetTargetTimeToStartMember = m_interfaceDescription->GetMember(s_method_SetTargetTimeToStart.c_str());
    InterfaceReceiver::CdmMethodHandler SetTargetTimeToStartHandler = static_cast<InterfaceReceiver::CdmMethodHandler>(&Impl::OnSetTargetTimeToStart);

    m_methodHandlers.push_back(make_pair(SetTargetTimeToStartMember, SetTargetTimeToStartHandler));

    const InterfaceDescription::Member* SetTargetTimeToStopMember = m_interfaceDescription->GetMember(s_method_SetTargetTimeToStop.c_str());
    InterfaceReceiver::CdmMethodHandler SetTargetTimeToStopHandler = static_cast<InterfaceReceiver::CdmMethodHandler>(&Impl::OnSetTargetTimeToStop);

    m_methodHandlers.push_back(make_pair(SetTargetTimeToStopMember, SetTargetTimeToStopHandler));

    return status;
}

QStatus TimerIntfControllee::Impl::OnGetProperty(const String& propName, MsgArg& msgarg)
{
    if (!(s_prop_Version.compare(propName))) {
        msgarg.typeId = ALLJOYN_UINT16;
        msgarg.v_uint16 = GetInterfaceVersion();
        return ER_OK;
    } else {
        if (!(s_prop_ReferenceTimer.compare(propName))) {
            int32_t value;
            auto status = m_TimerModelInterface->GetReferenceTimer(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            {
                CdmMsgCvt<int32_t> converter;
                converter.set(msgarg, value);
            }
            return ER_OK;
        } else        if (!(s_prop_TargetTimeToStart.compare(propName))) {
            int32_t value;
            auto status = m_TimerModelInterface->GetTargetTimeToStart(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            {
                CdmMsgCvt<int32_t> converter;
                converter.set(msgarg, value);
            }
            return ER_OK;
        } else        if (!(s_prop_TargetTimeToStop.compare(propName))) {
            int32_t value;
            auto status = m_TimerModelInterface->GetTargetTimeToStop(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            {
                CdmMsgCvt<int32_t> converter;
                converter.set(msgarg, value);
            }
            return ER_OK;
        } else        if (!(s_prop_EstimatedTimeToEnd.compare(propName))) {
            int32_t value;
            auto status = m_TimerModelInterface->GetEstimatedTimeToEnd(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            {
                CdmMsgCvt<int32_t> converter;
                converter.set(msgarg, value);
            }
            return ER_OK;
        } else        if (!(s_prop_RunningTime.compare(propName))) {
            int32_t value;
            auto status = m_TimerModelInterface->GetRunningTime(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            {
                CdmMsgCvt<int32_t> converter;
                converter.set(msgarg, value);
            }
            return ER_OK;
        } else        if (!(s_prop_TargetDuration.compare(propName))) {
            int32_t value;
            auto status = m_TimerModelInterface->GetTargetDuration(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            {
                CdmMsgCvt<int32_t> converter;
                converter.set(msgarg, value);
            }
            return ER_OK;
        } else {
            return ER_BUS_NO_SUCH_PROPERTY;
        }
    }
}

QStatus TimerIntfControllee::Impl::OnSetProperty(const String& propName, MsgArg& msgarg)
{
    if (!(s_prop_ReferenceTimer.compare(propName))) {
        if (msgarg.Signature() != "i") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        return ER_BUS_PROPERTY_VALUE_NOT_SET;
    } else    if (!(s_prop_TargetTimeToStart.compare(propName))) {
        if (msgarg.Signature() != "i") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        return ER_BUS_PROPERTY_VALUE_NOT_SET;
    } else    if (!(s_prop_TargetTimeToStop.compare(propName))) {
        if (msgarg.Signature() != "i") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        return ER_BUS_PROPERTY_VALUE_NOT_SET;
    } else    if (!(s_prop_EstimatedTimeToEnd.compare(propName))) {
        if (msgarg.Signature() != "i") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        return ER_BUS_PROPERTY_VALUE_NOT_SET;
    } else    if (!(s_prop_RunningTime.compare(propName))) {
        if (msgarg.Signature() != "i") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        return ER_BUS_PROPERTY_VALUE_NOT_SET;
    } else    if (!(s_prop_TargetDuration.compare(propName))) {
        if (msgarg.Signature() != "i") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        return ER_BUS_PROPERTY_VALUE_NOT_SET;
    } else {
        return ER_BUS_NO_SUCH_PROPERTY;
    }
}

void TimerIntfControllee::Impl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg, CdmControllee& controllee)
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

QStatus TimerIntfControllee::Impl::EmitTargetTimeToStartChanged(const int32_t newValue)
{
    QStatus status = ER_OK;

    MsgArg val;
    {
        CdmMsgCvt<int32_t> converter;
        converter.set(val, newValue);
    }
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_TargetTimeToStart.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);

    return status;
}
QStatus TimerIntfControllee::Impl::EmitTargetTimeToStopChanged(const int32_t newValue)
{
    QStatus status = ER_OK;

    MsgArg val;
    {
        CdmMsgCvt<int32_t> converter;
        converter.set(val, newValue);
    }
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_TargetTimeToStop.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);

    return status;
}
QStatus TimerIntfControllee::Impl::EmitTargetDurationChanged(const int32_t newValue)
{
    QStatus status = ER_OK;

    MsgArg val;
    {
        CdmMsgCvt<int32_t> converter;
        converter.set(val, newValue);
    }
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_TargetDuration.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);

    return status;
}

void TimerIntfControllee::Impl::OnSetTargetTimeToStart(const InterfaceDescription::Member* member, Message& msg, CdmControllee& controllee) {
    const MsgArg* args = NULL;
    size_t numArgs = 0;

    msg->GetArgs(numArgs, args);

    int32_t arg_targetTimeToStart;

    {
        CdmMsgCvt<int32_t> cvt;
        cvt.get(args[0], arg_targetTimeToStart);
    }

    ErrorCode errorCode = NOT_ERROR;
    auto status = m_TimerModelInterface->SetTargetTimeToStart(arg_targetTimeToStart, errorCode, controllee);


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
void TimerIntfControllee::Impl::OnSetTargetTimeToStop(const InterfaceDescription::Member* member, Message& msg, CdmControllee& controllee) {
    const MsgArg* args = NULL;
    size_t numArgs = 0;

    msg->GetArgs(numArgs, args);

    int32_t arg_targetTimeToStop;

    {
        CdmMsgCvt<int32_t> cvt;
        cvt.get(args[0], arg_targetTimeToStop);
    }

    ErrorCode errorCode = NOT_ERROR;
    auto status = m_TimerModelInterface->SetTargetTimeToStop(arg_targetTimeToStop, errorCode, controllee);


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
