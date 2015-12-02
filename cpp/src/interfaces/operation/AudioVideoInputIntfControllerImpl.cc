/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
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

#include <qcc/Util.h>

#include <alljoyn/hae/LogModule.h>
#include <alljoyn/hae/interfaces/operation/AudioVideoInputIntfControllerListener.h>

#include "AudioVideoInputIntfControllerImpl.h"
#include "HaeProxyBusObject.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

HaeInterface* AudioVideoInputIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, HaeProxyBusObject& haeProxyObject)
{
    return new AudioVideoInputIntfControllerImpl(busAttachment, static_cast<AudioVideoInputIntfControllerListener&>(listener), haeProxyObject);
}

AudioVideoInputIntfControllerImpl::AudioVideoInputIntfControllerImpl(BusAttachment& busAttachment, AudioVideoInputIntfControllerListener& listener, HaeProxyBusObject& haeProxyObject) :
    InterfaceController(haeProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

AudioVideoInputIntfControllerImpl::~AudioVideoInputIntfControllerImpl()
{
}

QStatus AudioVideoInputIntfControllerImpl::Init()
{
    QStatus status = HaeInterface::Init();
    if (ER_OK != status) {
        QCC_LogError(status, ("%s: Interface init failed.", __func__));
        return status;
    }

    status = m_proxyObject.RegisterPropertiesChangedListener(GetInterfaceName().c_str(), NULL, 0, *this, NULL);
    if (ER_OK != status) {
        QCC_LogError(status, ("%s: RegisterPropertiesChangedListener failed.", __func__));
    }

    return status;
}

QStatus AudioVideoInputIntfControllerImpl::SetInputSourceId(const uint16_t inputSourceId, void* context)
{
    QStatus status = ER_OK;

    MsgArg arg;
    arg.Set("q", inputSourceId);
    status = m_proxyObject.SetPropertyAsync(GetInterfaceName().c_str(), s_prop_InputSourceId.c_str(), arg, this, (ProxyBusObject::Listener::SetPropertyCB)&AudioVideoInputIntfControllerImpl::SetInputSourceIdPropertyCB, context);

    return status;
}

QStatus AudioVideoInputIntfControllerImpl::GetInputSourceId(void* context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_InputSourceId.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&AudioVideoInputIntfControllerImpl::GetInputSourceIdPropertyCB, context);

    return status;
}

QStatus AudioVideoInputIntfControllerImpl::GetSupportedInputSources(void* context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_SupportedInputSources.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&AudioVideoInputIntfControllerImpl::GetSupportedInputSourcesPropertyCB, context);

    return status;
}

void AudioVideoInputIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (!s_prop_InputSourceId.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_UINT16) {
                uint16_t inputSourceId = propValue->v_uint16;
                m_interfaceListener.InputSourceIdPropertyChanged(obj.GetPath(), inputSourceId);
            }
        } else if (!s_prop_SupportedInputSources.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_ARRAY) {
                const MsgArg* args = propValue->v_array.GetElements();
                size_t argsNum = propValue->v_array.GetNumElements();
                AudioVideoInputInterface::InputSources inputSources;
                AudioVideoInputInterface::InputSource inputSource;

                for(size_t i=0; i<argsNum; i++) {
                    uint16_t id, sourceType, portNumber;
                    uint8_t signalPresence;
                    const char* friendlyName;
                    args[i].Get("(qqyqs)", &id, &sourceType, &signalPresence, &portNumber, &friendlyName);

                    inputSource.sourceType = sourceType;
                    inputSource.signalPresence = signalPresence;
                    inputSource.portNumber = portNumber;
                    inputSource.friendlyName = String(friendlyName);
                    inputSources.insert(std::pair<uint16_t, AudioVideoInputInterface::InputSource>(id, inputSource));
                }
                m_interfaceListener.SupportedInputSourcesPropertyChanged(obj.GetPath(), inputSources);
            }
        }
    }
}

void AudioVideoInputIntfControllerImpl::SetInputSourceIdPropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    if (!obj) {
        return;
    }

    m_interfaceListener.SetInputSourceIdPropertyCallback(status, obj->GetPath(), context);
}

void AudioVideoInputIntfControllerImpl::GetInputSourceIdPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }

    uint16_t inputSourceId;
    value.Get("q", &inputSourceId);

    m_interfaceListener.GetInputSourceIdPropertyCallback(status, obj->GetPath(), inputSourceId, context);
}

void AudioVideoInputIntfControllerImpl::GetSupportedInputSourcesPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }

    MsgArg* arg = value.v_variant.val;
    if (!arg) {
        return;
    } else if (!arg->HasSignature("a(qqyqs)")) {
        return;
    }

    MsgArg* entries;
    size_t numEntries;
    AudioVideoInputInterface::InputSources inputSources;
    AudioVideoInputInterface::InputSource inputSource;
    arg->Get("a(qqyqs)", &numEntries, &entries);

    for (size_t i = 0; i < numEntries; ++i) {
        uint16_t id, sourceType, portNumber;
        uint8_t signalPresence;
        const char* friendlyName;
        entries[i].Get("(qqyqs)", &id, &sourceType, &signalPresence, &portNumber, &friendlyName);

        inputSource.sourceType = sourceType;
        inputSource.signalPresence = signalPresence;
        inputSource.portNumber = portNumber;
        inputSource.friendlyName = String(friendlyName);
        inputSources.insert(std::pair<uint16_t, AudioVideoInputInterface::InputSource>(id, inputSource));
    }
    m_interfaceListener.GetSupportedInputSourcesPropertyCallback(status, obj->GetPath(), inputSources, context);
}

} //namespace services
} //namespace ajn
