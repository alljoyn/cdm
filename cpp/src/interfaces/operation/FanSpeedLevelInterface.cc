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
#include <alljoyn/hae/interfaces/operation/FanSpeedLevelInterface.h>

namespace ajn {
namespace services {

const uint16_t FanSpeedLevelInterface::s_interfaceVersion = 1;

// Below none secure xml is only for test
const qcc::String FanSpeedLevelInterface::s_xml =
"<node xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='http://www.allseenalliance.org/schemas/introspect.xsd'>"
"    <interface name='org.alljoyn.SmartSpaces.Operation.FanSpeedLevel'>"
"        <description language='en'>This interface is for controlling fan speed level of a device.</description>"
"        <annotation name='org.alljoyn.Bus.Secure' value='true'/>"
"        <property name='Version' type='q' access='read'>"
"            <description language='en'>Interface version</description>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <property name='FanSpeedLevel' type='y' access='readwrite'>"
"            <description language='en'>Fan speed level of a device</description>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <property name='MaxFanSpeedLevel' type='y' access='read'>"
"            <description language='en'>Maximum level allowed for target fan speed level</description>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='false'/>"
"        </property>"
"        <property name='AutoMode' type='y' access='readwrite'>"
"            <description language='en'>Represent enabled/disabled state of the auto mode.</description>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"    </interface>"
"</node>"
;

const qcc::String FanSpeedLevelInterface::s_prop_Version = "Version";
const qcc::String FanSpeedLevelInterface::s_prop_FanSpeedLevel = "FanSpeedLevel";
const qcc::String FanSpeedLevelInterface::s_prop_MaxFanSpeedLevel = "MaxFanSpeedLevel";
const qcc::String FanSpeedLevelInterface::s_prop_AutoMode = "AutoMode";

} //namespace services
} //namespace ajn
