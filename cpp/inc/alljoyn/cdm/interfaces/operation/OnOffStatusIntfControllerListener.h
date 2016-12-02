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

#ifndef ONOFFSTATUSINTFCONTROLLERLISTENER_H_
#define ONOFFSTATUSINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>

namespace ajn {
namespace services {

/**
 * OnOffStatus Interface Controller Listener class
 */
class OnOffStatusIntfControllerListener : public InterfaceControllerListener {
  public:
    virtual ~OnOffStatusIntfControllerListener() {}

    /**
     * Callback handler for getting IsOn property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] IsOn value
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetIsOn(QStatus status, const qcc::String& objectPath, const bool value, void* context) {}

    /**
     * Handler for IsOn property changed
     * @param[in] objectPath the object path
     * @param[in] IsOn value
     */
    virtual void OnIsOnChanged(const qcc::String& objectPath, const bool value) {}

};

} //namespace services
} //namespace ajn

#endif /* ONOFFSTATUSINTFCONTROLLERLISTENER_H_ */