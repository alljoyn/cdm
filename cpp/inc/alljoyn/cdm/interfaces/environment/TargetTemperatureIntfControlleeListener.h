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

#ifndef TARGETTEMPERATUREINTFCONTROLLEELISTENER_H_
#define TARGETTEMPERATUREINTFCONTROLLEELISTENER_H_

#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/hae/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * TargetTemperature interface controllee listener class
 */
class TargetTemperatureIntfControlleeListener : public InterfaceControlleeListener {
  public:

    /**
     * Destructor of TargetTemperatureIntfControlleeListener
     */
    virtual ~TargetTemperatureIntfControlleeListener() {}

    /**
     * Handler for setting target temperature
     * @param[in] value the target temperature
     * @return ER_OK on success
     */
    virtual QStatus OnSetTargetValue(const double value) = 0;

    /**
     * Handler for getting target temperature
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value the target temperature
     * @return ER_OK on success
     */
    virtual QStatus OnGetTargetValue(double& value) = 0;

    /**
     * Handler for getting the minimum value of target temperature
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value the minimum value of target temperature
     * @return ER_OK on success
     */
    virtual QStatus OnGetMinValue(double& value) = 0;


    /**
     * Handler for getting the maximum value of target temperature
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value the maximum value of target temperature
     * @return ER_OK on success
     */
    virtual QStatus OnGetMaxValue(double& value) = 0;


    /**
     * Handler for getting the step value of target temperature
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value the step value of target temperature
     * @return ER_OK on success
     */
    virtual QStatus OnGetStepValue(double& value) = 0;
};

} //namespace services
} //namespace ajn

#endif /* TARGETTEMPERATUREINTFCONTROLLEELISTENER_H_ */
