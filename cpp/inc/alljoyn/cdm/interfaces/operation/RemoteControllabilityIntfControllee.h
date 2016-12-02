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

#ifndef REMOTECONTROLLABILITYINTFCONTROLLEE_H_
#define REMOTECONTROLLABILITYINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/RemoteControllabilityInterface.h>

namespace ajn {
namespace services {

/**
 * RemoteControllability Interface Controllee class
 */
class RemoteControllabilityIntfControllee : public RemoteControllabilityInterface {
  public:
    /**
     * Constructor of RemoteControllabilityIntfControllee
     */
    RemoteControllabilityIntfControllee() {}

    /**
     * Destructor of RemoteControllabilityIntfControllee
     */
    virtual ~RemoteControllabilityIntfControllee() {}

    /**
     * Get IsControllable
     * @return IsControllable
     */
    virtual const bool GetIsControllable() const = 0;

    /**
     * Set IsControllable
     * @param[in] isControllable IsControllable
     * @return ER_OK on success
     */
    virtual QStatus SetIsControllable(const bool isControllable) = 0;

};

} //namespace services
} //namespace ajn

#endif /* REMOTECONTROLLABILITYINTFCONTROLLEE_H_ */