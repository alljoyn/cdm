/******************************************************************************
 *  * 
 *    Copyright (c) 2016 Open Connectivity Foundation and AllJoyn Open
 *    Source Project Contributors and others.
 *    
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0

 ******************************************************************************/

#ifndef DISHWASHINGCYCLEPHASEINTFCONTROLLERIMPL_H_
#define DISHWASHINGCYCLEPHASEINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/DishWashingCyclePhaseIntfController.h>

namespace ajn {
namespace services {

class DishWashingCyclePhaseIntfControllerListener;
class CdmProxyBusObject;

/**
 * DishWashingCyclePhase Interface Controller implementation class
 */
class DishWashingCyclePhaseIntfControllerImpl : public InterfaceController, public DishWashingCyclePhaseIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of DishWashingCyclePhaseIntfControllerImpl
     */
    DishWashingCyclePhaseIntfControllerImpl(BusAttachment& busAttachment, DishWashingCyclePhaseIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of DishWashingCyclePhaseIntfControllerImpl
     */
    virtual ~DishWashingCyclePhaseIntfControllerImpl();

    /**
     * Initialize interface
     * @return status
     */
    virtual QStatus Init();

    /**
     * Get bus attachment
     * @return bus attachment
     */
    virtual BusAttachment& GetBusAttachment() const { return m_busAttachment; }

    /**
     * Get current cycle phase
     * @param[in] context
     * @return status
     */
    virtual QStatus GetCyclePhase(void* context);

    /**
     * Get list of supported cycle phases
     * @param[in] context
     * @return status
     */
    virtual QStatus GetSupportedCyclePhases(void* context );

    /**
     * Get vedor defined cycles descriptions
     * @param[in] context
     * @return status
     */
    virtual QStatus GetCyclePhasesDescriptions(const qcc::String& language, void* context);

  private:
    DishWashingCyclePhaseIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);

    void GetCyclePhasePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetSupportedCyclePhasesPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetCyclePhasesDescriptionReplyHandler(Message& message, void* context);

    BusAttachment& m_busAttachment;
    DishWashingCyclePhaseIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* DISHWASHINGCYCLEPHASEINTFCONTROLLERIMPL_H_ */