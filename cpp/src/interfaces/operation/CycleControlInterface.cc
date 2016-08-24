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
#include <alljoyn/cdm/interfaces/operation/CycleControlInterface.h>

namespace ajn {
namespace services {

const uint16_t CycleControlInterface::s_interfaceVersion = 1;

// Below none secure xml is only for test
const qcc::String CycleControlInterface::s_xml =
"<node xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='http://www.allseenalliance.org/schemas/introspect.xsd'>"
"    <interface name='org.alljoyn.SmartSpaces.Operation.CycleControl'>"
"        <annotation name='org.alljoyn.Bus.DocString.En' value='This interface provides capability to monitor the operational state of an appliance and to control it using relate commands.'/>"
"        <annotation name='org.alljoyn.Bus.Secure' value='true'/>"
"        <property name='Version' type='q' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The interface version.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='const'/>"
"        </property>"
"        <annotation name='org.alljoyn.Bus.Enum.OperationalState.Value.Idle' value='0'/>"
"        <annotation name='org.alljoyn.Bus.Enum.OperationalState.Value.Working' value='1'/>"
"        <annotation name='org.alljoyn.Bus.Enum.OperationalState.Value.ReadyToStart' value='2'/>"
"        <annotation name='org.alljoyn.Bus.Enum.OperationalState.Value.DelayedStart' value='3'/>"
"        <annotation name='org.alljoyn.Bus.Enum.OperationalState.Value.Paused' value='4'/>"
"        <annotation name='org.alljoyn.Bus.Enum.OperationalState.Value.EndOfCycle' value='5'/>"
"        <property name='OperationalState' type='y' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Current operational state of the appliance.'/>"
"            <annotation name='org.alljoyn.Bus.Type.Name' value='[OperationalState]'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <property name='SupportedOperationalStates' type='ay' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Operational states which are supported by the appliance.'/>"
"            <annotation name='org.alljoyn.Bus.Type.Name' value='a[OperationalState]'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='false'/>"
"        </property>"
"        <annotation name='org.alljoyn.Bus.Enum.OperationalCommands.Value.Start' value='0'/>"
"        <annotation name='org.alljoyn.Bus.Enum.OperationalCommands.Value.Stop' value='1'/>"
"        <annotation name='org.alljoyn.Bus.Enum.OperationalCommands.Value.Pause' value='2'/>"
"        <annotation name='org.alljoyn.Bus.Enum.OperationalCommands.Value.Resume' value='3'/>"
"        <property name='SupportedOperationalCommands' type='ay' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Operational commands which are supported by the appliance.'/>"
"            <annotation name='org.alljoyn.Bus.Type.Name' value='a[OperationalCommands]'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='false'/>"
"        </property>"
"        <method name='ExecuteOperationalCommand'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Execute an operational command.'/>"
"            <arg name='command' type='y' direction='in'>"
"                <annotation name='org.alljoyn.Bus.DocString.En' value='Operational command to be executed.'/>"
"                <annotation name='org.alljoyn.Bus.Type.Name' value='[OperationalCommands]'/>"
"            </arg>"
"        </method>"
"        <signal name='EndOfCycle' sessionless='true'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='This signal is emitted if the cycle is completed.'/>"
"        </signal>"
"    </interface>"
"</node>"
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
