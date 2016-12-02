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

#ifndef TARGETHUMIDITYINTFCONTROLLER_H_
#define TARGETHUMIDITYINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/environment/TargetHumidityInterface.h>

namespace ajn {
namespace services {

/**
 * TargetHumidity Interface Controller class
 */
class TargetHumidityIntfController : public TargetHumidityInterface {
  public:
    /**
     * Constructor of TargetHumidityIntfController
     */
    TargetHumidityIntfController() {}

    /**
     * Destructor of TargetHumidityIntfController
     */
    virtual ~TargetHumidityIntfController() {}

    /**
     * Get TargetValue property
     * (Target set-point value of relative humidity.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetTargetValue(void* context = NULL) = 0;

    /**
     * Set TargetValue property
     * (Target set-point value of relative humidity.)
     * @param[in] value The target value to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetTargetValue(const uint8_t value, void* context = NULL) = 0;

    /**
     * Get MinValue property
     * (Minimum value allowed for the TargetValue.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetMinValue(void* context = NULL) = 0;

    /**
     * Get MaxValue property
     * (Maximum value allowed for the TargetValue.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetMaxValue(void* context = NULL) = 0;

    /**
     * Get StepValue property
     * (Step value allowed for the TargetValue setting.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetStepValue(void* context = NULL) = 0;

    /**
     * Get SelectableHumidityLevels property
     * (List of the selectable levels of target humidity. The list is only available when this interface is implemented for setting a qualitative level of target humidity. (When MinValue = MaxValue))
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetSelectableHumidityLevels(void* context = NULL) = 0;
};

typedef std::shared_ptr<TargetHumidityIntfController> TargetHumidityIntfControllerPtr;

} //namespace services
} //namespace ajn

#endif /* TARGETHUMIDITYINTFCONTROLLER_H_ */
