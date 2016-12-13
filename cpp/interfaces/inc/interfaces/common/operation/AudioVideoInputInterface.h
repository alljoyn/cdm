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
        int32_t v = 0;
        msgarg.Get("i", &v);
        value = static_cast<AudioVideoInputInterface::SourceType>(v);
    }

    void set(MsgArg& msgarg, AudioVideoInputInterface::SourceType value)
    {
        int32_t v = static_cast<int32_t>(value);
        msgarg.Set("i", v);
    }

    std::string str(const MsgArg& msgarg)
    {
        std::ostringstream strm;
        int32_t value = 0;
        msgarg.Get("i", &value);
        strm << value;
        return strm.str();
    }
};

template<>
struct CdmMsgCvt<std::vector<AudioVideoInputInterface::SourceType>>
{
    void get(const MsgArg& msgarg, std::vector<AudioVideoInputInterface::SourceType>& value)
    {
        int32_t* v = 0;
        size_t l = 0;

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

    std::string str(const MsgArg& msgarg)
    {
        std::ostringstream strm;
        int32_t* v = 0;
        size_t l = 0;
        msgarg.Get("ai", &l, &v);
        for (size_t i = 0; i < l; ++i)
        {
            strm << v[i] << "\n";
        }
        return strm.str();
    }
};



template<>
struct CdmMsgCvt<AudioVideoInputInterface::SignalPresence>
{
    void get(const MsgArg& msgarg, AudioVideoInputInterface::SignalPresence& value)
    {
        int32_t v = 0;
        msgarg.Get("i", &v);
        value = static_cast<AudioVideoInputInterface::SignalPresence>(v);
    }

    void set(MsgArg& msgarg, AudioVideoInputInterface::SignalPresence value)
    {
        int32_t v = static_cast<int32_t>(value);
        msgarg.Set("i", v);
    }

    std::string str(const MsgArg& msgarg)
    {
        std::ostringstream strm;
        int32_t value = 0;
        msgarg.Get("i", &value);
        strm << value;
        return strm.str();
    }
};

template<>
struct CdmMsgCvt<std::vector<AudioVideoInputInterface::SignalPresence>>
{
    void get(const MsgArg& msgarg, std::vector<AudioVideoInputInterface::SignalPresence>& value)
    {
        int32_t* v = 0;
        size_t l = 0;

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

    std::string str(const MsgArg& msgarg)
    {
        std::ostringstream strm;
        int32_t* v = 0;
        size_t l = 0;
        msgarg.Get("ai", &l, &v);
        for (size_t i = 0; i < l; ++i)
        {
            strm << v[i] << "\n";
        }
        return strm.str();
    }
};

// Struct converters
template<>
struct CdmMsgCvt<AudioVideoInputInterface::InputSource>
{
    void get(const MsgArg& msgarg, AudioVideoInputInterface::InputSource& arg_)
    {
        uint16_t field_id{};
        int32_t field_sourceType{};
        int32_t field_signalPresence{};
        uint16_t field_portNumber{};
        const char* field_friendlyName{};
        msgarg.Get("(qqiqs)", &field_id, &field_sourceType, &field_signalPresence, &field_portNumber, &field_friendlyName);
        arg_.id = field_id;
        arg_.sourceType = static_cast<AudioVideoInputInterface::SourceType>(field_sourceType);
        arg_.signalPresence = static_cast<AudioVideoInputInterface::SignalPresence>(field_signalPresence);
        arg_.portNumber = field_portNumber;
        arg_.friendlyName = field_friendlyName;
    }

    void set(MsgArg& msgarg, const AudioVideoInputInterface::InputSource arg_)
    {
        uint16_t field_id = arg_.id;
        int32_t field_sourceType = arg_.sourceType;
        int32_t field_signalPresence = arg_.signalPresence;
        uint16_t field_portNumber = arg_.portNumber;
        const char* field_friendlyName = arg_.friendlyName.c_str();
        msgarg.Set("(qqiqs)", field_id, field_sourceType, field_signalPresence, field_portNumber, field_friendlyName);
    }

    std::string str(const MsgArg& msgarg)
    {
        AudioVideoInputInterface::InputSource arg_;
        get(msgarg, arg_);

        std::ostringstream strm;
        strm << "id=" << arg_.id;
        strm << " ";
        strm << "sourceType=" << arg_.sourceType;
        strm << " ";
        strm << "signalPresence=" << arg_.signalPresence;
        strm << " ";
        strm << "portNumber=" << arg_.portNumber;
        strm << " ";
        strm << "friendlyName=" << arg_.friendlyName;
        return strm.str();
    }
};


template<>
struct CdmMsgCvt<std::vector<AudioVideoInputInterface::InputSource>>
{
    void get(const MsgArg& msgarg, std::vector<AudioVideoInputInterface::InputSource>& arg_)
    {
        MsgArg* elems = 0;
        size_t  num = 0;

        msgarg.Get("a(qqiqs)", &num, &elems);
        arg_.resize(num);

        for (size_t i = 0; i < num; ++i)
        {
            uint16_t field_id{};
            int32_t field_sourceType{};
            int32_t field_signalPresence{};
            uint16_t field_portNumber{};
            const char* field_friendlyName{};
            elems[i].Get("(qqiqs)", &field_id, &field_sourceType, &field_signalPresence, &field_portNumber, &field_friendlyName);
            arg_[i].id = field_id;
            arg_[i].sourceType = static_cast<AudioVideoInputInterface::SourceType>(field_sourceType);
            arg_[i].signalPresence = static_cast<AudioVideoInputInterface::SignalPresence>(field_signalPresence);
            arg_[i].portNumber = field_portNumber;
            arg_[i].friendlyName = field_friendlyName;
        }
    }

    void set(MsgArg& msgarg, const std::vector<AudioVideoInputInterface::InputSource>& arg_)
    {
        size_t num = arg_.size();
        std::vector<MsgArg> elems(num);

        for (size_t i = 0; i < num; ++i)
        {
            uint16_t field_id = arg_[i].id;
            int32_t field_sourceType = arg_[i].sourceType;
            int32_t field_signalPresence = arg_[i].signalPresence;
            uint16_t field_portNumber = arg_[i].portNumber;
            const char* field_friendlyName = arg_[i].friendlyName.c_str();
            elems[i].Set("(qqiqs)", field_id, field_sourceType, field_signalPresence, field_portNumber, field_friendlyName);
        }

        msgarg.Set("a(qqiqs)", num, elems.data());
        msgarg.Stabilize();
    }

    std::string str(const MsgArg& msgarg)
    {
        std::vector<AudioVideoInputInterface::InputSource> vec;
        get(msgarg, vec);

        std::ostringstream strm;

        for (auto& v : vec)
        {
            strm << "{";
            strm << "id=" << v.id;
            strm << " ";
            strm << "sourceType=" << v.sourceType;
            strm << " ";
            strm << "signalPresence=" << v.signalPresence;
            strm << " ";
            strm << "portNumber=" << v.portNumber;
            strm << " ";
            strm << "friendlyName=" << v.friendlyName.c_str();
            strm << "}";
        }

        return strm.str();
    }
};


} //namespace services
} //namespace ajn

#endif /* AUDIOVIDEOINPUTINTERFACE_H_ */
