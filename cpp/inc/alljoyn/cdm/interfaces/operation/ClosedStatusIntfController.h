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

#ifndef CLOSEDSTATUSINTFCONTROLLER_H_
#define CLOSEDSTATUSINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/ClosedStatusInterface.h>

namespace ajn {
namespace services {

/**
 * ClosedStatus Interface Controller class
 */
class ClosedStatusIntfController : public ClosedStatusInterface {
  public:
    /**
     * Constructor of ClosedStatusIntfController
     */
    ClosedStatusIntfController() {}

    /**
     * Destructor of ClosedStatusIntfController
     */
    virtual ~ClosedStatusIntfController() {}

    /**
     * Get isClosed
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetIsClosed(void* context = NULL) = 0;
};

} //namespace services
} //namespace ajn

#endif /* CLOSEDSTATUSINTFCONTROLLER_H_ */