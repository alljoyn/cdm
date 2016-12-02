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

#ifndef RAPIDMODEINTFCONTROLLERLISTENER_H_
#define RAPIDMODEINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>

namespace ajn {
namespace services {

/**
 * RapidMode Interface Controller Listener class
 */
class RapidModeIntfControllerListener : public InterfaceControllerListener {
  public:
    virtual ~RapidModeIntfControllerListener() {}

    /**
     * Handler for RapidMode property changed
     * @param[in] objectPath the object path
     * @param[in] rapidMode rapid mode
     */
    virtual void OnRapidModeChanged(const qcc::String& objectPath, const bool rapidMode) {}

    /**
     * Callback handler for setting RapidMode property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetRapidMode(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for getting RapidMode property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] rapidMode rapid mode
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetRapidMode(QStatus status, const qcc::String& objectPath, const bool rapidMode, void* context) {}
};

} //namespace services
} //namespace ajn

#endif /* RAPIDMODEINTFCONTROLLERLISTENER_H_ */
