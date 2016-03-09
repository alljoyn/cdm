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
#include <alljoyn/hae/interfaces/operation/OvenCyclePhaseInterface.h>

namespace ajn {
namespace services {

const uint16_t OvenCyclePhaseInterface::s_interfaceVersion = 1;

// Below none secure xml is only for test
const qcc::String OvenCyclePhaseInterface::s_xml =
"<node xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='http://www.allseenalliance.org/schemas/introspect.xsd'>"
"    <interface name='org.alljoyn.SmartSpaces.Operation.OvenCyclePhase'>"
"        <description language='en'>This interface provides a capability to monitor the phase of the operational cycle of the Oven</description>"
"        <annotation name='org.alljoyn.Bus.Secure' value='true'/>"
"        <property name='Version' type='q' access='read'>"
"            <description language='en'>Interface version</description>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <property name='CyclePhase' type='y' access='read'>"
"            <description language='en'>Current cycle phase</description>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <property name='SupportedCyclePhases' type='ay' access='read'>"
"            <description language='en'>List of supported cycle phases</description>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <method name='GetVendorPhasesDescription'>"
"            <description language='en'>Get cycle phases description</description>"
"            <arg name='languageTag' type='s' direction='in'>"
"                <description language='en'>preferred language to be used in selecting the output strings</description>"
"            </arg>"
"            <arg name='phasesDescription' type='a(yss)' direction='out'>"
"                <description language='en'>Cycle phases description</description>"
"            </arg>"
"        </method>"
"   </interface>"
"</node>"
;

const qcc::String OvenCyclePhaseInterface::s_prop_Version = "Version";
const qcc::String OvenCyclePhaseInterface::s_prop_CyclePhase = "CyclePhase";
const qcc::String OvenCyclePhaseInterface::s_prop_SupportedCyclePhases = "SupportedCyclePhases";
const qcc::String OvenCyclePhaseInterface::s_method_GetVendorPhasesDescription = "GetVendorPhasesDescription";
const OvenCyclePhaseInterface::StandardCyclePhases OvenCyclePhaseInterface::m_standardCyclePhases = { OVEN_PHASE_UNAVAILABLE, OVEN_PHASE_PREHEATING, OVEN_PHASE_COOKING, OVEN_PHASE_CLEANING };

} //namespace services
} //namespace ajn
