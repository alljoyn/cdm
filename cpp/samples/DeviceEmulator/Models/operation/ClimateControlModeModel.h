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

#ifndef CLIMATECONTROLMODEMODEL_H_
#define CLIMATECONTROLMODEMODEL_H_

#include <interfaces/controllee/operation/ClimateControlModeIntfControlleeModel.h>

namespace ajn {
namespace services {
namespace emulator {


class ClimateControlModeModel : public virtual ClimateControlModeIntfControlleeModel {
  public:
    ClimateControlModeModel(const std::string& busPath);

    /**
     * Get Mode
     * @return current mode
     */
    QStatus GetMode(Mode& out) const override;

     /**
     * Set Mode
     * @param[in] value The mode to set
     * @return ER_OK on success
     */
    QStatus SetMode(const Mode value) override;

    /**
     * Get SupportedModes
     * @return current supported modes
     */
    QStatus GetSupportedModes(std::vector<Mode>& out) const override;

    /**
     * Get OperationalState
     * @return current operational state
     */
    QStatus GetOperationalState(OperationalState& out) const override;


  private:
    std::string m_busPath;
};

} // namespace emulator
} // namespace services
} // namespace ajn

#endif /* CLIMATECONTROLMODEMODEL_H_ */