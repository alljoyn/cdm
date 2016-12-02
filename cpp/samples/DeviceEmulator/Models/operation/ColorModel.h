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

#ifndef COLORMODEL_H_
#define COLORMODEL_H_

#include <interfaces/controllee/operation/ColorIntfControlleeModel.h>

namespace ajn {
namespace services {
namespace emulator {


class ColorModel : public virtual ColorIntfControlleeModel {
  public:
    ColorModel(const std::string& busPath);

    /**
     * Get Hue
     * @return current hue
     */
    QStatus GetHue(double& out) const override;

     /**
     * Set Hue
     * @param[in] value The hue to set
     * @return ER_OK on success
     */
    QStatus SetHue(const double value) override;

    /**
     * Get Saturation
     * @return current saturation
     */
    QStatus GetSaturation(double& out) const override;

     /**
     * Set Saturation
     * @param[in] value The saturation to set
     * @return ER_OK on success
     */
    QStatus SetSaturation(const double value) override;


  private:
    std::string m_busPath;
};

} // namespace emulator
} // namespace services
} // namespace ajn

#endif /* COLORMODEL_H_ */