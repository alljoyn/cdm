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

#ifndef INTERFACECONTROLLER_H_
#define INTERFACECONTROLLER_H_

#include <alljoyn/MessageReceiver.h>
#include <alljoyn/ProxyBusObject.h>

namespace ajn {
namespace services {

class CdmProxyBusObject;
/**
 * InterfaceController class
 */
class InterfaceController : public MessageReceiver, public ProxyBusObject::Listener, public ProxyBusObject::PropertiesChangedListener {
  public:

    /**
     * Constructor of InterfaceController
     */
    InterfaceController(CdmProxyBusObject& cdmProxyObject) : m_proxyObject(cdmProxyObject) {}

    /**
     * Destructor of InterfaceController
     */
    virtual ~InterfaceController() {}

  protected:
    CdmProxyBusObject& m_proxyObject;
};

} //namespace services
} //namespace ajn

#endif /* INTERFACECONTROLLER_H_ */