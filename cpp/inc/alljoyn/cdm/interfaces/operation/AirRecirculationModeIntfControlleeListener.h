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

#ifndef AIRRECIRCULATIONMODEINTFCONTROLLEELISTENER_H_
#define AIRRECIRCULATIONMODEINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterfaceErrors.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * AirRecirculationMode Interface Controllee Listener class
 */
class AirRecirculationModeIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of AirRecirculationModeIntfControlleeListener
     */
    virtual ~AirRecirculationModeIntfControlleeListener() {}

    /**
     * Handler for setting IsRecirculating property
     * @param[in] isRecirculating if air is being recirculated or not
     * @return ER_OK on success
     */
    virtual QStatus OnSetIsRecirculating(const bool& isRecirculating) = 0;

    /**
     * Handler for getting IsRecirculating property
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] isRecirculating if air is being recirculated or not
     * @return ER_OK on success
     */
    virtual QStatus OnGetIsRecirculating(bool& isRecirculating) = 0;
};

} //namespace services
} //namespace ajn

#endif /* AIRRECIRCULATIONMODEINTFCONTROLLEELISTENER_H_ */