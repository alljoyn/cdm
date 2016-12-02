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
#include <alljoyn/cdm/interfaces/operation/LockControlInterface.h>

namespace ajn {
namespace services {

const char* const LockControlInterface::INTERFACE_NAME = "org.alljoyn.SmartSpaces.Operation.LockControl";
const CdmInterfaceType LockControlInterface::INTERFACE_TYPE = LOCK_CONTROL_INTERFACE;


const uint16_t LockControlInterface::s_interfaceVersion = 1;

const qcc::String LockControlInterface::s_xml =
"<node xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='http://www.allseenalliance.org/schemas/introspect.xsd'>"
"    <interface name='org.alljoyn.SmartSpaces.Operation.LockControl'>"
"        <annotation name='org.alljoyn.Bus.DocString.En' value='This interface provides the capability to engage the locking mechanism.'/>"
"        <annotation name='org.alljoyn.Bus.Secure' value='true'/>"
"        <property name='Version' type='q' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The interface version.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='const'/>"
"        </property>"
"        <method name='Lock'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Engage the locking mechanism.'/>"
"        </method>"
"    </interface>"
"</node>"
;

const qcc::String LockControlInterface::s_prop_Version = "Version";
const qcc::String LockControlInterface::s_method_Lock = "Lock";

} //namespace services
} //namespace ajn
