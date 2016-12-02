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

#ifndef AUDIOVIDEOINPUTMODEL_H_
#define AUDIOVIDEOINPUTMODEL_H_

#include <interfaces/controllee/operation/AudioVideoInputIntfControlleeModel.h>

namespace ajn {
namespace services {
namespace emulator {


class AudioVideoInputModel : public virtual AudioVideoInputIntfControlleeModel {
  public:
    AudioVideoInputModel(const std::string& busPath);

    /**
     * Get InputSourceId
     * @return current input source id
     */
    QStatus GetInputSourceId(SourceType& out) const override;

     /**
     * Set InputSourceId
     * @param[in] value The input source id to set
     * @return ER_OK on success
     */
    QStatus SetInputSourceId(const SourceType value) override;

    /**
     * Get SupportedInputSources
     * @return current supported input sources
     */
    QStatus GetSupportedInputSources(std::vector<InputSource>& out) const override;


  private:
    std::string m_busPath;
};

} // namespace emulator
} // namespace services
} // namespace ajn

#endif /* AUDIOVIDEOINPUTMODEL_H_ */