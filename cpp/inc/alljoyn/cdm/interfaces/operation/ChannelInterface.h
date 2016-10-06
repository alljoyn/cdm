/******************************************************************************
 * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#ifndef CHANNELINTERFACE_H_
#define CHANNELINTERFACE_H_

#include <vector>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterface.h>

namespace ajn {
namespace services {

/**
 * Channel Interface class
 */
class ChannelInterface : public CdmInterface {
  public:
    /**
     * ChannelInfoRecord struct
     */
    typedef struct {
        qcc::String channelId;
        qcc::String channelNumber;
        qcc::String channelName;
    } ChannelInfoRecord;
    typedef std::vector<ChannelInfoRecord> ChannelInfoRecords;

    /**
     * Constructor of Channel
     */
    ChannelInterface() {}

    /**
     * Destructor of Channel
     */
    virtual ~ChannelInterface() {}

    /**
     * Get Interface Type
     * @return Interface type
     */
    const CdmInterfaceType GetInterfaceType() const { return CHANNEL_INTERFACE; }

    /**
     * Get Introspection Xml
     * @return Introspection xml
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

} //namespace services
} //namespace ajn

#endif /* CHANNELINTERFACE_H_ */