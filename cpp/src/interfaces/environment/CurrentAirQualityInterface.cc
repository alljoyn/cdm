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
#include <alljoyn/cdm/interfaces/environment/CurrentAirQualityInterface.h>

namespace ajn {
namespace services {

const uint16_t CurrentAirQualityInterface::s_interfaceVersion = 1;

const qcc::String CurrentAirQualityInterface::s_xml =
"<node xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xmlns='http://www.allseenalliance.org/schemas/introspect' xsi:schemaLocation='http://www.allseenalliance.org/schemas/introspect.xsd'>"
"    <interface name='org.alljoyn.SmartSpaces.Environment.CurrentAirQuality'>"
"        <annotation name='org.alljoyn.Bus.DocString.En' value='This interface provides capability to represent current value of air quality.'/>"
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
"        <property name='ContaminantType' type='y' access='read'>"
"            <annotation name='org.alljoyn.Bus.Type.Name' value='[ContaminantType]'/>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The contaminant type.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <property name='CurrentValue' type='d' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The current value of air quality.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <property name='MinValue' type='d' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The minimum value allowed for CurrentValue.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <property name='MaxValue' type='d' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The maximum value allowed for CurrentValue.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <property name='Precision' type='d' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The precision of the CurrentValue property.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <property name='UpdateMinTime' type='q' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The minimum time between updates of the CurrentValue property in milliseconds.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"            <annotation name='org.alljoyn.Bus.Type.Units' value='milliseconds'/>"
"        </property>"
"    </interface>"
"</node>"
;

const qcc::String CurrentAirQualityInterface::s_prop_Version = "Version";
const qcc::String CurrentAirQualityInterface::s_prop_ContaminantType = "ContaminantType";
const qcc::String CurrentAirQualityInterface::s_prop_CurrentValue = "CurrentValue";
const qcc::String CurrentAirQualityInterface::s_prop_MinValue = "MinValue";
const qcc::String CurrentAirQualityInterface::s_prop_MaxValue = "MaxValue";
const qcc::String CurrentAirQualityInterface::s_prop_Precision = "Precision";
const qcc::String CurrentAirQualityInterface::s_prop_UpdateMinTime = "UpdateMinTime";

} //namespace services
} //namespace ajn
