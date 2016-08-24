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
#include <alljoyn/cdm/interfaces/operation/RobotCleaningCyclePhaseInterface.h>

namespace ajn {
namespace services {

const uint16_t RobotCleaningCyclePhaseInterface::s_interfaceVersion = 1;

// Below none secure xml is only for test
const qcc::String RobotCleaningCyclePhaseInterface::s_xml =
"<node xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='http://www.allseenalliance.org/schemas/introspect.xsd'>"
"    <interface name='org.alljoyn.SmartSpaces.Operation.RobotCleaningCyclePhase'>"
"        <annotation name='org.alljoyn.Bus.DocString.En' value='This interface provides a capability to monitor the operational cycle phase of the robot cleaner.'/>"
"        <annotation name='org.alljoyn.Bus.Secure' value='true'/>"
"        <annotation name='org.alljoyn.Bus.Struct.CyclePhaseDescriptor.Field.phase.Type' value='y'/>"
"        <annotation name='org.alljoyn.Bus.Struct.CyclePhaseDescriptor.Field.name.Type' value='s'/>"
"        <annotation name='org.alljoyn.Bus.Struct.CyclePhaseDescriptor.Field.description.Type' value='s'/>"
"        <property name='Version' type='q' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The interface version.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='const'/>"
"        </property>"
"        <property name='CyclePhase' type='y' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Current cycle phase. Range value [0x00-0x7F] is for standard phases; range value [0x80-0xFF] is for vendor-defined phases and so the meanings depend on manufacturer.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <property name='SupportedCyclePhases' type='ay' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='List of supported cycle phases.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <method name='GetVendorPhasesDescription'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Get cycle phases description.'/>"
"            <arg name='languageTag' type='s' direction='in'>"
"                <annotation name='org.alljoyn.Bus.DocString.En' value='Preferred language to use in selecting output strings.'/>"
"            </arg>"
"            <arg name='phasesDescription' type='a(yss)' direction='out'>"
"                <annotation name='org.alljoyn.Bus.DocString.En' value='Cycle phases description.'/>"
"                <annotation name='org.alljoyn.Bus.Type.Name' value='a[CyclePhaseDescriptor]'/>"
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
