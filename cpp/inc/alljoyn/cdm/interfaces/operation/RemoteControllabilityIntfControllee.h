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

#ifndef REMOTECONTROLLABILITYINTFCONTROLLEE_H_
#define REMOTECONTROLLABILITYINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/RemoteControllabilityInterface.h>

namespace ajn {
namespace services {

/**
 * RemoteControllability Interface Controllee class
 */
class RemoteControllabilityIntfControllee : public RemoteControllabilityInterface {
  public:
    /**
     * Constructor of RemoteControllabilityIntfControllee
     */
    RemoteControllabilityIntfControllee() {}

    /**
     * Destructor of RemoteControllabilityIntfControllee
     */
    virtual ~RemoteControllabilityIntfControllee() {}

    /**
     * Get IsControllable
     * @return IsControllable
     */
    virtual const bool GetIsControllable() const = 0;

    /**
     * Set IsControllable
     * @param[in] isControllable IsControllable
     * @return ER_OK on success
     */
    virtual QStatus SetIsControllable(const bool isControllable) = 0;

};

} //namespace services
} //namespace ajn

#endif /* REMOTECONTROLLABILITYINTFCONTROLLEE_H_ */
