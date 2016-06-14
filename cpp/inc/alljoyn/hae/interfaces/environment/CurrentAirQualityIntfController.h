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

#ifndef CURRENTAIRQUALITYINTFCONTROLLER_H_
#define CURRENTAIRQUALITYINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/hae/interfaces/environment/CurrentAirQualityInterface.h>

namespace ajn {
namespace services {

/**
 * CurrentAirQuality Interface Controller class
 */
class CurrentAirQualityIntfController : public CurrentAirQualityInterface {
  public:
    /**
     * Constructor of CurrentAirQualityIntfController
     */
    CurrentAirQualityIntfController() {}

    /**
     * Destructor of CurrentAirQualityIntfController
     */
    virtual ~CurrentAirQualityIntfController() {}

    /**
     * Get ContaminantType
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetContaminantType(void* context = NULL) = 0;

    /**
     * Get CurrentValue
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetCurrentValue(void* context = NULL) = 0;

    /**
     * Get the maximum value of air quality
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetMaxValue(void* context = NULL) = 0;

    /**
     * Get the minimum value of air quality
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetMinValue(void* context = NULL) = 0;

    /**
     * Get Precision
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetPrecision(void* context = NULL) = 0;

    /**
     * Get UpdateMinTime
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetUpdateMinTime(void* context = NULL) = 0;
};

} //namespace services
} //namespace ajn

#endif /* CURRENTAIRQUALITYINTFCONTROLLER_H_ */
