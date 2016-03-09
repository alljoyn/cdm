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

#ifndef CURRENTPOWERINTFCONTROLLEELISTENER_H_
#define CURRENTPOWERINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/hae/interfaces/HaeInterfaceErrors.h>
#include <alljoyn/hae/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * CurrentPower Interface Controllee Listener class
 */
class CurrentPowerIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of CurrentPowerIntfControlleeListener
     */
    virtual ~CurrentPowerIntfControlleeListener() {}

    /**
     * Handler for setting CurrentPower
     * @param[in] CurrentPower
     * @return ER_OK on success
     */
    virtual QStatus OnSetCurrentPower(const double currentPower) = 0;

    /**
     * Handler for getting CurrentPower
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] CurrentPower
     * @return ER_OK on success
     */
    virtual QStatus OnGetCurrentPower(double& currentPower) = 0;

    /**
     * Handler for setting Precision
     * @param[in] Precision
     * @return ER_OK on success
     */
    virtual QStatus OnSetPrecision(const double precision) = 0;

    /**
     * Handler for getting Precision
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] Precision
     * @return ER_OK on success
     */
    virtual QStatus OnGetPrecision(double& precision) = 0;

    /**
     * Handler for setting UpdateMinTime
     * @param[in] UpdateMinTime
     * @return ER_OK on success
     */
    virtual QStatus OnSetUpdateMinTime(const uint16_t updateMinTime) = 0;

    /**
     * Handler for getting UpdateMinTime
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] UpdateMinTime
     * @return ER_OK on success
     */
    virtual QStatus OnGetUpdateMinTime(uint16_t& updateMinTime) = 0;
};

} //namespace services
} //namespace ajn

#endif /* CURRENTPOWERINTFCONTROLLEELISTENER_H_ */
