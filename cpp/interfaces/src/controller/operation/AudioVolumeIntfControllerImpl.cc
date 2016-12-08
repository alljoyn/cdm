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

// This file is automatically generated. Do not edit it.

#include <alljoyn/cdm/common/LogModule.h>
#include <alljoyn/cdm/common/CdmTypes.h>
#include <alljoyn/cdm/controller/InterfaceController.h>
#include <interfaces/controller/operation/AudioVolumeIntfControllerListener.h>
#include <interfaces/controller/operation/AudioVolumeIntfController.h>

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {
//======================================================================

typedef Ref<AudioVolumeIntfControllerListener> MyInterfaceListener;


class AudioVolumeIntfController::Impl : public InterfaceController
{
  public:

    Impl(
        AudioVolumeIntfController& outer,
        BusAttachment& busAttachment,
        MyInterfaceListener listener,
        Ref<ProxyBusObject> proxyBusObject
        )
      : InterfaceController(proxyBusObject),
        m_outer(outer),
        m_busAttachment(busAttachment),
        m_interfaceListener(listener)
    {
    }

    QStatus Init();

    const char* GetInterfaceName() const
    {
        return m_outer.GetInterfaceName().c_str();
    }

    QStatus GetVolume(void* context);
    QStatus SetVolume(const uint8_t value, void* context);
    QStatus GetMaxVolume(void* context);
    QStatus GetMute(void* context);
    QStatus SetMute(const bool value, void* context);


    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);

    void GetVolumePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetVolumePropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetMaxVolumePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetMutePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetMutePropertyCB(QStatus status, ProxyBusObject* obj, void* context);



    // The outer facet
    AudioVolumeIntfController& m_outer;

    // and inherit m_proxyObject from InterfaceController
    BusAttachment& m_busAttachment;
    MyInterfaceListener m_interfaceListener;
};

//======================================================================

QStatus AudioVolumeIntfController::Impl::Init()
{
    auto status = m_proxyObject->RegisterPropertiesChangedListener(GetInterfaceName(), NULL, 0, *this, NULL);

    if (ER_OK != status) {
        QCC_LogError(status, ("%s: RegisterPropertiesChangedListener failed.", __func__));
    }

    const InterfaceDescription* intf = m_outer.GetInterfaceDescription();
    if (intf) {
    } else {
        status = ER_FAIL;
        QCC_LogError(status, ("%s: The interface description does not exist.", __func__));
    }

    return status;
}




QStatus AudioVolumeIntfController::Impl::GetVolume(void* context)
{
    auto status = m_proxyObject->GetPropertyAsync(GetInterfaceName(), s_prop_Volume.c_str(), this,
                (ProxyBusObject::Listener::GetPropertyCB)&AudioVolumeIntfController::Impl::GetVolumePropertyCB, context);
    return status;
}

QStatus AudioVolumeIntfController::Impl::SetVolume(const uint8_t value, void* context)
{
    MsgArg arg;
    {
        CdmMsgCvt<uint8_t> converter;
        converter.set(arg, value);
    }

    auto status = m_proxyObject->SetPropertyAsync(GetInterfaceName(), s_prop_Volume.c_str(), arg, this,
                (ProxyBusObject::Listener::SetPropertyCB)&AudioVolumeIntfController::Impl::SetVolumePropertyCB, context);
    return status;
}

QStatus AudioVolumeIntfController::Impl::GetMaxVolume(void* context)
{
    auto status = m_proxyObject->GetPropertyAsync(GetInterfaceName(), s_prop_MaxVolume.c_str(), this,
                (ProxyBusObject::Listener::GetPropertyCB)&AudioVolumeIntfController::Impl::GetMaxVolumePropertyCB, context);
    return status;
}

QStatus AudioVolumeIntfController::Impl::GetMute(void* context)
{
    auto status = m_proxyObject->GetPropertyAsync(GetInterfaceName(), s_prop_Mute.c_str(), this,
                (ProxyBusObject::Listener::GetPropertyCB)&AudioVolumeIntfController::Impl::GetMutePropertyCB, context);
    return status;
}

QStatus AudioVolumeIntfController::Impl::SetMute(const bool value, void* context)
{
    MsgArg arg;
    {
        CdmMsgCvt<bool> converter;
        converter.set(arg, value);
    }

    auto status = m_proxyObject->SetPropertyAsync(GetInterfaceName(), s_prop_Mute.c_str(), arg, this,
                (ProxyBusObject::Listener::SetPropertyCB)&AudioVolumeIntfController::Impl::SetMutePropertyCB, context);
    return status;
}





void AudioVolumeIntfController::Impl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (s_prop_Volume == propNameStr) {
            uint8_t val;
            {
                CdmMsgCvt<uint8_t> converter;
                converter.get((*propValue), val);
            }
            m_interfaceListener->OnVolumeChanged(obj.GetPath(), val);
        } else if (s_prop_MaxVolume == propNameStr) {
            uint8_t val;
            {
                CdmMsgCvt<uint8_t> converter;
                converter.get((*propValue), val);
            }
            m_interfaceListener->OnMaxVolumeChanged(obj.GetPath(), val);
        } else if (s_prop_Mute == propNameStr) {
            bool val;
            {
                CdmMsgCvt<bool> converter;
                converter.get((*propValue), val);
            }
            m_interfaceListener->OnMuteChanged(obj.GetPath(), val);
        } else {
            QCC_DbgTrace(("Unknown property change signal received"));
        }
    }
}

//======================================================================
// Callbacks


void AudioVolumeIntfController::Impl::GetVolumePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (obj) {
        uint8_t val;
        {
            CdmMsgCvt<uint8_t> converter;
            converter.get(value, val);
        }
        if (_QCC_DbgPrintCheck(DBG_GEN_MESSAGE, QCC_MODULE)) {
            auto s = CdmMsgCvt<uint8_t>().str(value);
            QCC_DbgPrintf(("%s: received property %s=%s", __func__, "Volume", s.c_str()));
        }
        m_interfaceListener->OnResponseGetVolume(status, obj->GetPath(), val, context);
    }
}



void AudioVolumeIntfController::Impl::SetVolumePropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    QCC_DbgPrintf(("%s: set completed", __func__));
    if (obj) {
        m_interfaceListener->OnResponseSetVolume(status, obj->GetPath(), context);
    }
}

void AudioVolumeIntfController::Impl::GetMaxVolumePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (obj) {
        uint8_t val;
        {
            CdmMsgCvt<uint8_t> converter;
            converter.get(value, val);
        }
        if (_QCC_DbgPrintCheck(DBG_GEN_MESSAGE, QCC_MODULE)) {
            auto s = CdmMsgCvt<uint8_t>().str(value);
            QCC_DbgPrintf(("%s: received property %s=%s", __func__, "MaxVolume", s.c_str()));
        }
        m_interfaceListener->OnResponseGetMaxVolume(status, obj->GetPath(), val, context);
    }
}




void AudioVolumeIntfController::Impl::GetMutePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (obj) {
        bool val;
        {
            CdmMsgCvt<bool> converter;
            converter.get(value, val);
        }
        if (_QCC_DbgPrintCheck(DBG_GEN_MESSAGE, QCC_MODULE)) {
            auto s = CdmMsgCvt<bool>().str(value);
            QCC_DbgPrintf(("%s: received property %s=%s", __func__, "Mute", s.c_str()));
        }
        m_interfaceListener->OnResponseGetMute(status, obj->GetPath(), val, context);
    }
}



void AudioVolumeIntfController::Impl::SetMutePropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    QCC_DbgPrintf(("%s: set completed", __func__));
    if (obj) {
        m_interfaceListener->OnResponseSetMute(status, obj->GetPath(), context);
    }
}

//======================================================================
// Forward to the impl

AudioVolumeIntfController::AudioVolumeIntfController(
    BusAttachment& busAttachment,
    Ref<InterfaceControllerListener> listener,
    Ref<ProxyBusObject> cdmProxyObject
    )
  : m_impl(new Impl(*this, busAttachment, dynamic_pointer_cast<AudioVolumeIntfControllerListener>(listener), cdmProxyObject))
{
}



AudioVolumeIntfController::~AudioVolumeIntfController()
{
    delete m_impl;
}



Ref<CdmInterface> AudioVolumeIntfController::CreateInterface(BusAttachment& busAttachment, Ref<InterfaceControllerListener> listener, Ref<ProxyBusObject> cdmProxyObject)
{
    return mkRef<AudioVolumeIntfController>(busAttachment, dynamic_pointer_cast<AudioVolumeIntfControllerListener>(listener), cdmProxyObject);
}



QStatus AudioVolumeIntfController::Init()
{
    // Call the superclass Init
    QStatus status = CdmInterface::Init();
    if (ER_OK != status) {
        QCC_LogError(status, ("%s: Interface init failed.", __func__));
        return status;
    }

    return m_impl->Init();
}



BusAttachment& AudioVolumeIntfController::GetBusAttachment() const
{
    return m_impl->m_busAttachment;
}



QStatus AudioVolumeIntfController::GetVolume(void* context)
{
    return m_impl->GetVolume(context);
}



QStatus AudioVolumeIntfController::SetVolume(const uint8_t value, void* context)
{
    return m_impl->SetVolume(value, context);
}



QStatus AudioVolumeIntfController::GetMaxVolume(void* context)
{
    return m_impl->GetMaxVolume(context);
}



QStatus AudioVolumeIntfController::GetMute(void* context)
{
    return m_impl->GetMute(context);
}



QStatus AudioVolumeIntfController::SetMute(const bool value, void* context)
{
    return m_impl->SetMute(value, context);
}

//======================================================================
} //namespace services
} //namespace ajn