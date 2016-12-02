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

#ifndef RESOURCESAVINGINTFCONTROLLERLISTENER_H_
#define RESOURCESAVINGINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>

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