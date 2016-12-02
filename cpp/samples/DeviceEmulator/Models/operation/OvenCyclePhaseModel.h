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

#ifndef OVENCYCLEPHASEMODEL_H_
#define OVENCYCLEPHASEMODEL_H_

#include <interfaces/controllee/operation/OvenCyclePhaseIntfControlleeModel.h>

namespace ajn {
namespace services {
namespace emulator {


class OvenCyclePhaseModel : public virtual OvenCyclePhaseIntfControlleeModel {
  public:
    OvenCyclePhaseModel(const std::string& busPath);

    /**
     * Get CyclePhase
     * @return current cycle phase
     */
    QStatus GetCyclePhase(uint8_t& out) const override;

    /**
     * Get SupportedCyclePhases
     * @return current supported cycle phases
     */
    QStatus GetSupportedCyclePhases(std::vector<uint8_t>& out) const override;

    /**
     * Handler for method GetVendorPhasesDescription
     * @param[out] error Internal error code occurred during command execution
     * @return ER_OK on success
     */
    QStatus GetVendorPhasesDescription(qcc::String arg_languageTag, std::vector<CyclePhaseDescriptor>& arg_phasesDescription, ErrorCode& error, CdmSideEffects& sideEffects) override;

  private:
    std::string m_busPath;
};

} // namespace emulator
} // namespace services
} // namespace ajn

#endif /* OVENCYCLEPHASEMODEL_H_ */