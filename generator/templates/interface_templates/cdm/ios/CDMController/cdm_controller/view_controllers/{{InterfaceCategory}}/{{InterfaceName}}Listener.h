////////////////////////////////////////////////////////////////////////////////
// // Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
//    Source Project (AJOSP) Contributors and others.
//
//    SPDX-License-Identifier: Apache-2.0
//
//    All rights reserved. This program and the accompanying materials are
//    made available under the terms of the Apache License, Version 2.0
//    which accompanies this distribution, and is available at
//    http://www.apache.org/licenses/LICENSE-2.0
//
//    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
//    Alliance. All rights reserved.
//
//    Permission to use, copy, modify, and/or distribute this software for
//    any purpose with or without fee is hereby granted, provided that the
//    above copyright notice and this permission notice appear in all
//    copies.
//
//     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
//     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
//     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
//     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
//     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
//     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
//     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
//     PERFORMANCE OF THIS SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#ifndef {{Interface.Name}}Listener_h
#define {{Interface.Name}}Listener_h

#import "{{Interface.Name}}ViewController.h"
#import "alljoyn/cdm/interfaces/{{Interface.Category}}/{{Interface.Name}}Interface.h"
#import "alljoyn/cdm/interfaces/{{Interface.Category}}/{{Interface.Name}}IntfControllerListener.h"

class {{Interface.Name}}Listener : public ajn::services::{{Interface.Name}}IntfControllerListener
{
    public:
        {{Interface.Name}}Listener({{Interface.Name}}ViewController *viewController);
    
        virtual ~{{Interface.Name}}Listener();

        {% for property in Interface.UserProperties %}
        virtual void Update{{property.Name}}(const {{property.Type.cpptype_arg()}} value);
        virtual void OnResponseGet{{property.Name}}(QStatus status, const qcc::String& objectPath, const {{property.Type.cpptype_arg()}} value, void* context);
        {% if property.EmitsChangedSignal %}
        virtual void On{{property.Name}}Changed(const qcc::String& objectPath, const {{property.Type.cpptype_arg()}} value);
        {% endif %}
        {% if property.Writable %}
        virtual void OnResponseSet{{property.Name}}(QStatus status, const qcc::String& objectPath, void* context);
        {% endif %}

        {% endfor %}
        {% for method in Interface.Methods %}
        virtual void OnResponse{{method.Name}}(QStatus status, const qcc::String& objectPath, {% for arg in method.output_args() %}const {{arg.Type.cpptype_arg()}} {{arg.Name.camel_case()}}, {% endfor %}void* context, const char* errorName, const char* errorMessage);
        {% endfor %}
        
        {% for signal in Interface.Signals %}
        virtual void On{{signal.Name}}(const qcc::String& objectPath);
        {% endfor %}

    private:
        {{Interface.Name}}ViewController *viewController;
};

#endif /* {{Interface.Name}}Listener_h */