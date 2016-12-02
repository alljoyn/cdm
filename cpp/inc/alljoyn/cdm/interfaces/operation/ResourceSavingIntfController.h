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

#ifndef RESOURCESAVINGINTFCONTROLLER_H_
#define RESOURCESAVINGINTFCONTROLLER_H_

#include <vector>
#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/ResourceSavingInterface.h>

namespace ajn {
namespace services {

/**
 * ResourceSaving Interface Controller class
 */
class ResourceSavingIntfController : public ResourceSavingInterface {
  public:
    /**
     * Constructor of ResourceSavingIntfController
     */
    ResourceSavingIntfController() {}

    /**
     * Destructor of ResourceSavingIntfController
     */
    virtual ~ResourceSavingIntfController() {}

    /**
     * Get resource saving mode
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetResourceSavingMode(void* context = NULL) = 0;

    /**
     * Set resource saving mode
     * @param[in] mode resource saving mode
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetResourceSavingMode(const bool mode, void* context = NULL) = 0;
};

} //namespace services
} //namespace ajn

#endif /* RESOURCESAVINGINTFCONTROLLER_H_ */