/******************************************************************************
 *  * 
 *    Copyright (c) 2016 Open Connectivity Foundation and AllJoyn Open
 *    Source Project Contributors and others.
 *    
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0

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