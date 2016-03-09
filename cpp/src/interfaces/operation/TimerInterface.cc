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
#include <alljoyn/hae/interfaces/operation/TimerInterface.h>

namespace ajn {
namespace services {

const uint16_t TimerInterface::s_interfaceVersion = 1;

// Below none secure xml is only for test
const qcc::String TimerInterface::s_xml =
"<node xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='http://www.allseenalliance.org/schemas/introspect.xsd'>"
"    <interface name='org.alljoyn.SmartSpaces.Operation.Timer'>"
"        <description language='en'>This interface provides capability to monitor and control the times when the appliance executes its operations</description>"
"        <annotation name='org.alljoyn.Bus.Secure' value='true'/>"
"        <property name='Version' type='q' access='read'/>"
"        <property name='ReferenceTimer' type='i' access='read'>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='false'/>"
"            <description language='en'>Time counter to be used as reference</description>"
"        </property>"
"        <property name='TargetTimeToStart' type='i' access='read'>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"            <description language='en'>Time when the appliance is expected to start its operation</description>"
"        </property>"
"        <property name='TargetTimeToStop' type='i' access='read'>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"            <description language='en'>Time when the appliance is expected to stop its operation</description>"
"        </property>"
"        <property name='EstimatedTimeToEnd' type='i' access='read'>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='false'/>"
"            <description language='en'>Time to the ends of appliance operation</description>"
"        </property>"
"        <property name='RunningTime' type='i' access='read'>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='false'/>"
"            <description language='en'>Time of current operation</description>"
"        </property>"
"        <property name='TargetDuration' type='i' access='read'>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"            <description language='en'>Time representing the target duration of the operation as per user selection</description>"
"        </property>"
"        <method name='SetTargetTimeToStart'>"
"            <arg name='targetTimeToStart' type='i' direction='in'>"
"                <description language='en'>Time to be set</description>"
"            </arg>"
"        </method>"
"        <method name='SetTargetTimeToStop'>"
"             <arg name='targetTimeToStop' type='i' direction='in'>"
"                <description language='en'>Time to be set</description>"
"            </arg>"
"        </method>"
"    </interface>"
"</node>"
;

const qcc::String TimerInterface::s_prop_Version = "Version";
const qcc::String TimerInterface::s_prop_ReferenceTimer = "ReferenceTimer";
const qcc::String TimerInterface::s_prop_TargetTimeToStart = "TargetTimeToStart";
const qcc::String TimerInterface::s_prop_TargetTimeToStop = "TargetTimeToStop";
const qcc::String TimerInterface::s_prop_EstimatedTimeToEnd = "EstimatedTimeToEnd";
const qcc::String TimerInterface::s_prop_RunningTime = "RunningTime";
const qcc::String TimerInterface::s_prop_TargetDuration = "TargetDuration";

const qcc::String TimerInterface::s_method_SetTargetTimeToStart = "SetTargetTimeToStart";
const qcc::String TimerInterface::s_method_SetTargetTimeToStop = "SetTargetTimeToStop";

} //namespace services
} //namespace ajn
