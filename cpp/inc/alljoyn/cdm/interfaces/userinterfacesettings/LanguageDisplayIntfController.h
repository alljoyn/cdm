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
     * Get DisplayLanguage property
     * (The RFC 5646 tag of the current language being used by the device user interface)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetDisplayLanguage(void* context = NULL) = 0;

    /**
     * Set DisplayLanguage property
     * (The RFC 5646 tag of the current language being used by the device user interface)
     * @param[in] value The display language to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetDisplayLanguage(const qcc::String& value, void* context = NULL) = 0;

    /**
     * Get SupportedDisplayLanguages property
     * (The list of supported languages using RFC 5646 tags)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetSupportedDisplayLanguages(void* context = NULL) = 0;
};

typedef std::shared_ptr<LanguageDisplayIntfController> LanguageDisplayIntfControllerPtr;

} //namespace services
} //namespace ajn

#endif /* LANGUAGEDISPLAYINTFCONTROLLER_H_ */
