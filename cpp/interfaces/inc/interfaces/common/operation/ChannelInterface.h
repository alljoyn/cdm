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

#ifndef CHANNELINTERFACE_H_
#define CHANNELINTERFACE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/common/CdmInterface.h>
#include <alljoyn/cdm/util/CdmMsgCvt.h>

namespace ajn {
namespace services {

/**
 * Channel Interface class
 */
class ChannelInterface : public CdmInterface {
  public:
    static const char* const INTERFACE_NAME;
    static const CdmInterfaceType INTERFACE_TYPE;
    struct ChannelInfoRecord {
        qcc::String channelID;
        qcc::String channelNumber;
        qcc::String channelName;

        inline bool operator==(const ChannelInfoRecord& a) {
            return a.channelID==channelID && a.channelNumber==channelNumber && a.channelName==channelName;
        }
    };

    /**
     * Constructor of ChannelInterface
     */
    ChannelInterface() {}

    /**
     * Destructor of ChannelInterface
     */
    virtual ~ChannelInterface() {}

    /**
     * Get Interface Type
     * @return interface type
     */
    const CdmInterfaceType GetInterfaceType() const { return CHANNEL_INTERFACE; }

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
    static const qcc::String s_prop_ChannelId;
    static const qcc::String s_prop_TotalNumberOfChannels;
    static const qcc::String s_method_GetChannelList;
    static const qcc::String s_signal_ChannelListChanged;

  private:
    static const qcc::String s_xml;
    static const uint16_t s_interfaceVersion;
};

// Enum converters

// Struct converters
template<>
struct CdmMsgCvt<ChannelInterface::ChannelInfoRecord>
{
    void get(const MsgArg& msgarg, ChannelInterface::ChannelInfoRecord& value)
    {
        msgarg.Get("(sss)", &value.channelID, &value.channelNumber, &value.channelName);
    }

    void set(MsgArg& msgarg, ChannelInterface::ChannelInfoRecord value)
    {
        msgarg.Set("(sss)", &value.channelID, &value.channelNumber, &value.channelName);
    }
};


template<>
struct CdmMsgCvt<std::vector<ChannelInterface::ChannelInfoRecord>>
{
    void get(const MsgArg& msgarg, std::vector<ChannelInterface::ChannelInfoRecord>& value)
    {
        MsgArg* elems;
        size_t  num;

        msgarg.Get("a*", &num, &elems);
        value.resize(num);

        for (size_t i = 0; i < num; ++i)
        {
            elems[i].Get("(sss)", &value[i].channelID, &value[i].channelNumber, &value[i].channelName);
        }
    }

    void set(MsgArg& msgarg, std::vector<ChannelInterface::ChannelInfoRecord>& value)
    {
        size_t num = value.size();
        std::vector<MsgArg> elems(num);

        for (size_t i = 0; i < num; ++i)
        {
            elems[i].Set("(sss)", &value[i].channelID, &value[i].channelNumber, &value[i].channelName);
        }

        msgarg.Set("a*", num, elems.data());
    }
};


} //namespace services
} //namespace ajn

#endif /* CHANNELINTERFACE_H_ */
