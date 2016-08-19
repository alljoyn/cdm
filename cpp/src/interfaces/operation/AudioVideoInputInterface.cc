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
#include <alljoyn/cdm/interfaces/operation/AudioVideoInputInterface.h>

namespace ajn {
namespace services {

const uint16_t AudioVideoInputInterface::s_interfaceVersion = 1;

// Below none secure xml is only for test
const qcc::String AudioVideoInputInterface::s_xml =
"<node xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='http://www.allseenalliance.org/schemas/introspect.xsd'>"
"    <interface name='org.alljoyn.SmartSpaces.Operation.AudioVideoInput'>"
"        <annotation name='org.alljoyn.Bus.DocString.En' value='This interface provides capabilities to control and monitor audio video input source of device such as TV or SetTopBox.'/>"
"        <annotation name='org.alljoyn.Bus.Secure' value='true'/>"
"        <annotation name='org.alljoyn.Bus.Enum.SourceType.Value.Unknown' value='0'/>"
"        <annotation name='org.alljoyn.Bus.Enum.SourceType.Value.Tuner' value='1'/>"
"        <annotation name='org.alljoyn.Bus.Enum.SourceType.Value.Component' value='2'/>"
"        <annotation name='org.alljoyn.Bus.Enum.SourceType.Value.Composite' value='3'/>"
"        <annotation name='org.alljoyn.Bus.Enum.SourceType.Value.S-VIdeo' value='4'/>"
"        <annotation name='org.alljoyn.Bus.Enum.SourceType.Value.RGB' value='5'/>"
"        <annotation name='org.alljoyn.Bus.Enum.SourceType.Value.SDI' value='6'/>"
"        <annotation name='org.alljoyn.Bus.Enum.SourceType.Value.DVI' value='7'/>"
"        <annotation name='org.alljoyn.Bus.Enum.SourceType.Value.HDMI' value='8'/>"
"        <annotation name='org.alljoyn.Bus.Enum.SourceType.Value.DisplayPort' value='9'/>"
"        <annotation name='org.alljoyn.Bus.Enum.SourceType.Value.SCART' value='10'/>"
"        <annotation name='org.alljoyn.Bus.Enum.SourceType.Value.ExternalStorage' value='11'/>"
"        <annotation name='org.alljoyn.Bus.Enum.SourceType.Value.Network' value='12'/>"
"        <annotation name='org.alljoyn.Bus.Enum.SourceType.Value.Analog' value='13'/>"
"        <annotation name='org.alljoyn.Bus.Enum.SourceType.Value.Phono' value='14'/>"
"        <annotation name='org.alljoyn.Bus.Enum.SourceType.Value.S/PDIF-Coaxial' value='15'/>"
"        <annotation name='org.alljoyn.Bus.Enum.SourceType.Value.S/PDIF-Optical' value='16'/>"
"        <annotation name='org.alljoyn.Bus.Enum.SignalPresence.Value.Unknown' value='0'/>"
"        <annotation name='org.alljoyn.Bus.Enum.SignalPresence.Value.SignalPresent' value='1'/>"
"        <annotation name='org.alljoyn.Bus.Enum.SignalPresence.Value.SignalAbsent' value='2'/>"
"        <annotation name='org.alljoyn.Bus.Struct.InputSource.Field.id.Type' value='q'/>"
"        <annotation name='org.alljoyn.Bus.Struct.InputSource.Field.sourceType.Type' value='[SourceType]'/>"
"        <annotation name='org.alljoyn.Bus.Struct.InputSource.Field.signalPresence.Type' value='[SignalPresence]'/>"
"        <annotation name='org.alljoyn.Bus.Struct.InputSource.Field.portNumber.Type' value='q'/>"
"        <annotation name='org.alljoyn.Bus.Struct.InputSource.Field.friendlyName.Type' value='s'/>"
"        <property name='Version' type='q' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='The interface version.'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='const'/>"
"        </property>"
"        <property name='InputSourceId' type='q' access='readwrite'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Activated input source id.'/>"
"            <annotation name='org.alljoyn.Bus.Type.Name' value='[SourceType]'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"        <property name='SupportedInputSources' type='a(qqyqs)' access='read'>"
"            <annotation name='org.alljoyn.Bus.DocString.En' value='Array of supported input sources.'/>"
"            <annotation name='org.alljoyn.Bus.Type.Name' value='a[InputSource]'/>"
"            <annotation name='org.freedesktop.DBus.Property.EmitsChangedSignal' value='true'/>"
"        </property>"
"    </interface>"
"</node>"
;

const qcc::String AudioVideoInputInterface::s_prop_Version = "Version";
const qcc::String AudioVideoInputInterface::s_prop_InputSourceId = "InputSourceId";
const qcc::String AudioVideoInputInterface::s_prop_SupportedInputSources = "SupportedInputSources";


} //namespace services
} //namespace ajn
