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
#include <alljoyn/hae/interfaces/operation/CycleControlInterface.h>

namespace ajn {
namespace services {

const uint16_t CycleControlInterface::s_interfaceVersion = 1;

// Below none secure xml is only for test
const qcc::String CycleControlInterface::s_xml =
"<node xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='http://www.allseenalliance.org/schemas/introspect.xsd'>"
"    <interface name='org.alljoyn.SmartSpaces.Operation.CycleControl'>"
"        <description language='en'>This interface provides capability to monitor the operational state of an appliance and to control it using relate commands</description>"
"        <annotation name='org.alljoyn.Bus.Secure' value='true'/>"
"        <property name='Version' type='q' access='read'>"
"            <description language='en'>Interface version</description>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <property name='OperationalState' type='y' access='read'>"
"            <description language='en'>Current operational state of the appliance</description>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <property name='SupportedOperationalStates' type='ay' access='read'>"
"            <description language='en'>Operational states which are supported by the appliance</description>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='false'/>"
"        </property>"
"        <property name='SupportedOperationalCommands' type='ay' access='read'>"
"            <description language='en'>Operational commands which are supported by the appliance</description>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='false'/>"
"        </property>"
"        <method name='ExecuteOperationalCommand'>"
"            <description language='en'>Execute an operational command</description>"
"            <arg name='command' type='y' direction='in'>"
"                <description language='en'>Operational command to be executed</description>"
"            </arg>"
"        </method>"
"        <signal name='EndOfCycle' sessionless='true'>"
"            <description language='en'>This signal is emitted if the cycle is completed</description>"
"        </signal>"
"    </interface>"
"</node>"
""
;

const qcc::String CycleControlInterface::s_prop_Version = "Version";
const qcc::String CycleControlInterface::s_prop_OperationalState = "OperationalState";
const qcc::String CycleControlInterface::s_prop_SupportedOperationalCommands = "SupportedOperationalCommands";
const qcc::String CycleControlInterface::s_prop_SupportedOperationalStates = "SupportedOperationalStates";
const qcc::String CycleControlInterface::s_method_ExecuteCommand = "ExecuteOperationalCommand";
const qcc::String CycleControlInterface::s_signal_EndOfCycle = "EndOfCycle";
const qcc::String CycleControlInterface::OPERATIONAL_STATE_STRINGS[6] = {
        "Idle",
        "Working",
        "Ready to start",
        "Delayed start",
        "Paused",
        "End of cycle"
    };
const qcc::String CycleControlInterface::OPERATIONAL_COMMAND_STRINGS[4] = {
        "Start",
        "Stop",
        "Pause",
        "Resume"
    };

} //namespace services
} //namespace ajn
