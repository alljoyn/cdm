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

#ifndef CURRENTPOWERINTFCONTROLLERLISTENER_H_
#define CURRENTPOWERINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/hae/interfaces/InterfaceControllerListener.h>

namespace ajn {
namespace services {

/**
 * CurrentPower Interface Controller Listener class
 */
class CurrentPowerIntfControllerListener : public InterfaceControllerListener {
  public:
    virtual ~CurrentPowerIntfControllerListener() {}

    /**
     * Callback handler for getting CurrentPower property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] CurrentPower
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetCurrentPower(QStatus status, const qcc::String& objectPath, const double currentPower, void* context) {}

    /**
     * Callback handler for getting Precision property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] Precision
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetPrecision(QStatus status, const qcc::String& objectPath, const double precision, void* context) {}

    /**
     * Callback handler for getting UpdateMinTime property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] UpdateMinTime
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetUpdateMinTime(QStatus status, const qcc::String& objectPath, const uint16_t updateMinTime, void* context) {}

    /**
     * Handler for CurrentPower property changed
     * @param[in] objectPath the object path
     * @param[in] CurrentPower
     */
    virtual void OnCurrentPowerChanged(const qcc::String& objectPath, const double currentPower) {}

    /**
     * Handler for Precision property changed
     * @param[in] objectPath the object path
     * @param[in] Precision
     */
    virtual void OnPrecisionChanged(const qcc::String& objectPath, const double precision) {}

    /**
     * Handler for UpdateMinTime property changed
     * @param[in] objectPath the object path
     * @param[in] UpdateMinTime
     */
    virtual void OnUpdateMinTimeChanged(const qcc::String& objectPath, const uint16_t updateMinTime) {}
};

} //namespace services
} //namespace ajn

#endif /* CURRENTPOWERINTFCONTROLLERLISTENER_H_ */
