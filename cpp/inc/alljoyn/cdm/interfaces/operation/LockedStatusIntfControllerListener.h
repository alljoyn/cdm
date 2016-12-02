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

#ifndef LOCKEDSTATUSINTFCONTROLLERLISTENER_H_
#define LOCKEDSTATUSINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>
#include <alljoyn/cdm/interfaces/operation/LockedStatusInterface.h>

namespace ajn {
namespace services {

/**
 * LockedStatus Interface Controller Listener class
 */
class LockedStatusIntfControllerListener : public InterfaceControllerListener {
  public:

    /**
     * Destructor of LockedStatusIntfControllerListener
     */
    virtual ~LockedStatusIntfControllerListener() {}

    /**
     * Callback handler for GetIsLocked completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of IsLocked
     *                  (The status of the locking mechanism.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetIsLocked(QStatus status, const qcc::String& objectPath, const bool value, void* context) {}

    /**
     * Handler for IsLocked property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of IsLocked
     *                  (The status of the locking mechanism.)
     */
    virtual void OnIsLockedChanged(const qcc::String& objectPath, const bool value) {}
};

} //namespace services
} //namespace ajn

#endif /* LOCKEDSTATUSINTFCONTROLLERLISTENER_H_ */
