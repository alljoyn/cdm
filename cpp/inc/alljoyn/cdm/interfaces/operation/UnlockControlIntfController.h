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

#ifndef UNLOCKCONTROLINTFCONTROLLER_H_
#define UNLOCKCONTROLINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/UnlockControlInterface.h>

namespace ajn {
namespace services {

/**
 * UnlockControl Interface Controller class
 */
class UnlockControlIntfController : public UnlockControlInterface {
  public:
    /**
     * Constructor of UnlockControlIntfController
     */
    UnlockControlIntfController() {}

    /**
     * Destructor of UnlockControlIntfController
     */
    virtual ~UnlockControlIntfController() {}

    /**
     * Call Unlock method
     * (Disengage the locking mechanism.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus Unlock(void* context = NULL) = 0;
};

typedef std::shared_ptr<UnlockControlIntfController> UnlockControlIntfControllerPtr;

} //namespace services
} //namespace ajn

#endif /* UNLOCKCONTROLINTFCONTROLLER_H_ */
