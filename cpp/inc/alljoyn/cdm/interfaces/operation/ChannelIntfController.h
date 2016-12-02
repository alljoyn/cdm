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
     * Get ChannelId property
     * (Current channel id.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetChannelId(void* context = NULL) = 0;

    /**
     * Set ChannelId property
     * (Current channel id.)
     * @param[in] value The channel id to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetChannelId(const qcc::String& value, void* context = NULL) = 0;

    /**
     * Get TotalNumberOfChannels property
     * (Total number of scanned channels.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetTotalNumberOfChannels(void* context = NULL) = 0;

    /**
     * Call GetChannelList method
     * (Retrieve the list of channels.)
     * @param[in] startingRecord List built from this record number.
     * @param[in] numRecords List generated at most this many records.
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetChannelList(const uint16_t startingRecord, const uint16_t numRecords, void* context = NULL) = 0;
};

typedef std::shared_ptr<ChannelIntfController> ChannelIntfControllerPtr;

} //namespace services
} //namespace ajn

#endif /* CHANNELINTFCONTROLLER_H_ */
