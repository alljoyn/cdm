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

#ifndef LANGUAGEDISPLAYINTFCONTROLLEE_H_
#define LANGUAGEDISPLAYINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/userinterfacesettings/LanguageDisplayInterface.h>

namespace ajn {
namespace services {

/**
 * LanguageDisplay Interface Controllee class
 */
class LanguageDisplayIntfControllee : public LanguageDisplayInterface {
  public:
    /**
     * Constructor of LanguageDisplayIntfControllee
     */
    LanguageDisplayIntfControllee() {}

    /**
     * Destructor of LanguageDisplayIntfControllee
     */
    virtual ~LanguageDisplayIntfControllee() {}

    /**
     * Get DisplayLanguage
     * @return display language
     */

    virtual const qcc::String GetDisplayLanguage() = 0;

    /**
     * Set DisplayLanguage
     * @param[in] displayLanguage display language
     * @return ER_OK on success
     */
    virtual QStatus SetDisplayLanguage(const qcc::String& displayLanguage) = 0;

    /**
     * Get SupportedDisplayLanguages
     * @return list of supported display languages
     */
    virtual const std::vector<qcc::String>& GetSupportedDisplayLanguages() = 0;

    /**
     * Set SupportedDisplayLanguages
     * @param[in] supportedDisplayLanguages list of supported display languages
     * @return ER_OK on success
     */
    virtual QStatus SetSupportedDisplayLanguages(const std::vector<qcc::String>& supportedDisplayLanguages) = 0;
};

} //namespace services
} //namespace ajn

#endif /* LANGUAGEDISPLAYINTFCONTROLLEE_H_ */