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

#ifndef AUDIOVIDEOINPUTINTFCONTROLLERLISTENER_H_
#define AUDIOVIDEOINPUTINTFCONTROLLERLISTENER_H_

#include <map>
#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>
#include "AudioVideoInputInterface.h"

namespace ajn {
namespace services {

/**
 * AudioVideoInput Interface Controller Listener class
 */
class AudioVideoInputIntfControllerListener : public InterfaceControllerListener {
  public:
    /**
     * Destructor of AudioVideoInputIntfControllerListener
     */
    virtual ~AudioVideoInputIntfControllerListener() {}

    /**
     * Callback handler for setting InputSourceId property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetInputSourceId(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for getting InputSourceId property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] inputSourceId input source id
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetInputSourceId(QStatus status, const qcc::String& objectPath, const uint16_t inputSourceId, void* context) {}

    /**
     * Callback handler for getting SupportedInputSources property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] supportedInputSources supported input sources
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetSupportedInputSources(QStatus status, const qcc::String& objectPath, const AudioVideoInputInterface::InputSources& supportedInputSources, void* context) {}

    /**
     * Handler for InputSourceId property changed
     * @param[in] objectPath the object path
     * @param[in] inputSourceId input source id
     */
    virtual void OnInputSourceIdChanged(const qcc::String& objectPath, const uint16_t inputSourceId) {}

    /**
     * Handler for SupportedInputSources property changed
     * @param[in] objectPath the object path
     * @param[in] supportedInputSources supported input sources
     */
    virtual void OnSupportedInputSourcesChanged(const qcc::String& objectPath, const AudioVideoInputInterface::InputSources& supportedInputSources) {}
};

} //namespace services
} //namespace ajn

#endif /* AUDIOVIDEOINPUTINTFCONTROLLERLISTENER_H_ */