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

#ifndef CLOSEDSTATUSINTFCONTROLLEELISTENER_H_
#define CLOSEDSTATUSINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * ClosedStatus Interface Controllee Listener class
 */
class ClosedStatusIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of ClosedStatusIntfControlleeListener
     */
    virtual ~ClosedStatusIntfControlleeListener() {}

    /**
     * Handler for getting isClosed
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] isClosed isClosed
     * @return ER_OK on success
     */
    virtual QStatus OnGetIsClosed(bool& isClosed) = 0;
};

} //namespace services
} //namespace ajn

#endif /* CLOSEDSTATUSINTFCONTROLLEELISTENER_H_ */