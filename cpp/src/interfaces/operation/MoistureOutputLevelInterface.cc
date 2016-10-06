/******************************************************************************
 *  * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <alljoyn/cdm/LogModule.h>
#include <alljoyn/cdm/interfaces/operation/MoistureOutputLevelInterface.h>

namespace ajn {
namespace services {

const uint16_t MoistureOutputLevelInterface::s_interfaceVersion = 1;

// Below none secure xml is only for test
const qcc::String MoistureOutputLevelInterface::s_xml =
"<node xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='http://www.allseenalliance.org/schemas/introspect.xsd'>"
"    <interface name='org.alljoyn.SmartSpaces.Operation.MoistureOutputLevel'>"
"        <annotation name='org.alljoyn.Bus.DocString.En' value='This interface provides a capability to control and monitor the moisture output level.'/>"
"        <annotation name='org.alljoyn.Bus.Secure' value='true'/>"
"        <property name='Version' type='q' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The interface version.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='const'/>"
"        </property>"
"        <property name='MoistureOutputLevel' type='y' access='readwrite'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Current level of moisture output.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <property name='MaxMoistureOutputLevel' type='y' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Maximum level of moisture output.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <annotation name='org.alljoyn.Bus.Enum.AutoMode.Value.Off' value='0'/>"
"        <annotation name='org.alljoyn.Bus.Enum.AutoMode.Value.On' value='1'/>"
"        <annotation name='org.alljoyn.Bus.Enum.AutoMode.Value.NotSupported' value='255'/>"
"        <property name='AutoMode' type='y' access='readwrite'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Represent enabled/disabled state of the auto mode. The device decides the moisture output level for providing comfortable surroundings automatically.'/>"
"            <annotation name='org.alljoyn.Bus.Type.Name' value='[AutoMode]'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"    </interface>"
"</node>"
;

const qcc::String MoistureOutputLevelInterface::s_prop_Version = "Version";
const qcc::String MoistureOutputLevelInterface::s_prop_MoistureOutputLevel = "MoistureOutputLevel";
const qcc::String MoistureOutputLevelInterface::s_prop_MaxMoistureOutputLevel = "MaxMoistureOutputLevel";
const qcc::String MoistureOutputLevelInterface::s_prop_AutoMode = "AutoMode";

} //namespace services
} //namespace ajn