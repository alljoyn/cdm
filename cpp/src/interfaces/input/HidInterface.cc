/******************************************************************************
 *  *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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
#include <alljoyn/cdm/interfaces/input/HidInterface.h>

namespace ajn {
namespace services {

const uint16_t HidInterface::s_interfaceVersion = 1;

// Below none secure xml is only for test
const qcc::String HidInterface::s_xml =
        "<node>"
        "    <interface name='org.alljoyn.Input.Hid'>"
        "        <description language='en'>This interface provides capabilities to inject user input events for human interface device from _consumer_ to the _producer_.</description>"
        "        <annotation name='org.alljoyn.Bus.Secure' value='true'/>"
        "        <property name='Version' type='q' access='read'>"
        "            <description language='en'>Interface version</description>"
        "            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
        "        </property>"
        "        <property name='SupportedEvents' type='a(qqii)' access='read'>"
        "            <description language='en'>List of supported input events by a device</description>"
        "            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
        "        </property>"
        "        <method name='InjectEvents'>"
        "            <description language='en'>Inject the user input events for human interface device.</description>"
        "            <annotation name='org.freedesktop.DBus.Method.NoReply' value='true'/>"
        "            <arg name='inputEvents' type='a(qqi)' direction='in'/>"
        "        </method>"
        "    </interface>"
        "</node>";

const qcc::String HidInterface::s_prop_Version = "Version";
const qcc::String HidInterface::s_prop_SupportedEvents = "SupportedEvents";
const qcc::String HidInterface::s_method_InjectEvents = "InjectEvents";

} //namespace services
} //namespace ajn