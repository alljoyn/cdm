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

#ifndef CDMPROXYBUSOBJECT_H_
#define CDMPROXYBUSOBJECT_H_

#include <map>
#include <qcc/String.h>
#include <alljoyn/ProxyBusObject.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/CdmInterfaceTypes.h>

namespace ajn {
namespace services {

class CdmInterface;
class InterfaceControllerListener;
/**
 * Cdm ProxyBusObject class.
 */
class CdmProxyBusObject : public ProxyBusObject {
  public:

    /**
     * Constructor of CdmProxyBusObject
     */
    CdmProxyBusObject(BusAttachment& busAttachment, std::string const& busName, qcc::String const& objectPath, SessionId sessionId);

    /**
     * Destructor of CdmProxyBusObject
     */
    ~CdmProxyBusObject();

    /**
     * Create anb add interface to BusObject
     * @param[in] type  interface type
     * @param[in] listener  interface controller listener
     * @return interface
     */
    CdmInterface* CreateInterface(const CdmInterfaceType type, InterfaceControllerListener& listener);


  private:

    BusAttachment& m_busAttachment;
    std::map<qcc::String, CdmInterface*> m_cdmInterfacesMap;
};

}
}

#endif /* CDMPROXYBUSOBJECT_H_ */