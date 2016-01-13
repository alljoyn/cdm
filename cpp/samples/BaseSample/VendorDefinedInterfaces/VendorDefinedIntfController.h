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

#ifndef VENDORDEFINEDINTFCONTROLLER_H_
#define VENDORDEFINEDINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include "VendorDefinedInterface.h"

namespace ajn {
namespace services {

/**
 * VendorDefined Interface Controller class
 */
class VendorDefinedIntfController : public VendorDefinedInterface {
  public:
    /**
     * Constructor of VendorDefinedIntfController
     */
    VendorDefinedIntfController() {}

    /**
     * Destructor of VendorDefinedIntfController
     */
    virtual ~VendorDefinedIntfController() {}

    /**
     * TODO: define functions to request the set/get properties
     * GetProperty function of read-only property must not be defined in the controller side.
     */
    virtual QStatus SetTestProperty(int32_t property, void* context = NULL) = 0;
    virtual QStatus GetTestProperty(void*  context = NULL) = 0;

    /*
     * TODO: define functions to request the method call
     */
    virtual QStatus TestMethod(int32_t arg1, void* context = NULL) = 0;
};

} //namespace services
} //namespace ajn

#endif /* VENDORDEFINEDINTFCONTROLLER_H_ */
