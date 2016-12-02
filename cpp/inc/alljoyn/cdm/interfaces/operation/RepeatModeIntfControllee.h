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

#ifndef REPEATMODEINTFCONTROLLEE_H_
#define REPEATMODEINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/RepeatModeInterface.h>

namespace ajn {
namespace services {

/**
 * RepeatMode Interface Controllee class
 */
class RepeatModeIntfControllee : public RepeatModeInterface {
  public:
    /**
     * Constructor of RepeatModeIntfControllee
     */
    RepeatModeIntfControllee() {}

    /**
     * Destructor of RepeatModeIntfControllee
     */
    virtual ~RepeatModeIntfControllee() {}

    /**
     * Get RepeatMode
     * @return RepeatMode
     */
    virtual const bool GetRepeatMode() const = 0;

    /**
     * Set RepeatMode
     * @param[in] value
     * @return ER_OK on success
     */
    virtual QStatus SetRepeatMode(const bool value) = 0;

};

} //namespace services
} //namespace ajn

#endif /* REPEATMODEINTFCONTROLLEE_H_ */