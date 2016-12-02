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

#ifndef CHANNELINTFCONTROLLEE_H_
#define CHANNELINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/ChannelInterface.h>

namespace ajn {
namespace services {

/**
 * Channel Interface Controllee class
 */
class ChannelIntfControllee : public ChannelInterface {
  public:
    /**
     * Constructor of ChannelIntfControllee
     */
    ChannelIntfControllee() {}

    /**
     * Destructor of ChannelIntfControllee
     */
    virtual ~ChannelIntfControllee() {}

    /**
     * Get channel id
     * @return Channel id
     */
    virtual const qcc::String GetChannelId() const = 0;

    /**
     * Set channel id
     * @param[in] channelId channel id
     * @return ER_OK on success
     */
    virtual QStatus SetChannelId(const qcc::String& channelId) = 0;

    /**
     * Get total number of channels
     * @return Total number of channels
     */
    virtual const uint16_t GetTotalNumberOfChannels() const = 0;

    /**
     * Set total number of channels
     * @param[in] totalNumberOfChannels total number of channels
     * @return ER_OK on success
     */
    virtual QStatus SetTotalNumberOfChannels(const uint16_t totalNumberOfChannels) = 0;

    /**
     * Emit ChannelListChanged signal
     * @return ER_OK on success
     */
    virtual QStatus EmitChannelListChanged() = 0;

};

} //namespace services
} //namespace ajn

#endif /* CHANNELINTFCONTROLLEE_H_ */