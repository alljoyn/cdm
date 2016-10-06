/******************************************************************************
 *  *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
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
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#ifndef FANSPEEDLEVELINTFCONTROLLEEIMPL_H_
#define FANSPEEDLEVELINTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/cdm/interfaces/InterfaceControllee.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/cdm/interfaces/operation/FanSpeedLevelIntfControllee.h>

namespace ajn {
namespace services {

class FanSpeedLevelIntfControlleeListener;
class CdmBusObject;

/**
 * FanSpeedLevel Interface Controllee implementation class
 */
class FanSpeedLevelIntfControlleeImpl : public InterfaceControllee, public FanSpeedLevelIntfControllee {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Constructor of FanSpeedLevelIntfControlleeImpl
     */
    FanSpeedLevelIntfControlleeImpl(BusAttachment& busAttachment, FanSpeedLevelIntfControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Destructor of FanSpeedLevelIntfControlleeImpl
     */
    virtual ~FanSpeedLevelIntfControlleeImpl();

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
     * Set FanSpeedLevel
     * @param[in] FanSpeedLevel
     * @return status
     */
    virtual QStatus SetFanSpeedLevel(const uint8_t value);

    /**
     * Get FanSpeedLevel
     * @return state
     */
    virtual const uint8_t GetFanSpeedLevel() const { return m_FanSpeedLevel; }

    /**
     * Set MaxFanSpeedLevel
     * @param[in] MaxFanSpeedLevel
     * @return status
     */
    virtual QStatus SetMaxFanSpeedLevel(const uint8_t value);

    /**
     * Get MaxFanSpeedLevel
     * @return state
     */
    virtual const uint8_t GetMaxFanSpeedLevel() const { return m_MaxFanSpeedLevel; }

    /**
     * Set AutoMode
     * @param[in] AutoMode
     * @return status
     */
    virtual QStatus SetAutoMode(const uint8_t value);

    /**
     * Get AutoMode
     * @return state
     */
    virtual const uint8_t GetAutoMode() const { return m_AutoMode; }

  private:
    FanSpeedLevelIntfControlleeImpl();
    bool IsAutoModeValid(uint8_t autoMode);

    BusAttachment& m_busAttachment;
    FanSpeedLevelIntfControlleeListener& m_interfaceListener;
    MethodHandlers m_methodHandlers;

    uint8_t m_FanSpeedLevel;             // read-write, EmitsChangedSignal
    uint8_t m_MaxFanSpeedLevel;      // read-only, EmitsChangedSignal
    uint8_t m_AutoMode;                     // read-write, EmitsChangedSignal
};

} //namespace services
} //namespace ajn

#endif /* FANSPEEDLEVELINTFCONTROLLEEIMPL_H_ */