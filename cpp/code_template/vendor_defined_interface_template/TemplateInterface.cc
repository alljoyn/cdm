/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF), AllJoyn Open Source
 *    Project (AJOSP) Contributors and others.
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
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
******************************************************************************/

#include <alljoyn/cdm/LogModule.h>
#include "{interface_name}Interface.h"

namespace ajn {
namespace services {

const uint16_t {interface_name}Interface::s_interfaceVersion = 1;

// Below none secure xml is only for test
// TODO: modify interface xml (this xml is an example.)
const qcc::String {interface_name}Interface::s_xml =
        "<node>"
        "    <interface name='com.foo.bar.test'>"
        "        <description language='en'>This interface is a vendor defined interface sample.</description>"
        "        <annotation name='org.alljoyn.Bus.Secure' value='false'/>"
        "        <property name='Version' type='q' access='read'>"
        "            <description language='en'>Interface version</description>"
        "            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
        "        </property>"
        "        <property name='Property1' type='i' access='read'>"
        "            <description language='en'>Vendor defined interface property1(int)</description>"
        "            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
        "        </property>"
        "        <method name='TestMethod1'>"
        "            <description language='en'>Test method</description>"
        "            <arg name='arg1' type='i' direction='in'/>"
        "        </method>"
        "    </interface>"
        "</node>";

const qcc::String {interface_name}Interface::s_prop_Version = "Version";
/**
 * TODO: initialize property, method and signal name variable
 */

} //namespace services
} //namespace ajn