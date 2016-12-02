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

#include <interfaces/controllee/operation/OffControlIntfControllee.h>
#include <interfaces/controllee/operation/OffControlIntfControlleeModel.h>


using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

/**
 * OffControl Interface Controllee implementation class
 */
class OffControlIntfControllee::Impl :
    public InterfaceReceiver,
    public OffControlInterface
{

  public:
    static Impl* CreateInterface(BusAttachment& busAttachment, Ref<OffControlIntfControlleeModel> model, CdmBusObject& cdmBusObject);

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
     * Handler of SwitchOff method
     * @param member
     * @param msg reference of alljoyn Message
     */
    void OnSwitchOff(const InterfaceDescription::Member* member, Message& msg, CdmSideEffects& sideEffects);

  private:
    /**
     * Constructor of OffControlIntfControllee::Impl
     */
    Impl(BusAttachment& busAttachment, Ref<OffControlIntfControlleeModel> model, CdmBusObject& cdmBusObject);


    BusAttachment& m_busAttachment;
    Ref<OffControlIntfControlleeModel> m_OffControlModelInterface;

    MethodHandlers m_methodHandlers;
};

/*
 * Forwarding
 */
OffControlIntfControllee::OffControlIntfControllee(BusAttachment& busAttachment, Ref<InterfaceControlleeModel> model, CdmBusObject& cdmBusObject)
    : m_impl(Impl::CreateInterface(busAttachment, dynamic_pointer_cast<OffControlIntfControlleeModel>(model), cdmBusObject))
{}


OffControlIntfControllee::~OffControlIntfControllee()
{
    delete m_impl;
}

const qcc::String& OffControlIntfControllee::GetInterfaceName() const
{
    return m_impl->GetInterfaceName();
}


/*
 * Implementation
 */
 OffControlIntfControllee::Impl* OffControlIntfControllee::Impl::CreateInterface(
    BusAttachment& busAttachment,
    Ref<OffControlIntfControlleeModel> model,
    CdmBusObject& cdmBusObject)
{
    OffControlIntfControllee::Impl* interface = new OffControlIntfControllee::Impl(busAttachment, model, cdmBusObject);

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

OffControlIntfControllee::Impl::Impl(BusAttachment& busAttachment, Ref<OffControlIntfControlleeModel> model, CdmBusObject& cdmBusObject) :
    InterfaceReceiver(cdmBusObject),
    m_busAttachment(busAttachment),
    m_OffControlModelInterface(model),
    m_methodHandlers()
{}


QStatus OffControlIntfControllee::Impl::Init()
{
    QStatus status = CdmInterface::Init();

    const InterfaceDescription::Member* SwitchOffMember = m_interfaceDescription->GetMember(s_method_SwitchOff.c_str());
    InterfaceReceiver::CdmMethodHandler SwitchOffHandler = static_cast<InterfaceReceiver::CdmMethodHandler>(&Impl::OnSwitchOff);

    m_methodHandlers.push_back(make_pair(SwitchOffMember, SwitchOffHandler));

    return status;
}

QStatus OffControlIntfControllee::Impl::OnGetProperty(const String& propName, MsgArg& msgarg)
{
    QStatus status;

    if (!(s_prop_Version.compare(propName))) {
        msgarg.typeId = ALLJOYN_UINT16;
        msgarg.v_uint16 = GetInterfaceVersion();
        return ER_OK;
    } else {
 {
            return ER_BUS_NO_SUCH_PROPERTY;
        }
    }
}

QStatus OffControlIntfControllee::Impl::OnSetProperty(const String& propName, MsgArg& msgarg)
{
    QStatus status;

 {
        return ER_BUS_NO_SUCH_PROPERTY;
    }
}

void OffControlIntfControllee::Impl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg, CdmSideEffects& sideEffects)
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


void OffControlIntfControllee::Impl::OnSwitchOff(const InterfaceDescription::Member* member, Message& msg, CdmSideEffects& sideEffects) {
    QStatus status = ER_OK;
    const MsgArg* args = NULL;
    size_t numArgs = 0;

    msg->GetArgs(numArgs, args);


    ErrorCode errorCode = NOT_ERROR;
    status = m_OffControlModelInterface->SwitchOff(errorCode, sideEffects);


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