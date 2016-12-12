////////////////////////////////////////////////////////////////////////////////
// Copyright AllSeen Alliance. All rights reserved.
//
//    Permission to use, copy, modify, and/or distribute this software for any
//    purpose with or without fee is hereby granted, provided that the above
//    copyright notice and this permission notice appear in all copies.
//
//    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
//    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
//    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
//    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
//    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
//    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
//    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#import "{{Interface.Name}}Listener.h"
#import "{{Interface.Name}}ViewController.h"
#import "CDMUtil.h"

{{Interface.Name}}Listener::{{Interface.Name}}Listener({{Interface.Name}}ViewController *viewController):viewController(viewController)
{
    
}

{{Interface.Name}}Listener::~{{Interface.Name}}Listener()
{
    
}

{% for property in Interface.UserProperties %}
void {{Interface.Name}}Listener::Update{{property.Name}}(const {{property.Type.cpptype_arg()}} value)
{
    {% if property.is_selector() %}
    [viewController set{{property.Name}}:value];
    {% else %}
    {% if property.Type.is_array() %}
    NSString *valueArrayAsString = @"";
    {{property.Type.cpptype()}}::const_iterator it = value.begin();
    while(it != value.end()) {
        valueArrayAsString = [valueArrayAsString stringByAppendingString:[NSString stringWithFormat:@"%{{property.Type.objc_format_str()}},", {% if property.is_bool() %}[CDMUtil boolToNSString:*it]{% else %}*it{% endif %}]];
        ++it;
    }
    NSLog(@"Got {{property.Name}}: %@", valueArrayAsString);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.{{property.Name.camel_case()}}Cell.value.text = [NSString stringWithFormat:@"%@", valueArrayAsString];
    });
    {% else %}
    NSString *valueAsStr = [NSString stringWithFormat:@"%{{property.Type.objc_format_str()}}", {% if property.is_bool() %}[CDMUtil boolToNSString:value]{% elif property.is_string() %}value.c_str(){% else %}value{% endif %}];
    NSLog(@"Got {{property.Name}}: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.{{property.Name.camel_case()}}Cell.value.text = valueAsStr;
    });
    {% endif %}
    {% endif %}
}

void {{Interface.Name}}Listener::OnResponseGet{{property.Name}}(QStatus status, const qcc::String& objectPath, const {{property.Type.cpptype_arg()}} value, void* context)
{
    Update{{property.Name}}(value);
}

{% if property.EmitsChangedSignal %}
void {{Interface.Name}}Listener::On{{property.Name}}Changed(const qcc::String& objectPath, const {{property.Type.cpptype_arg()}} value)
{
    Update{{property.Name}}(value);
}
{% endif %}

{% if property.Writable %}
void {{Interface.Name}}Listener::OnResponseSet{{property.Name}}(QStatus status, const qcc::String& objectPath, void* context)
{
    if(status == ER_OK){
        NSLog(@"Set{{property.Name}}: succeeded");
    }else {
        NSLog(@"Set{{property.Name}}: failed");
    }
}
{% endif %}

{% endfor %}
{% for method in Interface.Methods %}
void {{Interface.Name}}Listener::OnResponse{{method.Name}}(QStatus status, const qcc::String& objectPath, {% for arg in method.output_args() %}const {{arg.Type.cpptype_arg()}} {{arg.Name.camel_case()}}, {% endfor %}void* context, const char* errorName, const char* errorMessage)
{
    {% if method.output_args() %}
    if(status == ER_OK) {
        {% if method.output_arg().Type.is_array() %}
        NSLog(@"{{method.Name}} succeeded");
        NSString *builtArgResponseStr = @"";
        {{method.output_arg().Type.cpptype()}}::const_iterator it;
        for(it = {{method.output_arg().Name}}.begin(); it != {{method.output_arg().Name}}.end(); ++it) {
            NSString *line = @""; // TODO: Replace with string representation of object
            builtArgResponseStr = [builtArgResponseStr stringByAppendingString:line];
        }
        dispatch_async(dispatch_get_main_queue(), ^{
            viewController.{{method.Name.camel_case()}}OutputCell.output.text = builtArgResponseStr;
        });
        {% else %}
        NSString *outputArgAsStr = [NSString stringWithFormat:@"%{{method.output_arg().Type.objc_format_str()}}", {% if method.output_arg().is_bool() %}[CDMUtil boolToNSString:{{arg.Name.camel_case()}}]{% elif method.output_arg().is_string() %}{{arg.Name.camel_case()}}.c_str(){% else %}{{arg.Name.camel_case()}}{% endif %}];
        dispatch_async(dispatch_get_main_queue(), ^{
            viewController.{{method.Name.camel_case()}}OutputCell.output.text = outputArgAsStr;
        });
        {% endif %}
    } else {
        NSLog(@"GetChannelList failed");
    }
    {% else %}
    if (status == ER_OK) {
        NSLog(@"{{method.Name}} succeeded");
    } else {
        NSLog(@"{{method.Name}} failed");
    }
    {% endif %}
}

{% endfor %}
{% for signal in Interface.Signals %}
void {{Interface.Name}}Listener::On{{signal.Name}}(const qcc::String& objectPath)
{
    // TODO: Implement on signal logic
}
{% endfor %}