/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

// This file is automatically generated. Do not edit it.

#ifndef AUDIOVIDEOINPUTINTFCONTROLLERLISTENER_H_
#define AUDIOVIDEOINPUTINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/controller/InterfaceControllerListener.h>
#include <interfaces/common/operation/AudioVideoInputInterface.h>

namespace ajn {
namespace services {

/**
 * AudioVideoInput Interface Controller Listener class
 */
class AudioVideoInputIntfControllerListener : public InterfaceControllerListener {
  public:
    using SourceType = AudioVideoInputInterface::SourceType;
    using SignalPresence = AudioVideoInputInterface::SignalPresence;
    using InputSource = AudioVideoInputInterface::InputSource;

    /**
     * Destructor of AudioVideoInputIntfControllerListener
     */
    virtual ~AudioVideoInputIntfControllerListener() {}

    /**
     * Callback handler for GetInputSourceId completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of InputSourceId
     *                  (Activated input source id.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetInputSourceId(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context) {}

    /**
     * Handler for InputSourceId property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of InputSourceId
     *                  (Activated input source id.)
     */
    virtual void OnInputSourceIdChanged(const qcc::String& objectPath, const uint16_t value) {}

    /**
     * Callback handler for SetInputSourceId completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetInputSourceId(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for GetSupportedInputSources completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of SupportedInputSources
     *                  (Array of supported input sources.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetSupportedInputSources(QStatus status, const qcc::String& objectPath, const std::vector<AudioVideoInputInterface::InputSource>& value, void* context) {}

    /**
     * Handler for SupportedInputSources property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of SupportedInputSources
     *                  (Array of supported input sources.)
     */
    virtual void OnSupportedInputSourcesChanged(const qcc::String& objectPath, const std::vector<AudioVideoInputInterface::InputSource>& value) {}
};

} //namespace services
} //namespace ajn

#endif /* AUDIOVIDEOINPUTINTFCONTROLLERLISTENER_H_ */
