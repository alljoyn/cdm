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


#ifndef CDMCONTROLLER_H_
#define CDMCONTROLLER_H_

#include <memory>
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
    std::shared_ptr<CdmInterface> CreateInterface(const CdmInterfaceType type, const std::string& busName, const qcc::String& objectPath, const SessionId& sessionId, InterfaceControllerListener& listener);

    template <typename T>
    std::shared_ptr<T> CreateInterface(const std::string& busName, const qcc::String& objectPath, const SessionId& sessionId, InterfaceControllerListener& listener) {
        return std::static_pointer_cast<T>(CreateInterface(T::INTERFACE_TYPE, busName, objectPath, sessionId, listener));
    }

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
