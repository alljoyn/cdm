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

#ifndef AUDIOVIDEOINPUTINTFCONTROLLEELISTENER_H_
#define AUDIOVIDEOINPUTINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/hae/interfaces/InterfaceControlleeListener.h>
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
     * Handler for setting input source id
     * @param[in] inputSourceId input source id
     * @return ER_OK on success
     */
    virtual QStatus OnSetInputSourceId(const uint16_t& inputSourceId) = 0;

    /**
     * Handler for getting input source id
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] inputSourceId input source id
     * @return ER_OK on success
     */
    virtual QStatus OnGetInputSourceId(uint16_t& inputSourceId) = 0;

    /**
     * Handler for getting supported input sources
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] supportedInputSources supported input sources
     * @return ER_OK on success
     */
    virtual QStatus OnGetSupportedInputSources(AudioVideoInputInterface::InputSources& supportedInputSources) = 0;
};

} //namespace services
} //namespace ajn

#endif /* AUDIOVIDEOINPUTINTFCONTROLLEELISTENER_H_ */
