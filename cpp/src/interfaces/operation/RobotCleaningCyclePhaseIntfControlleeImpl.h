/******************************************************************************
 *  * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#ifndef ROBOTCLEANINGCYCLEPHASEINTFCONTROLLEEIMPL_H_
#define ROBOTCLEANINGCYCLEPHASEINTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/cdm/interfaces/InterfaceControllee.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/cdm/interfaces/operation/RobotCleaningCyclePhaseIntfControllee.h>

namespace ajn {
namespace services {

class RobotCleaningCyclePhaseIntfControlleeListener;
class CdmBusObject;

/**
 * RobotCleaningCyclePhase Interface Controllee implementation class
 */
class RobotCleaningCyclePhaseIntfControlleeImpl : public InterfaceControllee, public RobotCleaningCyclePhaseIntfControllee {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Constructor of RobotCleaningCyclePhaseIntfControlleeImpl
     */
    RobotCleaningCyclePhaseIntfControlleeImpl(BusAttachment& busAttachment, RobotCleaningCyclePhaseIntfControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Destructor of RobotCleaningCyclePhaseIntfControlleeImpl
     */
    virtual ~RobotCleaningCyclePhaseIntfControlleeImpl();

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
     * Set cycle phase
     * @param[in] cycle phase
     * @return status
     */
    virtual QStatus SetCyclePhase(const uint8_t cyclePhase);

    /**
     * Get cycle phase
     * @return cycle phase
     */
    virtual const uint8_t GetCyclePhase() const { return m_cyclePhase; }

    /**
     * Set supported cycle phases
     * @param[in] supported cycle phases
     * @return status
     */
    virtual QStatus SetSupportedCyclePhases(const SupportedCyclePhases& supportedCyclePhases);

    /**
     * Get supported cycle phases
     * @return supported cycle phases
     */
    virtual const SupportedCyclePhases& GetSupportedCyclePhases() const { return m_supportedCyclePhases; }

    /**
     * Handler of GetVendorPhasesDescription method
     * @param member
     * @param msg reference of alljoyn Message
     */
    void OnGetVendorPhasesDescription(const InterfaceDescription::Member* member, Message& msg);

  private:
    RobotCleaningCyclePhaseIntfControlleeImpl();

    BusAttachment& m_busAttachment;
    RobotCleaningCyclePhaseIntfControlleeListener& m_interfaceListener;
    uint8_t m_cyclePhase;                        // read-only, EmitsChangedSignal
    SupportedCyclePhases m_supportedCyclePhases; // read-only, EmitsChangedSignal
    MethodHandlers m_methodHandlers;
};

} //namespace services
} //namespace ajn

#endif /* ROBOTCLEANINGCYCLEPHASEINTFCONTROLLEEIMPL_H_ */