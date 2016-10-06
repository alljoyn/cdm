/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
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
#include <alljoyn/cdm/interfaces/operation/EnergyUsageInterface.h>

namespace ajn {
namespace services {

const uint16_t EnergyUsageInterface::s_interfaceVersion = 1;

const qcc::String EnergyUsageInterface::s_xml =
"<node xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='http://www.allseenalliance.org/schemas/introspect.xsd'>"
"    <interface name='org.alljoyn.SmartSpaces.Operation.EnergyUsage'>"
"        <annotation name='org.alljoyn.Bus.DocString.En' value='Interface that exposes information on Energy consumption of the device.'/>"
"        <annotation name='org.alljoyn.Bus.Secure' value='true'/>"
"        <property name='Version' type='q' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The interface version.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='const'/>"
"        </property>"
"        <property name='CumulativeEnergy' type='d' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The cumulative energy consumption of the device'/>"
"            <annotation name='org.alljoyn.Bus.Type.Units' value='kilowatts hour'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <property name='Precision' type='d' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The precision of the CumulativeEnergy property; i.e., the value the actual energy consumption must change before CumulativeEnergy is updated'/>"
"            <annotation name='org.alljoyn.Bus.Type.Units' value='kilowatts hour'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <property name='UpdateMinTime' type='q' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The minimum time between updates of the CumulativeEnergy property'/>"
"            <annotation name='org.alljoyn.Bus.Type.Units' value='milliseconds'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <method name='ResetCumulativeEnergy'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Resets the value of CumulativeEnergy to 0.'/>"
"       </method>"
"    </interface>"
"</node>"
;

const qcc::String EnergyUsageInterface::s_prop_Version = "Version";
const qcc::String EnergyUsageInterface::s_prop_CumulativeEnergy = "CumulativeEnergy";
const qcc::String EnergyUsageInterface::s_prop_Precision = "Precision";
const qcc::String EnergyUsageInterface::s_prop_UpdateMinTime = "UpdateMinTime";
const qcc::String EnergyUsageInterface::s_method_ResetCumulativeEnergy = "ResetCumulativeEnergy";

} //namespace services
} //namespace ajn