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


#ifndef HAECONTROLLEE_H_
#define HAECONTROLLEE_H_

#include <alljoyn/Status.h>
#include <alljoyn/hae/HaeConfig.h>
#include <alljoyn/hae/interfaces/HaeInterface.h>
#include <alljoyn/hae/interfaces/HaeInterfaceTypes.h>

namespace ajn {

class BusAttachment;
class AuthListener;

namespace services {

class HaeInterface;
class InterfaceControlleeListener;
class HaeAboutData;
class HaeControlleeImpl;

/**
 * Hae Controllee class.
 * Used to create hae controllee device.
 */
class HaeControllee {
  public:
    /**
     * Constructor of HaeControllee
     * @param[in] bus bus attachment
     * @param[in] aboutData HAE About data
     */
    HaeControllee(BusAttachment& bus, HaeAboutData* aboutData);

    /**
     * Destructor of HaeControllee
     */
    virtual ~HaeControllee();

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
    HaeInterface* CreateInterface(const HaeInterfaceType type, const qcc::String& objectPath, InterfaceControlleeListener& listener);

    /**
     * Register vendor defined interface
     * @param[in] interfaceName interface name
     * @param[in] createIntfControllee interface creator function
     * @return HAE interface type
     */
    const HaeInterfaceType RegisterVendorDefinedInterface(const qcc::String& interfaceName, CreateIntfControlleeFptr createIntfControllee);

  private:
    HaeControlleeImpl* m_impl;

};

}
}

#endif // HAECONTROLLEE_H_
