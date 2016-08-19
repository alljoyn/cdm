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

#ifndef TARGETTEMPERATUREINTFCONTROLLEEIMPL_H_
#define TARGETTEMPERATUREINTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/cdm/interfaces/InterfaceControllee.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/cdm/interfaces/environment/TargetTemperatureIntfControllee.h>

namespace ajn {
namespace services {

class TargetTemperatureIntfControlleeListener;
class CdmBusObject;

/**
 * TargetTemperature interface controllee implementation class
 */
class TargetTemperatureIntfControlleeImpl : public InterfaceControllee, public TargetTemperatureIntfControllee {
  public:

    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Constructor of TargetTemperatureIntfControlleeImpl
     */
    TargetTemperatureIntfControlleeImpl(BusAttachment& busAttachment, TargetTemperatureIntfControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Destructor of TargetTemperatureIntfControlleeImpl
     */
    virtual ~TargetTemperatureIntfControlleeImpl();

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
     * Set TargetTemperature
     * @param[in] TargetTemperature
     * @return status
     */
    virtual QStatus SetTargetValue(const double value);

    /**
     * Get TargetTemperature
     * @return TargetTemperature
     */
    virtual const double GetTargetValue() const { return m_TargetValue; }

    /**
     * Set Minimum value of target temperature
     * @param[in] TargetTemperature
     * @return status
     */
    virtual QStatus SetMinValue(const double value);

    /**
     * Get Minimum value of target temperature
     * @return TargetTemperature
     */
    virtual const double GetMinValue() const { return m_MinValue; }

    /**
     * Set Maximum value of target temperature
     * @param[in] TargetTemperature
     * @return status
     */
    virtual QStatus SetMaxValue(const double value);

    /**
     * Get Maximum value of target temperature
     * @return TargetTemperature
     */
    virtual const double GetMaxValue() const { return m_MaxValue; }


    /**
     * Set step value of target temperature
     * @param[in] TargetTemperature
     * @return status
     */
    virtual QStatus SetStepValue(const double value);

    /**
     * Get step value of target temperature
     * @return TargetTemperature
     */
    virtual const double GetStepValue() const { return m_StepValue; }

    /**
     * Set strategy of adjusting target value
     * @param[in] strategy
     * @return status
     */
    virtual QStatus SetStrategyOfAdjustingTargetValue(AdjustTargetValue strategy);
  private:
    TargetTemperatureIntfControlleeImpl();

    BusAttachment& m_busAttachment;
    TargetTemperatureIntfControlleeListener& m_interfaceListener;

    double adjustTargetValue(double value);
    double m_TargetValue;                       // read-write, EmitsChangedSignal
    double m_MinValue;
    double m_MaxValue;
    double m_StepValue;
    MethodHandlers m_methodHandlers;

    AdjustTargetValue m_currentStrategy;
};

} //namespace services
} //namespace ajn

#endif /* TARGETTEMPERATUREINTFCONTROLLEEIMPL_H_ */
