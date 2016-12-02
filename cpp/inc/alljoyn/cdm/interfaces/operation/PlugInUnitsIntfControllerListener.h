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

#ifndef PLUGINUNITSINTFCONTROLLERLISTENER_H_
#define PLUGINUNITSINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>
#include <alljoyn/cdm/interfaces/operation/PlugInUnitsInterface.h>

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