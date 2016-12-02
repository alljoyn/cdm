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

#ifndef CHANNELINTFCONTROLLER_H_
#define CHANNELINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/ChannelInterface.h>

namespace ajn {
namespace services {

/**
 * Channel Interface Controller class
 */
class ChannelIntfController : public ChannelInterface {
  public:
    /**
     * Constructor of ChannelIntfController
     */
    ChannelIntfController() {}

    /**
     * Destructor of ChannelIntfController
     */
    virtual ~ChannelIntfController() {}

    /**
     * Set channel id
     * @param[in] channelId channel id
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetChannelId(const qcc::String channelId, void* context = NULL) = 0;

    /**
     * Get channel id
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetChannelId(void* context = NULL) = 0;

    /**
     * Get total number of channels
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetTotalNumberOfChannels(void* context = NULL) = 0;

    /**
     * Get channel list
     * @param[in] startingRecord starting record
     * @param[in] numRecords the number of records
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetChannelList(const uint16_t startingRecord, const uint16_t numRecords, void* context = NULL) = 0;
};

} //namespace services
} //namespace ajn

#endif /* CHANNELINTFCONTROLLER_H_ */