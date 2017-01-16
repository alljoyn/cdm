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

#ifndef CDMLSFTRANSLATOR_H_
#define CDMLSFTRANSLATOR_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/MessageReceiver.h>
#include <alljoyn/ProxyBusObject.h>
#include <alljoyn/cdm/controller/InterfaceController.h>
#include <interfaces/controller/operation/OnOffStatusIntfController.h>
#include <interfaces/controller/operation/OnOffStatusIntfControllerListener.h>
#include <alljoyn/cdm/controller/DeviceInfo.h>
#include <alljoyn/cdm/controller/CdmTranslator.h>
#include <interfaces/controller/operation/OnControlIntfController.h>
#include <interfaces/controller/operation/OffControlIntfController.h>
#include <interfaces/controller/operation/OnControlIntfControllerListener.h>
#include <interfaces/controller/operation/OffControlIntfControllerListener.h>
#include <unordered_set>


namespace ajn {
namespace services {


class CdmLsfTranslator : public CdmTranslator {
public:
    static void Attach(BusAttachment& busAttachment, Ref<DeviceInfo> deviceInfo);
    CdmLsfTranslator(BusAttachment& busAttachment, const std::unordered_set<std::string>& interfaces);
    ~CdmLsfTranslator() override;
    const std::unordered_set<std::string>& GetInterfaces() override { return m_interfaces; }
    Ref<CdmInterface> CreateInterface(const CdmInterfaceType type, Ref<InterfaceControllerListener> listener, Ref<ProxyBusObject> pbo) override;

private:
    BusAttachment& m_busAttachment;
    const std::unordered_set<std::string> m_interfaces;
};


class OnOffStatusIntfControllerLsfTranslator : public MessageReceiver, public ProxyBusObject::Listener, public OnOffStatusIntfController {
  public:
    OnOffStatusIntfControllerLsfTranslator(BusAttachment& busAttachment, Ref<OnOffStatusIntfControllerListener> listener, Ref<ProxyBusObject> pbo);
    ~OnOffStatusIntfControllerLsfTranslator() override;
    QStatus Init() override;
    BusAttachment& GetBusAttachment() const override { return m_busAttachment; }
    QStatus GetIsOn(void* context) override;

  private:
    void GetOnOffPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void LampStateChanged(const InterfaceDescription::Member* member, const char* srcPath, Message& message);

    BusAttachment& m_busAttachment;
    Ref<OnOffStatusIntfControllerListener> m_interfaceListener;
    Ref<ProxyBusObject> m_proxyObject;
    const InterfaceDescription::Member* m_lampStateChanged;
};

class OnControlIntfControllerLsfTranslator : public ProxyBusObject::Listener, public OnControlIntfController {
  public:
    OnControlIntfControllerLsfTranslator(BusAttachment& busAttachment, Ref<OnControlIntfControllerListener> listener, Ref<ProxyBusObject> pbo);
    ~OnControlIntfControllerLsfTranslator() override;
    QStatus Init() override;
    BusAttachment& GetBusAttachment() const override { return m_busAttachment; }
    QStatus SwitchOn(void* context) override;

  private:
    void SetOnOffPropertyCB(QStatus status, ProxyBusObject* obj, void* context);

    BusAttachment& m_busAttachment;
    Ref<OnControlIntfControllerListener> m_interfaceListener;
    Ref<ProxyBusObject> m_proxyObject;
};

class OffControlIntfControllerLsfTranslator : public ProxyBusObject::Listener, public OffControlIntfController {
  public:
    OffControlIntfControllerLsfTranslator(BusAttachment& busAttachment, Ref<OffControlIntfControllerListener> listener, Ref<ProxyBusObject> pbo);
    ~OffControlIntfControllerLsfTranslator() override;
    QStatus Init() override;
    BusAttachment& GetBusAttachment() const override { return m_busAttachment; }
    QStatus SwitchOff(void* context) override;

  private:
    void SetOnOffPropertyCB(QStatus status, ProxyBusObject* obj, void* context);

    BusAttachment& m_busAttachment;
    Ref<OffControlIntfControllerListener> m_interfaceListener;
    Ref<ProxyBusObject> m_proxyObject;
};


} //namespace services
} //namespace ajn

#endif //CDMLSFTRANSLATOR_H_
