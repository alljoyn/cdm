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

#ifndef HIDINTFCONTROLLER_H_
#define HIDINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/input/HidInterface.h>

namespace ajn {
namespace services {

/**
 * Hid Interface Controller class
 */
class HidIntfController : public HidInterface {
  public:
    /**
     * Constructor of HidIntfController
     */
    HidIntfController() {}

    /**
     * Destructor of HidIntfController
     */
    virtual ~HidIntfController() {}

    /**
     * Get SupportedEvents property
     * (List of supported input events by a device)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetSupportedEvents(void* context = NULL) = 0;

    /**
     * Call InjectEvents method
     * (Inject the user input events for human interface devices)
     * @param[in] inputEvents Injected input event
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus InjectEvents(const std::vector<InputEvent>& inputEvents, void* context = NULL) = 0;
};

typedef std::shared_ptr<HidIntfController> HidIntfControllerPtr;

} //namespace services
} //namespace ajn

#endif /* HIDINTFCONTROLLER_H_ */
