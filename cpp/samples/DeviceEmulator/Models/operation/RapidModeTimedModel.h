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

#ifndef RAPIDMODETIMEDMODEL_H_
#define RAPIDMODETIMEDMODEL_H_

#include <interfaces/controllee/operation/RapidModeTimedIntfControlleeModel.h>

namespace ajn {
namespace services {
namespace emulator {


class RapidModeTimedModel : public virtual RapidModeTimedIntfControlleeModel {
  public:
    RapidModeTimedModel(const std::string& busPath);

    /**
     * Get RapidModeMinutesRemaining
     * @return current rapid mode minutes remaining
     */
    QStatus GetRapidModeMinutesRemaining(uint16_t& out) const override;

     /**
     * Set RapidModeMinutesRemaining
     * @param[in] value The rapid mode minutes remaining to set
     * @return ER_OK on success
     */
    QStatus SetRapidModeMinutesRemaining(const uint16_t value) override;

    /**
     * Get MaxSetMinutes
     * @return current max set minutes
     */
    QStatus GetMaxSetMinutes(uint16_t& out) const override;


  private:
    std::string m_busPath;
};

} // namespace emulator
} // namespace services
} // namespace ajn

#endif /* RAPIDMODETIMEDMODEL_H_ */