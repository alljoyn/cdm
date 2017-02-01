/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF), AllJoyn Open Source
 *    Project (AJOSP) Contributors and others.
 *    
 *    SPDX-License-Identifier: Apache-2.0
 *    
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *    
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
 *    
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *    
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
******************************************************************************/


#ifndef CDMCONTROLLEEIMPL_H_
#define CDMCONTROLLEEIMPL_H_

#include <map>
#include <qcc/Mutex.h>
#include <alljoyn/Status.h>
#include <alljoyn/AboutObj.h>
#include <alljoyn/cdm/interfaces/CdmInterface.h>
#include <alljoyn/cdm/interfaces/CdmInterfaceTypes.h>

#include "SecurityInfo.h"

namespace ajn {

class BusAttachment;
class AuthListener;

namespace services {

class CdmInterface;
class InterfaceControlleeListener;
class CdmAboutData;
class CdmBusObject;
class CdmBusListener;

/**
 * Cdm ControlleeImpl class.
 * Used to create cdm controllee device.
 */
class CdmControlleeImpl {
  public:
    /**
     * Constructor of CdmControlleeImpl
     */
    CdmControlleeImpl(BusAttachment& bus, CdmAboutData* aboutData);

    /**
     * Destructor of CdmControlleeImpl
     */
    ~CdmControlleeImpl();

    /**
     * Enable peer-to-peer security.
     * @param authMechanisms   ALLJOYN_SRP_LOGON, ALLJOYN_SRP_KEYX, ALLJOYN_ECDHE_NULL, ALLJOYN_ECDHE_PSK,
     *                         ALLJOYN_ECDHE_ECDSA, GSSAPI.
     * @param listener
     * @param keyStoreFileName
     * @param isShared
     * @return status
     */
    QStatus EnablePeerSecurity(const char* authMechanisms,
                               AuthListener* listener,
                               const char* keyStoreFileName = NULL,
                               bool isShared = false);

    /**
     * Start controllee
     * @return status
     * @todo
     */
    QStatus Start();

    /**
     * Stop controllee
     * @return status
     * @todo
     */
    QStatus Stop();

    /**
     * Create interface
     * @param[in] type
     * @param[in] objectPath
     * @param[in] listener
     * @return interface
     */
    CdmInterface* CreateInterface(const CdmInterfaceType type, const qcc::String& objectPath, InterfaceControlleeListener& listener);

    /**
     * Register vendor defined interface
     * @param[in] interfaceName
     * @param[in] creator
     * @return CdmInterfaceType
     */
    const CdmInterfaceType RegisterVendorDefinedInterface(const qcc::String& interfaceName, CreateIntfControlleeFptr createIntfControllee);

  private:
    /**
     * Register Cdm Bus object
     * @return status
     * @todo
     */
    QStatus RegisterBusObject();


    /**
     * Register Cdm Bus listener
     * @param TBD
     * @return status
     * @todo
     */
    QStatus RegisterBusListener(CdmBusListener* listener, TransportMask transportMask = TRANSPORT_ANY);

    /**
     * Unregister Cdm Bus listener
     * @param TBD
     * @return status
     * @todo
     */
    QStatus UnregisterBusListener(CdmBusListener* listener);

    /**
     * Check device type validation in about custom fields
     * @return status
     */
    QStatus CheckAboutDeviceTypeValidation();

    qcc::Mutex m_lock;             /* Mutex that protects m_isStarted */
    BusAttachment& m_bus;
    CdmAboutData* m_aboutData;
    std::map<qcc::String, CdmBusObject*> m_cdmBusObjectsMap;
    CdmBusListener* m_cdmBusListener;
    bool m_isStarted;
    SecurityInfo m_security;
};

}
}

#endif  // CDMCONTROLLEEIMPL_H_