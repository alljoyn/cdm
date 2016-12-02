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
#include <alljoyn/cdm/common/CdmInterface.h>
#include <alljoyn/cdm/util/CdmMsgCvt.h>

namespace ajn {
namespace services {

/**
 * AudioVideoInput Interface class
 */
class AudioVideoInputInterface : public CdmInterface {
  public:
    static const char* const INTERFACE_NAME;
    static const CdmInterfaceType INTERFACE_TYPE;
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
        AudioVideoInputInterface::SourceType sourceType;
        AudioVideoInputInterface::SignalPresence signalPresence;
        uint16_t portNumber;
        qcc::String friendlyName;

        inline bool operator==(const InputSource& a) {
            return a.id==id && a.sourceType==sourceType && a.signalPresence==signalPresence && a.portNumber==portNumber && a.friendlyName==friendlyName;
        }
    };

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

  protected:
    static const qcc::String s_prop_Version;
    static const qcc::String s_prop_InputSourceId;
    static const qcc::String s_prop_SupportedInputSources;

  private:
    static const qcc::String s_xml;
    static const uint16_t s_interfaceVersion;
};

// Enum converters



template<>
struct CdmMsgCvt<AudioVideoInputInterface::SourceType>
{
    void get(const MsgArg& msgarg, AudioVideoInputInterface::SourceType& value)
    {
        int32_t v;
        msgarg.Get("i", &v);
        value = static_cast<AudioVideoInputInterface::SourceType>(v);
    }

    void set(MsgArg& msgarg, AudioVideoInputInterface::SourceType value)
    {
        int32_t v = static_cast<int32_t>(value);
        msgarg.Set("i", v);
    }
};

template<>
struct CdmMsgCvt<std::vector<AudioVideoInputInterface::SourceType>>
{
    void get(const MsgArg& msgarg, std::vector<AudioVideoInputInterface::SourceType>& value)
    {
        int32_t* v;
        size_t l;

        msgarg.Get("ai", &l, &v);
        value.resize(l);

        for (size_t i = 0; i < l; ++i)
        {
            value[i] = static_cast<AudioVideoInputInterface::SourceType>(v[i]);
        }
    }

    void set(MsgArg& msgarg, const std::vector<AudioVideoInputInterface::SourceType>& value)
    {
        size_t l = value.size();
        std::vector<int32_t> ints(l);

        for (size_t i = 0; i < l; ++i)
        {
            ints[i] = static_cast<int32_t>(value[i]);
        }

        msgarg.Set("ai", ints.size(), ints.data());
        msgarg.Stabilize();
    }
};



template<>
struct CdmMsgCvt<AudioVideoInputInterface::SignalPresence>
{
    void get(const MsgArg& msgarg, AudioVideoInputInterface::SignalPresence& value)
    {
        int32_t v;
        msgarg.Get("i", &v);
        value = static_cast<AudioVideoInputInterface::SignalPresence>(v);
    }

    void set(MsgArg& msgarg, AudioVideoInputInterface::SignalPresence value)
    {
        int32_t v = static_cast<int32_t>(value);
        msgarg.Set("i", v);
    }
};

template<>
struct CdmMsgCvt<std::vector<AudioVideoInputInterface::SignalPresence>>
{
    void get(const MsgArg& msgarg, std::vector<AudioVideoInputInterface::SignalPresence>& value)
    {
        int32_t* v;
        size_t l;

        msgarg.Get("ai", &l, &v);
        value.resize(l);

        for (size_t i = 0; i < l; ++i)
        {
            value[i] = static_cast<AudioVideoInputInterface::SignalPresence>(v[i]);
        }
    }

    void set(MsgArg& msgarg, const std::vector<AudioVideoInputInterface::SignalPresence>& value)
    {
        size_t l = value.size();
        std::vector<int32_t> ints(l);

        for (size_t i = 0; i < l; ++i)
        {
            ints[i] = static_cast<int32_t>(value[i]);
        }

        msgarg.Set("ai", ints.size(), ints.data());
        msgarg.Stabilize();
    }
};

// Struct converters
template<>
struct CdmMsgCvt<AudioVideoInputInterface::InputSource>
{
    void get(const MsgArg& msgarg, AudioVideoInputInterface::InputSource& value)
    {
        msgarg.Get("(qqiqs)", &value.id, &value.sourceType, &value.signalPresence, &value.portNumber, &value.friendlyName);
    }

    void set(MsgArg& msgarg, AudioVideoInputInterface::InputSource value)
    {
        msgarg.Set("(qqiqs)", &value.id, &value.sourceType, &value.signalPresence, &value.portNumber, &value.friendlyName);
    }
};


template<>
struct CdmMsgCvt<std::vector<AudioVideoInputInterface::InputSource>>
{
    void get(const MsgArg& msgarg, std::vector<AudioVideoInputInterface::InputSource>& value)
    {
        MsgArg* elems;
        size_t  num;

        msgarg.Get("a*", &num, &elems);
        value.resize(num);

        for (size_t i = 0; i < num; ++i)
        {
            elems[i].Get("(qqiqs)", &value[i].id, &value[i].sourceType, &value[i].signalPresence, &value[i].portNumber, &value[i].friendlyName);
        }
    }

    void set(MsgArg& msgarg, std::vector<AudioVideoInputInterface::InputSource>& value)
    {
        size_t num = value.size();
        std::vector<MsgArg> elems(num);

        for (size_t i = 0; i < num; ++i)
        {
            elems[i].Set("(qqiqs)", &value[i].id, &value[i].sourceType, &value[i].signalPresence, &value[i].portNumber, &value[i].friendlyName);
        }

        msgarg.Set("a*", num, elems.data());
    }
};


} //namespace services
} //namespace ajn

#endif /* AUDIOVIDEOINPUTINTERFACE_H_ */
