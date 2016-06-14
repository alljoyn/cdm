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
#include <alljoyn/hae/interfaces/operation/PlugInUnitsInterface.h>

namespace ajn {
namespace services {

const uint16_t PlugInUnitsInterface::s_interfaceVersion = 1;

// Below none secure xml is only for test
const qcc::String PlugInUnitsInterface::s_xml =
"<node xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='http://www.allseenalliance.org/schemas/introspect.xsd'>"
"    <interface name='org.alljoyn.SmartSpaces.Operation.PlugInUnits'>"
"        <annotation name='org.alljoyn.Bus.DocString.En' value='This interface provides the status of Plug in units.'/>"
"        <annotation name='org.alljoyn.Bus.Secure' value='true'/>"
"        <annotation name='org.alljoyn.Bus.Struct.PlugInInfo.Field.objectPath.Type' value='o'/>"
"        <annotation name='org.alljoyn.Bus.Struct.PlugInInfo.Field.deviceId.Type' value='u'/>"
"        <annotation name='org.alljoyn.Bus.Struct.PlugInInfo.Field.pluggedIn.Type' value='b'/>"
"        <property name='Version' type='q' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The interface version.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='const'/>"
"        </property>"
"        <property name='PlugInUnits' type='a(oub)' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The lists of all the possible hot pluggable devices and the associated status.'/>"
"            <annotation name='org.alljoyn.Bus.Type.Name' value='a[PlugInInfo]'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"    </interface>"
"</node>"
;

const qcc::String PlugInUnitsInterface::s_prop_Version = "Version";
const qcc::String PlugInUnitsInterface::s_prop_PlugInUnits= "PlugInUnits";

} //namespace services
} //namespace ajn
