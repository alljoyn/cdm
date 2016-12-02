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

#ifndef AUDIOVOLUMEINTFCONTROLLEE_H_
#define AUDIOVOLUMEINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/AudioVolumeInterface.h>

namespace ajn {
namespace services {

/**
 * AudioVolume Interface Controllee class
 */
class AudioVolumeIntfControllee : public AudioVolumeInterface {
  public:
    /**
     * Constructor of AudioVolumeIntfControllee
     */
    AudioVolumeIntfControllee() {}

    /**
     * Destructor of AudioVolumeIntfControllee
     */
    virtual ~AudioVolumeIntfControllee() {}

    /**
     * Get volume
     * @return Volume
     */
    virtual const uint8_t GetVolume() const = 0;

    /**
     * Set volume
     * @param[in] volume volume
     * @return ER_OK on success
     */
    virtual QStatus SetVolume(const uint8_t volume) = 0;

    /**
     * Get the maximum volume
     * @return The maximum volume
     */
    virtual const uint8_t GetMaxVolume() const = 0;

    /**
     * Set the maximum volume
     * @param[in] maxVolume the maximum volume
     * @return ER_OK on success
     */
    virtual QStatus SetMaxVolume(const uint8_t maxVolume) = 0;

    /**
     * Get mute
     * @return Mute
     */
    virtual const bool GetMute() const = 0;

    /**
     * Set mute
     * @param[in] mute mute
     * @return ER_OK on success
     */
    virtual QStatus SetMute(const bool mute) = 0;
};

} //namespace services
} //namespace ajn

#endif /* AUDIOVOLUMEINTFCONTROLLEE_H_ */