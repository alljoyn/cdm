/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#ifndef AUDIOVOLUMEINTFCONTROLLERIMPL_H_
#define AUDIOVOLUMEINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/AudioVolumeIntfController.h>

namespace ajn {
namespace services {

class AudioVolumeIntfControllerListener;

/**
 * AudioVolume Interface Controller implementation class
 */
class AudioVolumeIntfControllerImpl : public InterfaceController, public AudioVolumeIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, ProxyBusObject& ProxyBusObject);

    /**
     * Constructor of AudioVolumeIntfControllerImpl
     */
    AudioVolumeIntfControllerImpl(BusAttachment& busAttachment, AudioVolumeIntfControllerListener& listener, ProxyBusObject& ProxyBusObject);

    /**
     * Destructor of AudioVolumeIntfControllerImpl
     */
    virtual ~AudioVolumeIntfControllerImpl();

    /**
     * Initialize interface
     * @return status
     */
    virtual QStatus Init();

    /**
     * Get bus attachment
     * @return bus attachment
     */
    virtual BusAttachment& GetBusAttachment() const { return m_busAttachment; }

    /**
     * Get Volume property
     * (Speaker volume index of the device.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetVolume(void* context);

    /**
     * Set Volume property
     * (Speaker volume index of the device.)
     * @param[in] value The volume to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetVolume(const uint8_t value, void* context);

    /**
     * Get MaxVolume property
     * (Maximum value allowed for Volume.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetMaxVolume(void* context);

    /**
     * Get Mute property
     * (If true, state of volume is muted.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetMute(void* context);

    /**
     * Set Mute property
     * (If true, state of volume is muted.)
     * @param[in] value The mute to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetMute(const bool value, void* context);

  private:
    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void GetVolumePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetVolumePropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetMaxVolumePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetMutePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetMutePropertyCB(QStatus status, ProxyBusObject* obj, void* context);

    BusAttachment& m_busAttachment;
    AudioVolumeIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* AUDIOVOLUMEINTFCONTROLLERIMPL_H_ */