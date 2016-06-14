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

#ifndef RAPIDMODETIMEDINTFCONTROLLEEIMPL_H_
#define RAPIDMODETIMEDINTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/hae/interfaces/InterfaceControllee.h>
#include <alljoyn/hae/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/hae/interfaces/operation/RapidModeTimedIntfControllee.h>

namespace ajn {
namespace services {

class RapidModeTimedIntfControlleeListener;
class HaeBusObject;

/**
 * RapidModeTimed Interface Controllee implementation class
 */
class RapidModeTimedIntfControlleeImpl : public InterfaceControllee, public RapidModeTimedIntfControllee {
  public:
    /**
     * Create interface
     */
    static HaeInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, HaeBusObject& haeBusObject);

    /**
     * Constructor of RapidModeTimedIntfControlleeImpl
     */
    RapidModeTimedIntfControlleeImpl(BusAttachment& busAttachment, RapidModeTimedIntfControlleeListener& listener, HaeBusObject& haeBusObject);

    /**
     * Destructor of RapidModeTimedIntfControlleeImpl
     */
    virtual ~RapidModeTimedIntfControlleeImpl();

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
     * Get rapid mode minutes remaining
     * @return rapid mode minutes remaining
     */
    virtual const uint16_t GetRapidModeMinutesRemaining() const { return m_rapidModeMinutesRemaining; }

    /**
     * Set rapid mode minutes remaining
     * @param[in] value rapid mode minutes remaining
     * @return status
     */
    virtual QStatus SetRapidModeMinutesRemaining(const uint16_t value);

    /**
     * Get max set minutes
     * @return max set minutes
     */
    virtual const uint16_t GetMaxSetMinutes() const { return m_maxSetMinutes; }

    /**
     * Set max set minutes
     * @param[in] value max set minutes
     * @return status
     */
    virtual QStatus SetMaxSetMinutes(const uint16_t value);

  private:
    RapidModeTimedIntfControlleeImpl();
    bool IsRapidModeMinutesRemainingValid(uint16_t value);

    BusAttachment& m_busAttachment;
    RapidModeTimedIntfControlleeListener& m_interfaceListener;
    MethodHandlers m_methodHandlers;
    uint16_t m_rapidModeMinutesRemaining; // read-write, EmitsChangedSignal
    uint16_t m_maxSetMinutes;             // read-only, const
    bool m_maxSetMinutesInit;
};

} //namespace services
} //namespace ajn

#endif /* RAPIDMODETIMEDINTFCONTROLLEEIMPL_H_ */
