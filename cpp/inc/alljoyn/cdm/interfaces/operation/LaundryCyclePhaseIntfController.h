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

#ifndef LAUNDRYCYCLEPHASEINTFCONTROLLER_H_
#define LAUNDRYCYCLEPHASEINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/LaundryCyclePhaseInterface.h>

namespace ajn {
namespace services {

/**
 * LaundryCyclePhase Interface Controller class
 */
class LaundryCyclePhaseIntfController : public LaundryCyclePhaseInterface {
  public:
    /**
     * Constructor of LaundryCyclePhaseIntfController
     */
    LaundryCyclePhaseIntfController() {}

    /**
     * Destructor of LaundryCyclePhaseIntfController
     */
    virtual ~LaundryCyclePhaseIntfController() {}

    /**
     * Get CyclePhase property
     * (Current cycle phase. Range value [0x00-0x7F] is for standard phases; range value [0x80-0xFF] is for vendor-defined phases and so the meanings depend on manufacturer.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetCyclePhase(void* context = NULL) = 0;

    /**
     * Get SupportedCyclePhases property
     * (List of supported cycle phases.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetSupportedCyclePhases(void* context = NULL) = 0;

    /**
     * Call GetVendorPhasesDescription method
     * (Get cycle phases description.)
     * @param[in] languageTag Preferred language to be used in selecting the output strings.
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetVendorPhasesDescription(const qcc::String& languageTag, void* context = NULL) = 0;
};

typedef std::shared_ptr<LaundryCyclePhaseIntfController> LaundryCyclePhaseIntfControllerPtr;

} //namespace services
} //namespace ajn

#endif /* LAUNDRYCYCLEPHASEINTFCONTROLLER_H_ */
