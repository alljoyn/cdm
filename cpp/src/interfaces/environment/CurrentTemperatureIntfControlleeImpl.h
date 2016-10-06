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

#ifndef CURRENTTEMPERATUREINTFCONTROLLEEIMPL_H_
#define CURRENTTEMPERATUREINTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/cdm/interfaces/InterfaceControllee.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/cdm/interfaces/environment/CurrentTemperatureIntfControllee.h>

namespace ajn {
namespace services {

class CurrentTemperatureIntfControlleeListener;
class CdmBusObject;

/**
 * CurrentTemperature interface controllee implementation class
 */
class CurrentTemperatureIntfControlleeImpl : public InterfaceControllee, public CurrentTemperatureIntfControllee {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Constructor of CurrentTemperatureIntfControlleeImpl
     */
    CurrentTemperatureIntfControlleeImpl(BusAttachment& busAttachment, CurrentTemperatureIntfControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Destructor of CurrentTemperatureIntfControlleeImpl
     */
    virtual ~CurrentTemperatureIntfControlleeImpl();

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
     * Set current temperature
     * @param[in] value current temperature
     * @return status
     */
    virtual QStatus SetCurrentValue(const double value);

    /**
     * Get current temperature
     * @return Current temperature
     */
    virtual const double GetCurrentValue() const { return m_CurrentValue; }

    /**
     * Set precision
     * @param[in] precision precision
     * @return status
     */
    virtual QStatus SetPrecision(const double precision);

    /**
     * Get precision
     * @return Precision
     */
    virtual const double GetPrecision() const { return m_precision; }

    /**
     * Set the minimum update time
     * @param[in] updateMinTime the minimum update time
     * @return status
     */
    virtual QStatus SetUpdateMinTime(const uint16_t updateMinTime);

    /**
     * Get the minimum update time
     * @return The minimum update time
     */
    virtual const uint16_t GetUpdateMinTime() const { return m_updateMinTime; }

  private:
    CurrentTemperatureIntfControlleeImpl();

    BusAttachment& m_busAttachment;
    CurrentTemperatureIntfControlleeListener& m_interfaceListener;
    double m_CurrentValue;                       // read-only, EmitsChangedSignal
    double m_precision;                          // read-only, EmitsChangedSignal
    uint16_t m_updateMinTime;                    // read-only, EmitsChangedSignal
    MethodHandlers m_methodHandlers;
};

} //namespace services
} //namespace ajn

#endif /* CURRENTTEMPERATUREINTFCONTROLLEEIMPL_H_ */