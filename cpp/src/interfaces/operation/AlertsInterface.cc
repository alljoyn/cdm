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
#include <alljoyn/hae/interfaces/operation/AlertsInterface.h>

namespace ajn {
namespace services {

const uint16_t AlertsInterface::s_interfaceVersion = 1;

// Below none secure xml is only for test
const qcc::String AlertsInterface::s_xml =
"<node xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='http://www.allseenalliance.org/schemas/introspect.xsd'>"
"    <interface name='org.alljoyn.SmartSpaces.Operation.Alerts'>"
"        <description language='en'>This information provides the status of the alerts of an appliance</description>"
"        <annotation name='org.alljoyn.Bus.Secure' value='false'/>"
// "        <struct name='AlertRecord'>"
// "            <field name='severity' type='y'/>"
// "            <field name='alertCode' type='q'/>"
// "            <field name='needAcknowledgement' type='b'/>"
// "        </struct>"
// "        <struct name='AlertCodesDescriptor'>"
// "            <field name='alertCode' type='q'/>"
// "            <field name='description' type='s'/>"
// "        </struct>"
"        <property name='Version' type='q' access='read'>"
"            <description language='en'>Interface version</description>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <property name='Alerts' type='a(yqb)' access='read'>"
"            <description language='en'>List of current pending alerts</description>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <method name='GetAlertCodesDescription'>"
"            <description language='en'>Get alert codes description</description>"
"            <arg name='languageTag' type='s' direction='in'>"
"                <description language='en'>Language to be used in the output strings</description>"
"            </arg>"
"            <arg name='description' type='a(qs)' direction='out'>"
"                <description language='en'>alert codes description</description>"
"            </arg>"
"        </method>"
"        <method name='AcknowledgeAlert'>"
"            <description language='en'>Reset the user acknowledgment request of a specific pending alert</description>"
"            <arg name='alertCode' type='q' direction='in'>"
"                <description language='en'>Alert code of the alert to be acknowledged</description>"
"            </arg>"
"        </method>"
"        <method name='AcknowledgeAllAlerts'>"
"            <description language='en'>Reset the user acknowledgment request of any pending alert</description>"
"        </method>"
"    </interface>"
"</node>"
;

const qcc::String AlertsInterface::s_prop_Version = "Version";
const qcc::String AlertsInterface::s_prop_Alerts = "Alerts";
const qcc::String AlertsInterface::s_method_GetAlertCodesDescription = "GetAlertCodesDescription";
const qcc::String AlertsInterface::s_method_AcknowledgeAlert = "AcknowledgeAlert";
const qcc::String AlertsInterface::s_method_AcknowledgeAllAlerts = "AcknowledgeAllAlerts";

} //namespace services
} //namespace ajn
