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

#ifndef SPINSPEEDLEVELINTFCONTROLLEE_H_
#define SPINSPEEDLEVELINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <vector>
#include <alljoyn/cdm/interfaces/operation/SpinSpeedLevelInterface.h>

namespace ajn {
namespace services {

/**
 * SpinSpeedLevel Interface Controllee class
 */
class SpinSpeedLevelIntfControllee : public SpinSpeedLevelInterface {
  public:
    /**
     * Constructor of SpinSpeedLevelIntfControllee
     */
    SpinSpeedLevelIntfControllee() {}

    /**
     * Destructor of SpinSpeedLevelIntfControllee
     */
    virtual ~SpinSpeedLevelIntfControllee() {}

    /**
     * Get MaxLevel
     * @return MaxLevel
     */
    virtual const uint8_t GetMaxLevel() const = 0;

    /**
     * Set MaxLevel
     * @param[in] maxLevel maxLevel
     * @return ER_OK on success
     */
    virtual QStatus SetMaxLevel(uint8_t maxLevel) = 0;

    /**
     * Get TargetLevel
     * @return TargetLevel
     */
    virtual const uint8_t GetTargetLevel () const = 0;

    /**
     * Set TargetLevel
     * @param[in] targetLevel targetLevel
     * @return ER_OK on success
     */
    virtual QStatus SetTargetLevel(uint8_t targetLevel) = 0;

    /**
     * Get SelectableLevels
     * @return The list of selectable levels
     */
    virtual const std::vector<uint8_t>& GetSelectableLevels() const = 0;

    /**
     * Set SelectableLevels
     * @param[in] selectableLevels the list of levels
     * @return ER_OK on success
     */
    virtual QStatus SetSelectableLevels(const std::vector<uint8_t>& selectableLevels) = 0;
};

} //namespace services
} //namespace ajn

#endif /* SPINSPEEDLEVELINTFCONTROLLEE_H_ */