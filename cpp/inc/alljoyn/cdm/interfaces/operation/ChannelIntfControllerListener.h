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

#ifndef CHANNELINTFCONTROLLERLISTENER_H_
#define CHANNELINTFCONTROLLERLISTENER_H_

#include <vector>
#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>
#include "ChannelInterface.h"

namespace ajn {
namespace services {

/**
 * Channel Interface Controller Listener class
 */
class ChannelIntfControllerListener : public InterfaceControllerListener {
  public:
    /**
     * Destructor of ChannelIntfControllerListener
     */
    virtual ~ChannelIntfControllerListener() {}

    /**
     * Callback handler for setting ChannelId property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetChannelId(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for getting ChannelId property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] channelId channel id
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetChannelId(QStatus status, const qcc::String& objectPath, const qcc::String& channelId, void* context) {}

    /**
     * Callback handler for getting TotalNumberOfChannels property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] totalNumberOfChannels total number of channels
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetTotalNumberOfChannels(QStatus status, const qcc::String& objectPath, const uint16_t totalNumberOfChannels, void* context) {}

    /**
     * Callback handler for GetChannelList method
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] listOfChannelInfoRecords list of channel info records
     * @param[in] context the context that is passed from application
     * @param[in] errorName the detail errorName is passed when the method call is failed
     * @param[in] errorMessage the errorMessage that describes the error
     */
    virtual void OnResponseGetChannelList(QStatus status, const qcc::String& objectPath, const ChannelInterface::ChannelInfoRecords& listOfChannelInfoRecords,
                                          void* context, const char* errorName, const char* errorMessage) {}

    /**
     * Handler for ChannelId property changed
     * @param[in] objectPath the object path
     * @param[in] channelId channel id
     */
    virtual void OnChannelIdChanged(const qcc::String& objectPath, const qcc::String& channelId) {}

    /**
     * Handler for TotalNumberOfChannels property changed
     * @param[in] objectPath the object path
     * @param[in] totalNumberOfChannels total number of channels
     */
    virtual void OnTotalNumberOfChannelsChanged(const qcc::String& objectPath, const uint16_t totalNumberOfChannels) {}

    /**
     * Handler for ChannelListChanged signal
     * @param[in] objectPath the object path
     */
    virtual void OnChannelListChanged(const qcc::String& objectPath) {}
};

} //namespace services
} //namespace ajn

#endif /* CHANNELINTFCONTROLLERLISTENER_H_ */