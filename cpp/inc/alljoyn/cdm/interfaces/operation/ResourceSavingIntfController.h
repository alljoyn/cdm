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

#ifndef RESOURCESAVINGINTFCONTROLLER_H_
#define RESOURCESAVINGINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/ResourceSavingInterface.h>

namespace ajn {
namespace services {

/**
 * ResourceSaving Interface Controller class
 */
class ResourceSavingIntfController : public ResourceSavingInterface {
  public:
    /**
     * Constructor of ResourceSavingIntfController
     */
    ResourceSavingIntfController() {}

    /**
     * Destructor of ResourceSavingIntfController
     */
    virtual ~ResourceSavingIntfController() {}

    /**
     * Get ResourceSavingMode property
     * (The current resource saving mode of the device; true if device in saving mode.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetResourceSavingMode(void* context = NULL) = 0;

    /**
     * Set ResourceSavingMode property
     * (The current resource saving mode of the device; true if device in saving mode.)
     * @param[in] value The resource saving mode to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetResourceSavingMode(const bool value, void* context = NULL) = 0;
};

typedef std::shared_ptr<ResourceSavingIntfController> ResourceSavingIntfControllerPtr;

} //namespace services
} //namespace ajn

#endif /* RESOURCESAVINGINTFCONTROLLER_H_ */
