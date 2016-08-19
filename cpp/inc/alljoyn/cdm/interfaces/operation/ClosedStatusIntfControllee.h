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

#ifndef CLOSEDSTATUSINTFCONTROLLEE_H_
#define CLOSEDSTATUSINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/hae/interfaces/operation/ClosedStatusInterface.h>

namespace ajn {
namespace services {

/**
 * ClosedStatus Interface Controllee class
 */
class ClosedStatusIntfControllee : public ClosedStatusInterface {
  public:
    /**
     * Constructor of ClosedStatusIntfControllee
     */
    ClosedStatusIntfControllee() {}

    /**
     * Destructor of ClosedStatusIntfControllee
     */
    virtual ~ClosedStatusIntfControllee() {}

    /**
     * Get IsClosed
     * @return IsClosed
     */
    virtual const bool GetIsClosed() const = 0;

    /**
     * Set IsClosed
     * @param[in] isClosed isClosed
     * @return ER_OK on success
     */
    virtual QStatus SetIsClosed(const bool isClosed) = 0;
};

} //namespace services
} //namespace ajn

#endif /* CLOSEDSTATUSINTFCONTROLLEE_H_ */
