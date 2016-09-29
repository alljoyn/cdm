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

#ifndef AUDIOVIDEOINPUTINTERFACE_H_
#define AUDIOVIDEOINPUTINTERFACE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterface.h>

namespace ajn {
namespace services {

/**
 * AudioVideoInput Interface class
 */
class AudioVideoInputInterface : public CdmInterface {
  public:
    enum SourceType {
        SOURCE_TYPE_UNKNOWN = 0,
        SOURCE_TYPE_TUNER = 1,
        SOURCE_TYPE_COMPONENT = 2,
        SOURCE_TYPE_COMPOSITE = 3,
        SOURCE_TYPE_S_VIDEO = 4,
        SOURCE_TYPE_RGB = 5,
        SOURCE_TYPE_SDI = 6,
        SOURCE_TYPE_DVI = 7,
        SOURCE_TYPE_HDMI = 8,
        SOURCE_TYPE_DISPLAY_PORT = 9,
        SOURCE_TYPE_SCART = 10,
        SOURCE_TYPE_EXTERNAL_STORAGE = 11,
        SOURCE_TYPE_NETWORK = 12,
        SOURCE_TYPE_ANALOG = 13,
        SOURCE_TYPE_PHONO = 14,
        SOURCE_TYPE_SPDIF_COAXIAL = 15,
        SOURCE_TYPE_SPDIF_OPTICAL = 16,
    };
    enum SignalPresence {
        SIGNAL_PRESENCE_UNKNOWN = 0,
        SIGNAL_PRESENCE_SIGNAL_PRESENT = 1,
        SIGNAL_PRESENCE_SIGNAL_ABSENT = 2,
    };

    struct InputSource {
        uint16_t id;
        SourceType sourceType;
        SignalPresence signalPresence;
        uint16_t portNumber;
        qcc::String friendlyName;

        inline bool operator==(const InputSource& a) {
            return a.id==id && a.sourceType==sourceType && a.signalPresence==signalPresence && a.portNumber==portNumber && a.friendlyName==friendlyName;
        }
    };
    typedef std::map<uint16_t, InputSource> InputSources;

    /**
     * Constructor of AudioVideoInputInterface
     */
    AudioVideoInputInterface() {}

    /**
     * Destructor of AudioVideoInputInterface
     */
    virtual ~AudioVideoInputInterface() {}

    /**
     * Get Interface Type
     * @return interface type
     */
    const CdmInterfaceType GetInterfaceType() const { return AUDIO_VIDEO_INPUT_INTERFACE; }

    /**
     * Get Introspection XML
     * @return Introspection XML
     */
    virtual const qcc::String& GetIntrospectionXml() { return s_xml; }

    /**
     * Get Interface version
     * @return Interface version
     */
    virtual const uint16_t GetInterfaceVersion() const { return s_interfaceVersion; }

    enum {
        MIN_AUDIO_VIDEO_INPUT_SOURCE_TYPE = SOURCE_TYPE_UNKNOWN,
        MAX_AUDIO_VIDEO_INPUT_SOURCE_TYPE = SOURCE_TYPE_SPDIF_OPTICAL
    };

  protected:
    static const qcc::String s_prop_Version;
    static const qcc::String s_prop_InputSourceId;
    static const qcc::String s_prop_SupportedInputSources;

  private:
    static const qcc::String s_xml;
    static const uint16_t s_interfaceVersion;
};

} //namespace services
} //namespace ajn

#endif /* AUDIOVIDEOINPUTINTERFACE_H_ */
