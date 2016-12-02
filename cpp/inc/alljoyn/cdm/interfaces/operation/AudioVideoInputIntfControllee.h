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

#ifndef AUDIOVIDEOINPUTINTFCONTROLLEE_H_
#define AUDIOVIDEOINPUTINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/AudioVideoInputInterface.h>

namespace ajn {
namespace services {

/**
 * AudioVolumeInput Interface Controllee class
 */
class AudioVideoInputIntfControllee : public AudioVideoInputInterface {
  public:
    /**
     * Constructor of AudioVideoInputIntfControllee
     */
    AudioVideoInputIntfControllee() {}

    /**
     * Destructor of AudioVideoInputIntfControllee
     */
    virtual ~AudioVideoInputIntfControllee() {}

    /**
     * Get input source id
     * @return Input source id
     */
    virtual const uint16_t GetInputSourceId() const = 0;

    /**
     * Set input source id
     * @param[in] inputSourceId input source id
     * @return ER_OK on success
     */
    virtual QStatus SetInputSourceId(uint16_t inputSourceId) = 0;

    /**
     * Get supported input sources
     * @return Supported input sources
     */
    virtual const InputSources& GetSupportedInputSources() const = 0;

    /**
     * Set supported input sources
     * @param[in] supportedInputSources supported input sources
     * @return ER_OK on success
     */
    virtual QStatus SetSupportedInputSources(const InputSources& supportedInputSources) = 0;
};

} //namespace services
} //namespace ajn

#endif /* AUDIOVIDEOINPUTINTFCONTROLLEE_H_ */