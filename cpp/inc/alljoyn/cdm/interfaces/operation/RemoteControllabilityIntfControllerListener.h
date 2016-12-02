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

#ifndef REMOTECONTROLLABILITYINTFCONTROLLERLISTENER_H_
#define REMOTECONTROLLABILITYINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>
#include <alljoyn/cdm/interfaces/operation/RemoteControllabilityInterface.h>

namespace ajn {
namespace services {

/**
 * RemoteControllability Interface Controller Listener class
 */
class RemoteControllabilityIntfControllerListener : public InterfaceControllerListener {
  public:

    /**
     * Destructor of RemoteControllabilityIntfControllerListener
     */
    virtual ~RemoteControllabilityIntfControllerListener() {}

    /**
     * Callback handler for GetIsControllable completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of IsControllable
     *                  (Status of remote controllability; true if remote controllability enabled.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetIsControllable(QStatus status, const qcc::String& objectPath, const bool value, void* context) {}

    /**
     * Handler for IsControllable property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of IsControllable
     *                  (Status of remote controllability; true if remote controllability enabled.)
     */
    virtual void OnIsControllableChanged(const qcc::String& objectPath, const bool value) {}
};

} //namespace services
} //namespace ajn

#endif /* REMOTECONTROLLABILITYINTFCONTROLLERLISTENER_H_ */
