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

#ifndef OVENCYCLEPHASEINTFCONTROLLEEIMPL_H_
#define OVENCYCLEPHASEINTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/hae/interfaces/InterfaceControllee.h>
#include <alljoyn/hae/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/hae/interfaces/operation/OvenCyclePhaseIntfControllee.h>

namespace ajn {
namespace services {

class OvenCyclePhaseIntfControlleeListener;
class HaeBusObject;

/**
 * OvenCyclePhase Interface Controllee implementation class
 */
class OvenCyclePhaseIntfControlleeImpl : public InterfaceControllee, public OvenCyclePhaseIntfControllee {
  public:
    /**
     * Create interface
     */
    static HaeInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, HaeBusObject& haeBusObject);

    /**
     * Constructor of OvenCyclePhaseIntfControlleeImpl
     */
    OvenCyclePhaseIntfControlleeImpl(BusAttachment& busAttachment, OvenCyclePhaseIntfControlleeListener& listener, HaeBusObject& haeBusObject);

    /**
     * Destructor of OvenCyclePhaseIntfControlleeImpl
     */
    virtual ~OvenCyclePhaseIntfControlleeImpl();

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
    virtual QStatus OnGetProperty(const qcc::String propName, MsgArg& val);

    /**
     * a callback function for setting property.
     * @param propName  Identifies the property to set
     * @param val       The property value to set. The type of this value is the actual value type.
     */
    virtual QStatus OnSetProperty(const qcc::String propName, MsgArg& val);

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
     * Get CyclePhase
     * @return cycle phase
     */
    virtual const uint8_t GetCyclePhase() const { return m_cyclePhase; }

    /**
     * Set SyclePhase
     * @param[in] cyclePhase
     * @return status
     */
    virtual QStatus SetCyclePhase(const uint8_t cyclePhase);

    /**
     * Get list of supported cycle phases
     * @return list of cycle phases
     */
    virtual const SupportedCyclePhases& GetSupportedCyclePhases() const { return m_supportedCyclePhases; }

    /**
     * Set list of supported cycle phases
     * @param[in] supportedPhases
     * @return status
     */
    virtual QStatus SetSupportedCyclePhases(const SupportedCyclePhases& supportedPhases);

    /**
     * Handler of GetCyclePhasesDescription method
     * @param[in] member
     * @param[in] msg reference of alljoyn Message
     */
    void OnGetCyclePhasesDescription(const InterfaceDescription::Member* member, Message& msg);

    /**
     * Set list of vendor defined cycle phases
     * @param[in] vendorPhases
     * @return status
     */
    virtual QStatus SetVendorDefinedCyclePhases(const std::vector<uint8_t>& vendorPhases);

  private:
    OvenCyclePhaseIntfControlleeImpl();

    BusAttachment& m_busAttachment;
    OvenCyclePhaseIntfControlleeListener& m_interfaceListener;
    MethodHandlers m_methodHandlers;
    uint8_t m_cyclePhase;
    SupportedCyclePhases m_supportedCyclePhases;
    std::vector<uint8_t> m_vendorDefinedCyclePhases;

};

} //namespace services
} //namespace ajn

#endif /* OVENCYCLEPHASEINTFCONTROLLEEIMPL_H_ */
