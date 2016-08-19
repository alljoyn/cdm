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

#ifndef WATERLEVELINTFCONTROLLEEIMPL_H_
#define WATERLEVELINTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/cdm/interfaces/InterfaceControllee.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/cdm/interfaces/environment/WaterLevelIntfControllee.h>

namespace ajn {
namespace services {

class WaterLevelIntfControlleeListener;
class CdmBusObject;

/**
 * WaterLevel Interface Controllee implementation class
 */
class WaterLevelIntfControlleeImpl : public InterfaceControllee, public WaterLevelIntfControllee {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Constructor of WaterLevelIntfControlleeImpl
     */
    WaterLevelIntfControlleeImpl(BusAttachment& busAttachment, WaterLevelIntfControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Destructor of WaterLevelIntfControlleeImpl
     */
    virtual ~WaterLevelIntfControlleeImpl();

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
     * Get CurrentLevel
     * @return current level
     */
    virtual const uint8_t GetCurrentLevel() const {return m_currentLevel; }

    /**
     * Set CurrentLevel
     * @param[in] currentLevel currentLevel
     * @return ER_OK on success
     */
    virtual QStatus SetCurrentLevel (const uint8_t currentLevel);

    /**
     * Get MaxLevel
     * @return max level
     */
    virtual const uint8_t GetMaxLevel() const { return m_maxLevel; }

    /**
     * Set MaxLevel
     * @param[in] maxLevel maxLevel
     * @return ER_OK on success
     */
    virtual QStatus SetMaxLevel(const uint8_t maxLevel);

    /**
     * Get SupplySource
     * @return supply source
     */
    virtual const WaterLevelSupplySource GetSupplySource() const { return m_supplySource; }


    /**
     * Set SupplySource
     * @param[in] supplySource supply source
     * @return ER_OK on success
     */
    virtual QStatus SetSupplySource(const WaterLevelSupplySource supplySource);

  private:
    WaterLevelIntfControlleeImpl();

    BusAttachment& m_busAttachment;
    WaterLevelIntfControlleeListener& m_interfaceListener;
    MethodHandlers m_methodHandlers;
    uint8_t m_currentLevel;
    WaterLevelSupplySource m_supplySource;
    uint8_t m_maxLevel;
};

} //namespace services
} //namespace ajn

#endif /* WATERLEVELINTFCONTROLLEEIMPL_H_ */
