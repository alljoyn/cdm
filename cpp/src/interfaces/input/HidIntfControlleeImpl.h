/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#ifndef HIDINTFCONTROLLEEIMPL_H_
#define HIDINTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/hae/interfaces/InterfaceControllee.h>
#include <alljoyn/hae/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/hae/interfaces/input/HidIntfControllee.h>

namespace ajn {
namespace services {

class HidIntfControlleeListener;
class HaeBusObject;

/**
 * Hid Interface Controllee implementation class
 */
class HidIntfControlleeImpl : public InterfaceControllee, public HidIntfControllee {
  public:
    /**
     * Create interface
     */
    static HaeInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, HaeBusObject& haeBusObject);

    /**
     * Constructor of HidIntfControlleeImpl
     */
    HidIntfControlleeImpl(BusAttachment& busAttachment, HidIntfControlleeListener& listener, HaeBusObject& haeBusObject);

    /**
     * Destructor of HidIntfControlleeImpl
     */
    virtual ~HidIntfControlleeImpl();

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
     * Set supported events
     * @param[in] supported events
     * @return status
     */
    virtual QStatus SetSupportedEvents(const HidInterface::SupportedInputEvents& supportedEvents);

    /**
     * Get supported events
     * @return mute
     */
    virtual const HidInterface::SupportedInputEvents& GetSupportedEvents() const { return m_supportedEvents; }

    /**
     * Handler of InjectEvents method
     * @param member
     * @param msg reference of alljoyn Message
     */
    void OnInjectEvents(const InterfaceDescription::Member* member, Message& msg);

  private:
    HidIntfControlleeImpl();

    BusAttachment& m_busAttachment;
    HidIntfControlleeListener& m_interfaceListener;
    SupportedInputEvents m_supportedEvents; // read-only, EmitsChangedSignal
    MethodHandlers m_methodHandlers;
};

} //namespace services
} //namespace ajn

#endif /* HIDINTFCONTROLLEEIMPL_H_ */
