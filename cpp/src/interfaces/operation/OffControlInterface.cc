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
#include <alljoyn/hae/interfaces/operation/OffControlInterface.h>

namespace ajn {
namespace services {

const uint16_t OffControlInterface::s_interfaceVersion = 1;

// Below none secure xml is only for test
const qcc::String OffControlInterface::s_xml =
"<node xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='http://www.allseenalliance.org/schemas/introspect.xsd'>"
"    <interface name='org.alljoyn.SmartSpaces.Operation.OffControl'>"
"        <description language='en'>This interface provides a capability switch off the device.</description>"
"        <annotation name='org.alljoyn.Bus.Secure' value='false'/>"
"        <property name='Version' type='q' access='read'>"
"            <description language='en'>Interface version</description>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <method name='SwitchOff'>"
"            <description language='en'>Switch off the device.</description>"
"        </method>"
"    </interface>"
"</node>"
;

const qcc::String OffControlInterface::s_prop_Version = "Version";
const qcc::String OffControlInterface::s_method_SwitchOff = "SwitchOff";

} //namespace services
} //namespace ajn
