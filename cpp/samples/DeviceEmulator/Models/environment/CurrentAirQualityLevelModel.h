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

#ifndef CURRENTAIRQUALITYLEVELMODEL_H_
#define CURRENTAIRQUALITYLEVELMODEL_H_

#include <interfaces/controllee/environment/CurrentAirQualityLevelIntfControlleeModel.h>

namespace ajn {
namespace services {
namespace emulator {


class CurrentAirQualityLevelModel : public virtual CurrentAirQualityLevelIntfControlleeModel {
  public:
    CurrentAirQualityLevelModel(const std::string& busPath);

    /**
     * Get ContaminantType
     * @return current contaminant type
     */
    QStatus GetContaminantType(CurrentAirQualityLevelInterface::ContaminantType& out) const override;

    /**
     * Get CurrentLevel
     * @return current current level
     */
    QStatus GetCurrentLevel(uint8_t& out) const override;

    /**
     * Get MaxLevel
     * @return current max level
     */
    QStatus GetMaxLevel(uint8_t& out) const override;


  private:
    std::string m_busPath;
};

} // namespace emulator
} // namespace services
} // namespace ajn

#endif /* CURRENTAIRQUALITYLEVELMODEL_H_ */