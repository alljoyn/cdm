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
#include <alljoyn/cdm/interfaces/operation/HeatingZoneInterface.h>

namespace ajn {
namespace services {

const uint16_t HeatingZoneInterface::s_interfaceVersion = 1;

// Below none secure xml is only for test
const qcc::String HeatingZoneInterface::s_xml =
"<node xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='http://www.allseenalliance.org/schemas/introspect.xsd'>"
"    <interface name='org.alljoyn.SmartSpaces.Operation.HeatingZone'>"
"        <annotation name='org.alljoyn.Bus.DocString.En' value='This interface provides a capability to monitor the status of heating zones.'/>"
"        <annotation name='org.alljoyn.Bus.Secure' value='true'/>"
"        <property name='Version' type='q' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The interface version.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='const'/>"
"        </property>"
"        <property name='NumberOfHeatingZones' type='y' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Number of heating zones.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <property name='MaxHeatingLevels' type='ay' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Max heating levels for each zone.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <property name='HeatingLevels' type='ay' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Current heating levels for each zone.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"    </interface>"
"</node>"
;

const qcc::String HeatingZoneInterface::s_prop_Version = "Version";
const qcc::String HeatingZoneInterface::s_prop_NumberOfHeatingZones = "NumberOfHeatingZones";
const qcc::String HeatingZoneInterface::s_prop_MaxHeatingLevels = "MaxHeatingLevels";
const qcc::String HeatingZoneInterface::s_prop_HeatingLevels = "HeatingLevels";

} //namespace services
} //namespace ajn