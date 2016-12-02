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

#ifndef ONOFFSTATUSINTFCONTROLLEELISTENER_H_
#define ONOFFSTATUSINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * OnOffStatus Interface Controllee Listener class
 */
class OnOffStatusIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of OnOffStatusIntfControlleeListener
     */
    virtual ~OnOffStatusIntfControlleeListener() {}

    /**
     * Handler for getting IsOn
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] IsOn
     * @return ER_OK on success
     */
    virtual QStatus OnGetIsOn(bool& value) = 0;

};

} //namespace services
} //namespace ajn

#endif /* ONOFFSTATUSINTFCONTROLLEELISTENER_H_ */