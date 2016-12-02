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

#ifndef AUDIOVOLUMEINTFCONTROLLER_H_
#define AUDIOVOLUMEINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/AudioVolumeInterface.h>

namespace ajn {
namespace services {

/**
 * AudioVolume Interface Controller class
 */
class AudioVolumeIntfController : public AudioVolumeInterface {
  public:
    /**
     * Constructor of AudioVolumeIntfController
     */
    AudioVolumeIntfController() {}

    /**
     * Destructor of AudioVolumeIntfController
     */
    virtual ~AudioVolumeIntfController() {}

    /**
     * Set volume
     * @param[in] volume volume
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetVolume(const uint8_t volume, void* context = NULL) = 0;

    /**
     * Set mute
     * @param[in] mute mute
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetMute(const bool mute, void* context = NULL) = 0;

    /**
     * Get volume
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetVolume(void* context = NULL) = 0;

    /**
     * Get the maximum volume
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetMaxVolume(void* context = NULL) = 0;

    /**
     * Get mute
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetMute(void* context = NULL) = 0;
};

} //namespace services
} //namespace ajn

#endif /* AUDIOVOLUMEINTFCONTROLLER_H_ */