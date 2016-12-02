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

#ifndef ROBOTCLEANINGCYCLEPHASEINTFCONTROLLERIMPL_H_
#define ROBOTCLEANINGCYCLEPHASEINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/RobotCleaningCyclePhaseIntfController.h>

namespace ajn {
namespace services {

class RobotCleaningCyclePhaseIntfControllerListener;
class CdmProxyBusObject;

/**
 * RobotCleaningCyclePhase Interface Controller implementation class
 */
class RobotCleaningCyclePhaseIntfControllerImpl : public InterfaceController, public RobotCleaningCyclePhaseIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of RobotCleaningCyclePhaseIntfControllerImpl
     */
    RobotCleaningCyclePhaseIntfControllerImpl(BusAttachment& busAttachment, RobotCleaningCyclePhaseIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of RobotCleaningCyclePhaseIntfControllerImpl
     */
    virtual ~RobotCleaningCyclePhaseIntfControllerImpl();

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
     * Get cycle phase
     * @param[in] context
     * @return status
     */
    QStatus GetCyclePhase(void* context);

    /**
     * Get supported cycle phases
     * @param[in] context
     * @return status
     */
    QStatus GetSupportedCyclePhases(void* context);

    /**
     * Get vendor phases description
     * @param[in] language tag
     * @param[in] context
     * @return status
     */
    virtual QStatus GetVendorPhasesDescription(const qcc::String& languageTag, void* context);

  private:
    RobotCleaningCyclePhaseIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void GetCyclePhasePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetSupportedCyclePhasesPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetVendorPhasesDescriptionReplyHandler(Message& message, void* context);

    BusAttachment& m_busAttachment;
    RobotCleaningCyclePhaseIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* ROBOTCLEANINGCYCLEPHASEINTFCONTROLLERIMPL_H_ */