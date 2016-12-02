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

#ifndef CHANNELINTFCONTROLLERIMPL_H_
#define CHANNELINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/ChannelIntfController.h>

namespace ajn {
namespace services {

class ChannelIntfControllerListener;
class CdmProxyBusObject;

/**
 * Channel Interface Controller implementation class
 */
class ChannelIntfControllerImpl : public InterfaceController, public ChannelIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of ChannelIntfControllerImpl
     */
    ChannelIntfControllerImpl(BusAttachment& busAttachment, ChannelIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of ChannelIntfControllerImpl
     */
    virtual ~ChannelIntfControllerImpl();

    /**
     * Initialize interface
     * @return status
     */
    virtual QStatus Init();

    /**
     * Get bus attachment
     * @return bus attachment
     */
    virtual BusAttachment& GetBusAttachment() const { return m_busAttachment; }

    /**
     * Set channel id
     * @param[in] channel id
     * @param[in] context
     * @return status
     */
    virtual QStatus SetChannelId(const qcc::String channelId, void* context);

    /**
     * Get channel id
     * @param[in] context
     * @return status
     */
    virtual QStatus GetChannelId(void* context);

    /**
     * Get total number of channels
     * @param[in] context
     * @return status
     */
    virtual QStatus GetTotalNumberOfChannels(void* context);

    /**
     * Get channel list
     * @param[in] starting record
     * @param[in] number of records
     * @param[in] context
     * @return status
     */
    virtual QStatus GetChannelList(const uint16_t startingRecord, const uint16_t numRecords, void* context);

  private:
    ChannelIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void SetChannelIdPropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetChannelIdPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetTotalNumberOfChannelsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetChannelListReplyHandler(Message& message, void* context);
    void ChannelListChanged(const InterfaceDescription::Member* member, const char* srcPath, Message& message);

    BusAttachment& m_busAttachment;
    ChannelIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* CHANNELINTFCONTROLLERIMPL_H_ */