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

#include <alljoyn/cdm/common/LogModule.h>
#include <interfaces/common/operation/ColorTemperatureInterface.h>

namespace ajn {
namespace services {

const char* const ColorTemperatureInterface::INTERFACE_NAME = "org.alljoyn.SmartSpaces.Operation.ColorTemperature";
const CdmInterfaceType ColorTemperatureInterface::INTERFACE_TYPE = COLOR_TEMPERATURE_INTERFACE;


const uint16_t ColorTemperatureInterface::s_interfaceVersion = 1;

const qcc::String ColorTemperatureInterface::s_xml =
"<node xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='http://www.allseenalliance.org/schemas/introspect.xsd'>"
"    <interface name='org.alljoyn.SmartSpaces.Operation.ColorTemperature'>"
"        <annotation name='org.alljoyn.Bus.DocString.En' value='This interface provides capabilities to control and monitor the color temperature.'/>"
"        <annotation name='org.alljoyn.Bus.Secure' value='true'/>"
"        <property name='Version' type='q' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The interface version.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='const'/>"
"        </property>"
"        <property name='Temperature' type='d' access='readwrite'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Color temperature of the device.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"            <annotation name='org.alljoyn.Bus.Type.Min' value='0.0'/>"
"            <annotation name='org.alljoyn.Bus.Type.Units' value='K'/>"
"        </property>"
"        <property name='MinTemperature' type='d' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The minimum color temperature supported by the device.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='const'/>"
"            <annotation name='org.alljoyn.Bus.Type.Min' value='0.0'/>"
"            <annotation name='org.alljoyn.Bus.Type.Units' value='K'/>"
"        </property>"
"        <property name='MaxTemperature' type='d' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The maximum color temperature supported by the device.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='const'/>"
"            <annotation name='org.alljoyn.Bus.Type.Min' value='0.0'/>"
"            <annotation name='org.alljoyn.Bus.Type.Units' value='K'/>"
"        </property>"
"    </interface>"
"</node>"
;

const qcc::String ColorTemperatureInterface::s_prop_Version = "Version";
const qcc::String ColorTemperatureInterface::s_prop_Temperature = "Temperature";
const qcc::String ColorTemperatureInterface::s_prop_MinTemperature = "MinTemperature";
const qcc::String ColorTemperatureInterface::s_prop_MaxTemperature = "MaxTemperature";

} //namespace services
} //namespace ajn
