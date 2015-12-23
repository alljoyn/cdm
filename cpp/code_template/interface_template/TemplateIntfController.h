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

#ifndef {interface_nameu}INTFCONTROLLER_H_
#define {interface_nameu}INTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/hae/interfaces/{interface_category}/{interface_name}Interface.h>

namespace ajn {
namespace services {

/**
 * {interface_name} Interface Controller class
 */
class {interface_name}IntfController : public {interface_name}Interface {
  public:
    /**
     * Constructor of {interface_name}IntfController
     */
    {interface_name}IntfController() {}

    /**
     * Destructor of {interface_name}IntfController
     */
    virtual ~{interface_name}IntfController() {}

    /**
     * TODO: define functions to request the set/get properties
     * SetProperty function of read-only property must not be defined in the controller side.
     */

    /*
     * TODO: define functions to request the method call
     */
};

} //namespace services
} //namespace ajn

#endif /* {interface_nameu}INTFCONTROLLER_H_ */
