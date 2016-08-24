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
#include <alljoyn/cdm/interfaces/userinterfacesettings/TimeDisplayInterface.h>

namespace ajn {
namespace services {

const uint16_t TimeDisplayInterface::s_interfaceVersion = 1;

// Below none secure xml is only for test
const qcc::String TimeDisplayInterface::s_xml =
"<node xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='http://www.allseenalliance.org/schemas/introspect.xsd'>"
"    <interface name='org.alljoyn.SmartSpaces.UserInterfaceSettings.TimeDisplay'>"
"        <annotation name='org.alljoyn.Bus.DocString.En' value='Interface to determine/control time display format on devices local user interface'/>"
"        <annotation name='org.alljoyn.Bus.Secure' value='true'/>"
"        <property name='Version' type='q' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The interface version'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='const'/>"
"        </property>"
"        <property name='DisplayTimeFormat' type='y' access='readwrite'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The clock format which is currently used to display time (0=12-hour, 1=24-hour)'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <property name='SupportedDisplayTimeFormats' type='ay' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='List of supported clock formats'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='const'/>"
"        </property>"
"    </interface>"
"</node>"
;

const qcc::String TimeDisplayInterface::s_prop_Version = "Version";
const qcc::String TimeDisplayInterface::s_prop_DisplayTimeFormat = "DisplayTimeFormat";
const qcc::String TimeDisplayInterface::s_prop_SupportedDisplayTimeFormats = "SupportedDisplayTimeFormats";

} //namespace services
} //namespace ajn
