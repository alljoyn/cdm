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
#include <alljoyn/cdm/interfaces/operation/TriggerSensorInterface.h>

namespace ajn {
namespace services {

const char* const TriggerSensorInterface::INTERFACE_NAME = "org.alljoyn.SmartSpaces.Operation.TriggerSensor";
const CdmInterfaceType TriggerSensorInterface::INTERFACE_TYPE = TRIGGER_SENSOR_INTERFACE;


const uint16_t TriggerSensorInterface::s_interfaceVersion = 1;

const qcc::String TriggerSensorInterface::s_xml =
"<node xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='http://www.allseenalliance.org/schemas/introspect.xsd'>"
"    <interface name='org.alljoyn.SmartSpaces.Operation.TriggerSensor'>"
"        <annotation name='org.alljoyn.Bus.DocString.En' value='This interface provides the capability to monitor the status of a triggered sensor.'/>"
"        <annotation name='org.alljoyn.Bus.Secure' value='true'/>"
"        <property name='Version' type='q' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The interface version.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='const'/>"
"        </property>"
"        <property name='CurrentlyTriggered' type='b' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The current status of the sensor's trigger.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"    </interface>"
"</node>"
;

const qcc::String TriggerSensorInterface::s_prop_Version = "Version";
const qcc::String TriggerSensorInterface::s_prop_CurrentlyTriggered = "CurrentlyTriggered";

} //namespace services
} //namespace ajn
