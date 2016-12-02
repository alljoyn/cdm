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

#ifndef REPEATMODEINTFCONTROLLERLISTENER_H_
#define REPEATMODEINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>
#include <alljoyn/cdm/interfaces/operation/RepeatModeInterface.h>

namespace ajn {
namespace services {

/**
 * RepeatMode Interface Controller Listener class
 */
class RepeatModeIntfControllerListener : public InterfaceControllerListener {
  public:

    /**
     * Destructor of RepeatModeIntfControllerListener
     */
    virtual ~RepeatModeIntfControllerListener() {}

    /**
     * Callback handler for GetRepeatMode completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of RepeatMode
     *                  (True if the device works in repeat mode.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetRepeatMode(QStatus status, const qcc::String& objectPath, const bool value, void* context) {}

    /**
     * Handler for RepeatMode property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of RepeatMode
     *                  (True if the device works in repeat mode.)
     */
    virtual void OnRepeatModeChanged(const qcc::String& objectPath, const bool value) {}

    /**
     * Callback handler for SetRepeatMode completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetRepeatMode(QStatus status, const qcc::String& objectPath, void* context) {}
};

} //namespace services
} //namespace ajn

#endif /* REPEATMODEINTFCONTROLLERLISTENER_H_ */
