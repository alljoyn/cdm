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

#ifndef RESOURCESAVINGINTFCONTROLLEELISTENER_H_
#define RESOURCESAVINGINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/hae/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * ResourceSaving interface controllee listener class
 */
class ResourceSavingIntfControlleeListener : public InterfaceControlleeListener {
  public:

    /**
     * Destructor of ResourceSavingIntfControlleeListener
     */
    virtual ~ResourceSavingIntfControlleeListener() {}

    /**
     * Handler for setting resource saving mode
     * @param[in] mode resource saving mode
     * @return ER_OK on success
     */
    virtual QStatus OnSetResourceSavingMode(const bool& mode) = 0;

    /**
     * Handler for getting resource saving mode
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] mode resource saving mode
     * @return ER_OK on success
     */
    virtual QStatus OnGetResourceSavingMode(bool& mode) = 0;
};

} //namespace services
} //namespace ajn

#endif /* RESOURCESAVINGINTFCONTROLLEELISTENER_H_ */
