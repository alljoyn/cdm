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