/******************************************************************************
 *  * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

// This file is automatically generated. Do not edit it.

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
    void get(const MsgArg& msgarg, ChannelInterface::ChannelInfoRecord& arg_)
    {
        const char* field_channelID{};
        const char* field_channelNumber{};
        const char* field_channelName{};
        msgarg.Get("(sss)", &field_channelID, &field_channelNumber, &field_channelName);
        arg_.channelID = field_channelID;
        arg_.channelNumber = field_channelNumber;
        arg_.channelName = field_channelName;
    }

    void set(MsgArg& msgarg, const ChannelInterface::ChannelInfoRecord arg_)
    {
        const char* field_channelID = arg_.channelID.c_str();
        const char* field_channelNumber = arg_.channelNumber.c_str();
        const char* field_channelName = arg_.channelName.c_str();
        msgarg.Set("(sss)", field_channelID, field_channelNumber, field_channelName);
    }

    std::string str(const MsgArg& msgarg)
    {
        ChannelInterface::ChannelInfoRecord arg_;
        get(msgarg, arg_);

        std::ostringstream strm;
        strm << "channelID=" << arg_.channelID;
        strm << " ";
        strm << "channelNumber=" << arg_.channelNumber;
        strm << " ";
        strm << "channelName=" << arg_.channelName;
        return strm.str();
    }
};


template<>
struct CdmMsgCvt<std::vector<ChannelInterface::ChannelInfoRecord>>
{
    void get(const MsgArg& msgarg, std::vector<ChannelInterface::ChannelInfoRecord>& arg_)
    {
        MsgArg* elems = 0;
        size_t  num = 0;

        msgarg.Get("a(sss)", &num, &elems);
        arg_.resize(num);

        for (size_t i = 0; i < num; ++i)
        {
            const char* field_channelID{};
            const char* field_channelNumber{};
            const char* field_channelName{};
            elems[i].Get("(sss)", &field_channelID, &field_channelNumber, &field_channelName);
            arg_[i].channelID = field_channelID;
            arg_[i].channelNumber = field_channelNumber;
            arg_[i].channelName = field_channelName;
        }
    }

    void set(MsgArg& msgarg, const std::vector<ChannelInterface::ChannelInfoRecord>& arg_)
    {
        size_t num = arg_.size();
        std::vector<MsgArg> elems(num);

        for (size_t i = 0; i < num; ++i)
        {
            const char* field_channelID = arg_[i].channelID.c_str();
            const char* field_channelNumber = arg_[i].channelNumber.c_str();
            const char* field_channelName = arg_[i].channelName.c_str();
            elems[i].Set("(sss)", field_channelID, field_channelNumber, field_channelName);
        }

        msgarg.Set("a(sss)", num, elems.data());
        msgarg.Stabilize();
    }

    std::string str(const MsgArg& msgarg)
    {
        std::vector<ChannelInterface::ChannelInfoRecord> vec;
        get(msgarg, vec);

        std::ostringstream strm;

        for (auto& v : vec)
        {
            strm << "{";
            strm << "channelID=" << v.channelID.c_str();
            strm << " ";
            strm << "channelNumber=" << v.channelNumber.c_str();
            strm << " ";
            strm << "channelName=" << v.channelName.c_str();
            strm << "}";
        }

        return strm.str();
    }
};


} //namespace services
} //namespace ajn

#endif /* CHANNELINTERFACE_H_ */