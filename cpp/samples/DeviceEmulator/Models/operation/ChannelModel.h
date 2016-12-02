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

#ifndef CHANNELMODEL_H_
#define CHANNELMODEL_H_

#include <interfaces/controllee/operation/ChannelIntfControlleeModel.h>

namespace ajn {
namespace services {
namespace emulator {


class ChannelModel : public virtual ChannelIntfControlleeModel {
  public:
    ChannelModel(const std::string& busPath);

    /**
     * Get ChannelId
     * @return current channel id
     */
    QStatus GetChannelId(qcc::String& out) const override;

     /**
     * Set ChannelId
     * @param[in] value The channel id to set
     * @return ER_OK on success
     */
    QStatus SetChannelId(const qcc::String& value) override;

    /**
     * Get TotalNumberOfChannels
     * @return current total number of channels
     */
    QStatus GetTotalNumberOfChannels(uint16_t& out) const override;

    /**
     * Handler for method GetChannelList
     * @param[out] error Internal error code occurred during command execution
     * @return ER_OK on success
     */
    QStatus GetChannelList(uint16_t arg_startingRecord, uint16_t arg_numRecords, std::vector<ChannelInterface::ChannelInfoRecord>& arg_listOfChannelInfoRecords, ErrorCode& error, CdmControllee& controllee) override;

  private:
    std::string m_busPath;
};

} // namespace emulator
} // namespace services
} // namespace ajn

#endif /* CHANNELMODEL_H_ */