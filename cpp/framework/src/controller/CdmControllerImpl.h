/******************************************************************************
 * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
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
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/


#ifndef CDMCONTROLLERIMPL_H_
#define CDMCONTROLLERIMPL_H_

#include <qcc/Mutex.h>
#include <alljoyn/Status.h>
#include <alljoyn/SessionListener.h>
#include <alljoyn/cdm/common/CdmConfig.h>
#include <alljoyn/cdm/common/CdmInterface.h>
#include "../common/CdmBusListener.h"

#include "DeviceManager.h"
#include "../common/SecurityInfo.h"

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
    Ref<CdmInterface> CreateInterface(const std::string& ifaceName, const std::string& busName, const qcc::String& objectPath, const SessionId& sessionId, Ref<InterfaceControllerListener> listener);

    /**
     * Register an interface
     * @param[in] interfaceName
     * @param[in] creator
     * @return ER_OK or ER_DUPLICATE_KEY
     */
    QStatus RegisterInterface(const std::string& interfaceName, CreateIntfControllerFptr createIntfController);

    /**
     * Unregister an interface
     * @param[in] interfaceName
     * @param[in] creator
     * @return ER_OK or ER_FAIL
     */
    QStatus UnregisterInterface(const std::string& interfaceName, CreateIntfControllerFptr createIntfController);


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