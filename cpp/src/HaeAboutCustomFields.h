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
#ifndef HAEABOUTCUSTOMFIELDS_H_
#define HAEABOUTCUSTOMFIELDS_H_

#include <qcc/String.h>

namespace ajn {
namespace services {
/**
 * custom field name
 */
static const qcc::String COUNTRY_OF_PRODUCTION   = "CountryOfProduction";
static const qcc::String CORPORATE_BRAND         = "CorporateBrand";
static const qcc::String PRODUCT_BRAND           = "ProductBrand";
static const qcc::String LOCATION                = "Location";
static const qcc::String DEVICE_TYPE_DESCRIPTION = "DeviceTypeDescription";

}
}

#endif //HAEABOUTCUSTOMFIELDS_H_
