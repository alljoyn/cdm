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
#include "VendorDefinedInterface.h"

namespace ajn {
namespace services {

const uint16_t VendorDefinedInterface::s_interfaceVersion = 1;

// Below none secure xml is only for test
// TODO: modify interface xml
const qcc::String VendorDefinedInterface::s_xml =
        "<node>"
        "    <interface name='com.foo.bar.test'>"
        "        <description language='en'>This interface is a vendor defined interface sample.</description>"
        "        <annotation name='org.alljoyn.Bus.Secure' value='false'/>"
        "        <property name='Version' type='q' access='read'>"
        "            <description language='en'>Interface version</description>"
        "            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
        "        </property>"
        "        <property name='TestProperty' type='i' access='readwrite'>"
        "            <description language='en'>Vendor defined interface property1(int)</description>"
        "            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
        "        </property>"
        "        <method name='TestMethod'>"
        "            <description language='en'>Test method</description>"
        "            <arg name='arg1' type='i' direction='in'/>"
        "        </method>"
        "        <signal name='TestSignal' sessionless='false'>"
        "            <description language='en'>Test signal</description>"
        "        </signal>"
        "    </interface>"
        "</node>";

const qcc::String VendorDefinedInterface::s_prop_Version = "Version";
const qcc::String VendorDefinedInterface::s_prop_TestProperty = "TestProperty";
const qcc::String VendorDefinedInterface::s_method_TestMethod = "TestMethod";
const qcc::String VendorDefinedInterface::s_signal_TestSignal = "TestSignal";
} //namespace services
} //namespace ajn
