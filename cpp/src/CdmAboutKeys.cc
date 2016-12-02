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
#include <CdmAboutKeys.h>
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