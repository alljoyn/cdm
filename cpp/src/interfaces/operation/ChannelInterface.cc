/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
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

#include <alljoyn/cdm/LogModule.h>
#include <alljoyn/cdm/interfaces/operation/ChannelInterface.h>

namespace ajn {
namespace services {

const uint16_t ChannelInterface::s_interfaceVersion = 1;

// Below none secure xml is only for test
const qcc::String ChannelInterface::s_xml =
"<node xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='http://www.allseenalliance.org/schemas/introspect.xsd'>"
"    <interface name='org.alljoyn.SmartSpaces.Operation.Channel'>"
"        <annotation name='org.alljoyn.Bus.DocString.En' value='This interface provides capabilities to set and get channel of device that has a channel list.'/>"
"        <annotation name='org.alljoyn.Bus.Secure' value='true'/>"
"        <annotation name='org.alljoyn.Bus.Struct.ChannelInfoRecord.Field.channelID.Type' value='s'/>"
"        <annotation name='org.alljoyn.Bus.Struct.ChannelInfoRecord.Field.channelNumber.Type' value='s'/>"
"        <annotation name='org.alljoyn.Bus.Struct.ChannelInfoRecord.Field.channelName.Type' value='s'/>"
"        <property name='Version' type='q' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The interface version.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='const'/>"
"        </property>"
"        <property name='ChannelId' type='s' access='readwrite'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Current channel id.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <property name='TotalNumberOfChannels' type='q' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Total number of scanned channels.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <method name='GetChannelList'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Retrieve the list of channels.'/>"
"            <arg name='startingRecord' type='q' direction='in'>"
"                <annotation name='org.alljoyn.Bus.DocString.En' value='List built from this record number.'/>"
"             </arg>"
"            <arg name='numRecords' type='q' direction='in'>"
"                <annotation name='org.alljoyn.Bus.DocString.En' value='List generated at most this many records.'/>"
"            </arg>"
"            <arg name='listOfChannelInfoRecords' type='a(sss)' direction='out'>"
"                <annotation name='org.alljoyn.Bus.DocString.En' value='List of channel information records.'/>"
"                <annotation name='org.alljoyn.Bus.Type.Name' value='a[ChannelInfoRecord]'/>"
"            </arg>"
"        </method>"
"        <signal name='ChannelListChanged' sessionless='false'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='This signal is emitted when the channel list is changed.'/>"
"        </signal>"
"    </interface>"
"</node>"
;

const qcc::String ChannelInterface::s_prop_Version = "Version";
const qcc::String ChannelInterface::s_prop_ChannelId = "ChannelId";
const qcc::String ChannelInterface::s_prop_TotalNumberOfChannels = "TotalNumberOfChannels";
const qcc::String ChannelInterface::s_method_GetChannelList = "GetChannelList";
const qcc::String ChannelInterface::s_signal_ChannelListChanged = "ChannelListChanged";


} //namespace services
} //namespace ajn