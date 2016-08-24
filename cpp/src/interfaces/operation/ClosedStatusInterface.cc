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
#include <alljoyn/cdm/interfaces/operation/ClosedStatusInterface.h>

namespace ajn {
namespace services {

const uint16_t ClosedStatusInterface::s_interfaceVersion = 1;

// Below none secure xml is only for test
const qcc::String ClosedStatusInterface::s_xml =
"<node xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='http://www.allseenalliance.org/schemas/introspect.xsd'>"
"    <interface name='org.alljoyn.SmartSpaces.Operation.ClosedStatus'>"
"        <annotation name='org.alljoyn.Bus.DocString.En' value='This interface provides the status of any object that can report a two state open closed condition; e.g., door or window.'/>"
"        <annotation name='org.alljoyn.Bus.Secure' value='true'/>"
"        <property name='Version' type='q' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The Version of this interface.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='const'/>"
"        </property>"
"        <property name='IsClosed' type='b' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='If true, object is closed.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"    </interface>"
"</node>"
;

const qcc::String ClosedStatusInterface::s_prop_Version = "Version";
const qcc::String ClosedStatusInterface::s_prop_IsClosed = "IsClosed";

} //namespace services
} //namespace ajn
