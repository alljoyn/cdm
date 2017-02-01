/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF), AllJoyn Open Source
 *    Project (AJOSP) Contributors and others.
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

#include <alljoyn/cdm/LogModule.h>
#include <alljoyn/cdm/interfaces/operation/RapidModeTimedInterface.h>

namespace ajn {
namespace services {

const uint16_t RapidModeTimedInterface::s_interfaceVersion = 1;

const qcc::String RapidModeTimedInterface::s_xml =
"<node xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='http://www.allseenalliance.org/schemas/introspect.xsd'>"
"    <interface name='org.alljoyn.SmartSpaces.Operation.RapidModeTimed'>"
"        <annotation name='org.alljoyn.Bus.DocString.En' value='This interface is for controlling a rapid mode of a device that has a limited duration.'/>"
"        <annotation name='org.alljoyn.Bus.Secure' value='true'/>"
"        <property name='Version' type='q' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The interface version.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='const'/>"
"        </property>"
"        <property name='RapidModeMinutesRemaining' type='q' access='readwrite'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Time remaining in rapid mode. Zero indicates not in rapid mode.'/>"
"            <annotation name='org.alljoyn.Bus.Type.Units' value='minutes'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <property name='MaxSetMinutes' type='q' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Maximum rapid mode set time. It does not change to accomodate already in rapid mode.'/>"
"            <annotation name='org.alljoyn.Bus.Type.Units' value='minutes'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='const'/>"
"        </property>"
"    </interface>"
"</node>"
;

const qcc::String RapidModeTimedInterface::s_prop_Version = "Version";
const qcc::String RapidModeTimedInterface::s_prop_RapidModeMinutesRemaining = "RapidModeMinutesRemaining";
const qcc::String RapidModeTimedInterface::s_prop_MaxSetMinutes = "MaxSetMinutes";

} //namespace services
} //namespace ajn