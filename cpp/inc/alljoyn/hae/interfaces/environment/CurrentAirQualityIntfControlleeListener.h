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

#ifndef CURRENTAIRQUALITYINTFCONTROLLEELISTENER_H_
#define CURRENTAIRQUALITYINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/hae/interfaces/HaeInterfaceErrors.h>
#include <alljoyn/hae/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * CurrentAirQuality Interface Controllee Listener class
 */
class CurrentAirQualityIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of CurrentAirQualityIntfControlleeListener
     */
    virtual ~CurrentAirQualityIntfControlleeListener() {}

    /**
     * Handler for getting the contatminant type
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] type the contaminant type
     * @return ER_OK on success
     */
    virtual QStatus OnGetContaminantType(uint8_t& type) = 0;

    /**
     * Handler for getting current air quality
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value the air quality
     * @return ER_OK on success
     */
    virtual QStatus OnGetCurrentValue(double& value) = 0;

    /**
     * Handler for getting the maximum value of air quality
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value the maximum value of air quality
     * @return ER_OK on success
     */
    virtual QStatus OnGetMaxValue(double& value) = 0;

    /**
     * Handler for getting the minimum value of air quality
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value the minimum value of air quality
     * @return ER_OK on success
     */
    virtual QStatus OnGetMinValue(double& value) = 0;

    /**
     * Handler for getting Precision
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] Precision precision
     * @return ER_OK on success
     */
    virtual QStatus OnGetPrecision(double& precision) = 0;

    /**
     * Handler for getting UpdateMinTime
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] UpdateMinTime the minimum time between updates
     * @return ER_OK on success
     */
    virtual QStatus OnGetUpdateMinTime(uint16_t& updateMinTime) = 0;
};

} //namespace services
} //namespace ajn

#endif /* CURRENTAIRQUALITYINTFCONTROLLEELISTENER_H_ */
