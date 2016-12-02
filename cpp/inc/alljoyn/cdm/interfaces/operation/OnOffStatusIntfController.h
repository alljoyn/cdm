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

#ifndef ONOFFSTATUSINTFCONTROLLER_H_
#define ONOFFSTATUSINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/OnOffStatusInterface.h>

namespace ajn {
namespace services {

/**
 * OnOffStatus Interface Controller class
 */
class OnOffStatusIntfController : public OnOffStatusInterface {
  public:
    /**
     * Constructor of OnOffStatusIntfController
     */
    OnOffStatusIntfController() {}

    /**
     * Destructor of OnOffStatusIntfController
     */
    virtual ~OnOffStatusIntfController() {}

    /**
     * Get IsOn
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetIsOn(void* context = NULL) = 0;

};

} //namespace services
} //namespace ajn

#endif /* ONOFFSTATUSINTFCONTROLLER_H_ */