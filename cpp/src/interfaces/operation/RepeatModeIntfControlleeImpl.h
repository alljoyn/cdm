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

#ifndef REPEATMODEINTFCONTROLLEEIMPL_H_
#define REPEATMODEINTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/hae/interfaces/InterfaceControllee.h>
#include <alljoyn/hae/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/hae/interfaces/operation/RepeatModeIntfControllee.h>

namespace ajn {
namespace services {

class RepeatModeIntfControlleeListener;
class HaeBusObject;

/**
 * RepeatMode Interface Controllee implementation class
 */
class RepeatModeIntfControlleeImpl : public InterfaceControllee, public RepeatModeIntfControllee {
  public:
    /**
     * Create interface
     */
    static HaeInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, HaeBusObject& haeBusObject);

    /**
     * Constructor of RepeatModeIntfControlleeImpl
     */
    RepeatModeIntfControlleeImpl(BusAttachment& busAttachment, RepeatModeIntfControlleeListener& listener, HaeBusObject& haeBusObject);

    /**
     * Destructor of RepeatModeIntfControlleeImpl
     */
    virtual ~RepeatModeIntfControlleeImpl();

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
     * Set RepeatMode
     * @param[in] RepeatMode
     * @return status
     */
    virtual QStatus SetRepeatMode(const bool value);

    /**
     * Get RepeatMode
     * @return RepeatMode
     */
    virtual const bool GetRepeatMode() const { return m_RepeatMode; }

  private:
    RepeatModeIntfControlleeImpl();

    BusAttachment& m_busAttachment;
    RepeatModeIntfControlleeListener& m_interfaceListener;
    MethodHandlers m_methodHandlers;

    bool m_RepeatMode;
};

} //namespace services
} //namespace ajn

#endif /* REPEATMODEINTFCONTROLLEEIMPL_H_ */
