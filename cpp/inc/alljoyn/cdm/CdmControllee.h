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


#ifndef CDMCONTROLLEE_H_
#define CDMCONTROLLEE_H_

#include <alljoyn/Status.h>
#include <alljoyn/cdm/CdmConfig.h>
#include <alljoyn/cdm/interfaces/CdmInterface.h>
#include <alljoyn/cdm/interfaces/CdmInterfaceTypes.h>

namespace ajn {

class BusAttachment;
class AuthListener;

namespace services {

class CdmInterface;
class InterfaceControlleeListener;
class CdmAboutData;
class CdmControlleeImpl;

/**
 * Cdm Controllee class.
 * Used to create cdm controllee device.
 */
class CdmControllee {
  public:
    /**
     * Constructor of CdmControllee
     * @param[in] bus bus attachment
     * @param[in] aboutData CDM About data
     */
    CdmControllee(BusAttachment& bus, CdmAboutData* aboutData);

    /**
     * Destructor of CdmControllee
     */
    virtual ~CdmControllee();

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
     * Start controllee
     * @return ER_OK on success
     */
    QStatus Start();

    /**
     * Stop controllee
     * @return ER_OK on success
     */
    QStatus Stop();

    /**
     * Create interface
     * @param[in] type interface type
     * @param[in] objectPath the object path including the interface
     * @param[in] listener interface listener
     * @return Interface
     */
    CdmInterface* CreateInterface(const CdmInterfaceType type, const qcc::String& objectPath, InterfaceControlleeListener& listener);

    /**
     * Register vendor defined interface
     * @param[in] interfaceName interface name
     * @param[in] createIntfControllee interface creator function
     * @return CDM interface type
     */
    const CdmInterfaceType RegisterVendorDefinedInterface(const qcc::String& interfaceName, CreateIntfControlleeFptr createIntfControllee);

  private:
    CdmControlleeImpl* m_impl;

};

}
}

#endif // CDMCONTROLLEE_H_