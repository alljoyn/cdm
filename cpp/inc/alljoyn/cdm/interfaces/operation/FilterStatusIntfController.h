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

#ifndef FILTERSTATUSINTFCONTROLLER_H_
#define FILTERSTATUSINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/FilterStatusInterface.h>

namespace ajn {
namespace services {

/**
 * FilterStatus Interface Controller class
 */
class FilterStatusIntfController : public FilterStatusInterface {
  public:
    /**
     * Constructor of FilterStatusIntfController
     */
    FilterStatusIntfController() {}

    /**
     * Destructor of FilterStatusIntfController
     */
    virtual ~FilterStatusIntfController() {}

    /**
     * Get expected life in days
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetExpectedLifeInDays(void* context = NULL) = 0;

    /**
     * Get is cleanable
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetIsCleanable(void* context = NULL) = 0;

    /**
     * Get order percentage
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetOrderPercentage(void* context = NULL) = 0;

    /**
     * Get manufacturer
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetManufacturer(void* context = NULL) = 0;

    /**
     * Get part number
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetPartNumber(void* context = NULL) = 0;

    /**
     * Get url
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetUrl(void* context = NULL) = 0;

    /**
     * Get life remaining
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetLifeRemaining(void* context = NULL) = 0;
};

} //namespace services
} //namespace ajn

#endif /* FILTERSTATUSINTFCONTROLLER_H_ */