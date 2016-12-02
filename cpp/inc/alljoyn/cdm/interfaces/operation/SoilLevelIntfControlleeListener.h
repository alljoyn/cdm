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

#ifndef SOILLEVELINTFCONTROLLEELISTENER_H_
#define SOILLEVELINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <vector>
#include <alljoyn/cdm/interfaces/CdmInterfaceErrors.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * SoilLevel Interface Controllee Listener class
 */
class SoilLevelIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of SoilLevelIntfControlleeListener
     */
    virtual ~SoilLevelIntfControlleeListener() {}

    /**
     * Handler for getting MaxLevel
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] maxLevel maxLevel
     * @return ER_OK on success
     */
    virtual QStatus OnGetMaxLevel(uint8_t& maxLevel) = 0;

    /**
     * Handler for setting MaxLevel
     * @param[in] maxLevel maxLevel
     * @return ER_OK on success
     */
    virtual QStatus OnSetMaxLevel(const uint8_t& maxLevel) = 0;

    /**
     * Handler for getting TargetLevel
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] targetLevel targetLevel
     * @return ER_OK on success
     */
    virtual QStatus OnGetTargetLevel(uint8_t& targetLevel) = 0;

    /**
     * Handler for setting TargetLevel
     * @param[in] targetLevel targetLevel
     * @return ER_OK on success
     */
    virtual QStatus OnSetTargetLevel(const uint8_t& targetLevel) = 0;

    /**
     * Handler for getting SelectableLevels
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] selectableLevels the list of selectable levels
     * @return ER_OK on success
     */
    virtual QStatus OnGetSelectableLevels(std::vector<uint8_t>& selectableLevels) = 0;

    /**
     * Handler for setting SelectableLevels
     * @param[in] selectableLevels the list of selectable levels
     * @return ER_OK on success
     */
    virtual QStatus OnSetSelectableLevels(const std::vector<uint8_t>& selectableLevels) = 0;
};

} //namespace services
} //namespace ajn

#endif /* SOILLEVELINTFCONTROLLEELISTENER_H_ */