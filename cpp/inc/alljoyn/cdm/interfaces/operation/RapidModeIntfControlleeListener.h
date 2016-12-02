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

#ifndef RAPIDMODEINTFCONTROLLEELISTENER_H_
#define RAPIDMODEINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterfaceErrors.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * RapidMode Interface Controllee Listener class
 */
class RapidModeIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of RapidModeIntfControlleeListener
     */
    virtual ~RapidModeIntfControlleeListener() {}

    /**
     * Handler for setting RapidMode property
     * @param[in] rapidMode rapid mode
     * @return ER_OK on success
     */
    virtual QStatus OnSetRapidMode(const bool& rapidMode) = 0;

    /**
     * Handler for getting RapidMode property
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] rapidMode if device is in rapid mode
     * @return ER_OK on success
     */
    virtual QStatus OnGetRapidMode(bool& rapidMode) = 0;

};

} //namespace services
} //namespace ajn

#endif /* RAPIDMODEINTFCONTROLLEELISTENER_H_ */