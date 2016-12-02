/******************************************************************************
 *  * 
 *    Copyright (c) 2016 Open Connectivity Foundation and AllJoyn Open
 *    Source Project Contributors and others.
 *    
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0

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