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

#ifndef AUDIOVIDEOINPUTLISTENER_H_
#define AUDIOVIDEOINPUTLISTENER_H_

#include <alljoyn/hae/interfaces/operation/AudioVideoInputIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class AudioVideoInputListener : public AudioVideoInputIntfControlleeListener
{
  public:
    virtual QStatus OnSetInputSourceId(const uint16_t& inputSourceId);
    virtual QStatus OnGetInputSourceId(uint16_t& inputSourceId);
    virtual QStatus OnGetSupportedInputSources(AudioVideoInputInterface::InputSources& supportedInputSources);
};

#endif /* AUDIOVIDEOINPUTLISTENER_H_ */