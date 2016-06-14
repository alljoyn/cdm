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

#ifndef PLUGINUNITSINTFCONTROLLERLISTENER_H_
#define PLUGINUNITSINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/hae/interfaces/InterfaceControllerListener.h>
#include <alljoyn/hae/interfaces/operation/PlugInUnitsInterface.h>

namespace ajn {
namespace services {

/**
 * PlugInUnits Interface Controller Listener class
 */
class PlugInUnitsIntfControllerListener : public InterfaceControllerListener {
  public:
    virtual ~PlugInUnitsIntfControllerListener() {}

    /**
     * Callback handler for getting list of plug in units
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] plugInUnits list of plug in unit
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetPlugInUnits(QStatus status, const qcc::String& objectPath, const PlugInUnitsInterface::PlugInUnits& plugInUnits, void* context) {}

    /**
     * Handler for PlugInUnits property changed
     * @param[in] plugInUnits plug in units
     */
    virtual void OnPlugInUnitsPropertyChanged(const qcc::String& objectPath, const PlugInUnitsInterface::PlugInUnits& plugInUints) {}

 };

} //namespace services
} //namespace ajn

#endif /* PLUGINUNITSINTFCONTROLLERLISTENER_H_ */
