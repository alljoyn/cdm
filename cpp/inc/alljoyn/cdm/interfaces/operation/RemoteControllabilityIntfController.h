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

#ifndef REMOTECONTROLLABILITYINTFCONTROLLER_H_
#define REMOTECONTROLLABILITYINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/RemoteControllabilityInterface.h>

namespace ajn {
namespace services {

/**
 * RemoteControllability Interface Controller class
 */
class RemoteControllabilityIntfController : public RemoteControllabilityInterface {
  public:
    /**
     * Constructor of RemoteControllabilityIntfController
     */
    RemoteControllabilityIntfController() {}

    /**
     * Destructor of RemoteControllabilityIntfController
     */
    virtual ~RemoteControllabilityIntfController() {}

    /**
     * Get isControllable
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetIsControllable(void* context = NULL) = 0;

};

} //namespace services
} //namespace ajn

#endif /* REMOTECONTROLLABILITYINTFCONTROLLER_H_ */