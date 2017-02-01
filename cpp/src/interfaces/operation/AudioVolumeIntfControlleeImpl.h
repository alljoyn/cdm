/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF), AllJoyn Open Source
 *    Project (AJOSP) Contributors and others.
 *    
 *    SPDX-License-Identifier: Apache-2.0
 *    
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *    
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
 *    
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *    
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
******************************************************************************/

#ifndef AUDIOVOLUMEINTFCONTROLLEEIMPL_H_
#define AUDIOVOLUMEINTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/cdm/interfaces/InterfaceControllee.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/cdm/interfaces/operation/AudioVolumeIntfControllee.h>

namespace ajn {
namespace services {

class AudioVolumeIntfControlleeListener;
class CdmBusObject;

/**
 * AudioVolume Interface Controllee implementation class
 */
class AudioVolumeIntfControlleeImpl : public InterfaceControllee, public AudioVolumeIntfControllee {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Constructor of AudioVolumeIntfControlleeImpl
     */
    AudioVolumeIntfControlleeImpl(BusAttachment& busAttachment, AudioVolumeIntfControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Destructor of AudioVolumeIntfControlleeImpl
     */
    virtual ~AudioVolumeIntfControlleeImpl();

    /**
     * Initialize interface
     * @return status
     */
     virtual QStatus Init();

    /**
     * a callback function for getting property.
     * @param propName   Identifies the property to get
     * @param[out] val   Returns the property value. The type of this value is the actual value type.
     * @return status
     */
    virtual QStatus OnGetProperty(const qcc::String& propName, MsgArg& val);

    /**
     * a callback function for setting property.
     * @param propName  Identifies the property to set
     * @param val       The property value to set. The type of this value is the actual value type.
     */
    virtual QStatus OnSetProperty(const qcc::String& propName, MsgArg& val);

    /**
     * method handler
     * @param member    Method interface member entry.
     * @param message   The received method call message.
     */
    virtual void OnMethodHandler(const InterfaceDescription::Member* member, Message& msg);

    /**
     * Get method handlers
     * @return MethodHandlers
     */
    virtual const MethodHandlers& GetMethodHanders() const { return m_methodHandlers; }

    /**
     * Get bus attachment
     * @return bus attachment
     */
    virtual BusAttachment& GetBusAttachment() const { return m_busAttachment; }

    /**
     * Set volume
     * @param[in] volume
     * @return status
     */
    virtual QStatus SetVolume(const uint8_t volume);

    /**
     * Get volume
     * @return volume
     */
    virtual const uint8_t GetVolume() const { return m_volume; }

    /**
     * Set mute
     * @param[in] mute
     * @return status
     */
    virtual QStatus SetMute(const bool mute);

    /**
     * Get mute
     * @return mute
     */
    virtual const bool GetMute() const { return m_mute; }

    /**
     * Set max volume
     * @param[in] max volume
     * @return status
     */
    virtual QStatus SetMaxVolume(const uint8_t maxVolume);

    /**
     * Get max volume
     * @return max volume
     */
    virtual const uint8_t GetMaxVolume() const { return m_maxVolume; }

  private:
    AudioVolumeIntfControlleeImpl();

    BusAttachment& m_busAttachment;
    AudioVolumeIntfControlleeListener& m_interfaceListener;
    uint8_t m_volume;                   // read-write, EmitsChangedSignal
    bool m_mute;                        // read-write, EmitsChangedSignal
    uint8_t m_maxVolume;                // read-only, EmitsChangedSignal
    MethodHandlers m_methodHandlers;
};

} //namespace services
} //namespace ajn

#endif /* AUDIOVOLUMEINTFCONTROLLEEIMPL_H_ */