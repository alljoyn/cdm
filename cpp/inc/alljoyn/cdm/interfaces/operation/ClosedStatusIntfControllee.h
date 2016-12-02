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

#ifndef CLOSEDSTATUSINTFCONTROLLEE_H_
#define CLOSEDSTATUSINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/ClosedStatusInterface.h>

namespace ajn {
namespace services {

/**
 * ClosedStatus Interface Controllee class
 */
class ClosedStatusIntfControllee : public ClosedStatusInterface {
  public:
    /**
     * Constructor of ClosedStatusIntfControllee
     */
    ClosedStatusIntfControllee() {}

    /**
     * Destructor of ClosedStatusIntfControllee
     */
    virtual ~ClosedStatusIntfControllee() {}

    /**
     * Get IsClosed
     * @return IsClosed
     */
    virtual const bool GetIsClosed() const = 0;

    /**
     * Set IsClosed
     * @param[in] isClosed isClosed
     * @return ER_OK on success
     */
    virtual QStatus SetIsClosed(const bool isClosed) = 0;
};

} //namespace services
} //namespace ajn

#endif /* CLOSEDSTATUSINTFCONTROLLEE_H_ */