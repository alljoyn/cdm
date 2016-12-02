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

#ifndef LANGUAGEDISPLAYINTFCONTROLLERIMPL_H_
#define LANGUAGEDISPLAYINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/userinterfacesettings/LanguageDisplayIntfController.h>

namespace ajn {
namespace services {

class LanguageDisplayIntfControllerListener;
class CdmProxyBusObject;

/**
 * LanguageDisplay Interface Controller implementation class
 */
class LanguageDisplayIntfControllerImpl : public InterfaceController, public LanguageDisplayIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of LanguageDisplayIntfControllerImpl
     */
    LanguageDisplayIntfControllerImpl(BusAttachment& busAttachment, LanguageDisplayIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of LanguageDisplayIntfControllerImpl
     */
    virtual ~LanguageDisplayIntfControllerImpl();

    /**
     * Initialize interface
     * @return status
     */
    virtual QStatus Init();

    /**
     * Get bus attachment
     * @return bus attachment
     */
    virtual BusAttachment& GetBusAttachment() const { return m_busAttachment; }

    /**
     * Get DisplayLanguage
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetDisplayLanguage(void* context = NULL);

    /**
     * Set DisplayLanguage
     * @param[in] displayLanguage display language
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetDisplayLanguage(const qcc::String& displayLanguage, void* context = NULL);

    /**
     * Get SupportedDisplayLanguages
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetSupportedDisplayLanguages(void* context = NULL);

  private:
    LanguageDisplayIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);

    void GetDisplayLanguagePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetDisplayLanguagePropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetSupportedDisplayLanguagesPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    LanguageDisplayIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* LANGUAGEDISPLAYINTFCONTROLLERIMPL_H_ */