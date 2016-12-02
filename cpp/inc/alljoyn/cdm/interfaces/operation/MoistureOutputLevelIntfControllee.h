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

#ifndef MOISTUREOUTPUTLEVELINTFCONTROLLEE_H_
#define MOISTUREOUTPUTLEVELINTFCONTROLLEE_H_

#include <vector>
#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/MoistureOutputLevelInterface.h>

namespace ajn {
namespace services {

/**
 * MoistureOutputLevel Interface Controllee class
 */
class MoistureOutputLevelIntfControllee : public MoistureOutputLevelInterface {
  public:
    /**
     * Constructor of MoistureOutputLevelIntfControllee
     */
    MoistureOutputLevelIntfControllee() {}

    /**
     * Destructor of MoistureOutputLevelIntfControllee
     */
    virtual ~MoistureOutputLevelIntfControllee() {}

    /**
     * Get moisture output level
     * @return Moisture output level
     */
    virtual const uint8_t GetMoistureOutputLevel() const = 0;

    /**
     * Set moisture output level
     * @param[in] value moisture output level
     * @return ER_OK on success
     */
    virtual QStatus SetMoistureOutputLevel(const uint8_t value) = 0;

    /**
     * Get the maximum moisture output level
     * @return The maximum moisture output level
     */
    virtual const uint8_t GetMaxMoistureOutputLevel() const = 0;

    /**
     * Set the maximum moisture output level
     * @param[in] value the maximum moisture output level
     * @return ER_OK on success
     */
    virtual QStatus SetMaxMoistureOutputLevel(const uint8_t value) = 0;

    /**
     * Get auto mode
     * @return Auto mode
     */
    virtual const uint8_t GetAutoMode () const = 0;

    /**
     * Set auto mode
     * @param[in] autoMode auto mode
     * @return ER_OK on success
     */
    virtual QStatus SetAutoMode (const uint8_t autoMode) = 0;
};

} //namespace services
} //namespace ajn


#endif /* MOISTUREOUTPUTLEVELINTFCONTROLLEE_H_ */