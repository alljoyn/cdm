/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
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
         * TODO put in a table listing the properties for all of the about fields 
         *      when similar todo in <alljoyn/AboutKeys.h> is implemented
         */
        // @{
        
static const qcc::String COUNTRY_OF_PRODUCTION;
static const qcc::String CORPORATE_BRAND;
static const qcc::String PRODUCT_BRAND;
static const qcc::String LOCATION;
static const qcc::String DEVICE_TYPE_DESCRIPTION;
    };

}
}

#endif //CDMABOUTKEYS_H_