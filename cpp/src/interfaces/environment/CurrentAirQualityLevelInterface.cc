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
#include <alljoyn/cdm/interfaces/environment/CurrentAirQualityLevelInterface.h>

namespace ajn {
namespace services {

const uint16_t CurrentAirQualityLevelInterface::s_interfaceVersion = 1;

// Below none secure xml is only for test
const qcc::String CurrentAirQualityLevelInterface::s_xml =
"<node xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xmlns='http://www.allseenalliance.org/schemas/introspect' xsi:schemaLocation='http://www.allseenalliance.org/schemas/introspect.xsd'>"
"    <interface name='org.alljoyn.SmartSpaces.Environment.CurrentAirQualityLevel'>"
"        <annotation name='org.alljoyn.Bus.DocString.En' value='This information provides current air quality level measured by a device.'/>"
"        <annotation name='org.alljoyn.Bus.Secure' value='true'/>"
"        <property name='Version' type='q' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The interface version.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='const'/>"
"        </property>"
"        <annotation name='org.alljoyn.Bus.Enum.ContaminantType.Value.CH2O' value='0'/>"
"        <annotation name='org.alljoyn.Bus.Enum.ContaminantType.Value.CO2' value='1'/>"
"        <annotation name='org.alljoyn.Bus.Enum.ContaminantType.Value.CO' value='2'/>"
"        <annotation name='org.alljoyn.Bus.Enum.ContaminantType.Value.PM2_5' value='3'/>"
"        <annotation name='org.alljoyn.Bus.Enum.ContaminantType.Value.PM10' value='4'/>"
"        <annotation name='org.alljoyn.Bus.Enum.ContaminantType.Value.VOC' value='5'/>"
"        <annotation name='org.alljoyn.Bus.Enum.ContaminantType.Value.Smoke' value='253'/>"
"        <annotation name='org.alljoyn.Bus.Enum.ContaminantType.Value.Odor' value='254'/>"
"        <annotation name='org.alljoyn.Bus.Enum.ContaminantType.Value.AirPollution' value='255'/>"
"        <property name='ContaminantType' type='y' access='read'>"
"            <annotation name='org.alljoyn.Bus.Type.Name' value='[ContaminantType]'/>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The contaminant type.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <property name='CurrentLevel' type='y' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The qualitative representation of current air quality level.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"            <annotation name='org.alljoyn.Bus.Type.Min' value='0'/>"
"        </property>"
"        <property name='MaxLevel' type='y' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Maximum level allowed for represented air quality level.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"    </interface>"
"</node>"
;

const qcc::String CurrentAirQualityLevelInterface::s_prop_Version = "Version";
const qcc::String CurrentAirQualityLevelInterface::s_prop_ContaminantType = "ContaminantType";
const qcc::String CurrentAirQualityLevelInterface::s_prop_CurrentLevel = "CurrentLevel";
const qcc::String CurrentAirQualityLevelInterface::s_prop_MaxLevel = "MaxLevel";

} //namespace services
} //namespace ajn
