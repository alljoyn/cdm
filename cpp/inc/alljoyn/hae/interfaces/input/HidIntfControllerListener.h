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
#include <alljoyn/hae/interfaces/InterfaceControllerListener.h>
#include "HidInterface.h"

namespace ajn {
namespace services {

/**
 * Hid Interface Controller Listener class
 */
class HidIntfControllerListener : public InterfaceControllerListener {
  public:
    /**
     * Destructor of HidIntfControllerListener
     */
    virtual ~HidIntfControllerListener() {}

    /**
     * Handler for SupportedEvents property changed
     * @param[in] objectPath the object path
     * @param[in] supportedEvents supported events
     */
    virtual void SupportedEventsPropertyChanged(const qcc::String& objectPath, const HidInterface::SupportedInputEvents& supportedEvents) {}

    /**
     * Callback handler for getting SupportedEvents property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] supportedEvents supported events
     * @param[in] context the context that is passed from application
     */
    virtual void GetSupportedEventsPropertyCallback(QStatus status, const qcc::String& objectPath, const HidInterface::SupportedInputEvents& supportedEvents, void* context) {}
};

} //namespace services
} //namespace ajn

#endif /* HIDINTFCONTROLLERLISTENER_H_ */
