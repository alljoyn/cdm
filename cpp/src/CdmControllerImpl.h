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


#ifndef HAECONTROLLERIMPL_H_
#define HAECONTROLLERIMPL_H_

#include <qcc/Mutex.h>
#include <alljoyn/Status.h>
#include <alljoyn/SessionListener.h>
#include <alljoyn/hae/HaeConfig.h>
#include <alljoyn/hae/interfaces/HaeInterface.h>
#include "HaeBusListener.h"

#include "DeviceManager.h"
#include "SecurityInfo.h"

namespace ajn {

class BusAttachment;
class AuthListener;

namespace services {

class DeviceListener;
/**
 * Hae ControllerImpl class.
 */
class HaeControllerImpl : public ajn::AboutListener
                        , public ajn::SessionListener
                        //, public ajn::BusAttachment::JoinSessionAsyncCB
{
  public:
    /**
     * Constructor of HaeControllerImpl
     */
    HaeControllerImpl(BusAttachment& bus, DeviceListener* listener);

    /**
     * Destructor of HaeControllerImpl
     */
    virtual ~HaeControllerImpl();

    /**
     * initiate controller
     * @return status
     * @todo
     */
    QStatus Init(const InterestDeviceList& list);

    /**
     * Startup controller
     * @return status
     * @todo
     */
    QStatus Start();

    /**
     * Shutdown controller
     * @return status
     * @todo
     */
    QStatus Stop();

    /**
     * Join device
     * @param[in] bus name
     * @param[in] session port
     * @param[in] hae about data
     * @param[in] about object description
     * @return interface
     */
    QStatus JoinDevice(const std::string& busName, SessionPort port, const HaeAboutData& data,
                       AboutObjectDescription& description);

    /**
     * Create interface
     * @param[in] type
     * @param[in] bus name
     * @param[in] objectPath
     * @param[in] session id
     * @param[in] listener
     * @return interface
     */
    HaeInterface* CreateInterface(const HaeInterfaceType type, const std::string& busName, const qcc::String& objectPath, const SessionId& sessionId, InterfaceControllerListener& listener);

    /**
     * Register vendor defined interface
     * @param[in] interfaceName
     * @param[in] creator
     * @return HaeInterfaceType
     */
    const HaeInterfaceType RegisterVendorDefinedInterface(const qcc::String& interfaceName, CreateIntfControllerFptr createIntfController);


    QStatus EnablePeerSecurity(const char* authMechanisms,
                                          AuthListener* authListener,
                                          const char* keyStoreFileName,
                                          bool isKeyStoreShared);

    //QStatus GetAboutObjectDescription(const DeviceInfo& deviceInfo, AboutObjectDescription& aboutObjectDesc);


    virtual void Announced(const char* busName, uint16_t version, SessionPort port, const MsgArg& objectDescriptionArg, const MsgArg& aboutDataArg);
    /**
     * SessionLost
     * @param sessionId
     * @param reason
     */
    void SessionLost(ajn::SessionId sessionId, ajn::SessionListener::SessionLostReason reason);

    /**
     * JoinSessionCB
     * @param status
     * @param id
     * @param opts
     * @param context
     */
    //void JoinSessionCB(QStatus status, ajn::SessionId id, const ajn::SessionOpts& opts, void* context);


  private:
    bool m_isStarted;
    qcc::Mutex m_lock;
    BusAttachment& m_bus;
    HaeBusListener m_haeBusListener;
    DeviceManager m_deviceManager;
    DeviceListener* m_deviceListener;
    SecurityInfo m_security;
};

}  /* ajn */
}  /* services */

#endif /* HAECONTROLLERIMPL_H_ */
