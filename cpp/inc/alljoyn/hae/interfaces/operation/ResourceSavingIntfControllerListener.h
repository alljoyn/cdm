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

#ifndef RESOURCESAVINGINTFCONTROLLERLISTENER_H_
#define RESOURCESAVINGINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/hae/interfaces/InterfaceControllerListener.h>

namespace ajn {
namespace services {

/**
 * ResourceSaving interface controller listener class
 */
class ResourceSavingIntfControllerListener : public InterfaceControllerListener {
  public:

    /**
     * Destructor of ResourceSavingIntfControllerListener
     */
    virtual ~ResourceSavingIntfControllerListener() {}

    /**
     * Handler for OnResourceSavingMode property changed
     * @param[in] objectPath the object path
     * @param[in] value resource saving mode
     */
    virtual void OnResourceSavingModeChanged(const qcc::String& objectPath, const bool value) {}

    /**
     * Callback handler for setting ResourceSavingMode property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetResourceSavingMode(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for getting ResourceSavingMode property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value resource saving mode
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetResourceSavingMode(QStatus status, const qcc::String& objectPath, const bool value, void* context) {}
};

} //namespace services
} //namespace ajn

#endif /* RESOURCESAVINGINTFCONTROLLERLISTENER_H_ */
