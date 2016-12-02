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

#ifndef AUDIOVIDEOINPUTINTFCONTROLLER_H_
#define AUDIOVIDEOINPUTINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/AudioVideoInputInterface.h>

namespace ajn {
namespace services {

/**
 * AudioVideoInput Interface Controller class
 */
class AudioVideoInputIntfController : public AudioVideoInputInterface {
  public:
    /**
     * Constructor of AudioVideoInputIntfController
     */
    AudioVideoInputIntfController() {}

    /**
     * Destructor of AudioVideoInputIntfController
     */
    virtual ~AudioVideoInputIntfController() {}

    /**
     * Set input source id
     * @param[in] inputSourceId input source id
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetInputSourceId(const uint16_t inputSourceId, void* context = NULL) = 0;

    /**
     * Get input source id
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetInputSourceId(void* context = NULL) = 0;

    /**
     * Get supported input sources
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetSupportedInputSources(void* context = NULL) = 0;
};

} //namespace services
} //namespace ajn

#endif /* AUDIOVIDEOINPUTINTFCONTROLLER_H_ */