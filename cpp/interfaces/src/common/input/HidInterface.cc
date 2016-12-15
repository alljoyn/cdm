/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

// This file is automatically generated. Do not edit it.

#include <alljoyn/cdm/common/LogModule.h>
#include <interfaces/common/input/HidInterface.h>

namespace ajn {
namespace services {

const char* const HidInterface::INTERFACE_NAME = "org.alljoyn.Input.Hid";
const CdmInterfaceType HidInterface::INTERFACE_TYPE = HID_INTERFACE;


const uint16_t HidInterface::s_interfaceVersion = 1;

const qcc::String HidInterface::s_xml =
"<node xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='http://www.allseenalliance.org/schemas/introspect.xsd'>"
"    <interface name='org.alljoyn.Input.Hid'>"
"        <description language='en'>This interface provides a capability to inject user input events for human interface devices from the _consumer_ to the _producer_</description>"
"        <annotation name='org.alljoyn.Bus.Secure' value='true'/>"
"        <annotation name='org.alljoyn.Bus.Struct.InputEvent.Field.type.Type' value='q'/>"
"        <annotation name='org.alljoyn.Bus.Struct.InputEvent.Field.code.Type' value='q'/>"
"        <annotation name='org.alljoyn.Bus.Struct.InputEvent.Field.value.Type' value='i'/>"
"        <annotation name='org.alljoyn.Bus.Struct.SupportedInputEvent.Field.type.Type' value='q'/>"
"        <annotation name='org.alljoyn.Bus.Struct.SupportedInputEvent.Field.code.Type' value='q'/>"
"        <annotation name='org.alljoyn.Bus.Struct.SupportedInputEvent.Field.min.Type' value='i'/>"
"        <annotation name='org.alljoyn.Bus.Struct.SupportedInputEvent.Field.max.Type' value='i'/>"
"        <property name='Version' type='q' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The interface version'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='const'/>"
"        </property>"
"        <property name='SupportedEvents' type='a(qqii)' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='List of supported input events by a device'/>"
"            <annotation name='org.alljoyn.Bus.Type.Name' value='a[SupportedInputEvent]'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <method name='InjectEvents'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Inject the user input events for human interface devices'/>"
"            <annotation name='org.freedesktop.DBus.Method.NoReply' value='true'/>"
"            <arg name='inputEvents' type='a(qqi)' direction='in'>"
"                <annotation name='org.alljoyn.Bus.DocString.En' value='Injected input event'/>"
"                <annotation name='org.alljoyn.Bus.Type.Name' value='a[InputEvent]'/>"
"            </arg>"
"        </method>"
"    </interface>"
"</node>"
;

const qcc::String HidInterface::s_prop_Version = "Version";
const qcc::String HidInterface::s_prop_SupportedEvents = "SupportedEvents";
const qcc::String HidInterface::s_method_InjectEvents = "InjectEvents";

} //namespace services
} //namespace ajn