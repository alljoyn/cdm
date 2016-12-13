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

#ifndef LANGUAGEDISPLAYMODEL_H_
#define LANGUAGEDISPLAYMODEL_H_

#include <interfaces/controllee/userinterfacesettings/LanguageDisplayIntfControlleeModel.h>

namespace ajn {
namespace services {
namespace emulator {


class LanguageDisplayModel : public virtual LanguageDisplayIntfControlleeModel {
  public:
    LanguageDisplayModel(const std::string& busPath);

    /**
     * Get DisplayLanguage
     * @return current display language
     */
    QStatus GetDisplayLanguage(qcc::String& out) const override;

     /**
     * Set DisplayLanguage
     * @param[in] value The display language to set
     * @return ER_OK on success
     */
    QStatus SetDisplayLanguage(const qcc::String& value) override;

    /**
     * Get SupportedDisplayLanguages
     * @return current supported display languages
     */
    QStatus GetSupportedDisplayLanguages(std::vector<qcc::String>& out) const override;


  private:
    std::string m_busPath;
};

} // namespace emulator
} // namespace services
} // namespace ajn

#endif /* LANGUAGEDISPLAYMODEL_H_ */