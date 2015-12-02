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

#ifndef CHANNELINTFCONTROLLERLISTENER_H_
#define CHANNELINTFCONTROLLERLISTENER_H_

#include <vector>
#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/hae/interfaces/InterfaceControllerListener.h>
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
     * Handler for ChannelId property changed
     * @param[in] objectPath the object path
     * @param[in] channelId channel id
     */
    virtual void ChannelIdPropertyChanged(const qcc::String& objectPath, const qcc::String channelId) {}

    /**
     * Handler for TotalNumberOfChannels property changed
     * @param[in] objectPath the object path
     * @param[in] totalNumberOfChannels total number of channels
     */
    virtual void TotalNumberOfChannelsPropertyChanged(const qcc::String& objectPath, const uint16_t totalNumberOfChannels) {}

    /**
     * Callback handler for getting ChannelId property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] channelId channel id
     * @param[in] context the context that is passed from application
     */
    virtual void GetChannelIdPropertyCallback(QStatus status, const qcc::String& objectPath, const qcc::String channelId, void* context) {}

    /**
     * Callback handler for getting TotalNumberOfChannels property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] totalNumberOfChannels total number of channels
     * @param[in] context the context that is passed from application
     */
    virtual void GetTotalNumberOfChannelsPropertyCallback(QStatus status, const qcc::String& objectPath, const uint16_t totalNumberOfChannels, void* context) {}

    /**
     * Callback handler for setting ChannelId property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void SetChannelIdPropertyCallback(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for GetChannelList method
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] listOfChannelInfoRecords list of channel info records
     * @param[in] context the context that is passed from application
     */
    virtual void GetChannelListMethodCallback(QStatus status, const qcc::String& objectPath, const ChannelInterface::ChannelInfoRecords& listOfChannelInfoRecords, void* context) {}

    /**
     * Handler for ChannelListChanged signal
     * @param[in] objectPath the object path
     */
    virtual void ChannelListChangedSignal(const qcc::String& objectPath) {}
};

} //namespace services
} //namespace ajn

#endif /* CHANNELINTFCONTROLLERLISTENER_H_ */
