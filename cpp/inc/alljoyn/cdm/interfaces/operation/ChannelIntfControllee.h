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

#ifndef CHANNELINTFCONTROLLEE_H_
#define CHANNELINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/hae/interfaces/operation/ChannelInterface.h>

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
