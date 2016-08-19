
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
#include <alljoyn/cdm/interfaces/environment/TargetTemperatureInterface.h>

namespace ajn {
namespace services {

const uint16_t TargetTemperatureInterface::s_interfaceVersion = 1;

const qcc::String TargetTemperatureInterface::s_xml =
"<node xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xmlns='http://www.allseenalliance.org/schemas/introspect' xsi:schemaLocation='http://www.allseenalliance.org/schemas/introspect.xsd'>"
"    <interface name='org.alljoyn.SmartSpaces.Environment.TargetTemperature'>"
"        <annotation name='org.alljoyn.Bus.DocString.En' value='This interface provides a capability to set target temperature.'/>"
"        <annotation name='org.alljoyn.Bus.Secure' value='true'/>"
"        <property name='Version' type='q' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The interface version.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='const'/>"
"        </property>"
"        <property name='TargetValue' type='d' access='readwrite'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Target temperature expressed in Celsius.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"            <annotation name='org.alljoyn.Bus.Type.Units' value='degrees Celsius'/>"
"        </property>"
"        <property name='MinValue' type='d' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Minimum value of target temperature.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"            <annotation name='org.alljoyn.Bus.Type.Units' value='degrees Celsius'/>"
"        </property>"
"        <property name='MaxValue' type='d' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Maximum value of target temperature.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"            <annotation name='org.alljoyn.Bus.Type.Units' value='degrees Celsius'/>"
"        </property>"
"        <property name='StepValue' type='d' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Step value allowed for the TargetTemperature setting.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"            <annotation name='org.alljoyn.Bus.Type.Units' value='degrees Celsius'/>"
"        </property>"
"    </interface>"
"</node>";

const qcc::String TargetTemperatureInterface::s_prop_Version = "Version";
const qcc::String TargetTemperatureInterface::s_prop_TargetValue = "TargetValue";
const qcc::String TargetTemperatureInterface::s_prop_MinValue = "MinValue";
const qcc::String TargetTemperatureInterface::s_prop_MaxValue = "MaxValue";
const qcc::String TargetTemperatureInterface::s_prop_StepValue = "StepValue";

} //namespace services
} //namespace ajn
