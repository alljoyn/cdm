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

#ifndef RESOURCESAVINGINTFCONTROLLEE_H_
#define RESOURCESAVINGINTFCONTROLLEE_H_

#include <vector>
#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/ResourceSavingInterface.h>

namespace ajn {
namespace services {

/**
 * ResourceSaving Interface Controllee class
 */
class ResourceSavingIntfControllee : public ResourceSavingInterface {
  public:
    /**
     * Constructor of ResourceSavingIntfControllee
     */
    ResourceSavingIntfControllee() {}

    /**
     * Destructor of ResourceSavingIntfControllee
     */
    virtual ~ResourceSavingIntfControllee() {}

    /**
     * Get resource saving mode
     * @return Resource saving mode
     */
    virtual const bool GetResourceSavingMode() const = 0;

    /**
     * Set resource saving mode
     * @param[in] mode resource saving mode
     * @return ER_OK on success
     */
    virtual QStatus SetResourceSavingMode(const bool mode) = 0;
};

} //namespace services
} //namespace ajn

#endif /* RESOURCESAVINGINTFCONTROLLEE_H_ */