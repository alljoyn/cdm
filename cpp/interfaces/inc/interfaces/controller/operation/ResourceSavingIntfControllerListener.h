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

// This file is automatically generated. Do not edit it.

#ifndef RESOURCESAVINGINTFCONTROLLERLISTENER_H_
#define RESOURCESAVINGINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/controller/InterfaceControllerListener.h>
#include <interfaces/common/operation/ResourceSavingInterface.h>

namespace ajn {
namespace services {

/**
 * ResourceSaving Interface Controller Listener class
 */
class ResourceSavingIntfControllerListener : public InterfaceControllerListener {
  public:

    /**
     * Destructor of ResourceSavingIntfControllerListener
     */
    virtual ~ResourceSavingIntfControllerListener() {}

    /**
     * Callback handler for GetResourceSavingMode completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of ResourceSavingMode
     *                  (The current resource saving mode of the device; true if device in saving mode.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetResourceSavingMode(QStatus status, const qcc::String& objectPath, const bool value, void* context) {}

    /**
     * Handler for ResourceSavingMode property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of ResourceSavingMode
     *                  (The current resource saving mode of the device; true if device in saving mode.)
     */
    virtual void OnResourceSavingModeChanged(const qcc::String& objectPath, const bool value) {}

    /**
     * Callback handler for SetResourceSavingMode completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetResourceSavingMode(QStatus status, const qcc::String& objectPath, void* context) {}
};

} //namespace services
} //namespace ajn

#endif /* RESOURCESAVINGINTFCONTROLLERLISTENER_H_ */
