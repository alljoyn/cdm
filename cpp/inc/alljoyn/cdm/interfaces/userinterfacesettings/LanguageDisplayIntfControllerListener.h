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

#ifndef LANGUAGEDISPLAYINTFCONTROLLERLISTENER_H_
#define LANGUAGEDISPLAYINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>

namespace ajn {
namespace services {

/**
 * LanguageDisplay Interface Controller Listener class
 */
class LanguageDisplayIntfControllerListener : public InterfaceControllerListener {
  public:
    virtual ~LanguageDisplayIntfControllerListener() {}

    /**
     * Callback handler for getting DisplayLanguage
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] displayLanguage display language
     * @param[in] context the context that is passed from application
     */
    virtual void GetDisplayLanguagePropertyCallback(QStatus status, const qcc::String& objectPath, const qcc::String displayLanguage, void* context) {};

    /**
     * Callback handler for setting DisplayLanguage
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void SetDisplayLanguagePropertyCallback(QStatus status, const qcc::String& objectPath, void* context) {};

    /**
     * Callback handler for getting SupportedDisplayLanguages
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] SupportedDisplayLanguages list of supported display languages
     * @param[in] context the context that is passed from application
     */
    virtual void GetSupportedDisplayLanguagesPropertyCallback(QStatus status, const qcc::String& objectPath, const std::vector<qcc::String>& supportedDisplayLanguages, void* context) {};

    /**
     * Handler for DisplayLanguage property changed
     * @param[in] objectPath the object path
     * @param[in] displayLanguage display language
     */
    virtual void DisplayLanguagePropertyChanged(const qcc::String& objectPath, const qcc::String& displayLanguage) {};

    /**
     * Handler for SupportedDisplayLanguages property changed
     * @param[in] objectPath the object path
     * @param[in] SupportedDisplayLanguages list of supported display languages
     */
    virtual void SupportedDisplayLanguagesPropertyChanged(const qcc::String& objectPath, const std::vector<qcc::String>& supportedDisplayLanguages) {};
};

} //namespace services
} //namespace ajn

#endif /* LANGUAGEDISPLAYINTFCONTROLLERLISTENER_H_ */