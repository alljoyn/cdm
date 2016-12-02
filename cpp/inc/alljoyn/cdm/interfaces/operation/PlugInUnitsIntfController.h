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

#ifndef PLUGINUNITSINTFCONTROLLER_H_
#define PLUGINUNITSINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/PlugInUnitsInterface.h>

namespace ajn {
namespace services {

/**
 * PlugInUnits Interface Controller class
 */
class PlugInUnitsIntfController : public PlugInUnitsInterface {
  public:
    /**
     * Constructor of PlugInUnitsIntfController
     */
    PlugInUnitsIntfController() {}

    /**
     * Destructor of PlugInUnitsIntfController
     */
    virtual ~PlugInUnitsIntfController() {}

    /**
     * Get PlugInUnits
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetPlugInUnits(void* context = NULL) = 0;
};

} //namespace services
} //namespace ajn

#endif /* PLUGINUNITSINTFCONTROLLER_H_ */