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
#include <interfaces/common/operation/UnlockControlInterface.h>

namespace ajn {
namespace services {

const char* const UnlockControlInterface::INTERFACE_NAME = "org.alljoyn.SmartSpaces.Operation.UnlockControl";
const CdmInterfaceType UnlockControlInterface::INTERFACE_TYPE = UNLOCK_CONTROL_INTERFACE;


const uint16_t UnlockControlInterface::s_interfaceVersion = 1;

const qcc::String UnlockControlInterface::s_xml =
"<node xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='http://www.allseenalliance.org/schemas/introspect.xsd'>"
"    <interface name='org.alljoyn.SmartSpaces.Operation.UnlockControl'>"
"        <annotation name='org.alljoyn.Bus.DocString.En' value='This interface provides the capability to disengage the locking mechanism.'/>"
"        <annotation name='org.alljoyn.Bus.Secure' value='true'/>"
"        <property name='Version' type='q' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The interface version.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='const'/>"
"        </property>"
"        <method name='Unlock'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Disengage the locking mechanism.'/>"
"        </method>"
"    </interface>"
"</node>"
;

const qcc::String UnlockControlInterface::s_prop_Version = "Version";
const qcc::String UnlockControlInterface::s_method_Unlock = "Unlock";

} //namespace services
} //namespace ajn
