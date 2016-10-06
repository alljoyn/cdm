/******************************************************************************
 * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#ifndef TIMEDISPLAYINTFCONTROLLEEIMPL_H_
#define TIMEDISPLAYINTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/cdm/interfaces/InterfaceControllee.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/cdm/interfaces/userinterfacesettings/TimeDisplayIntfControllee.h>

namespace ajn {
namespace services {

class TimeDisplayIntfControlleeListener;
class CdmBusObject;

/**
 * TimeDisplay Interface Controllee implementation class
 */
class TimeDisplayIntfControlleeImpl : public InterfaceControllee, public TimeDisplayIntfControllee {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Constructor of TimeDisplayIntfControlleeImpl
     */
    TimeDisplayIntfControlleeImpl(BusAttachment& busAttachment, TimeDisplayIntfControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Destructor of TimeDisplayIntfControlleeImpl
     */
    virtual ~TimeDisplayIntfControlleeImpl();

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
     * Get DisplayTimeFormat
     * @return display time format
     */
    virtual const uint8_t GetDisplayTimeFormat() { return m_timeFormat; };

    /**
     * Set DisplayTimeFormat
     * @param[in] timeFormat timeFormat
     * @return ER_OK on success
     */
    virtual QStatus SetDisplayTimeFormat(const uint8_t timeFormat);

    /**
     * Get SupportedDisplayTimeFormats
     * @return list of supported time formats
     */
    virtual const std::vector<uint8_t>& GetSupportedDisplayTimeFormats() { return m_supportedDisplayTimeFormats; };
 
    virtual QStatus SetSupportedDisplayTimeFormats(const std::vector<uint8_t>& supportedTimeFormats);

  private:
    TimeDisplayIntfControlleeImpl();

    BusAttachment& m_busAttachment;
    TimeDisplayIntfControlleeListener& m_interfaceListener;
    MethodHandlers m_methodHandlers;

    uint8_t m_timeFormat;
    std::vector<uint8_t> m_supportedDisplayTimeFormats;

};

} //namespace services
} //namespace ajn

#endif /* TIMEDISPLAYINTFCONTROLLEEIMPL_H_ */