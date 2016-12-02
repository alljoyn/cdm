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

#ifndef INTERFACECONTROLLEELISTENER_H_
#define INTERFACECONTROLLEELISTENER_H_


#include <alljoyn/cdm/interfaces/CdmInterfaceListener.h>

namespace ajn {
namespace services {

/**
 * InterfaceControlleeListener class
 */
class InterfaceControlleeListener : public CdmInterfaceListener {
  public:

    /**
     * Destructor of InterfaceControlleeListener
     */
    virtual ~InterfaceControlleeListener() {}

};

} //namespace services
} //namespace ajn

#endif /* INTERFACECONTROLLEELISTENER_H_ */