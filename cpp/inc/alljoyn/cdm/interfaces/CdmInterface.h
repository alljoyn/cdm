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

#ifndef CDMINTERFACE_H_
#define CDMINTERFACE_H_

#include <qcc/String.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/cdm/interfaces/CdmInterfaceTypes.h>
#include <alljoyn/cdm/interfaces/CdmInterfaceErrors.h>

namespace ajn {
namespace services {

class CdmInterface;
class InterfaceControlleeListener;
class InterfaceControllerListener;
class CdmBusObject;
class CdmProxyBusObject;

typedef CdmInterface* (*CreateIntfControlleeFptr)(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject);
typedef CdmInterface* (*CreateIntfControllerFptr)(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

/**
 * Cdm Interface class.
 * Used as a base class for other CDM interfaces.
 */
class CdmInterface {
  public:
    /**
     * Constructor of CdmInterface
     */
    CdmInterface() : m_interfaceDescription(NULL) {}

    /**
     * Destructor of CdmInterface
     */
    virtual ~CdmInterface() {}

    /**
     * Get bus attachment
     * @return Bus attachment
     */
    virtual BusAttachment& GetBusAttachment() const = 0;

    /**
     * Get interface Type
     * @return Interface type
     */
    virtual const CdmInterfaceType GetInterfaceType() const = 0;

    /**
     * Get specific interface name
     * @param[in] type interface type
     * @return Interface name
     */
    static const qcc::String& GetInterfaceName(CdmInterfaceType type) { return InterfaceTypesMap.find(type)->second; }

    /**
     * Get Interface version
     * @return interface version
     */
    virtual const uint16_t GetInterfaceVersion() const = 0;

    /**
     * Initialize interface
     * @return ER_OK on success
     */
    virtual QStatus Init();

    /**
     * Get interface name
     * @return Interface name
     */
    const qcc::String& GetInterfaceName() const { return InterfaceTypesMap.find(GetInterfaceType())->second; }

    /**
     * Get interface description
     * @return Interface description
     */
    const InterfaceDescription* GetInterfaceDescription() const { return m_interfaceDescription; }

    /**
     * Get interface error name
     * @return Interface error name
     */
    static qcc::String& GetInterfaceErrorName(ErrorCode errorCode) { return InterfaceErrorNameMap[errorCode]; }

    /**
     * Get interface error message
     * @return Interface error message
     */
    static qcc::String& GetInterfaceErrorMessage(ErrorCode errorCode) { return InterfaceErrorMessageMap[errorCode]; }

  protected:
    /**
     * Get introspection xml
     * @return Introspection xml
     */
    virtual const qcc::String& GetIntrospectionXml() = 0;

    const InterfaceDescription* m_interfaceDescription;

  private:
    static std::map<ErrorCode, qcc::String> InterfaceErrorNameMap;
    static std::map<ErrorCode, qcc::String> InterfaceErrorMessageMap;
};

} //namespace services
} //namespace ajn

#endif /* CDMINTERFACE_H_ */