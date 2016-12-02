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

#include <interfaces/controllee/operation/AudioVideoInputIntfControllee.h>
#include <interfaces/controllee/operation/AudioVideoInputIntfControlleeModel.h>


using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

/**
 * AudioVideoInput Interface Controllee implementation class
 */
class AudioVideoInputIntfControllee::Impl :
    public InterfaceReceiver,
    public AudioVideoInputInterface
{

  public:
    static Impl* CreateInterface(BusAttachment& busAttachment, Ref<AudioVideoInputIntfControlleeModel> model, CdmBusObject& cdmBusObject);

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
     * Emits a changed signal for the InputSourceId property
     * @param[in] newValue new value of input source id
     * @return ER_OK on success
     */
    QStatus EmitInputSourceIdChanged(const SourceType newValue);

    /**
     * Emits a changed signal for the SupportedInputSources property
     * @param[in] newValue new value of supported input sources
     * @return ER_OK on success
     */
    QStatus EmitSupportedInputSourcesChanged(const std::vector<InputSource> newValue);

  private:
    /**
     * Constructor of AudioVideoInputIntfControllee::Impl
     */
    Impl(BusAttachment& busAttachment, Ref<AudioVideoInputIntfControlleeModel> model, CdmBusObject& cdmBusObject);


    BusAttachment& m_busAttachment;
    Ref<AudioVideoInputIntfControlleeModel> m_AudioVideoInputModelInterface;

    MethodHandlers m_methodHandlers;
};

/*
 * Forwarding
 */
AudioVideoInputIntfControllee::AudioVideoInputIntfControllee(BusAttachment& busAttachment, Ref<InterfaceControlleeModel> model, CdmBusObject& cdmBusObject)
    : m_impl(Impl::CreateInterface(busAttachment, dynamic_pointer_cast<AudioVideoInputIntfControlleeModel>(model), cdmBusObject))
{}


AudioVideoInputIntfControllee::~AudioVideoInputIntfControllee()
{
    delete m_impl;
}

const qcc::String& AudioVideoInputIntfControllee::GetInterfaceName() const
{
    return m_impl->GetInterfaceName();
}

QStatus AudioVideoInputIntfControllee::EmitInputSourceIdChanged(const SourceType newValue)
{
    return (m_impl == nullptr) ? ER_FAIL : m_impl->EmitInputSourceIdChanged(newValue);
}

QStatus AudioVideoInputIntfControllee::EmitSupportedInputSourcesChanged(const std::vector<InputSource> newValue)
{
    return (m_impl == nullptr) ? ER_FAIL : m_impl->EmitSupportedInputSourcesChanged(newValue);
}


/*
 * Implementation
 */
 AudioVideoInputIntfControllee::Impl* AudioVideoInputIntfControllee::Impl::CreateInterface(
    BusAttachment& busAttachment,
    Ref<AudioVideoInputIntfControlleeModel> model,
    CdmBusObject& cdmBusObject)
{
    AudioVideoInputIntfControllee::Impl* interface = new AudioVideoInputIntfControllee::Impl(busAttachment, model, cdmBusObject);

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

AudioVideoInputIntfControllee::Impl::Impl(BusAttachment& busAttachment, Ref<AudioVideoInputIntfControlleeModel> model, CdmBusObject& cdmBusObject) :
    InterfaceReceiver(cdmBusObject),
    m_busAttachment(busAttachment),
    m_AudioVideoInputModelInterface(model),
    m_methodHandlers()
{}


QStatus AudioVideoInputIntfControllee::Impl::Init()
{
    QStatus status = CdmInterface::Init();

    return status;
}

QStatus AudioVideoInputIntfControllee::Impl::OnGetProperty(const String& propName, MsgArg& msgarg)
{
    QStatus status;

    if (!(s_prop_Version.compare(propName))) {
        msgarg.typeId = ALLJOYN_UINT16;
        msgarg.v_uint16 = GetInterfaceVersion();
        return ER_OK;
    } else {
        if (!(s_prop_InputSourceId.compare(propName))) {
            SourceType value;
            status = m_AudioVideoInputModelInterface->GetInputSourceId(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            CdmMsgCvt<SourceType> converter;
            converter.set(msgarg, value);
            return ER_OK;
        } else        if (!(s_prop_SupportedInputSources.compare(propName))) {
            std::vector<InputSource> value;
            status = m_AudioVideoInputModelInterface->GetSupportedInputSources(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

            {
                std::vector<MsgArg> array(value.size());
                for (auto& v : value) {
                    msgarg.Set("(qqyqs)", v.id, v.sourceType, v.signalPresence, v.portNumber, v.friendlyName.c_str());
                }
                msgarg.Set("a(qqyqs)", array.size(), array.data());
                msgarg.Stabilize();
            }
            return ER_OK;
        } else {
            return ER_BUS_NO_SUCH_PROPERTY;
        }
    }
}

QStatus AudioVideoInputIntfControllee::Impl::OnSetProperty(const String& propName, MsgArg& msgarg)
{
    QStatus status;

    if (!(s_prop_InputSourceId.compare(propName))) {
        if (msgarg.Signature() != "q") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        SourceType value;
        CdmMsgCvt<SourceType> converter;
        converter.get(msgarg, value);

        status = m_AudioVideoInputModelInterface->SetInputSourceId(value);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: failed to set property value", __func__));
            return ER_BUS_PROPERTY_VALUE_NOT_SET;
        }

        EmitInputSourceIdChanged(value);

        return ER_OK;
    } else    if (!(s_prop_SupportedInputSources.compare(propName))) {
        if (msgarg.Signature() != "a(qqyqs)") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        return ER_BUS_PROPERTY_VALUE_NOT_SET;
    } else {
        return ER_BUS_NO_SUCH_PROPERTY;
    }
}

void AudioVideoInputIntfControllee::Impl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg, CdmSideEffects& sideEffects)
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

QStatus AudioVideoInputIntfControllee::Impl::EmitInputSourceIdChanged(const SourceType newValue)
{
    QStatus status = ER_OK;

    MsgArg val;
    CdmMsgCvt<SourceType> converter;
    converter.set(val, newValue);
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_InputSourceId.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);

    return status;
}
QStatus AudioVideoInputIntfControllee::Impl::EmitSupportedInputSourcesChanged(const std::vector<InputSource> newValue)
{
    QStatus status = ER_OK;

    MsgArg val;
    {
        std::vector<MsgArg> array(newValue.size());
        for (auto& v : newValue) {
            val.Set("(qqyqs)", v.id, v.sourceType, v.signalPresence, v.portNumber, v.friendlyName.c_str());
        }
        val.Set("a(qqyqs)", array.size(), array.data());
        val.Stabilize();
    }
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_SupportedInputSources.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);

    return status;
}


} //namespace services
} //namespace ajn