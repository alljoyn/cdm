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
#include <alljoyn/cdm/interfaces/operation/SpinSpeedLevelInterface.h>

namespace ajn {
namespace services {

const uint16_t SpinSpeedLevelInterface::s_interfaceVersion = 1;

const qcc::String SpinSpeedLevelInterface::s_xml =
"<node xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='http://www.allseenalliance.org/schemas/introspect.xsd'>"
"    <interface name='org.alljoyn.SmartSpaces.Operation.SpinSpeedLevel'>"
"        <annotation name='org.alljoyn.Bus.DocString.En' value='This interface provides a capability to set the spin speed level.'/>"
"        <annotation name='org.alljoyn.Bus.Secure' value='true'/>"
"        <property name='Version' type='q' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The interface version.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='const'/>"
"        </property>"
"        <property name='MaxLevel' type='y' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Maximum value allowed for the spin speed level setting.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='const'/>"
"        </property>"
"        <property name='TargetLevel' type='y' access='readwrite'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Target set-point value of spin speed level.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <property name='SelectableLevels' type='ay' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='List of the values of spin speed level which can be selected.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"    </interface>"
"</node>"
;

const qcc::String SpinSpeedLevelInterface::s_prop_Version = "Version";
const qcc::String SpinSpeedLevelInterface::s_prop_MaxLevel = "MaxLevel";
const qcc::String SpinSpeedLevelInterface::s_prop_TargetLevel = "TargetLevel";
const qcc::String SpinSpeedLevelInterface::s_prop_SelectableLevels = "SelectableLevels";

} //namespace services
} //namespace ajn
