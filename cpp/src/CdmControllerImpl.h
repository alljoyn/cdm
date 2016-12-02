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


#ifndef CDMCONTROLLERIMPL_H_
#define CDMCONTROLLERIMPL_H_

#include <qcc/Mutex.h>
#include <alljoyn/Status.h>
#include <alljoyn/SessionListener.h>
#include <alljoyn/cdm/CdmConfig.h>
#include <alljoyn/cdm/interfaces/CdmInterface.h>
#include "CdmBusListener.h"

#include "DeviceManager.h"
#include "SecurityInfo.h"

namespace ajn {

class BusAttachment;
class AuthListener;

namespace services {

class DeviceListener;
/**
 * Cdm ControllerImpl class.
 */
class CdmControllerImpl : public ajn::AboutListener
                        , public ajn::SessionListener
                        //, public ajn::BusAttachment::JoinSessionAsyncCB
{
  public:
    /**
     * Constructor of CdmControllerImpl
     */
    CdmControllerImpl(BusAttachment& bus, DeviceListener* listener);

    /**
     * Destructor of CdmControllerImpl
     */
    virtual ~CdmControllerImpl();

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
     * @param[in] cdm about data
     * @param[in] about object description
     * @return interface
     */
    QStatus JoinDevice(const std::string& busName, SessionPort port, const CdmAboutData& data,
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
    CdmInterface* CreateInterface(const CdmInterfaceType type, const std::string& busName, const qcc::String& objectPath, const SessionId& sessionId, InterfaceControllerListener& listener);

    /**
     * Register vendor defined interface
     * @param[in] interfaceName
     * @param[in] creator
     * @return CdmInterfaceType
     */
    const CdmInterfaceType RegisterVendorDefinedInterface(const qcc::String& interfaceName, CreateIntfControllerFptr createIntfController);


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
    CdmBusListener m_cdmBusListener;
    DeviceManager m_deviceManager;
    DeviceListener* m_deviceListener;
    SecurityInfo m_security;
};

}  /* ajn */
}  /* services */

#endif /* CDMCONTROLLERIMPL_H_ */