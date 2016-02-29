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
#include <alljoyn/hae/interfaces/operation/RobotCleaningCyclePhaseInterface.h>

namespace ajn {
namespace services {

const uint16_t RobotCleaningCyclePhaseInterface::s_interfaceVersion = 1;

const qcc::String RobotCleaningCyclePhaseInterface::s_xml =
"<node xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='http://www.allseenalliance.org/schemas/introspect.xsd'>"
"    <interface name='org.alljoyn.SmartSpaces.Operation.RobotCleaningCyclePhase'>"
"        <description language='en'> This interface provides a capability to monitor the operational cycle phase of the robot cleaner.</description>"
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
"                <description language='en'>Preferred language to use in selecting output strings</description>"
"            </arg>"
"            <arg name='phasesDescription' type='a(yss)' direction='out'>"
"                <description language='en'>Cycle phases description</description>"
"            </arg>"
"        </method>"
"   </interface>"
"</node>"
;

const qcc::String RobotCleaningCyclePhaseInterface::s_prop_Version = "Version";
const qcc::String RobotCleaningCyclePhaseInterface::s_prop_CyclePhase = "CyclePhase";
const qcc::String RobotCleaningCyclePhaseInterface::s_prop_SupportedCyclePhases = "SupportedCyclePhases";
const qcc::String RobotCleaningCyclePhaseInterface::s_method_GetVendorPhasesDescription = "GetVendorPhasesDescription";

} //namespace services
} //namespace ajn
