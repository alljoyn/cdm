/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF), AllJoyn Open Source
 *    Project (AJOSP) Contributors and others.
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
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
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