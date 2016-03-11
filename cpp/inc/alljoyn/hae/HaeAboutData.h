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


#ifndef HAEABOUTDATA_H_
#define HAEABOUTDATA_H_

#include <alljoyn/AboutData.h>
#include <alljoyn/hae/HaeAboutKeys.h>
#include <qcc/String.h>

namespace ajn {
namespace services {

class DeviceTypeDescription;

/**
 * Hae BusObject class.
 */
class HaeAboutData : public AboutData , public HaeAboutKeys {
  public:
    /**
     * Constructor of HaeAboutData
     */
    HaeAboutData();

    /**
     * Constructor
     *
     * @param[in] defaultLanguage the default language for the AboutData fields
     */
    HaeAboutData(const char* defaultLanguage);

    /**
     * Constructor
     *
     * Fill in the fields of the HaeAboutData class using a MsgArg.  The provided
     * MsgArg must contain a dictionary with signature a{sv} with AboutData fields.
     *
     * If the passed in MsgArg is an ill formed AboutData MsgArg this constructor
     * will fail silently. If the MsgArg does not come from About Announce signal
     * it is best to create an empty AboutData class and use the CreatFromMsgArg
     * member function to fill in the AboutData class.
     *
     * @param[in] arg MsgArg with signature a{sv}containing HaeAboutData fields.
     * @param[in] language the language of the arg MsgArg. Use NULL for default language
     */
    HaeAboutData(const MsgArg arg, const char* language = NULL);

    /**
     * Destructor of HaeAboutData
     */
    ~HaeAboutData();

    /**
     * Set country of production
     * @param[in] country the country
     * @param[in] language the IETF language tag specified by RFC 5646
     *            if language is NULL the Description will be set for the default language.
     * @return ER_OK on success
     */
    QStatus SetCountryOfProduction(const char* country, const char* language = NULL);

    /**
     * Get country of production
     * @param[out] country the country
     * @param[in] language the IETF language tag specified by RFC 5646
     *            if language is NULL the Description for the default language will be returned.
     * @return ER_OK on success
     */
    QStatus GetCountryOfProduction(char** country, const char* language = NULL);

    /**
     * Set corporate brand
     * @param[in] brand corporate brand
     * @param[in] language the IETF language tag specified by RFC 5646
     *            if language is NULL the Description will be set for the default language.
     * @return ER_OK on success
     */
    QStatus SetCorporateBrand(const char* brand, const char* language = NULL);

    /**
     * Get corporate brand
     * @param[out] brand corporate brand
     * @param[in] language the IETF language tag specified by RFC 5646
     *            if language is NULL the Description for the default language will be returned.
     * @return ER_OK on success
     */
    QStatus GetCorporateBrand(char** brand, const char* language = NULL);

    /**
     * Set product brand
     * @param[in] brand product brand
     * @param[in] language the IETF language tag specified by RFC 5646
     *            if language is NULL the Description will be set for the default language.
     * @return ER_OK on success
     */
    QStatus SetProductBrand(const char* brand, const char* language = NULL);

    /**
     * Get product brand
     * @param[out] brand product brand
     * @param[in] language the IETF language tag specified by RFC 5646
     *            if language is NULL the Description for the default language will be returned.
     * @return ER_OK on success
     */
    QStatus GetProductBrand(char** brand, const char* language = NULL);

    /**
     * Set location
     * @param[in] location the location
     * @param[in] language the IETF language tag specified by RFC 5646
     *            if language is NULL the Description will be set for the default language.
     * @return ER_OK on success
     */
    QStatus SetLocation(const char* location, const char* language = NULL);

    /**
     * Get location
     * @param[out] location the location
     * @param[in] language the IETF language tag specified by RFC 5646
     *            if language is NULL the Description for the default language will be returned.
     * @return ER_OK on success
     */
    QStatus GetLocation(char** location, const char* language = NULL);

    /**
     * Set device type description
     * @param[in] deviceTypes device type description
     * @return ER_OK on success
     */
    QStatus SetDeviceTypeDescription(const DeviceTypeDescription *deviceTypes);

    /**
     * Get device type description
     * @param[out] deviceTypeDescription device type description
     * @return ER_OK on success
     */
    QStatus GetDeviceTypeDescription(DeviceTypeDescription **deviceTypeDescription);

  private:
    /**
     * Initialize the details of custom field
     */
    void InitializeCustomFieldDetails();
};

}
}

#endif // HAEABOUTDATA_H_
