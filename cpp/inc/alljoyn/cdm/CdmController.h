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


#ifndef CDMCONTROLLER_H_
#define CDMCONTROLLER_H_

#include <alljoyn/Status.h>
#include <alljoyn/cdm/CdmConfig.h>
#include <alljoyn/cdm/interfaces/CdmInterface.h>
#include <alljoyn/cdm/interfaces/CdmInterfaceTypes.h>

namespace ajn {

class AboutObjectDescription;

namespace services {

class CdmProxyBusObject;
class CdmControllerImpl;
class CdmInterface;
class InterfaceControllerListener;
class CdmAboutData;
class DeviceListener;
class DeviceInfo;

/**
 * Cdm Controller class.
 */
class CdmController {

  public:
    /**
     * Constructor of CdmController
     * @param[in] bus bus attachment
     * @param[in] aboutData CDM About data
     */
    CdmController(BusAttachment& bus, DeviceListener* listener);

    /**
     * Destructor of CdmController
     */
    virtual ~CdmController();

    /**
     * Enable peer-to-peer security.
     * @param[in] authMechanisms   ALLJOYN_SRP_LOGON, ALLJOYN_SRP_KEYX, ALLJOYN_ECDHE_NULL, ALLJOYN_ECDHE_PSK,
     *                         ALLJOYN_ECDHE_ECDSA, GSSAPI.
     * @param[in] listener authentication listener
     * @param[in] keyStoreFileName optional parameter to specify the filename of the default key store
     * @param[in] isShared optional parameter that indicates if the key store is shared between multiple applications.
     * @return ER_OK on success
     */
    QStatus EnablePeerSecurity(const char* authMechanisms,
                               AuthListener* listener,
                               const char* keyStoreFileName = NULL,
                               bool isShared = false);

    /**
     * Initiate controller
     * @param[in] list interest device list
     * @return ER_OK on success
     */
    QStatus Init(const InterestDeviceList& list);

    /**
     * Startup controller
     * @return ER_OK on success
     */
    QStatus Start();

    /**
     * Shutdown controller
     * @return ER_OK on success
     */
    QStatus Stop();

    /**
     * Join device
     * @param[in] busName bus name
     * @param[in] port session port
     * @param[in] data CDM About data
     * @param[in] description About object description
     * @return ER_OK on success
     */
    QStatus JoinDevice(const std::string& busName, SessionPort port, const CdmAboutData& data,
                       AboutObjectDescription& description);

    /**
     * Create interface
     * @param[in] type interface type
     * @param[in] busName bus name
     * @param[in] objectPath the object path including the interface
     * @param[in] sessionId session id
     * @param[in] listener interface listener
     * @return Interface
     */
    CdmInterface* CreateInterface(const CdmInterfaceType type, const std::string& busName, const qcc::String& objectPath, const SessionId& sessionId, InterfaceControllerListener& listener);

    /**
     * Register vendor defined interface
     * @param[in] interfaceName interface name
     * @param[in] createIntfController interface creator function
     * @return CDM interface type
     */
    const CdmInterfaceType RegisterVendorDefinedInterface(const qcc::String& interfaceName, CreateIntfControllerFptr createIntfController);

  private:
    CdmControllerImpl* m_impl;
};

}  /* ajn */
}  /* services */

#endif /* CDMCONTROLLER_H_ */