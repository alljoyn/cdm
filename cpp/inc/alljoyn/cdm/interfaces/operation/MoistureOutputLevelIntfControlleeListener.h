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

#ifndef MOISTUREOUTPUTLEVELINTFCONTROLLEELISTENER_H_
#define MOISTUREOUTPUTLEVELINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * MoistureOutputLevel interface controllee listener class
 */
class MoistureOutputLevelIntfControlleeListener : public InterfaceControlleeListener {
  public:

    /**
     * Destructor of MoistureOutputLevelIntfControlleeListener
     */
    virtual ~MoistureOutputLevelIntfControlleeListener() {}

    /**
     * Handler for setting moisture output level
     * @param[in] value moisture output level
     * @return ER_OK on success
     */
    virtual QStatus OnSetMoistureOutputLevel(const uint8_t& value) = 0;

    /**
     * Handler for getting moisture output level
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value moisture output level
     * @return ER_OK on success
     */
    virtual QStatus OnGetMoistureOutputLevel(uint8_t& value) = 0;

    /**
     * Handler for getting the maximum moisture output level
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value the maximum moisture output level
     * @return ER_OK on success
     */
    virtual QStatus OnGetMaxMoistureOutputLevel(uint8_t& value) = 0;

    /**
     * Handler for setting auto mode
     * @param[in] autoMode auto mode
     * @return ER_OK on success
     */
    virtual QStatus OnSetAutoMode(const uint8_t& autoMode) = 0;

    /**
     * Handler for getting auto mode
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value auto mode
     * @return ER_OK on success
     */
    virtual QStatus OnGetAutoMode(uint8_t& value) = 0;
};

} //namespace services
} //namespace ajn




#endif /* MOISTUREOUTPUTLEVELINTFCONTROLLEELISTENER_H_ */