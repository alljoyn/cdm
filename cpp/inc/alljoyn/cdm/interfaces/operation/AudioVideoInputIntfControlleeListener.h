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

#ifndef AUDIOVIDEOINPUTINTFCONTROLLEELISTENER_H_
#define AUDIOVIDEOINPUTINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include "AudioVideoInputInterface.h"

namespace ajn {
namespace services {

/**
 * AudioVideoInput Interface Controllee Listener class
 */
class AudioVideoInputIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of AudioVideoInputIntfControlleeListener
     */
    virtual ~AudioVideoInputIntfControlleeListener() {}

    /**
     * Handler for setting InputSourceId property
     * @param[in] inputSourceId input source id
     * @return ER_OK on success
     */
    virtual QStatus OnSetInputSourceId(const uint16_t& inputSourceId) = 0;

    /**
     * Handler for getting InputSourceId property
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] inputSourceId input source id
     * @return ER_OK on success
     */
    virtual QStatus OnGetInputSourceId(uint16_t& inputSourceId) = 0;

    /**
     * Handler for getting SupportedInputSources property
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] supportedInputSources supported input sources
     * @return ER_OK on success
     */
    virtual QStatus OnGetSupportedInputSources(AudioVideoInputInterface::InputSources& supportedInputSources) = 0;
};

} //namespace services
} //namespace ajn

#endif /* AUDIOVIDEOINPUTINTFCONTROLLEELISTENER_H_ */