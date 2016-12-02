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

#ifndef PLUGINUNITSINTFCONTROLLEELISTENER_H_
#define PLUGINUNITSINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterfaceErrors.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/cdm/interfaces/operation/PlugInUnitsInterface.h>

namespace ajn {
namespace services {

/**
 * PlugInUnits Interface Controllee Listener class
 */
class PlugInUnitsIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of PlugInUnitsIntfControlleeListener
     */
    virtual ~PlugInUnitsIntfControlleeListener() {}

    /**
     * Handler for getting list of plug in uint
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] plugInUnits list of plug in unit
     * @return ER_OK on success
     */
    virtual QStatus OnGetPlugInUnits(PlugInUnitsInterface::PlugInUnits& plugInUnits) = 0;

};

} //namespace services
} //namespace ajn

#endif /* PLUGINUNITSINTFCONTROLLEELISTENER_H_ */