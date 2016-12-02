/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#ifndef CDMINTERFACE_H_
#define CDMINTERFACE_H_

#include <qcc/String.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/cdm/common/CdmTypes.h>
#include <alljoyn/cdm/common/CdmInterfaceTypes.h>
#include <alljoyn/cdm/common/CdmInterfaceErrors.h>

namespace ajn {
namespace services {

class CdmInterface;
class InterfaceControlleeModel;
class InterfaceControllerListener;
class CdmBusObject;

typedef CdmInterface* (*CreateIntfControlleeFptr)(BusAttachment& busAttachment, Ref<InterfaceControlleeModel> listener, CdmBusObject& cdmBusObject);
typedef Ref<CdmInterface> (*CreateIntfControllerFptr)(BusAttachment& busAttachment, Ref<InterfaceControllerListener> listener, Ref<ProxyBusObject> cdmProxyObject);

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
