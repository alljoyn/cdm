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


#ifndef HAECONTROLLEEIMPL_H_
#define HAECONTROLLEEIMPL_H_

#include <map>
#include <qcc/Mutex.h>
#include <alljoyn/Status.h>
#include <alljoyn/AboutObj.h>
#include <alljoyn/hae/interfaces/HaeInterface.h>
#include <alljoyn/hae/interfaces/HaeInterfaceTypes.h>

#include "SecurityInfo.h"

namespace ajn {

class BusAttachment;
class AuthListener;

namespace services {

class HaeInterface;
class InterfaceControlleeListener;
class HaeAboutData;
class HaeBusObject;
class HaeBusListener;

/**
 * Hae ControlleeImpl class.
 * Used to create hae controllee device.
 */
class HaeControlleeImpl {
  public:
    /**
     * Constructor of HaeControlleeImpl
     */
    HaeControlleeImpl(BusAttachment& bus, HaeAboutData* aboutData);

    /**
     * Destructor of HaeControlleeImpl
     */
    ~HaeControlleeImpl();

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
    HaeInterface* CreateInterface(const HaeInterfaceType type, const qcc::String& objectPath, InterfaceControlleeListener& listener);

    /**
     * Register vendor defined interface
     * @param[in] interfaceName
     * @param[in] creator
     * @return HaeInterfaceType
     */
    const HaeInterfaceType RegisterVendorDefinedInterface(const qcc::String& interfaceName, CreateIntfControlleeFptr createIntfControllee);

  private:
    /**
     * Register Hae Bus object
     * @return status
     * @todo
     */
    QStatus RegisterBusObject();


    /**
     * Register Hae Bus listener
     * @param TBD
     * @return status
     * @todo
     */
    QStatus RegisterBusListener(HaeBusListener* listener, TransportMask transportMask = TRANSPORT_ANY);

    /**
     * Unregister Hae Bus listener
     * @param TBD
     * @return status
     * @todo
     */
    QStatus UnregisterBusListener(HaeBusListener* listener);

    /**
     * Check device type validation in about custom fields
     * @return status
     */
    QStatus CheckAboutDeviceTypeValidation();

    qcc::Mutex m_lock;             /* Mutex that protects m_isStarted */
    BusAttachment& m_bus;
    HaeAboutData* m_aboutData;
    std::map<qcc::String, HaeBusObject*> m_haeBusObjectsMap;
    HaeBusListener* m_haeBusListener;
    bool m_isStarted;
    SecurityInfo m_security;
};

}
}

#endif  // HAECONTROLLEEIMPL_H_
