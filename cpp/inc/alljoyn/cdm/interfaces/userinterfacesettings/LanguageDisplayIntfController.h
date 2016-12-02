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

#ifndef LANGUAGEDISPLAYINTFCONTROLLER_H_
#define LANGUAGEDISPLAYINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/userinterfacesettings/LanguageDisplayInterface.h>

namespace ajn {
namespace services {

/**
 * LanguageDisplay Interface Controller class
 */
class LanguageDisplayIntfController : public LanguageDisplayInterface {
  public:
    /**
     * Constructor of LanguageDisplayIntfController
     */
    LanguageDisplayIntfController() {}

    /**
     * Destructor of LanguageDisplayIntfController
     */
    virtual ~LanguageDisplayIntfController() {}

    /**
     * Get DisplayLanguage
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetDisplayLanguage(void* context = NULL) = 0;

    /**
     * Set DisplayLanguage
     * @param[in] displayLanguage display language
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetDisplayLanguage(const qcc::String& displayLanguage, void* context = NULL) = 0;

    /**
     * Get SupportedDisplayLanguages
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetSupportedDisplayLanguages(void* context = NULL) = 0;
};

} //namespace services
} //namespace ajn

#endif /* LANGUAGEDISPLAYINTFCONTROLLER_H_ */