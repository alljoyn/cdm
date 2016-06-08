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
#include <alljoyn/hae/interfaces/operation/ClimateControlModeInterface.h>

namespace ajn {
namespace services {

const uint16_t ClimateControlModeInterface::s_interfaceVersion = 1;

// Below none secure xml is only for test
const qcc::String ClimateControlModeInterface::s_xml =
"<node xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='http://www.allseenalliance.org/schemas/introspect.xsd'>"
"    <interface name='org.alljoyn.SmartSpaces.Operation.ClimateControlMode'>"
"        <annotation name='org.alljoyn.Bus.DocString.En' value='This interface provides capabilities to control and monitor air conditioner and thermostat climate settings..'/>"
"        <annotation name='org.alljoyn.Bus.Secure' value='true'/>"
"        <property name='Version' type='q' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The interface version.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='const'/>"
"        </property>"
"        <annotation name='org.alljoyn.Bus.Enum.Mode.Value.Off' value='0'/>"
"        <annotation name='org.alljoyn.Bus.Enum.Mode.Value.Heat' value='1'/>"
"        <annotation name='org.alljoyn.Bus.Enum.Mode.Value.Cool' value='2'/>"
"        <annotation name='org.alljoyn.Bus.Enum.Mode.Value.Auto' value='3'/>"
"        <annotation name='org.alljoyn.Bus.Enum.Mode.Value.AuxiliaryHeat' value='4'/>"
"        <annotation name='org.alljoyn.Bus.Enum.Mode.Value.Dry' value='5'/>"
"        <annotation name='org.alljoyn.Bus.Enum.Mode.Value.ContinuousDry' value='6'/>"
"        <property name='Mode' type='q' access='readwrite'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Current mode of device.'/>"
"            <annotation name='org.alljoyn.Bus.Type.Name' value='[Mode]'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <property name='SupportedModes' type='aq' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Array of supported modes.'/>"
"            <annotation name='org.alljoyn.Bus.Type.Name' value='[Mode]'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <annotation name='org.alljoyn.Bus.Enum.OperationalState.Value.Idle' value='0'/>"
"        <annotation name='org.alljoyn.Bus.Enum.OperationalState.Value.Heating' value='1'/>"
"        <annotation name='org.alljoyn.Bus.Enum.OperationalState.Value.Cooling' value='2'/>"
"        <annotation name='org.alljoyn.Bus.Enum.OperationalState.Value.PendingHeat' value='3'/>"
"        <annotation name='org.alljoyn.Bus.Enum.OperationalState.Value.PendingCool' value='4'/>"
"        <annotation name='org.alljoyn.Bus.Enum.OperationalState.Value.AuxilliaryHeat' value='5'/>"
"        <property name='OperationalState' type='q' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Current status of device.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"    </interface>"
"</node>"
;

const qcc::String ClimateControlModeInterface::s_prop_Version = "Version";
const qcc::String ClimateControlModeInterface::s_prop_Mode = "Mode";
const qcc::String ClimateControlModeInterface::s_prop_SupportedModes = "SupportedModes";
const qcc::String ClimateControlModeInterface::s_prop_OperationalState = "OperationalState";

} //namespace services
} //namespace ajn
