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
#include <alljoyn/hae/interfaces/operation/SpinSpeedLevelInterface.h>

namespace ajn {
namespace services {

const uint16_t SpinSpeedLevelInterface::s_interfaceVersion = 1;

// Below none secure xml is only for test
const qcc::String SpinSpeedLevelInterface::s_xml =
"<node xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='http://www.allseenalliance.org/schemas/introspect.xsd'>"
"    <interface name='org.alljoyn.SmartSpaces.Operation.SpinSpeedLevel'>"
"        <description language='en'>This interface provides a capability to set the spin speed level</description>"
"        <annotation name='org.alljoyn.Bus.Secure' value='true'/>"
"        <property name='Version' type='q' access='read'>"
"            <description language='en'>The interface version</description>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <property name='MaxLevel' type='y' access='read'>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='false'/>"
"            <description language='en'>Maximum value allowed for the spin speed level setting</description>"
"        </property>"
"        <property name='TargetLevel' type='y' access='readwrite'>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"            <description language='en'>Target set-point value of spin speed level</description>"
"        </property>"
"        <property name='SelectableLevels' type='ay' access='read'>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"            <description language='en'>List of the values of spin speed level which can be selected</description>"
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
