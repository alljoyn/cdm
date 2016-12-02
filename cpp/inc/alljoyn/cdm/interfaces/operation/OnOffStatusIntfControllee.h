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

#ifndef ONOFFSTATUSINTFCONTROLLEE_H_
#define ONOFFSTATUSINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/OnOffStatusInterface.h>

namespace ajn {
namespace services {

/**
 * OnOffStatus Interface Controllee class
 */
class OnOffStatusIntfControllee : public OnOffStatusInterface {
  public:
    /**
     * Constructor of OnOffStatusIntfControllee
     */
    OnOffStatusIntfControllee() {}

    /**
     * Destructor of OnOffStatusIntfControllee
     */
    virtual ~OnOffStatusIntfControllee() {}

    /**
     * Get IsOn
     * @return IsOn
     */
    virtual const bool GetIsOn() const = 0;

    /**
     * Set IsOn
     * @param[in] value
     * @return ER_OK on success
     */
    virtual QStatus SetIsOn(const bool value) = 0;

};

} //namespace services
} //namespace ajn

#endif /* ONOFFSTATUSINTFCONTROLLEE_H_ */