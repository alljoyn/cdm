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


#ifndef HAECONTROLLER_H_
#define HAECONTROLLER_H_

#include <alljoyn/Status.h>
#include <alljoyn/hae/HaeConfig.h>
#include <alljoyn/hae/interfaces/HaeInterface.h>
#include <alljoyn/hae/interfaces/HaeInterfaceTypes.h>

namespace ajn {

class AboutObjectDescription;

namespace services {

class HaeProxyBusObject;
class HaeControllerImpl;
class HaeInterface;
class InterfaceControllerListener;
class HaeAboutData;
class DeviceListener;
class DeviceInfo;

/**
 * Hae Controller class.
 */
class HaeController {

  public:
    /**
     * Constructor of HaeController
     * @param[in] bus bus attachment
     * @param[in] aboutData HAE About data
     */
    HaeController(BusAttachment& bus, DeviceListener* listener);

    /**
     * Destructor of HaeController
     */
    virtual ~HaeController();

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
     * @param[in] data HAE About data
     * @param[in] description About object description
     * @return ER_OK on success
     */
    QStatus JoinDevice(const std::string& busName, SessionPort port, const HaeAboutData& data,
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
    HaeInterface* CreateInterface(const HaeInterfaceType type, const std::string& busName, const qcc::String& objectPath, const SessionId& sessionId, InterfaceControllerListener& listener);

    /**
     * Register vendor defined interface
     * @param[in] interfaceName interface name
     * @param[in] createIntfController interface creator function
     * @return HAE interface type
     */
    const HaeInterfaceType RegisterVendorDefinedInterface(const qcc::String& interfaceName, CreateIntfControllerFptr createIntfController);

  private:
    HaeControllerImpl* m_impl;
};

}  /* ajn */
}  /* services */

#endif /* HAECONTROLLER_H_ */
