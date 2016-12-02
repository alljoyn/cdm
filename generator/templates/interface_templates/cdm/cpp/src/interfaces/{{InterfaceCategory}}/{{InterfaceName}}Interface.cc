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
#include <alljoyn/cdm/interfaces/{{Interface.Category}}/{{Interface.Name}}Interface.h>

namespace ajn {
namespace services {

const char* const {{Interface.Name}}Interface::INTERFACE_NAME = "{{Interface.FullName}}";
const CdmInterfaceType {{Interface.Name}}Interface::INTERFACE_TYPE = {{Interface.Name.upper_snake()}}_INTERFACE;


const uint16_t {{Interface.Name}}Interface::s_interfaceVersion = 1;

const qcc::String {{Interface.Name}}Interface::s_xml =
{{Interface.XML}}
;

{% for property in Interface.Properties %}
const qcc::String {{Interface.Name}}Interface::s_prop_{{property.Name}} = "{{property.Name}}";
{% endfor %}
{% for method in Interface.Methods %}
const qcc::String {{Interface.Name}}Interface::s_method_{{method.Name}} = "{{method.Name}}";
{% endfor %}
{% for signal in Interface.Signals %}
const qcc::String {{Interface.Name}}Interface::s_signal_{{signal.Name}} = "{{signal.Name}}";
{% endfor %}

} //namespace services
} //namespace ajn
