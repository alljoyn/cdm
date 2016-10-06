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

#ifndef CHANNELINTFCONTROLLEEIMPL_H_
#define CHANNELINTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/cdm/interfaces/InterfaceControllee.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/cdm/interfaces/operation/ChannelIntfControllee.h>

namespace ajn {
namespace services {

class ChannelIntfControlleeListener;
class CdmBusObject;

/**
 * Channel Interface Controllee implementation class
 */
class ChannelIntfControlleeImpl : public InterfaceControllee, public ChannelIntfControllee {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Constructor of ChannelIntfControlleeImpl
     */
    ChannelIntfControlleeImpl(BusAttachment& busAttachment, ChannelIntfControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Destructor of ChannelIntfControlleeImpl
     */
    virtual ~ChannelIntfControlleeImpl();

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
     * Set channel id
     * @return status
     */
    virtual QStatus SetChannelId(const qcc::String& channelId);

    /**
     * Get channel id
     * @return channel id
     */
    virtual const qcc::String GetChannelId() const { return m_channelId; }

    /**
     * Set total number of channels
     * @return status
     */
    virtual QStatus SetTotalNumberOfChannels(const uint16_t totalNumberOfChannels);

    /**
     * Get total number of channels
     * @return total number of channels
     */
    virtual const uint16_t GetTotalNumberOfChannels() const { return m_totalNumberOfChannels; }

    /**
     * Handler of GetChannelList method
     * @param member
     * @param msg reference of alljoyn Message
     */
    void OnGetChannelList(const InterfaceDescription::Member* member, Message& msg);

    /**
     * Emit ChannelListChanged signal
     * @return status
     */
    virtual QStatus EmitChannelListChanged();

  private:
    ChannelIntfControlleeImpl();

    BusAttachment& m_busAttachment;
    ChannelIntfControlleeListener& m_interfaceListener;
    qcc::String m_channelId;                   // read-write, EmitsChangedSignal
    uint8_t m_totalNumberOfChannels;           // read-only, EmitsChangedSignal
    MethodHandlers m_methodHandlers;
};

} //namespace services
} //namespace ajn

#endif /* CHANNELINTFCONTROLLEEIMPL_H_ */