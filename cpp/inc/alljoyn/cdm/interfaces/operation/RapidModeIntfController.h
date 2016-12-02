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

#ifndef RAPIDMODEINTFCONTROLLER_H_
#define RAPIDMODEINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/RapidModeInterface.h>

namespace ajn {
namespace services {

/**
 * RapidMode Interface Controller class
 */
class RapidModeIntfController : public RapidModeInterface {
  public:
    /**
     * Constructor of RapidModeIntfController
     */
    RapidModeIntfController() {}

    /**
     * Destructor of RapidModeIntfController
     */
    virtual ~RapidModeIntfController() {}

    /**
     * Get rapid mode
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetRapidMode(void* context = NULL) = 0;

    /**
     * Set rapid mode
     * @param[in] rapidMide rapid mode
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetRapidMode(const bool rapidMode, void* context = NULL) = 0;
};

} //namespace services
} //namespace ajn

#endif /* RAPIDMODEINTFCONTROLLER_H_ */