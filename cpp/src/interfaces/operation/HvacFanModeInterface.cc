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
#include <alljoyn/cdm/interfaces/operation/HvacFanModeInterface.h>

namespace ajn {
namespace services {

const uint16_t HvacFanModeInterface::s_interfaceVersion = 1;

const qcc::String HvacFanModeInterface::s_xml =
"<node xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='http://www.allseenalliance.org/schemas/introspect.xsd'>"
"    <interface name='org.alljoyn.SmartSpaces.Operation.HvacFanMode'>"
"        <annotation name='org.alljoyn.Bus.DocString.En' value='This interface provides capabilities to control and monitor air conditioner and thermostat fan settings.'/>"
"        <annotation name='org.alljoyn.Bus.Secure' value='true'/>"
"        <property name='Version' type='q' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The interface version.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='const'/>"
"        </property>"
"        <annotation name='org.alljoyn.Bus.Enum.Mode.Value.Auto' value='0'/>"
"        <annotation name='org.alljoyn.Bus.Enum.Mode.Value.Circulation' value='1'/>"
"        <annotation name='org.alljoyn.Bus.Enum.Mode.Value.Continuous' value='2'/>"
"        <property name='Mode' type='q' access='readwrite'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Current mode of device.'/>"
"            <annotation name='org.alljoyn.Bus.Type.Name' value='[Mode]'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <property name='SupportedModes' type='aq' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Array of supported modes.'/>"
"            <annotation name='org.alljoyn.Bus.Type.Name' value='a[Mode]'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"    </interface>"
"</node>"
;

const qcc::String HvacFanModeInterface::s_prop_Version = "Version";
const qcc::String HvacFanModeInterface::s_prop_Mode = "Mode";
const qcc::String HvacFanModeInterface::s_prop_SupportedModes = "SupportedModes";

} //namespace services
} //namespace ajn
