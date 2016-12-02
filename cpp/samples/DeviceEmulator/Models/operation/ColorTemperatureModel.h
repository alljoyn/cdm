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

#ifndef COLORTEMPERATUREMODEL_H_
#define COLORTEMPERATUREMODEL_H_

#include <interfaces/controllee/operation/ColorTemperatureIntfControlleeModel.h>

namespace ajn {
namespace services {
namespace emulator {


class ColorTemperatureModel : public virtual ColorTemperatureIntfControlleeModel {
  public:
    ColorTemperatureModel(const std::string& busPath);

    /**
     * Get Temperature
     * @return current temperature
     */
    QStatus GetTemperature(double& out) const override;

     /**
     * Set Temperature
     * @param[in] value The temperature to set
     * @return ER_OK on success
     */
    QStatus SetTemperature(const double value) override;

    /**
     * Get MinTemperature
     * @return current min temperature
     */
    QStatus GetMinTemperature(double& out) const override;

    /**
     * Get MaxTemperature
     * @return current max temperature
     */
    QStatus GetMaxTemperature(double& out) const override;


  private:
    std::string m_busPath;
};

} // namespace emulator
} // namespace services
} // namespace ajn

#endif /* COLORTEMPERATUREMODEL_H_ */