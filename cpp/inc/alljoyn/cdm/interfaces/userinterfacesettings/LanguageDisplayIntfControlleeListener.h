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

#ifndef LANGUAGEDISPLAYINTFCONTROLLEELISTENER_H_
#define LANGUAGEDISPLAYINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterfaceErrors.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * LanguageDisplay Interface Controllee Listener class
 */
class LanguageDisplayIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of LanguageDisplayIntfControlleeListener
     */
    virtual ~LanguageDisplayIntfControlleeListener() {}

    /**
     * Handler for setting DisplayLanguage property
     * @param[in] displayLanguage display language
     * @return ER_OK on success
     */
    virtual QStatus OnSetDisplayLanguage(const qcc::String& displayLanguage) = 0;

    /**
     * Handler for getting DisplayLanguage property
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] displayLanguage display language
     * @return ER_OK on success
     */
    virtual QStatus OnGetDisplayLanguage(qcc::String& displayLanguage) = 0;

    /**
     * Handler for getting SupportedDisplayLanguages
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] supportedDisplayLanguages the list of supported display languages
     * @return ER_OK on success
     */
    virtual QStatus OnGetSupportedDisplayLanguages(std::vector<qcc::String>& supportedDisplayLanguages) = 0;
};

} //namespace services
} //namespace ajn

#endif /* LANGUAGEDISPLAYINTFCONTROLLEELISTENER_H_ */