/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 * Source Project (AJOSP) Contributors and others.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * All rights reserved. This program and the accompanying materials are
 * made available under the terms of the Apache License, Version 2.0
 * which accompanies this distribution, and is available at
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Copyright 2016 Open Connectivity Foundation and Contributors to
 * AllSeen Alliance. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all
 * copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#ifdef _MSC_VER
#if _MSC_VER < 1900
#define __func__ __FUNCTION__
#endif
#endif

#include <qcc/Debug.h>
#include <alljoyn/ProxyBusObject.h>
#include <alljoyn/MsgArg.h>
#include <alljoyn/cdm/controller/CdmLsfTranslator.h>
#include <alljoyn/ProxyBusObject.h>

#include "interfaces/controller/operation/OnOffStatusIntfController.h"
#include "interfaces/controller/operation/BrightnessIntfController.h"
#include "interfaces/controller/operation/ColorIntfController.h"
#include "interfaces/controller/operation/ColorTemperatureIntfController.h"

#include <alljoyn/cdm/common/LogModule.h>

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

////////////////////////////////////////
//// Constant strings for LSF
////////////////////////////////////////

static const char* LampServiceObjectPath = "/org/allseen/LSF/Lamp";
static const char* LampServiceStateInterfaceName = "org.allseen.LSF.LampState";
static const char* LampServiceDetailsInterfaceName = "org.allseen.LSF.LampDetails";
static const char* LampServiceXML =
R"XML(
<node>
  <interface name='org.allseen.LSF.LampParameters'>
    <property name='Version' type='u' access='read'/>
    <property name='Energy_Usage_Milliwatts' type='u' access='read'/>
    <property name='Brightness_Lumens' type='u' access='read'/>
  </interface>
  <interface name='org.allseen.LSF.LampDetails'>
    <property name='Version' type='u' access='read'/>
    <property name='Make' type='u' access='read'/>
    <property name='Model' type='u' access='read'/>
    <property name='Type' type='u' access='read'/>
    <property name='LampType' type='u' access='read'/>
    <property name='LampBaseType' type='u' access='read'/>
    <property name='LampBeamAngle' type='u' access='read'/>
    <property name='Dimmable' type='b' access='read'/>
    <property name='Color' type='b' access='read'/>
    <property name='VariableColorTemp' type='b' access='read'/>
    <property name='HasEffects' type='b' access='read'/>
    <property name='MinVoltage' type='u' access='read'/>
    <property name='MaxVoltage' type='u' access='read'/>
    <property name='Wattage' type='u' access='read'/>
    <property name='IncandescentEquivalent' type='u' access='read'/>
    <property name='MaxLumens' type='u' access='read'/>
    <property name='MinTemperature' type='u' access='read'/>
    <property name='MaxTemperature' type='u' access='read'/>
    <property name='ColorRenderingIndex' type='u' access='read'/>
    <property name='LampID' type='s' access='read'/>
  </interface>
  <interface name='org.allseen.LSF.LampService'>
    <property name='Version' type='u' access='read'/>
    <property name='LampServiceVersion' type='u' access='read'/>
    <property name='LampFaults' type='au' access='read'/>
    <method name='ClearLampFault'>
      <arg name='LampFaultCode' type='u' direction='in'/>
      <arg name='LampResponseCode' type='u' direction='out'/>
      <arg name='LampFaultCode' type='u' direction='out'/>
    </method>
  </interface>
  <interface name='org.allseen.LSF.LampState'>
    <property name='Version' type='u' access='read'/>
    <property name='OnOff' type='b' access='read'/>
    <property name='Hue' type='u' access='read'/>
    <property name='Saturation' type='u' access='read'/>
    <property name='ColorTemp' type='u' access='read'/>
    <property name='Brightness' type='u' access='read'/>
    <method name='TransitionLampState'>
      <arg name='Timestamp' type='t' direction='in'/>
      <arg name='NewState' type='a{sv}' direction='in'/>
      <arg name='TransitionPeriod' type='u' direction='in'/>
      <arg name='LampResponseCode' type='u' direction='out'/>
    </method>
    <method name='ApplyPulseEffect'>
      <arg name='FromState' type='a{sv}' direction='in'/>
      <arg name='ToState' type='a{sv}' direction='in'/>
      <arg name='period' type='u' direction='in'/>
      <arg name='duration' type='u' direction='in'/>
      <arg name='numPulses' type='u' direction='in'/>
      <arg name='timestamp' type='t' direction='in'/>
      <arg name='LampResponseCode' type='u' direction='out'/>
    </method>
    <signal name='LampStateChanged'>
      <arg name='LampID' type='s' direction='out'/>
    </signal>
  </interface>
</node>
)XML";


////////////////////////////////////////
//// CdmLsfTranslator
////////////////////////////////////////

void CdmLsfTranslator::Attach(BusAttachment& busAttachment, Ref<DeviceInfo> deviceInfo) {
    QStatus status = busAttachment.CreateInterfacesFromXml(LampServiceXML);
    if (status != ER_OK && status != ER_BUS_IFACE_ALREADY_EXISTS) {
        QCC_LogError(status, ("%s: CreateInterfacesFromXml failed", __func__));
        return;
    }

    if (
        !deviceInfo->GetAboutObjectDescription().HasInterface(LampServiceObjectPath, LampServiceStateInterfaceName) ||
        !deviceInfo->GetAboutObjectDescription().HasInterface(LampServiceObjectPath, LampServiceDetailsInterfaceName)
    ) {
        // This device is not an LSF device
        return;
    }

    // TODO: we should ensure /org/allseen/LSF/Lamp does not have CDM interfaces present.
    // (Some devices might expose both LSF and CDM interfaces on the same bus path for compatibility reasons, we don't want to interfere with that)

    std::unordered_set<std::string> interfaces;

    interfaces.insert(OnOffStatusInterface::INTERFACE_NAME);
    interfaces.insert(OnControlInterface::INTERFACE_NAME);
    interfaces.insert(OffControlInterface::INTERFACE_NAME);

    ProxyBusObject pbo(busAttachment, deviceInfo->GetBusName().c_str(), LampServiceObjectPath, deviceInfo->GetSessionId());
    pbo.AddInterface(LampServiceDetailsInterfaceName);

    MsgArg dimmableProperty;
    status = pbo.GetProperty(LampServiceDetailsInterfaceName, "Dimmable", dimmableProperty);
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: %s Failed to read Dimmable", __func__, deviceInfo->GetBusName().c_str()));
    } else {
        bool value;
        status = dimmableProperty.Get("b", &value);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: %s failed to decode Dimmable", __func__, deviceInfo->GetBusName().c_str()));
        } else {
            QCC_DbgPrintf(("%s: %s has brightness", __func__, deviceInfo->GetBusName().c_str()));
            interfaces.insert(BrightnessInterface::INTERFACE_NAME);
        }
    }

    MsgArg colorProperty;
    status = pbo.GetProperty(LampServiceDetailsInterfaceName, "Color", colorProperty);
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: %s Failed to read Color", __func__, deviceInfo->GetBusName().c_str()));
    } else {
        bool value;
        status = colorProperty.Get("b", &value);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: %s failed to decode Color", __func__, deviceInfo->GetBusName().c_str()));
        } else if (value) {
            QCC_DbgPrintf(("%s: %s has color", __func__, deviceInfo->GetBusName().c_str()));
            interfaces.insert(ColorInterface::INTERFACE_NAME);
        }
    }

    MsgArg variableColorTempProperty;
    status = pbo.GetProperty(LampServiceDetailsInterfaceName, "VariableColorTemp", variableColorTempProperty);
    if (status != ER_OK) {
            QCC_LogError(status, ("%s: %s Failed to read VariableColorTemp", __func__, deviceInfo->GetBusName().c_str()));
    } else {
        bool value;
        status = variableColorTempProperty.Get("b", &value);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: %s failed to decode VariableColorTemp", __func__, deviceInfo->GetBusName().c_str()));
        } else if (value) {
            QCC_DbgPrintf(("%s: %s has color temperature", __func__, deviceInfo->GetBusName().c_str()));
            interfaces.insert(ColorTemperatureInterface::INTERFACE_NAME);
        }
    }

    QCC_DbgPrintf(("%s: Installing LSF translator for device %s", __func__, deviceInfo->GetBusName().c_str()));

    deviceInfo->RegisterTranslator("/org/allseen/LSF/Lamp", make_shared<CdmLsfTranslator>(busAttachment, interfaces));
}


CdmLsfTranslator::CdmLsfTranslator(BusAttachment& busAttachment, const std::unordered_set<std::string>& interfaces)
    : m_busAttachment(busAttachment), m_interfaces(interfaces) {
}

CdmLsfTranslator::~CdmLsfTranslator() {
}

Ref<CdmInterface> CdmLsfTranslator::CreateInterface(const CdmInterfaceType type, Ref<InterfaceControllerListener> listener, Ref<ProxyBusObject> pbo) {
    if (type == OnOffStatusInterface::INTERFACE_TYPE && m_interfaces.count(OnOffStatusInterface::INTERFACE_NAME)) {
        return mkRef<OnOffStatusIntfControllerLsfTranslator>(m_busAttachment, dynamic_pointer_cast<OnOffStatusIntfControllerListener>(listener), pbo);
    } else if (type == OnControlInterface::INTERFACE_TYPE && m_interfaces.count(OnControlInterface::INTERFACE_NAME)) {
        return mkRef<OnControlIntfControllerLsfTranslator>(m_busAttachment, dynamic_pointer_cast<OnControlIntfControllerListener>(listener), pbo);
    } else if (type == OffControlInterface::INTERFACE_TYPE && m_interfaces.count(OffControlInterface::INTERFACE_NAME)) {
        return mkRef<OffControlIntfControllerLsfTranslator>(m_busAttachment, dynamic_pointer_cast<OffControlIntfControllerListener>(listener), pbo);
    } else if (type == BrightnessInterface::INTERFACE_TYPE && m_interfaces.count(BrightnessInterface::INTERFACE_NAME)) {
        //return mkRef<BrightnessIntfControllerLsfTranslator>(m_busAttachment, dynamic_pointer_cast<BrightnessIntfControllerListener>(listener), pbo);
    } else if (type == ColorInterface::INTERFACE_TYPE && m_interfaces.count(ColorInterface::INTERFACE_NAME)) {
        //return mkRef<ColorIntfControllerLsfTranslator>(m_busAttachment, dynamic_pointer_cast<ColorIntfControllerListener>(listener), pbo);
    } else if (type == ColorTemperatureInterface::INTERFACE_TYPE && m_interfaces.count(ColorTemperatureInterface::INTERFACE_NAME)) {
        //return mkRef<ColorTemperatureIntfControllerLsfTranslator>(m_busAttachment, dynamic_pointer_cast<ColorTemperatureIntfControllerListener>(listener), pbo);
    }
    return Ref<CdmInterface>();
}

////////////////////////////////////////
//// OnOffStatusIntfControllerLsfTranslator
////////////////////////////////////////

OnOffStatusIntfControllerLsfTranslator::OnOffStatusIntfControllerLsfTranslator(BusAttachment& busAttachment, Ref<OnOffStatusIntfControllerListener> listener, Ref<ProxyBusObject> pbo)
  : OnOffStatusIntfController(busAttachment, listener, pbo),
    m_busAttachment(busAttachment), m_interfaceListener(listener), m_proxyObject(pbo), m_lampStateChanged(NULL)
{
}

OnOffStatusIntfControllerLsfTranslator::~OnOffStatusIntfControllerLsfTranslator() {
    QStatus status;
    if (m_lampStateChanged) {
        status = m_busAttachment.UnregisterSignalHandler(this, static_cast<SignalHandler>(&OnOffStatusIntfControllerLsfTranslator::LampStateChanged), m_lampStateChanged, NULL);
        if (ER_OK != status) {
            QCC_LogError(status, ("%s: UnregisterSignalHandler for ChannelListChanged signal failed.", __func__));
        }
    }
}

QStatus OnOffStatusIntfControllerLsfTranslator::Init() {
    QStatus status;
    status = m_proxyObject->AddInterface(LampServiceStateInterfaceName);
    if (status != ER_OK && status != ER_BUS_IFACE_ALREADY_EXISTS) {
        QCC_LogError(status, ("%s: AddInterface failed.", __func__));
        return status;
    }

    const InterfaceDescription* intf = m_busAttachment.GetInterface(LampServiceStateInterfaceName);
    if (!intf) {
        status = ER_FAIL;
        QCC_LogError(status, ("%s: failed to get interface description.", __func__));
        return status;
    }

    m_lampStateChanged = intf->GetMember("LampStateChanged");
    if (!m_lampStateChanged) {
        status = ER_FAIL;
        QCC_LogError(status, ("%s: failed to resolve LampStateChanged signal.", __func__));
        return status;
    }

    status = m_busAttachment.RegisterSignalHandler(this, static_cast<SignalHandler>(&OnOffStatusIntfControllerLsfTranslator::LampStateChanged), m_lampStateChanged, NULL);
    if (ER_OK != status) {
        QCC_LogError(status, ("%s: RegisterSignalHandler for ChannelListChanged signal failed.", __func__));
        return status;
    }

    std::vector<const ajn::InterfaceDescription*> interfaces(m_proxyObject->GetInterfaces());
    m_proxyObject->GetInterfaces(interfaces.data(), interfaces.size());
    return ER_OK;
}

QStatus OnOffStatusIntfControllerLsfTranslator::GetIsOn(void* context) {
    return m_proxyObject->GetPropertyAsync(LampServiceStateInterfaceName, "OnOff", this, (ProxyBusObject::Listener::GetPropertyCB)&OnOffStatusIntfControllerLsfTranslator::GetOnOffPropertyCB, context);
}

void OnOffStatusIntfControllerLsfTranslator::GetOnOffPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context) {
    if (!obj) {
        return;
    }

    bool val;
    value.Get("b", &val);
    m_interfaceListener->OnResponseGetIsOn(status, obj->GetPath(), val, context);
}

void OnOffStatusIntfControllerLsfTranslator::LampStateChanged(const InterfaceDescription::Member* member, const char* srcPath, Message& message) {
    MsgArg property;
    QCC_DbgPrintf(("%s: State updated!", __func__));

    m_busAttachment.EnableConcurrentCallbacks();
    QStatus status = m_proxyObject->GetProperty(LampServiceStateInterfaceName, "OnOff", property);
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: Failed to get OnOff state!", __func__));
        return;
    }

    bool value;
    status = property.Get("b", &value);
    if (status) {
        QCC_LogError(status, ("%s: Bad type %d", __func__, property.typeId));
        return;
    }

    m_interfaceListener->OnIsOnChanged(srcPath, value);
}

////////////////////////////////////////
//// OnControlIntfControllerLsfTranslator
////////////////////////////////////////

OnControlIntfControllerLsfTranslator::OnControlIntfControllerLsfTranslator(BusAttachment& busAttachment, Ref<OnControlIntfControllerListener> listener, Ref<ProxyBusObject> pbo)
    : OnControlIntfController(busAttachment, listener, pbo),
      m_busAttachment(busAttachment), m_interfaceListener(listener), m_proxyObject(pbo)
{
}

OnControlIntfControllerLsfTranslator::~OnControlIntfControllerLsfTranslator() {
}

QStatus OnControlIntfControllerLsfTranslator::Init() {
    QStatus status;
    status = m_proxyObject->AddInterface(LampServiceStateInterfaceName);
    if (status != ER_OK && status != ER_BUS_IFACE_ALREADY_EXISTS) {
        QCC_LogError(status, ("%s: AddInterface failed.", __func__));
        return status;
    }
    return ER_OK;
}

QStatus OnControlIntfControllerLsfTranslator::SwitchOn(void* context) {
    MsgArg arg("b", true);
    return m_proxyObject->SetPropertyAsync(LampServiceStateInterfaceName, "OnOff", arg, this, (ProxyBusObject::Listener::SetPropertyCB)&OnControlIntfControllerLsfTranslator::SetOnOffPropertyCB, context);
}

void OnControlIntfControllerLsfTranslator::SetOnOffPropertyCB(QStatus status, ProxyBusObject* obj, void* context) {
    m_interfaceListener->OnResponseSwitchOn(status, obj->GetPath(), context, QCC_StatusText(status), "");
}

////////////////////////////////////////
//// OffControlIntfControllerLsfTranslator
////////////////////////////////////////

OffControlIntfControllerLsfTranslator::OffControlIntfControllerLsfTranslator(BusAttachment& busAttachment, Ref<OffControlIntfControllerListener> listener, Ref<ProxyBusObject> pbo)
    : OffControlIntfController(busAttachment, listener, pbo),
      m_busAttachment(busAttachment), m_interfaceListener(listener), m_proxyObject(pbo)
{
}

OffControlIntfControllerLsfTranslator::~OffControlIntfControllerLsfTranslator() {
}

QStatus OffControlIntfControllerLsfTranslator::Init() {
    QStatus status;
    status = m_proxyObject->AddInterface(LampServiceStateInterfaceName);
    if (status != ER_OK && status != ER_BUS_IFACE_ALREADY_EXISTS) {
        QCC_LogError(status, ("%s: AddInterface failed.", __func__));
        return status;
    }
    return ER_OK;
}

QStatus OffControlIntfControllerLsfTranslator::SwitchOff(void* context) {
    MsgArg arg("b", false);
    return m_proxyObject->SetPropertyAsync(LampServiceStateInterfaceName, "OnOff", arg, this, (ProxyBusObject::Listener::SetPropertyCB)&OffControlIntfControllerLsfTranslator::SetOnOffPropertyCB, context);
}

void OffControlIntfControllerLsfTranslator::SetOnOffPropertyCB(QStatus status, ProxyBusObject* obj, void* context) {
    m_interfaceListener->OnResponseSwitchOff(status, obj->GetPath(), context, QCC_StatusText(status), "");
}



} //namespace services
} //namespace ajn
