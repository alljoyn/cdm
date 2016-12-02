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

#ifndef HEATINGZONEINTFCONTROLLERIMPL_H_
#define HEATINGZONEINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/HeatingZoneIntfController.h>

namespace ajn {
namespace services {

class HeatingZoneIntfControllerListener;
class CdmProxyBusObject;

/**
 * HeatingZone Interface Controller implementation class
 */
class HeatingZoneIntfControllerImpl : public InterfaceController, public HeatingZoneIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of HeatingZoneIntfControllerImpl
     */
    HeatingZoneIntfControllerImpl(BusAttachment& busAttachment, HeatingZoneIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of HeatingZoneIntfControllerImpl
     */
    virtual ~HeatingZoneIntfControllerImpl();

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
     * Get number of heating zones
     * @param[in] context
     * @return status
     */
    virtual QStatus GetNumberOfHeatingZones(void* context);

    /**
     * Get list of max heating levels
     * @param[in] context
     * @return status
     */
    virtual QStatus GetMaxHeatingLevels(void* context );

    /**
     * Get list of heating levels
     * @param[in] context
     * @return status
     */
    virtual QStatus GetHeatingLevels(void* context);

  private:
    HeatingZoneIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);

    void GetNumberOfHeatingZonesPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    void GetMaxHeatingLevelsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    void GetHeatingLevelsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    HeatingZoneIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* HEATINGZONEINTFCONTROLLERIMPL_H_ */