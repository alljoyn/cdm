/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
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

#include <alljoyn/hae/LogModule.h>
#include <alljoyn/hae/interfaces/operation/ChannelInterface.h>

namespace ajn {
namespace services {

const uint16_t ChannelInterface::s_interfaceVersion = 1;

// Below none secure xml is only for test
const qcc::String ChannelInterface::s_xml =
        "<node>"
        "    <interface name='org.alljoyn.SmartSpaces.Operation.Channel'>"
        "        <description language='en'>This interface provides capabilities to set and get channel of device that has a channel list.</description>"
        "        <annotation name='org.alljoyn.Bus.Secure' value='true'/>"
        "        <property name='Version' type='q' access='read'>"
        "            <description language='en'>Interface version</description>"
        "            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
        "        </property>"
        "        <property name='ChannelId' type='s' access='readwrite'>"
        "            <description language='en'>Current channel id</description>"
        "            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
        "        </property>"
        "        <property name='TotalNumberOfChannels' type='q' access='read'>"
        "            <description language='en'>Maximum number of scanned channels</description>"
        "            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
        "        </property>"
        "        <method name='GetChannelList'>"
        "            <description language='en'>Invoke this method to retrieve the list of channels</description>"
        "            <arg name='startingRecord' type='q' direction='in'/>"
        "            <arg name='numRecords' type='q' direction='in'/>"
        "            <arg name='listOfChannelInfoRecords' type='a(sss)' direction='out'/>"
        "        </method>"
        "        <signal name='ChannelListChanged' sessionless='false'>"
        "            <description language='en'>Emitted this signal if the channel list is changed</description>"
        "        </signal>"
        "    </interface>"
        "</node>";

const qcc::String ChannelInterface::s_prop_Version = "Version";
const qcc::String ChannelInterface::s_prop_ChannelId = "ChannelId";
const qcc::String ChannelInterface::s_prop_TotalNumberOfChannels = "TotalNumberOfChannels";
const qcc::String ChannelInterface::s_method_GetChannelList = "GetChannelList";
const qcc::String ChannelInterface::s_signal_ChannelListChanged = "ChannelListChanged";


} //namespace services
} //namespace ajn
