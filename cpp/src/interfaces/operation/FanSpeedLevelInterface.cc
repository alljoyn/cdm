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

#include <alljoyn/cdm/LogModule.h>
#include <alljoyn/cdm/interfaces/operation/FanSpeedLevelInterface.h>

namespace ajn {
namespace services {

const uint16_t FanSpeedLevelInterface::s_interfaceVersion = 1;

// Below none secure xml is only for test
const qcc::String FanSpeedLevelInterface::s_xml =
"<node xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='http://www.allseenalliance.org/schemas/introspect.xsd'>"
"    <interface name='org.alljoyn.SmartSpaces.Operation.FanSpeedLevel'>"
"        <annotation name='org.alljoyn.Bus.DocString.En' value='This interface is for controlling fan speed level of a device.'/>"
"        <annotation name='org.alljoyn.Bus.Secure' value='true'/>"
"        <property name='Version' type='q' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The interface version.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='const'/>"
"        </property>"
"        <property name='FanSpeedLevel' type='y' access='readwrite'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Fan speed level of a device. Special value: 0x00 - Fan operation is turned off and controller shall not set 0x00. Turning on/off shall be operated by a different interface (OnOff).'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <property name='MaxFanSpeedLevel' type='y' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Maximum level allowed for target fan speed level.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='false'/>"
"        </property>"
"        <annotation name='org.alljoyn.Bus.Enum.AutoMode.Value.Off' value='0x00'/>"
"        <annotation name='org.alljoyn.Bus.Enum.AutoMode.Value.On' value='0x01'/>"
"        <annotation name='org.alljoyn.Bus.Enum.AutoMode.Value.NotSupported' value='0xFF'/>"
"        <property name='AutoMode' type='y' access='readwrite'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Enabled/disabled state of the auto mode.'/>"
"            <annotation name='org.alljoyn.Bus.Type.Name' value='[AutoMode]'/>"
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
