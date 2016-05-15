
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
#include <alljoyn/hae/interfaces/environment/WindDirectionInterface.h>

namespace ajn {
namespace services {

const uint16_t WindDirectionInterface::s_interfaceVersion = 1;

const qcc::String WindDirectionInterface::s_xml =
"<node xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xmlns='http://www.allseenalliance.org/schemas/introspect' xsi:schemaLocation='http://www.allseenalliance.org/schemas/introspect.xsd'>"
"    <interface name='org.alljoyn.SmartSpaces.Environment.WindDirection'>"
"        <annotation name='org.alljoyn.Bus.DocString.En' value='This interface is for controlling wind direction of a device.'/>"
"        <annotation name='org.alljoyn.Bus.Secure' value='true'/>"
"        <property name='Version' type='q' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The interface version.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='const'/>"
"        </property>"
"        <property name='HorizontalDirection' type='q' access='readwrite'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Horizontal wind direction of a device.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <property name='HorizontalMax' type='q' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Maximum value allowed for a target horizontal wind direction.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <annotation name='org.alljoyn.Bus.Enum.AutoMode.Value.Off' value='0'/>"
"        <annotation name='org.alljoyn.Bus.Enum.AutoMode.Value.On' value='1'/>"
"        <annotation name='org.alljoyn.Bus.Enum.AutoMode.Value.NotSupported' value='255'/>"
"        <property name='HorizontalAutoMode' type='y' access='readwrite'>"
"            <annotation name='org.alljoyn.Bus.Type.Name' value='[AutoMode]'/>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Represent enabled/disabled state of the horizontal auto mode. HorizontalAutoMode is for controlling horizontal wind direction automatically.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <property name='VerticalDirection' type='q' access='readwrite'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Vertical wind direction of a device.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <property name='VerticalMax' type='q' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Maximum value allowed for a target vertical wind direction.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <property name='VerticalAutoMode' type='y' access='readwrite'>"
"            <annotation name='org.alljoyn.Bus.Type.Name' value='[AutoMode]'/>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Represent enabled/disabled state of the vertical auto mode. VerticalAutoMode is for controlling vertical wind direction automatically.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"    </interface>"
"</node>";
const qcc::String WindDirectionInterface::s_prop_Version = "Version";
const qcc::String WindDirectionInterface::s_prop_HorizontalDirection = "HorizontalDirection";
const qcc::String WindDirectionInterface::s_prop_HorizontalMax = "HorizontalMax";
const qcc::String WindDirectionInterface::s_prop_HorizontalAutoMode = "HorizontalAutoMode";
const qcc::String WindDirectionInterface::s_prop_VerticalDirection = "VerticalDirection";
const qcc::String WindDirectionInterface::s_prop_VerticalMax = "VerticalMax";
const qcc::String WindDirectionInterface::s_prop_VerticalAutoMode = "VerticalAutoMode";

} //namespace services
} //namespace ajn
