/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
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
#include <alljoyn/cdm/interfaces/operation/FilterStatusInterface.h>

namespace ajn {
namespace services {

const uint16_t FilterStatusInterface::s_interfaceVersion = 1;

const qcc::String FilterStatusInterface::s_xml =
"<node xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='http://www.allseenalliance.org/schemas/introspect.xsd'>"
"    <interface name='org.alljoyn.SmartSpaces.Operation.FilterStatus'>"
"        <annotation name='org.alljoyn.Bus.DocString.En' value='Interface for determining the status of filters.'/>"
"        <annotation name='org.alljoyn.Bus.Secure' value='true'/>"
"        <property name='Version' type='q' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The interface version.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='const'/>"
"        </property>"
"        <property name='ExpectedLifeInDays' type='q' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Days a new filter will last. Used to convert percentage into remaining days. If 0xFFFF there is no predicted life. If 0 the life is less than 1 day.'/>"
"            <annotation name='org.alljoyn.Bus.Type.Units' value='days'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <property name='IsCleanable' type='b' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='This is a static property of the filter. If the property is true a new filter does not need to be ordered, just clean.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <property name='OrderPercentage' type='y' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='LifeRemaining it is recommended that a new filter be orderedIt can have a value of 0 because the remaining life is unpredictable, for example a psid switch. It can also have a value of 255 if OrderPercentage is N/A, for example a cleanable filter.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <property name='Manufacturer' type='s' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Identification of the filter manufacturer, which along with the part number act as a tuple to identify the filter within the Alljoyn device. Either one or both may be a null string.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='const'/>"
"        </property>"
"        <property name='PartNumber' type='s' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Identification of the filter manufacturer, which along with the part number act as a tuple to identify the filter within the Alljoyn device. Either one or both may be a null string.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='const'/>"
"        </property>"
"        <property name='Url' type='s' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Url can be just a domain or a complete URL to the exact filter. It may provide additional information of a site for ordering. A null string is acceptable.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='const'/>"
"        </property>"
"        <property name='LifeRemaining' type='y' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Lifespan Remaining in percentage (100 - 0). 0 indicates replace/clean. A simple device may just implement 100/0 or 100/OrderPercentage/0 instead of implementing the entire range of values.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"    </interface>"
"</node>";

const qcc::String FilterStatusInterface::s_prop_Version = "Version";
const qcc::String FilterStatusInterface::s_prop_ExpectedLifeInDays = "ExpectedLifeInDays";
const qcc::String FilterStatusInterface::s_prop_IsCleanable = "IsCleanable";
const qcc::String FilterStatusInterface::s_prop_OrderPercentage = "OrderPercentage";
const qcc::String FilterStatusInterface::s_prop_Manufacturer = "Manufacturer";
const qcc::String FilterStatusInterface::s_prop_PartNumber = "PartNumber";
const qcc::String FilterStatusInterface::s_prop_Url = "Url";
const qcc::String FilterStatusInterface::s_prop_LifeRemaining = "LifeRemaining";

} //namespace services
} //namespace ajn