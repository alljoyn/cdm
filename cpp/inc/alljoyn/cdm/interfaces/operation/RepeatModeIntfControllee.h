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

#ifndef REPEATMODEINTFCONTROLLEE_H_
#define REPEATMODEINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/RepeatModeInterface.h>

namespace ajn {
namespace services {

/**
 * RepeatMode Interface Controllee class
 */
class RepeatModeIntfControllee : public RepeatModeInterface {
  public:
    /**
     * Constructor of RepeatModeIntfControllee
     */
    RepeatModeIntfControllee() {}

    /**
     * Destructor of RepeatModeIntfControllee
     */
    virtual ~RepeatModeIntfControllee() {}

    /**
     * Get RepeatMode
     * @return RepeatMode
     */
    virtual const bool GetRepeatMode() const = 0;

    /**
     * Set RepeatMode
     * @param[in] value
     * @return ER_OK on success
     */
    virtual QStatus SetRepeatMode(const bool value) = 0;

};

} //namespace services
} //namespace ajn

#endif /* REPEATMODEINTFCONTROLLEE_H_ */
