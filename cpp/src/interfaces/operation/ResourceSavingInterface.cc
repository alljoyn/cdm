
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
#include <alljoyn/hae/interfaces/operation/ResourceSavingInterface.h>

namespace ajn {
namespace services {

const uint16_t ResourceSavingInterface::s_interfaceVersion = 1;

const qcc::String ResourceSavingInterface::s_xml =
        "<node>"
        "   <interface name='org.alljoyn.SmartSpaces.Operation.ResourceSaving'>"
        "        <description language='en'>Interface that exposes the resource saving mode.  Depending on the device this resource could be electricity, water, natural gas, etc. </description>"
        "        <annotation name='org.alljoyn.Bus.Secure' value='true'/>"
        "        <property name='Version' type='q' access='read'>"
        "            <description language='en'>The version of this interface</description>"
        "            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
        "        </property>"
        "        <property name='ResourceSavingMode' type='b' access='readwrite'>"
        "           <description language='en'>The current resource saving mode of the device</description>"
        "           <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
        "       </property>"
        "   </interface>"
        "</node>";

const qcc::String ResourceSavingInterface::s_prop_Version = "Version";
const qcc::String ResourceSavingInterface::s_prop_ResourceSavingMode = "ResourceSavingMode";

} //namespace services
} //namespace ajn

