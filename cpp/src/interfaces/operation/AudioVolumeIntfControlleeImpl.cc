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
#include <alljoyn/hae/interfaces/operation/AudioVolumeIntfControlleeListener.h>
#include <alljoyn/hae/HaeBusObject.h>
#include "AudioVolumeIntfControlleeImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

HaeInterface* AudioVolumeIntfControlleeImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, HaeBusObject& haeBusObject)
{
    return new AudioVolumeIntfControlleeImpl(busAttachment, static_cast<AudioVolumeIntfControlleeListener&>(listener), haeBusObject);
}

AudioVolumeIntfControlleeImpl::AudioVolumeIntfControlleeImpl(BusAttachment& busAttachment, AudioVolumeIntfControlleeListener& listener, HaeBusObject& haeBusObject) :
    InterfaceControllee(haeBusObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener),
    m_volume(0),
    m_mute(false),
    m_maxVolume(100)
{
}

AudioVolumeIntfControlleeImpl::~AudioVolumeIntfControlleeImpl()
{
}

QStatus AudioVolumeIntfControlleeImpl::Init()
{
    QStatus status = HaeInterface::Init();

    return status;
}

QStatus AudioVolumeIntfControlleeImpl::SetVolume(const uint8_t volume)
{
    if (volume > m_maxVolume) {
        QCC_LogError(ER_INVALID_DATA, ("%s: Out of range.", __func__));
        return ER_INVALID_DATA;
    }

    if (m_volume != volume) {
        MsgArg val;
        val.typeId = ALLJOYN_BYTE;
        val.v_byte = volume;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_Volume.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_volume = volume;
    }
    return ER_OK;
}

QStatus AudioVolumeIntfControlleeImpl::SetMute(const bool mute)
{
    if (m_mute != mute) {
        MsgArg val;
        val.typeId = ALLJOYN_BOOLEAN;
        val.v_bool = mute;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_Mute.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_mute = mute;
    }
    return ER_OK;
}

QStatus AudioVolumeIntfControlleeImpl::SetMaxVolume(const uint8_t maxVolume)
{
    if (m_maxVolume != maxVolume) {
        MsgArg val;
        val.typeId = ALLJOYN_BYTE;
        val.v_byte = maxVolume;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_MaxVolume.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_maxVolume = maxVolume;
        if (m_maxVolume < m_volume) {
            SetVolume(m_maxVolume);
        }
    }
    return ER_OK;
}

QStatus AudioVolumeIntfControlleeImpl::OnGetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    if (!(s_prop_Version.compare(propName))) {
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = GetInterfaceVersion();
    } else {
        if (s_retrievingActualPropertyValue) {
            if (!(s_prop_Volume.compare(propName))) {
                uint8_t volume;
                status = m_interfaceListener.OnGetVolume(volume);
                if (status != ER_OK) {
                    volume = GetVolume();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetVolume(volume); // update the value in AudioVolumeIntfControllee.
                }

                val.typeId = ALLJOYN_BYTE;
                val.v_byte = volume;
            } else if (!(s_prop_Mute.compare(propName))) {
                bool mute;
                status = m_interfaceListener.OnGetMute(mute);
                if (status != ER_OK) {
                    mute = GetMute();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetMute(mute); // update the value in AudioVolumeIntfControllee.
                }

                val.typeId = ALLJOYN_BOOLEAN;
                val.v_bool = mute;
            } else if (!(s_prop_MaxVolume.compare(propName))) {
                uint8_t maxVolume;
                status = m_interfaceListener.OnGetMaxVolume(maxVolume);
                if (status != ER_OK) {
                    maxVolume = GetMaxVolume();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetMaxVolume(maxVolume); // update the value in AudioVolumeIntfControllee.
                }

                val.typeId = ALLJOYN_BYTE;
                val.v_byte = maxVolume;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
        } else {
            if (!(s_prop_Volume.compare(propName))) {
                const uint8_t volume = GetVolume();
                val.typeId = ALLJOYN_BYTE;
                val.v_byte = volume;
            } else if (!(s_prop_Mute.compare(propName))) {
                const bool mute = GetMute();
                val.typeId = ALLJOYN_BOOLEAN;
                val.v_bool = mute;
            } else if (!(s_prop_MaxVolume.compare(propName))) {
                const uint8_t maxVolume = GetMaxVolume();
                val.typeId = ALLJOYN_BYTE;
                val.v_byte = maxVolume;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
        }
    }

    return status;
}

QStatus AudioVolumeIntfControlleeImpl::OnSetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    if (!(s_prop_Volume.compare(propName))) {
        if (val.typeId != ALLJOYN_BYTE) {
            status = ER_BUS_NO_SUCH_PROPERTY;
            return status;
        }
        uint8_t volume = val.v_byte;
        if (volume > m_maxVolume) {
            volume = m_maxVolume;
        }
        status = m_interfaceListener.OnSetVolume(volume);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: failed to set property value", __func__));
            status = ER_BUS_PROPERTY_VALUE_NOT_SET;
        } else {
            SetVolume(volume); // update the value in AudioVolumeIntfControllee.
        }
    } else if (!(s_prop_Mute.compare(propName))) {
        if (val.typeId != ALLJOYN_BOOLEAN) {
            status = ER_BUS_NO_SUCH_PROPERTY;
            return status;
        }
        bool mute = val.v_bool;
        status = m_interfaceListener.OnSetMute(mute);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: failed to set property value", __func__));
            status = ER_BUS_PROPERTY_VALUE_NOT_SET;
        } else {
            SetMute(mute); // update the value in AudioVolumeIntfControllee.
        }
    } else {
        status = ER_BUS_NO_SUCH_PROPERTY;
    }

    return status;
}

void AudioVolumeIntfControlleeImpl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
{
    QStatus status = ER_OK;
    bool isFound = false;
    MethodHandlers::const_iterator it;
    for (it = m_methodHandlers.begin(); it != m_methodHandlers.end(); ++it) {
        if (it->first == member) {
            MessageReceiver::MethodHandler handler = it->second;
            (this->*handler)(member, msg);
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


} //namespace services
} //namespace ajn
