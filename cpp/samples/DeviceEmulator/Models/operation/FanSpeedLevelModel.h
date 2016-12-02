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

#ifndef FANSPEEDLEVELMODEL_H_
#define FANSPEEDLEVELMODEL_H_

#include <interfaces/controllee/operation/FanSpeedLevelIntfControlleeModel.h>

namespace ajn {
namespace services {
namespace emulator {


class FanSpeedLevelModel : public virtual FanSpeedLevelIntfControlleeModel {
  public:
    FanSpeedLevelModel(const std::string& busPath);

    /**
     * Get FanSpeedLevel
     * @return current fan speed level
     */
    QStatus GetFanSpeedLevel(uint8_t& out) const override;

     /**
     * Set FanSpeedLevel
     * @param[in] value The fan speed level to set
     * @return ER_OK on success
     */
    QStatus SetFanSpeedLevel(const uint8_t value) override;

    /**
     * Get MaxFanSpeedLevel
     * @return current max fan speed level
     */
    QStatus GetMaxFanSpeedLevel(uint8_t& out) const override;

    /**
     * Get AutoMode
     * @return current auto mode
     */
    QStatus GetAutoMode(AutoMode& out) const override;

     /**
     * Set AutoMode
     * @param[in] value The auto mode to set
     * @return ER_OK on success
     */
    QStatus SetAutoMode(const AutoMode value) override;


  private:
    std::string m_busPath;
};

} // namespace emulator
} // namespace services
} // namespace ajn

#endif /* FANSPEEDLEVELMODEL_H_ */