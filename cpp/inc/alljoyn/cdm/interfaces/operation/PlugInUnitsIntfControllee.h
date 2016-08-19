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

#ifndef PLUGINUNITSINTFCONTROLLEE_H_
#define PLUGINUNITSINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/PlugInUnitsInterface.h>

namespace ajn {
namespace services {

/**
 * PlugInUnits Interface Controllee class
 */
class PlugInUnitsIntfControllee : public PlugInUnitsInterface {
  public:
    /**
     * Constructor of PlugInUnitsIntfControllee
     */
    PlugInUnitsIntfControllee() {}

    /**
     * Destructor of PlugInUnitsIntfControllee
     */
    virtual ~PlugInUnitsIntfControllee() {}

    /**
     * Get PlugInUnits
     * @return the list of plug in units
     */
    virtual const PlugInUnits& GetPlugInUnits() const = 0;

    /**
     * Set PlugInUnits
     * @param[in]  plugInUnits the list of plug in units
     * @return ER_OK on success
     */
    virtual QStatus SetPlugInUnits(const PlugInUnits& plugInUnits) = 0;
};

} //namespace services
} //namespace ajn

#endif /* PLUGINUNITSINTFCONTROLLEE_H_ */
