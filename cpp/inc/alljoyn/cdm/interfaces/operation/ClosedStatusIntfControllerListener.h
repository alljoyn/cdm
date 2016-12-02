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

#ifndef CLOSEDSTATUSINTFCONTROLLERLISTENER_H_
#define CLOSEDSTATUSINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>

namespace ajn {
namespace services {

/**
 * ClosedStatus Interface Controller Listener class
 */
class ClosedStatusIntfControllerListener : public InterfaceControllerListener {
  public:
    virtual ~ClosedStatusIntfControllerListener() {}
    /**
     * Callback handler for getting IsClosed property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] isClosed isClosed
     * @param[in] context the context that is passed from application
     */
    virtual void GetIsClosedPropertyCallback(QStatus status, const qcc::String& objectPath, const bool isClosed, void* context) {}

    /**
     * Handler for IsClosed property changed
     * @param[in] objectPath the object path
     * @param[in] isClosed isClosed
     */
    virtual void IsClosedPropertyChanged(const qcc::String& objectPath, const bool isClosed) { }

};

} //namespace services
} //namespace ajn

#endif /* CLOSEDSTATUSINTFCONTROLLERLISTENER_H_ */