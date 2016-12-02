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

#ifndef AUDIOVOLUMEINTFCONTROLLEELISTENER_H_
#define AUDIOVOLUMEINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * AudioVolume Interface Controllee Listener class
 */
class AudioVolumeIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of AudioVolumeIntfControlleeListener
     */
    virtual ~AudioVolumeIntfControlleeListener() {}

    /**
     * Handler for setting Volume property
     * @param[in] volume volume
     * @return ER_OK on success
     */
    virtual QStatus OnSetVolume(const uint8_t& volume) = 0;

    /**
     * Handler for getting Volume property
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] volume volume
     * @return ER_OK on success
     */
    virtual QStatus OnGetVolume(uint8_t& volume) = 0;

    /**
     * Handler for getting MaxVolume property
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] maxVolume the maximum volume
     * @return ER_OK on success
     */
     virtual QStatus OnGetMaxVolume(uint8_t& maxVolume) = 0;

     /**
      * Handler for setting Mute property
      * @param[in] mute mute
      * @return ER_OK on success
      */
     virtual QStatus OnSetMute(const bool& mute) = 0;

     /**
      * Handler for getting Mute property
      * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
      * @param[out] mute mute
      * @return ER_OK on success
      */
     virtual QStatus OnGetMute(bool& mute) = 0;
};

} //namespace services
} //namespace ajn

#endif /* AUDIOVOLUMEINTFCONTROLLEELISTENER_H_ */