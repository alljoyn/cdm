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

#ifndef HIDINTFCONTROLLERLISTENER_H_
#define HIDINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>
#include <alljoyn/cdm/interfaces/input/HidInterface.h>

namespace ajn {
namespace services {

/**
 * Hid Interface Controller Listener class
 */
class HidIntfControllerListener : public InterfaceControllerListener {
  public:
    using InputEvent = HidInterface::InputEvent;
    using SupportedInputEvent = HidInterface::SupportedInputEvent;

    /**
     * Destructor of HidIntfControllerListener
     */
    virtual ~HidIntfControllerListener() {}

    /**
     * Callback handler for GetSupportedEvents completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of SupportedEvents
     *                  (List of supported input events by a device)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetSupportedEvents(QStatus status, const qcc::String& objectPath, const std::vector<SupportedInputEvent>& value, void* context) {}

    /**
     * Handler for SupportedEvents property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of SupportedEvents
     *                  (List of supported input events by a device)
     */
    virtual void OnSupportedEventsChanged(const qcc::String& objectPath, const std::vector<SupportedInputEvent>& value) {}

    /**
     * Callback handler for InjectEvents completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     * @param[in] errorName the detail errorName is passed when the method call is failed
     * @param[in] errorMessage the errorMessage that describes the error
     */
    virtual void OnResponseInjectEvents(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage) {}
};

} //namespace services
} //namespace ajn

#endif /* HIDINTFCONTROLLERLISTENER_H_ */
