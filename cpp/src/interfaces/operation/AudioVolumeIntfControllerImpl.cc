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

#include <qcc/Util.h>

#include <alljoyn/hae/LogModule.h>
#include <alljoyn/hae/interfaces/operation/AudioVolumeIntfControllerListener.h>

#include "AudioVolumeIntfControllerImpl.h"
#include <alljoyn/hae/HaeProxyBusObject.h>

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

HaeInterface* AudioVolumeIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, HaeProxyBusObject& haeProxyObject)
{
    return new AudioVolumeIntfControllerImpl(busAttachment, static_cast<AudioVolumeIntfControllerListener&>(listener), haeProxyObject);
}

AudioVolumeIntfControllerImpl::AudioVolumeIntfControllerImpl(BusAttachment& busAttachment, AudioVolumeIntfControllerListener& listener, HaeProxyBusObject& haeProxyObject) :
    InterfaceController(haeProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

AudioVolumeIntfControllerImpl::~AudioVolumeIntfControllerImpl()
{
}

QStatus AudioVolumeIntfControllerImpl::Init()
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

QStatus AudioVolumeIntfControllerImpl::SetVolume(const uint8_t volume, void* context)
{
    QStatus status = ER_OK;

    MsgArg arg;
    arg.Set("y", volume);
    status = m_proxyObject.SetPropertyAsync(GetInterfaceName().c_str(), s_prop_Volume.c_str(), arg, this, (ProxyBusObject::Listener::SetPropertyCB)&AudioVolumeIntfControllerImpl::SetVolumePropertyCB, context);

    return status;
}

QStatus AudioVolumeIntfControllerImpl::SetMute(const bool mute, void* context)
{
    QStatus status = ER_OK;

    MsgArg arg;
    arg.Set("b", mute);
    status = m_proxyObject.SetPropertyAsync(GetInterfaceName().c_str(), s_prop_Mute.c_str(), arg, this, (ProxyBusObject::Listener::SetPropertyCB)&AudioVolumeIntfControllerImpl::SetMutePropertyCB, context);

    return status;
}

QStatus AudioVolumeIntfControllerImpl::GetVolume(void* context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_Volume.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&AudioVolumeIntfControllerImpl::GetVolumePropertyCB, context);

    return status;
}

QStatus AudioVolumeIntfControllerImpl::GetMaxVolume(void* context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_MaxVolume.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&AudioVolumeIntfControllerImpl::GetMaxVolumePropertyCB, context);

    return status;
}

QStatus AudioVolumeIntfControllerImpl::GetMute(void* context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_Mute.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&AudioVolumeIntfControllerImpl::GetMutePropertyCB, context);

    return status;
}

void AudioVolumeIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (!s_prop_Volume.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_BYTE) {
                uint8_t volume = propValue->v_byte;
                m_interfaceListener.OnVolumeChanged(obj.GetPath(), volume);
            }
        } else if (!s_prop_MaxVolume.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_BYTE) {
                uint8_t maxVolume = propValue->v_byte;
                m_interfaceListener.OnMaxVolumeChanged(obj.GetPath(), maxVolume);
            }
        } else if (!s_prop_Mute.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_BOOLEAN) {
                bool mute = propValue->v_bool;
                m_interfaceListener.OnMuteChanged(obj.GetPath(), mute);
            }
        }
    }
}

void AudioVolumeIntfControllerImpl::SetVolumePropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    if (!obj) {
        return;
    }

    m_interfaceListener.OnResponseSetVolume(status, obj->GetPath(), context);
}

void AudioVolumeIntfControllerImpl::SetMutePropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    if(!obj) {
        return;
    }

    m_interfaceListener.OnResponseSetMute(status, obj->GetPath(), context);
}

void AudioVolumeIntfControllerImpl::GetVolumePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }

    uint8_t volume;
    value.Get("y", &volume);

    m_interfaceListener.OnResponseGetVolume(status, obj->GetPath(), volume, context);
}

void AudioVolumeIntfControllerImpl::GetMaxVolumePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }

    uint8_t maxVolume;
    value.Get("y", &maxVolume);

    m_interfaceListener.OnResponseGetMaxVolume(status, obj->GetPath(), maxVolume, context);
}

void AudioVolumeIntfControllerImpl::GetMutePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }

    bool mute;
    value.Get("b", &mute);

    m_interfaceListener.OnResponseGetMute(status, obj->GetPath(), mute, context);
}

} //namespace services
} //namespace ajn
