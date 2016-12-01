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
#include <alljoyn/cdm/interfaces/{{InterfaceCategory}}/{{InterfaceName}}Interface.h>

namespace ajn {
namespace services {

const uint16_t {{InterfaceName}}Interface::s_interfaceVersion = 1;

// Below none secure xml is only for test
const qcc::String {{InterfaceName}}Interface::s_xml =
{{InterfaceXML}}
;

{{#properties}}
const qcc::String {{InterfaceName}}Interface::s_prop_{{PropertyName}} = "{{PropertyName}}";
{{/properties}}

{{#methods}}
const qcc::String {{InterfaceName}}Interface::s_method_{{MethodName}} = "{{MethodName}}";
{{/methods}}

{{#signals}}
const qcc::String {{InterfaceName}}Interface::s_signal_{{SignalName}} = "{{SignalName}}";
{{/signals}}

} //namespace services
} //namespace ajn
