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
#include <alljoyn/cdm/common/CdmAboutKeys.h>
#include <qcc/String.h>

#define QCC_MODULE "ALLJOYN_ABOUT"

namespace ajn {
    namespace services {
    const qcc::String CdmAboutKeys::COUNTRY_OF_PRODUCTION   = "CountryOfProduction";
    const qcc::String CdmAboutKeys::CORPORATE_BRAND         = "CorporateBrand";
    const qcc::String CdmAboutKeys::PRODUCT_BRAND           = "ProductBrand";
    const qcc::String CdmAboutKeys::LOCATION                = "Location";
    const qcc::String CdmAboutKeys::DEVICE_TYPE_DESCRIPTION = "DeviceTypeDescription";

    }
}
