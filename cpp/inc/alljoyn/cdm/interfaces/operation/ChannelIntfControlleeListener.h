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

#ifndef CHANNELINTFCONTROLLEELISTENER_H_
#define CHANNELINTFCONTROLLEELISTENER_H_

#include <vector>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include "ChannelInterface.h"

namespace ajn {
namespace services {

/**
 * Channel Interface Controllee Listener class
 */
class ChannelIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of ChannelIntfControlleeListener
     */
    virtual ~ChannelIntfControlleeListener() {}

    /**
     * Handler for setting ChannelId property
     * @param[in] channelId channel id
     * @return ER_OK on success
     */
    virtual QStatus OnSetChannelId(const qcc::String& channelId) = 0;

    /**
     * Handler for getting ChannelId property
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] channelId channel id
     * @return ER_OK on success
     */
    virtual QStatus OnGetChannelId(qcc::String& channelId) = 0;

    /**
     * Handler for getting TotalNumberOfChannels property
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] totalNumberOfChannels total number of channels
     * @return ER_OK on success
     */
     virtual QStatus OnGetTotalNumberOfChannels(uint16_t& totalNumberOfChannels) = 0;

    /**
     * Handler for GetChannelList method
     * @param[in] startingRecord starting record
     * @param[in] numRecords the number of records
     * @param[out] listOfChannelInfoRecords list of channel info records
     * @param[out] errorCode the error code should be set when the method call is failed
     * @return ER_OK on succes
     */
     virtual QStatus OnGetChannelList(const uint16_t& startingRecord, const uint16_t& numRecords,
                                      ChannelInterface::ChannelInfoRecords& listOfChannelInfoRecords,
                                      ErrorCode& errorCode) = 0;
};

} //namespace services
} //namespace ajn

#endif /* CHANNELINTFCONTROLLEELISTENER_H_ */