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

#ifndef AUDIOVIDEOINPUTINTFCONTROLLER_H_
#define AUDIOVIDEOINPUTINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/hae/interfaces/operation/AudioVideoInputInterface.h>

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
