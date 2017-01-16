/******************************************************************************
 * 
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 * 
 *    SPDX-License-Identifier: Apache-2.0
 * 
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 * 
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
 * 
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 * 
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/
#ifndef CDMABOUTKEYS_H_
#define CDMABOUTKEYS_H_

#include <qcc/String.h>

namespace ajn {
namespace services {
    /**
     * CdmAboutKeys
     */
    class CdmAboutKeys {
    public:
        /**
         * @anchor CdmAboutFields
         * @name Custome Cdm AboutFields
         *
         * The additional fields in the Cdm About interface
         */
        // @{
        static const qcc::String COUNTRY_OF_PRODUCTION; ///< The country of production
        static const qcc::String CORPORATE_BRAND; ///< The brand name for the corporation
        static const qcc::String PRODUCT_BRAND; ///< The brand name for the product
        static const qcc::String LOCATION; ///< Where the device is located
        static const qcc::String DEVICE_TYPE_DESCRIPTION; ///< A device type code and bus path
        // @}
    };

}
}

#endif //CDMABOUTKEYS_H_
