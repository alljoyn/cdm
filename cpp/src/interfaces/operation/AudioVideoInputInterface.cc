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
#include <alljoyn/hae/interfaces/operation/AudioVideoInputInterface.h>

namespace ajn {
namespace services {

const uint16_t AudioVideoInputInterface::s_interfaceVersion = 1;

// Below none secure xml is only for test
const qcc::String AudioVideoInputInterface::s_xml =
        "<node>"
        "    <interface name='org.alljoyn.SmartSpaces.Operation.AudioVideoInput'>"
        "        <description language='en'>This interface provides capabilities to control and monitor audio video input source of device such as TV or SetTopBox.</description>"
        "        <annotation name='org.alljoyn.Bus.Secure' value='false'/>"
        "        <property name='Version' type='q' access='read'>"
        "            <description language='en'>Interface version</description>"
        "            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
        "        </property>"
        "        <property name='InputSourceId' type='q' access='readwrite'>"
        "            <description language='en'>Activated input source id</description>"
        "            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
        "        </property>"
        "        <property name='SupportedInputSources' type='a(qqyqs)' access='read'>"
        "            <description language='en'>Array of supported input sources</description>"
        "            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
        "        </property>"
        "    </interface>"
        "</node>";

const qcc::String AudioVideoInputInterface::s_prop_Version = "Version";
const qcc::String AudioVideoInputInterface::s_prop_InputSourceId = "InputSourceId";
const qcc::String AudioVideoInputInterface::s_prop_SupportedInputSources = "SupportedInputSources";


} //namespace services
} //namespace ajn
