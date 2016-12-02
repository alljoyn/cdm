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

#ifndef CYCLECONTROLINTFCONTROLLERIMPL_H_
#define CYCLECONTROLINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/CycleControlIntfController.h>

namespace ajn {
namespace services {

class CycleControlIntfControllerListener;
class CdmProxyBusObject;

/**
 * CycleControl Interface Controller implementation class
 */
class CycleControlIntfControllerImpl : public InterfaceController, public CycleControlIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of CycleControlIntfControllerImpl
     */
    CycleControlIntfControllerImpl(BusAttachment& busAttachment, CycleControlIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of CycleControlIntfControllerImpl
     */
    virtual ~CycleControlIntfControllerImpl();

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
     * Get operational state
     * @param[in] context
     * @return status
     */
    virtual QStatus GetOperationalState(void* context);

    /**
     * Get supported operational commands
     * @param[in] context
     * @return status
     */
    virtual QStatus GetSupportedOperationalCommands(void* context);

    /**
     * Get supported operational states
     * @param[in] context
     * @return status
     */
    virtual QStatus GetSupportedOperationalStates(void* context);

    /**
     * Execute command
     * @param[in] command to execute
     * @param[in] context
     * @return status
     */
    virtual QStatus ExecuteCommand(const CycleControlOperationalCommand command, void* context);

  private:
    CycleControlIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);

    void GetOperationalStatePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    void GetSupportedOperationalCommandsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    void GetSupportedOperationalStatesPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    void ExecuteCommandReplyHandler(Message& message, void* context);

    BusAttachment& m_busAttachment;
    CycleControlIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* CYCLECONTROLINTFCONTROLLERIMPL_H_ */