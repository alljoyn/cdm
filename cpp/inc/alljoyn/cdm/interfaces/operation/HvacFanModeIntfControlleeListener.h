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

#ifndef HVACFANMODEINTFCONTROLLEELISTENER_H_
#define HVACFANMODEINTFCONTROLLEELISTENER_H_

#include <vector>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * HvacFanMode interface controllee listener class
 */
class HvacFanModeIntfControlleeListener : public InterfaceControlleeListener {
  public:
    typedef std::vector<uint16_t> SupportedModes;

    /**
     * Destructor of HvacFanModeIntfControlleeListener
     */
    virtual ~HvacFanModeIntfControlleeListener() {}

    /**
     * Handler for setting mode
     * @param[in] mode mode
     * @return ER_OK on success
     */
    virtual QStatus OnSetMode(const uint16_t& mode) = 0;

    /**
     * Handler for getting mode
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] mode mode
     * @return ER_OK on success
     */
    virtual QStatus OnGetMode(uint16_t& mode) = 0;

    /**
     * Handler for getting supported modes
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] modes supported modes
     * @return ER_OK on success
     */
    virtual QStatus OnGetSupportedModes(SupportedModes& modes) = 0;
};

} //namespace services
} //namespace ajn

#endif /* HVACFANMODEINTFCONTROLLEELISTENER_H_ */