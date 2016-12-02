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

#ifndef RAPIDMODEINTFCONTROLLEE_H_
#define RAPIDMODEINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/RapidModeInterface.h>

namespace ajn {
namespace services {

/**
 * RapidMode Interface Controllee class
 */
class RapidModeIntfControllee : public RapidModeInterface {
  public:
    /**
     * Constructor of RapidModeIntfControllee
     */
    RapidModeIntfControllee() {}

    /**
     * Destructor of RapidModeIntfControllee
     */
    virtual ~RapidModeIntfControllee() {}

    /**
     * Get RapidMode
     * @return rapid mode
     */
    virtual const bool GetRapidMode() const = 0;

    /**
     * Set RapidMode
     * @param[in] rapidMode rapidMode
     * @return ER_OK on success
     */
    virtual QStatus SetRapidMode(const bool rapidMode) = 0;

};

} //namespace services
} //namespace ajn

#endif /* RAPIDMODEINTFCONTROLLEE_H_ */