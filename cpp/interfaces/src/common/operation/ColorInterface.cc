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
#include <interfaces/common/operation/ColorInterface.h>

namespace ajn {
namespace services {

const char* const ColorInterface::INTERFACE_NAME = "org.alljoyn.SmartSpaces.Operation.Color";
const CdmInterfaceType ColorInterface::INTERFACE_TYPE = COLOR_INTERFACE;


const uint16_t ColorInterface::s_interfaceVersion = 1;

const qcc::String ColorInterface::s_xml =
"<node xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='http://www.allseenalliance.org/schemas/introspect.xsd'>"
"    <interface name='org.alljoyn.SmartSpaces.Operation.Color'>"
"        <annotation name='org.alljoyn.Bus.DocString.En' value='This interface provides capabilities to control and monitor color.'/>"
"        <annotation name='org.alljoyn.Bus.Secure' value='true'/>"
"        <property name='Version' type='q' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The interface version.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='const'/>"
"        </property>"
"        <property name='Hue' type='d' access='readwrite'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Hue of the device.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"            <annotation name='org.alljoyn.Bus.Type.Min' value='0.0'/>"
"            <annotation name='org.alljoyn.Bus.Type.Max' value='360.0'/>"
"        </property>"
"        <property name='Saturation' type='d' access='readwrite'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Saturation of the device.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"            <annotation name='org.alljoyn.Bus.Type.Min' value='0.0'/>"
"            <annotation name='org.alljoyn.Bus.Type.Max' value='1.0'/>"
"        </property>"
"    </interface>"
"</node>"
;

const qcc::String ColorInterface::s_prop_Version = "Version";
const qcc::String ColorInterface::s_prop_Hue = "Hue";
const qcc::String ColorInterface::s_prop_Saturation = "Saturation";

} //namespace services
} //namespace ajn