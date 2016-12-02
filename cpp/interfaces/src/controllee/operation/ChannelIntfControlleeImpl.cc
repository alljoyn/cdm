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

#include <interfaces/controllee/operation/ChannelIntfControllee.h>
#include <interfaces/controllee/operation/ChannelIntfControlleeModel.h>


using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

/**
 * Channel Interface Controllee implementation class
 */
class ChannelIntfControllee::Impl :
    public InterfaceReceiver,
    public ChannelInterface
{

  public:
    static Impl* CreateInterface(BusAttachment& busAttachment, Ref<ChannelIntfControlleeModel> model, CdmBusObject& cdmBusObject);

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
     * Emits a changed signal for the ChannelId property
     * @param[in] newValue new value of channel id
     * @return ER_OK on success
     */
    QStatus EmitChannelIdChanged(const qcc::String newValue);

    /**
     * Emits a changed signal for the TotalNumberOfChannels property
     * @param[in] newValue new value of total number of channels
     * @return ER_OK on success
     */
    QStatus EmitTotalNumberOfChannelsChanged(const uint16_t newValue);

    /**
     * Handler of GetChannelList method
     * @param member
     * @param msg reference of alljoyn Message
     */
    void OnGetChannelList(const InterfaceDescription::Member* member, Message& msg, CdmSideEffects& sideEffects);

    /**
     * Emit ChannelListChanged signal
     * @return ER_OK on success
     */
    QStatus EmitChannelListChanged();

  private:
    /**
     * Constructor of ChannelIntfControllee::Impl
     */
    Impl(BusAttachment& busAttachment, Ref<ChannelIntfControlleeModel> model, CdmBusObject& cdmBusObject);


    BusAttachment& m_busAttachment;
    Ref<ChannelIntfControlleeModel> m_ChannelModelInterface;

    MethodHandlers m_methodHandlers;
};

/*
 * Forwarding
 */
ChannelIntfControllee::ChannelIntfControllee(BusAttachment& busAttachment, Ref<InterfaceControlleeModel> model, CdmBusObject& cdmBusObject)
    : m_impl(Impl::CreateInterface(busAttachment, dynamic_pointer_cast<ChannelIntfControlleeModel>(model), cdmBusObject))
{}


ChannelIntfControllee::~ChannelIntfControllee()
{
    delete m_impl;
}

const qcc::String& ChannelIntfControllee::GetInterfaceName() const
{
    return m_impl->GetInterfaceName();
}

QStatus ChannelIntfControllee::EmitChannelIdChanged(const qcc::String newValue)
{
    return (m_impl == nullptr) ? ER_FAIL : m_impl->EmitChannelIdChanged(newValue);
}

QStatus ChannelIntfControllee::EmitTotalNumberOfChannelsChanged(const uint16_t newValue)
{
    return (m_impl == nullptr) ? ER_FAIL : m_impl->EmitTotalNumberOfChannelsChanged(newValue);
}

QStatus ChannelIntfControllee::EmitChannelListChanged()
{
    return m_impl->EmitChannelListChanged();
}


/*
 * Implementation
 */
 ChannelIntfControllee::Impl* ChannelIntfControllee::Impl::CreateInterface(
    BusAttachment& busAttachment,
    Ref<ChannelIntfControlleeModel> model,
    CdmBusObject& cdmBusObject)
{
    ChannelIntfControllee::Impl* interface = new ChannelIntfControllee::Impl(busAttachment, model, cdmBusObject);

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

ChannelIntfControllee::Impl::Impl(BusAttachment& busAttachment, Ref<ChannelIntfControlleeModel> model, CdmBusObject& cdmBusObject) :
    InterfaceReceiver(cdmBusObject),
    m_busAttachment(busAttachment),
    m_ChannelModelInterface(model),
    m_methodHandlers()
{}


QStatus ChannelIntfControllee::Impl::Init()
{
    QStatus status = CdmInterface::Init();

    const InterfaceDescription::Member* GetChannelListMember = m_interfaceDescription->GetMember(s_method_GetChannelList.c_str());
    InterfaceReceiver::CdmMethodHandler GetChannelListHandler = static_cast<InterfaceReceiver::CdmMethodHandler>(&Impl::OnGetChannelList);

    m_methodHandlers.push_back(make_pair(GetChannelListMember, GetChannelListHandler));

    return status;
}

QStatus ChannelIntfControllee::Impl::OnGetProperty(const String& propName, MsgArg& msgarg)
{
    QStatus status;

    if (!(s_prop_Version.compare(propName))) {
        msgarg.typeId = ALLJOYN_UINT16;
        msgarg.v_uint16 = GetInterfaceVersion();
        return ER_OK;
    } else {
        if (!(s_prop_ChannelId.compare(propName))) {
            qcc::String value;
            status = m_ChannelModelInterface->GetChannelId(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            CdmMsgCvt<qcc::String> converter;
            converter.set(msgarg, value);
            return ER_OK;
        } else        if (!(s_prop_TotalNumberOfChannels.compare(propName))) {
            uint16_t value;
            status = m_ChannelModelInterface->GetTotalNumberOfChannels(value);
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

QStatus ChannelIntfControllee::Impl::OnSetProperty(const String& propName, MsgArg& msgarg)
{
    QStatus status;

    if (!(s_prop_ChannelId.compare(propName))) {
        if (msgarg.Signature() != "s") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        qcc::String value;
        CdmMsgCvt<qcc::String> converter;
        converter.get(msgarg, value);

        status = m_ChannelModelInterface->SetChannelId(value);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: failed to set property value", __func__));
            return ER_BUS_PROPERTY_VALUE_NOT_SET;
        }

        EmitChannelIdChanged(value);

        return ER_OK;
    } else    if (!(s_prop_TotalNumberOfChannels.compare(propName))) {
        if (msgarg.Signature() != "q") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        return ER_BUS_PROPERTY_VALUE_NOT_SET;
    } else {
        return ER_BUS_NO_SUCH_PROPERTY;
    }
}

void ChannelIntfControllee::Impl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg, CdmSideEffects& sideEffects)
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

QStatus ChannelIntfControllee::Impl::EmitChannelIdChanged(const qcc::String newValue)
{
    QStatus status = ER_OK;

    MsgArg val;
    CdmMsgCvt<qcc::String> converter;
    converter.set(val, newValue);
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_ChannelId.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);

    return status;
}
QStatus ChannelIntfControllee::Impl::EmitTotalNumberOfChannelsChanged(const uint16_t newValue)
{
    QStatus status = ER_OK;

    MsgArg val;
    CdmMsgCvt<uint16_t> converter;
    converter.set(val, newValue);
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_TotalNumberOfChannels.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);

    return status;
}

void ChannelIntfControllee::Impl::OnGetChannelList(const InterfaceDescription::Member* member, Message& msg, CdmSideEffects& sideEffects) {
    QStatus status = ER_OK;
    const MsgArg* args = NULL;
    size_t numArgs = 0;

    msg->GetArgs(numArgs, args);

    uint16_t arg_startingRecord;
    uint16_t arg_numRecords;
    std::vector<ChannelInfoRecord> arg_listOfChannelInfoRecords;

    {
        CdmMsgCvt<uint16_t> cvt;
        cvt.get(args[0], arg_startingRecord);
    }

    {
        CdmMsgCvt<uint16_t> cvt;
        cvt.get(args[1], arg_numRecords);
    }

    ErrorCode errorCode = NOT_ERROR;
    status = m_ChannelModelInterface->GetChannelList(arg_startingRecord, arg_numRecords, arg_listOfChannelInfoRecords, errorCode, sideEffects);

    MsgArg reply;
    CdmMsgCvt<std::vector<ChannelInfoRecord>> replyCvt;
    replyCvt.set(reply, arg_listOfChannelInfoRecords);

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

QStatus ChannelIntfControllee::Impl::EmitChannelListChanged()
{
    const InterfaceDescription::Member* member = GetInterfaceDescription()->GetMember(s_signal_ChannelListChanged.c_str());
    assert(member);
    return m_busObject.Signal(NULL, SESSION_ID_ALL_HOSTED, *member, NULL, 0, 0);
}} //namespace services
} //namespace ajn
