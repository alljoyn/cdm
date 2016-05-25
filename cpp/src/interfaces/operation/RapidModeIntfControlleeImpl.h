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

#ifndef RAPIDMODEINTFCONTROLLEEIMPL_H_
#define RAPIDMODEINTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/hae/interfaces/InterfaceControllee.h>
#include <alljoyn/hae/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/hae/interfaces/operation/RapidModeIntfControllee.h>

namespace ajn {
namespace services {

class RapidModeIntfControlleeListener;
class HaeBusObject;

/**
 * RapidMode Interface Controllee implementation class
 */
class RapidModeIntfControlleeImpl : public InterfaceControllee, public RapidModeIntfControllee {
  public:
    /**
     * Create interface
     */
    static HaeInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, HaeBusObject& haeBusObject);

    /**
     * Constructor of RapidModeIntfControlleeImpl
     */
    RapidModeIntfControlleeImpl(BusAttachment& busAttachment, RapidModeIntfControlleeListener& listener, HaeBusObject& haeBusObject);

    /**
     * Destructor of RapidModeIntfControlleeImpl
     */
    virtual ~RapidModeIntfControlleeImpl();

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
     * Get RapidMode
     * @return rapid mode
     */
    virtual const bool GetRapidMode() const { return m_rapidMode; }

    /**
     * Set RapidMode
     * @param[in] rapid mode
     * @return ER_OK on successful
     */
    virtual QStatus SetRapidMode(const bool rapidMode);

  private:
    RapidModeIntfControlleeImpl();

    BusAttachment& m_busAttachment;
    RapidModeIntfControlleeListener& m_interfaceListener;
    MethodHandlers m_methodHandlers;
    bool m_rapidMode;
};

} //namespace services
} //namespace ajn

#endif /* RAPIDMODEINTFCONTROLLEEIMPL_H_ */
