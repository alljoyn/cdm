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

#ifndef HIDMODEL_H_
#define HIDMODEL_H_

#include <interfaces/controllee/input/HidIntfControlleeModel.h>

namespace ajn {
namespace services {
namespace emulator {


class HidModel : public virtual HidIntfControlleeModel {
  public:
    HidModel(const std::string& busPath);

    /**
     * Get SupportedEvents
     * @return current supported events
     */
    QStatus GetSupportedEvents(std::vector<HidInterface::SupportedInputEvent>& out) const override;

    /**
     * Handler for method InjectEvents
     * @param[out] error Internal error code occurred during command execution
     * @return ER_OK on success
     */
    QStatus InjectEvents(std::vector<HidInterface::InputEvent>& arg_inputEvents, ErrorCode& error, CdmControllee& controllee) override;

  private:
    std::string m_busPath;
};

} // namespace emulator
} // namespace services
} // namespace ajn

#endif /* HIDMODEL_H_ */