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

#ifndef LANGUAGEDISPLAYINTFCONTROLLERLISTENER_H_
#define LANGUAGEDISPLAYINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/hae/interfaces/InterfaceControllerListener.h>

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
