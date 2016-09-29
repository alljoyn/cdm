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
#include <alljoyn/cdm/interfaces/operation/AlertsInterface.h>

namespace ajn {
namespace services {

const uint16_t AlertsInterface::s_interfaceVersion = 1;

const qcc::String AlertsInterface::s_xml =
"<node xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='http://www.allseenalliance.org/schemas/introspect.xsd'>"
"    <interface name='org.alljoyn.SmartSpaces.Operation.Alerts'>"
"        <annotation name='org.alljoyn.Bus.DocString.En' value='This information provides the status of the alerts of an appliance.'/>"
"        <annotation name='org.alljoyn.Bus.Secure' value='true'/>"
"        <annotation name='org.alljoyn.Bus.Enum.Severity.Value.warning' value='0'/>"
"        <annotation name='org.alljoyn.Bus.Enum.Severity.Value.alarm' value='1'/>"
"        <annotation name='org.alljoyn.Bus.Enum.Severity.Value.fault' value='2'/>"
"        <annotation name='org.alljoyn.Bus.Struct.AlertRecord.Field.severity.Type' value='[Severity]'/>"
"        <annotation name='org.alljoyn.Bus.Struct.AlertRecord.Field.alertCode.Type' value='q'/>"
"        <annotation name='org.alljoyn.Bus.Struct.AlertRecord.Field.needAcknowledgement.Type' value='b'/>"
"        <annotation name='org.alljoyn.Bus.Struct.AlertCodesDescriptor.Field.alertCode.Type' value='q'/>"
"        <annotation name='org.alljoyn.Bus.Struct.AlertCodesDescriptor.Field.description.Type' value='s'/>"
"        <property name='Version' type='q' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The interface version.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='const'/>"
"        </property>"
"        <property name='Alerts' type='a(yqb)' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='List of current pending alerts.'/>"
"            <annotation name='org.alljoyn.Bus.Type.Name' value='a[AlertRecord]'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <method name='GetAlertCodesDescription'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Get alert codes description.'/>"
"            <arg name='languageTag' type='s' direction='in'>"
"                <annotation name='org.alljoyn.Bus.DocString.En' value='Language to be used in the output strings.'/>"
"            </arg>"
"            <arg name='description' type='a(qs)' direction='out'>"
"                <annotation name='org.alljoyn.Bus.DocString.En' value='Alert codes description.'/>"
"                <annotation name='org.alljoyn.Bus.Type.Name' value='a[AlertCodesDescriptor]'/>"
"            </arg>"
"        </method>"
"        <method name='AcknowledgeAlert'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Reset the user acknowledgment request of a specific pending alert.'/>"
"            <arg name='alertCode' type='q' direction='in'>"
"                <annotation name='org.alljoyn.Bus.DocString.En' value='Alert code of the alert to be acknowledged.'/>"
"            </arg>"
"        </method>"
"        <method name='AcknowledgeAllAlerts'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Reset the user acknowledgment request of any pending alert.'/>"
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
