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

#ifndef MOISTUREOUTPUTLEVELINTFCONTROLLEEIMPL_H_
#define MOISTUREOUTPUTLEVELINTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/cdm/interfaces/InterfaceControllee.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/cdm/interfaces/operation/MoistureOutputLevelIntfControllee.h>

namespace ajn {
namespace services {

class MoistureOutputLevelIntfControlleeListener;
class CdmBusObject;

/**
 * MoistureOutputLevel interface controllee implementation class
 */
class MoistureOutputLevelIntfControlleeImpl : public InterfaceControllee, public MoistureOutputLevelIntfControllee {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Constructor of MoistureOutputLevelIntfControlleeImpl
     */
    MoistureOutputLevelIntfControlleeImpl(BusAttachment& busAttachment, MoistureOutputLevelIntfControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Destructor of MoistureOutputLevelIntfControlleeImpl
     */
    virtual ~MoistureOutputLevelIntfControlleeImpl();

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
     * Get bus attachment
     * @return bus attachment
     */
    virtual BusAttachment& GetBusAttachment() const { return m_busAttachment; }

    /**
     * Get method handlers
     * @return MethodHandlers
     */
    virtual const MethodHandlers& GetMethodHanders() const { return m_methodHandlers; }

    /**
     * Get MoistureOutputLevel
     * @return MoistureOutputLevel
     */
    virtual const uint8_t GetMoistureOutputLevel () const { return m_moistureOutputLevel; }

    /**
     * Set MoistureOutputLevel
     * @param[in] value MoistureOutputLevel
     * @return status
     */
    virtual QStatus SetMoistureOutputLevel (const uint8_t value);

    /**
     * Get MaxMoistureOutputLevel
     * @return MaxMoistureOutputLevel
     */
    virtual const uint8_t GetMaxMoistureOutputLevel() const { return m_maxMoistureOutputLevel; }

    /**
     * Set MaxMoistureOutputLevel
     * @param[in] value MaxMoistureOutputLevel
     * @return status
     */
    virtual QStatus SetMaxMoistureOutputLevel (const uint8_t value);

    /**
     * Get AutoMode
     * @return AutoMode
     */
    virtual const uint8_t GetAutoMode () const { return m_autoMode; }

    /**
     * Set AutoMode
     * @param[in] autoMode AutoMode
     * @return status
     */
    virtual QStatus SetAutoMode (const uint8_t autoMode);

  private:
    MoistureOutputLevelIntfControlleeImpl();

    bool IsMoistureOutputLevelValid(uint8_t value);
    bool IsAutoModeValid(uint8_t autoMode);

    BusAttachment& m_busAttachment;
    MoistureOutputLevelIntfControlleeListener& m_interfaceListener;
    MethodHandlers m_methodHandlers;
    uint8_t m_moistureOutputLevel;            // read-write, EmitsChangedSignal
    uint8_t m_maxMoistureOutputLevel;         // read,       EmitsChangedSignal
    uint8_t m_autoMode;                       // read-write, EmitsChangedSignal
};

} //namespace services
} //namespace ajn

#endif /* MOISTUREOUTPUTLEVELINTFCONTROLLEEIMPL_H_ */