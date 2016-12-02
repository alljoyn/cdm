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

#ifndef AUDIOVOLUMEINTFCONTROLLERLISTENER_H_
#define AUDIOVOLUMEINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>

namespace ajn {
namespace services {

/**
 * AudioVolume Interface Controller Listener class
 */
class AudioVolumeIntfControllerListener : public InterfaceControllerListener {
  public:

    /**
     * Destructor of AudioVideoInputIntfControllerListener
     */
    virtual ~AudioVolumeIntfControllerListener() {}

    /**
     * Callback handler for setting Volume property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetVolume(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for getting Volume property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] volume volume
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetVolume(QStatus status, const qcc::String& objectPath, const uint8_t volume, void* context) {}

    /**
     * Callback handler for getting MaxVolume property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] maxVolume the maximum volume
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetMaxVolume(QStatus status, const qcc::String& objectPath, const uint8_t maxVolume, void* context) {}

    /**
     * Callback handler for setting Mute property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetMute(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for getting Mute property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] mute mute
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetMute(QStatus status, const qcc::String& objectPath, const bool mute, void* context) {}

    /**
     * Handler for Volume property changed
     * @param[in] objectPath the object path
     * @param[in] volume volume
     */
    virtual void OnVolumeChanged(const qcc::String& objectPath, const uint8_t volume) {}

    /**
     * Handler for MaxVolume property changed
     * @param[in] objectPath the object path
     * @param[in] maxVolume the maximum volume
     */
    virtual void OnMaxVolumeChanged(const qcc::String& objectPath, const uint8_t maxVolume) {}

    /**
     * Handler for Mute property changed
     * @param[in] objectPath the object path
     * @param[in] mute mute
     */
    virtual void OnMuteChanged(const qcc::String& objectPath, const bool mute) {}
};

} //namespace services
} //namespace ajn

#endif /* AUDIOVOLUMEINTFCONTROLLERLISTENER_H_ */