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

#ifndef BRIGHTNESSINTFCONTROLLERLISTENER_H_
#define BRIGHTNESSINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>
#include <alljoyn/cdm/interfaces/operation/BrightnessInterface.h>

namespace ajn {
namespace services {

/**
 * Brightness Interface Controller Listener class
 */
class BrightnessIntfControllerListener : public InterfaceControllerListener {
  public:

    /**
     * Destructor of BrightnessIntfControllerListener
     */
    virtual ~BrightnessIntfControllerListener() {}

    /**
     * Callback handler for GetBrightness completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of Brightness
     *                  (Brightness of the device.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetBrightness(QStatus status, const qcc::String& objectPath, const double value, void* context) {}

    /**
     * Handler for Brightness property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of Brightness
     *                  (Brightness of the device.)
     */
    virtual void OnBrightnessChanged(const qcc::String& objectPath, const double value) {}

    /**
     * Callback handler for SetBrightness completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetBrightness(QStatus status, const qcc::String& objectPath, void* context) {}
};

} //namespace services
} //namespace ajn

#endif /* BRIGHTNESSINTFCONTROLLERLISTENER_H_ */
