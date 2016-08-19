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
#include <alljoyn/cdm/interfaces/operation/TimerInterface.h>

namespace ajn {
namespace services {

const uint16_t TimerInterface::s_interfaceVersion = 1;

// Below none secure xml is only for test
const qcc::String TimerInterface::s_xml =
"<node xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='http://www.allseenalliance.org/schemas/introspect.xsd'>"
"    <interface name='org.alljoyn.SmartSpaces.Operation.Timer'>"
"        <annotation name='org.alljoyn.Bus.DocString.En' value='This interface provides capability to monitor and control the times when the appliance executes its operations.'/>"
"        <annotation name='org.alljoyn.Bus.Secure' value='true'/>"
"        <property name='Version' type='q' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The interface version.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='const'/>"
"        </property>"
"        <property name='ReferenceTimer' type='i' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Time counter to be used as reference.'/>"
"            <annotation name='org.alljoyn.Bus.Type.Units' value='seconds'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='false'/>"
"        </property>"
"        <property name='TargetTimeToStart' type='i' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Time when the appliance is expected to start its operation.'/>"
"            <annotation name='org.alljoyn.Bus.Type.Units' value='seconds'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <property name='TargetTimeToStop' type='i' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Time when the appliance is expected to stop its operation.'/>"
"            <annotation name='org.alljoyn.Bus.Type.Units' value='seconds'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <property name='EstimatedTimeToEnd' type='i' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Time to the end of appliance operation.'/>"
"            <annotation name='org.alljoyn.Bus.Type.Units' value='seconds'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='false'/>"
"        </property>"
"        <property name='RunningTime' type='i' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Time of current operation.'/>"
"            <annotation name='org.alljoyn.Bus.Type.Units' value='seconds'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='false'/>"
"        </property>"
"        <property name='TargetDuration' type='i' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Time representing the target duration of the operation as per user selection.'/>"
"            <annotation name='org.alljoyn.Bus.Type.Units' value='seconds'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <method name='SetTargetTimeToStart'>"
"            <arg name='targetTimeToStart' type='i' direction='in'>"
"                <annotation name='org.alljoyn.Bus.DocString.En' value='Time to be set.'/>"
"                <annotation name='org.alljoyn.Bus.Type.Units' value='seconds'/>"
"            </arg>"
"        </method>"
"        <method name='SetTargetTimeToStop'>"
"             <arg name='targetTimeToStop' type='i' direction='in'>"
"                <annotation name='org.alljoyn.Bus.DocString.En' value='Time to be set.'/>"
"                <annotation name='org.alljoyn.Bus.Type.Units' value='seconds'/>"
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
