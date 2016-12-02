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


#ifndef CDMBUSLISTENER_H_
#define CDMBUSLISTENER_H_

#include <alljoyn/BusAttachment.h>
#include <alljoyn/BusListener.h>
#include <alljoyn/SessionPortListener.h>
#include <vector>

namespace ajn {
namespace services {


/**
 * Cdm bus listener class.
 * This class implements BusListener, SessionPortListener and SessionListener
 */
class CdmBusListener : public BusListener, public SessionPortListener, public SessionListener {
  public:

    /**
     * Constructor of CdmBusListener
     */
    CdmBusListener(BusAttachment& bus);

    /**
     * Destructor of CdmBusListener
     */
    ~CdmBusListener();


    /**
     * Set the Value of the SessionPort associated with this SessionPortListener
     * @param sessionPort
     */
    void SetSessionPort(SessionPort sessionPort);

    /**
     * Get the SessionPort of the listener
     * @return
     */
    const SessionPort GetSessionPort() const;

    /**
     * AcceptSessionJoiner - Receive request to join session and decide whether to accept it or not
     * @param sessionPort - the port of the request
     * @param joiner - the name of the joiner
     * @param opts - the session options
     * @return true/false
     */
    virtual bool AcceptSessionJoiner(SessionPort sessionPort, const char* joiner, const SessionOpts& opts);

    /**
     * SessionJoined
     * @param sessionPort
     * @param sessionId
     * @param joiner
     */
    virtual void SessionJoined(SessionPort sessionPort, SessionId sessionId, const char* joiner);

    /**
     * SessionLost
     * @param sessionId
     * @param reason
     */
    virtual void SessionLost(SessionId sessionId, SessionLostReason reason);

    /**
     * Called when a BusAttachment this listener is registered with is stopping.
     */
    virtual void BusStopping();

    /**
     * Called when a BusAttachment this listener is registered with has become disconnected from
     * the bus.
     */
    virtual void BusDisconnected();

    /**
     * Get the SessionIds associated with this Listener
     * @return vector of sessionIds
     */
    const std::vector<SessionId>& GetSessionIds() const;

  private:
    /**
     * Bus attachment
     */
    BusAttachment& m_bus;

    /**
     * The port used as part of the join session request
     */
    SessionPort m_sessionPort;

    /**
     * The sessionIds for the port
     */
    std::vector<SessionId> m_sessionIds;
};

}
}

#endif //CDMBUSLISTENER_H_