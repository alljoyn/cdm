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

#ifndef TARGETTEMPERATURELEVELINTFCONTROLLEEIMPL_H_
#define TARGETTEMPERATURELEVELINTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/hae/interfaces/InterfaceControllee.h>
#include <alljoyn/hae/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/hae/interfaces/environment/TargetTemperatureLevelIntfControllee.h>

namespace ajn {
namespace services {

class TargetTemperatureLevelIntfControlleeListener;
class HaeBusObject;

/**
 * TargetTemperatureLevel interface controllee implementation class
 */
class TargetTemperatureLevelIntfControlleeImpl : public InterfaceControllee, public TargetTemperatureLevelIntfControllee {
  public:

    /**
     * Create interface
     */
    static HaeInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, HaeBusObject& haeBusObject);

    /**
     * Constructor of TargetTemperatureLevelIntfControlleeImpl
     */
    TargetTemperatureLevelIntfControlleeImpl(BusAttachment& busAttachment, TargetTemperatureLevelIntfControlleeListener& listener, HaeBusObject& haeBusObject);

    /**
     * Destructor of TargetTemperatureLevelIntfControlleeImpl
     */
    virtual ~TargetTemperatureLevelIntfControlleeImpl();

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
     * Set TargetTemperatureLevel
     * @param[in] TargetTemperatureLevel
     * @return status
     */
    virtual QStatus SetTargetLevel(const uint8_t value);

    /**
     * Get TargetTemperatureLevel
     * @return TargetTemperatureLevel
     */
    virtual const uint8_t GetTargetLevel() const { return m_TargetLevel; }

    /**
     * Set Maximum value of target temperature level
     * @param[in] TargetTemperatureLevel
     * @return status
     */
    virtual QStatus SetMaxLevel(const uint8_t value);

    /**
     * Get Maximum value of target temperature level
     * @return TargetTemperatureLevel
     */
    virtual const uint8_t GetMaxLevel() const { return m_MaxLevel; }

    /**
     * Set Selectable TemperatureLevel Levels
     * @param[in] SelectableTemperatureLevels
     * @return status
     */
    virtual QStatus SetSelectableTemperatureLevels(const TargetTemperatureLevelInterface::TemperatureLevels& levels);

    /**
     * Get Selectable TemperatureLevel Levels
     * @return SelectableTemperatureLevels
     */
    virtual const TargetTemperatureLevelInterface::TemperatureLevels& GetSelectableTemperatureLevels() const { return m_SelectableTemperatureLevels; }
  private:
    TargetTemperatureLevelIntfControlleeImpl();

    BusAttachment& m_busAttachment;
    TargetTemperatureLevelIntfControlleeListener& m_interfaceListener;

    uint8_t AdjustTargetValue(uint8_t value);
    bool IsValidTargetValue(uint8_t value);
    uint8_t m_TargetLevel;                       // read-write, EmitsChangedSignal
    uint8_t m_MaxLevel;
    TargetTemperatureLevelInterface::TemperatureLevels m_SelectableTemperatureLevels;
    MethodHandlers m_methodHandlers;
};

} //namespace services
} //namespace ajn

#endif /* TARGETTEMPERATURELEVELINTFCONTROLLEEIMPL_H_ */
