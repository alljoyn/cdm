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

#ifndef FILTERSTATUSINTFCONTROLLEEIMPL_H_
#define FILTERSTATUSINTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/cdm/interfaces/InterfaceControllee.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/cdm/interfaces/operation/FilterStatusIntfControllee.h>

namespace ajn {
namespace services {

class FilterStatusIntfControlleeListener;
class CdmBusObject;

/**
 * FilterStatus Interface Controllee implementation class
 */
class FilterStatusIntfControlleeImpl : public InterfaceControllee, public FilterStatusIntfControllee {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Constructor of FilterStatusIntfControlleeImpl
     */
    FilterStatusIntfControlleeImpl(BusAttachment& busAttachment, FilterStatusIntfControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Destructor of FilterStatusIntfControlleeImpl
     */
    virtual ~FilterStatusIntfControlleeImpl();

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
     * Get ExpectedLifeInDays
     * @return ExpectedLifeInDays
     */
    virtual const uint16_t GetExpectedLifeInDays() const { return m_expectedLifeInDays; }

    /**
     * Set ExpectedLifeInDays
     * @param[in] value ExpectedLifeInDays
     * @return status
     */
    virtual QStatus SetExpectedLifeInDays(const uint16_t value);

    /**
     * Get IsCleanable
     * @return IsCleanable
     */
    virtual const bool GetIsCleanable() const { return m_isCleanable; }

    /**
     * Set IsCleanable
     * @param[in] isCleanable IsCleanable
     * @return status
     */
    virtual QStatus SetIsCleanable(const bool isCleanable);

    /**
     * Get OrderPercentage
     * @return OrderPercentage
     */
    virtual const uint8_t GetOrderPercentage() const { return m_orderPercentage; }

    /**
     * Set OrderPercentage
     * @param[in] value OrderPercentage
     * @return status
     */
    virtual QStatus SetOrderPercentage(const uint8_t value);

    /**
     * Get Manufacturer
     * @return Manufacturer
     */
    virtual const qcc::String GetManufacturer() const { return m_manufacturer; }

    /**
     * Set Manufacturer
     * @return status
     */
    virtual QStatus SetManufacturer(const qcc::String& manufacturer);

    /**
     * Get PartNumber
     * @return PartNumber
     */
    virtual const qcc::String GetPartNumber() const { return m_partNumber; }

    /**
     * Set PartNumber
     * @return status
     */
    virtual QStatus SetPartNumber(const qcc::String& partNumber);

    /**
     * Get Url
     * @return Url
     */
    virtual const qcc::String GetUrl() const { return m_url; }

    /**
     * Set Url
     * @return status
     */
    virtual QStatus SetUrl(const qcc::String& url);

    /**
     * Get LifeRemaining
     * @return LifeRemaining
     */
    virtual const uint8_t GetLifeRemaining() const { return m_lifeRemaining; }

    /**
     * Set LifeRemaining
     * @param[in] value LifeRemaining
     * @return status
     */
    virtual QStatus SetLifeRemaining(const uint8_t value);

  private:
    FilterStatusIntfControlleeImpl();

    BusAttachment& m_busAttachment;
    FilterStatusIntfControlleeListener& m_interfaceListener;
    MethodHandlers m_methodHandlers;
    uint16_t m_expectedLifeInDays;   // read, EmitsChangedSignal
    bool m_isCleanable;              // read, EmitsChangedSignal
    uint8_t m_orderPercentage;       // read, EmitsChangedSignal
    qcc::String m_manufacturer;      // read, const
    qcc::String m_partNumber;        // read, const
    qcc::String m_url;               // read, const
    uint8_t m_lifeRemaining;         // read, EmitsChangedSignal
    bool m_manufacturerInit;
    bool m_partNumberInit;
    bool m_urlInit;
};

} //namespace services
} //namespace ajn

#endif /* FILTERSTATUSINTFCONTROLLEEIMPL_H_ */