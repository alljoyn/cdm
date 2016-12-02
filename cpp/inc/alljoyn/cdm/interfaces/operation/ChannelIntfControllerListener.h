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

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>
#include <alljoyn/cdm/interfaces/operation/ChannelInterface.h>

namespace ajn {
namespace services {

/**
 * Channel Interface Controller Listener class
 */
class ChannelIntfControllerListener : public InterfaceControllerListener {
  public:
    using ChannelInfoRecord = ChannelInterface::ChannelInfoRecord;

    /**
     * Destructor of ChannelIntfControllerListener
     */
    virtual ~ChannelIntfControllerListener() {}

    /**
     * Callback handler for GetChannelId completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of ChannelId
     *                  (Current channel id.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetChannelId(QStatus status, const qcc::String& objectPath, const qcc::String& value, void* context) {}

    /**
     * Handler for ChannelId property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of ChannelId
     *                  (Current channel id.)
     */
    virtual void OnChannelIdChanged(const qcc::String& objectPath, const qcc::String& value) {}

    /**
     * Callback handler for SetChannelId completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetChannelId(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for GetTotalNumberOfChannels completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of TotalNumberOfChannels
     *                  (Total number of scanned channels.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetTotalNumberOfChannels(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context) {}

    /**
     * Handler for TotalNumberOfChannels property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of TotalNumberOfChannels
     *                  (Total number of scanned channels.)
     */
    virtual void OnTotalNumberOfChannelsChanged(const qcc::String& objectPath, const uint16_t value) {}

    /**
     * Callback handler for GetChannelList completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] listOfChannelInfoRecords List of channel information records.
     * @param[in] context the context that is passed from application
     * @param[in] errorName the detail errorName is passed when the method call is failed
     * @param[in] errorMessage the errorMessage that describes the error
     */
    virtual void OnResponseGetChannelList(QStatus status, const qcc::String& objectPath, const std::vector<ChannelInfoRecord>& listOfChannelInfoRecords, void* context, const char* errorName, const char* errorMessage) {}

    /**
     * Callback handler for ChannelListChanged signal
     * @param[in] objectPath the object path
     */
    virtual void OnChannelListChanged(const qcc::String& objectPath) {}
};

} //namespace services
} //namespace ajn

#endif /* CHANNELINTFCONTROLLERLISTENER_H_ */
