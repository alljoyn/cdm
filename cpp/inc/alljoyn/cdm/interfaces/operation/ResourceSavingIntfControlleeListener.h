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

#ifndef RESOURCESAVINGINTFCONTROLLEELISTENER_H_
#define RESOURCESAVINGINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>

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