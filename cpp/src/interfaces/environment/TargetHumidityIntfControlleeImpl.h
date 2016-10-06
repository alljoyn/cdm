/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#ifndef TARGETHUMIDITYINTFCONTROLLEEIMPL_H_
#define TARGETHUMIDITYINTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/cdm/interfaces/InterfaceControllee.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/cdm/interfaces/environment/TargetHumidityIntfControllee.h>

namespace ajn {
namespace services {

class TargetHumidityIntfControlleeListener;
class CdmBusObject;

/**
 * TargetHumidity interface controllee implementation class
 */
class TargetHumidityIntfControlleeImpl : public InterfaceControllee, public TargetHumidityIntfControllee {
  public:

    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Constructor of TargetHumidityIntfControlleeImpl
     */
    TargetHumidityIntfControlleeImpl(BusAttachment& busAttachment, TargetHumidityIntfControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Destructor of TargetHumidityIntfControlleeImpl
     */
    virtual ~TargetHumidityIntfControlleeImpl();

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
     * Set TargetHumidity
     * @param[in] TargetHumidity
     * @return status
     */
    virtual QStatus SetTargetValue(const uint8_t value);

    /**
     * Get TargetHumidity
     * @return TargetHumidity
     */
    virtual const uint8_t GetTargetValue() const { return m_TargetValue; }

    /**
     * Set Minimum value of target humidity
     * @param[in] TargetHumidity
     * @return status
     */
    virtual QStatus SetMinValue(const uint8_t value);

    /**
     * Get Minimum value of target humidity
     * @return TargetHumidity
     */
    virtual const uint8_t GetMinValue() const { return m_MinValue; }

    /**
     * Set Maximum value of target humidity
     * @param[in] TargetHumidity
     * @return status
     */
    virtual QStatus SetMaxValue(const uint8_t value);

    /**
     * Get Maximum value of target humidity
     * @return TargetHumidity
     */
    virtual const uint8_t GetMaxValue() const { return m_MaxValue; }


    /**
     * Set step value of target humidity
     * @param[in] TargetHumidity
     * @return status
     */
    virtual QStatus SetStepValue(const uint8_t value);

    /**
     * Get step value of target humidity
     * @return TargetHumidity
     */
    virtual const uint8_t GetStepValue() const { return m_StepValue; }

    /**
     * Set Selectable Humidity Levels
     * @param[in] SelectableHumidityLevels
     * @return status
     */
    virtual QStatus SetSelectableHumidityLevels(const TargetHumidityInterface::HumidityLevels& humidityLevels);

    /**
     * Get Selectable Humidity Levels
     * @return SelectableHumidityLevels
     */
    virtual const TargetHumidityInterface::HumidityLevels& GetSelectableHumidityLevels() const { return m_SelectableHumidityLevels; }

    /**
     * Set strategy of adjusting target value
     * @param[in] strategy
     * @return status
     */
    virtual QStatus SetStrategyOfAdjustingTargetValue(AdjustStrategy strategy);
  private:
    TargetHumidityIntfControlleeImpl();

    BusAttachment& m_busAttachment;
    TargetHumidityIntfControlleeListener& m_interfaceListener;

    uint8_t AdjustTargetValue(uint8_t value);
    bool IsValidTargetValue(uint8_t value);
    uint8_t m_TargetValue;                       // read-write, EmitsChangedSignal
    uint8_t m_MinValue;
    uint8_t m_MaxValue;
    uint8_t m_StepValue;
    TargetHumidityInterface::HumidityLevels m_SelectableHumidityLevels;
    MethodHandlers m_methodHandlers;

    AdjustStrategy m_currentStrategy;
};

} //namespace services
} //namespace ajn

#endif /* TARGETHUMIDITYINTFCONTROLLEEIMPL_H_ */