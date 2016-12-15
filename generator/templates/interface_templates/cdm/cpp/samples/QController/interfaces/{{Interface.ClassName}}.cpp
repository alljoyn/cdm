/******************************************************************************
 * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#include "{{Interface.ClassName}}.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <sstream>


{% for struc in Interface.Structs %}
template<>
QString
QStringFrom<{{Interface.Name}}Interface::{{struc.Name}}>(const {{Interface.Name}}Interface::{{struc.Name}}& value)
{
    std::ostringstream strm;
    strm << "{";
{% for field in struc.Fields %}
{% if not loop.first %}
    strm << " ";
{% endif %}
    strm << "{{field.Name}}=" << {{field.Type.toMsgArg("value."~field.Name)}};
{% endfor %}
    strm << "}";

    return QString::fromStdString(strm.str());
}


template<>
QString
QStringFrom<std::vector<{{Interface.Name}}Interface::{{struc.Name}}>>(const std::vector<{{Interface.Name}}Interface::{{struc.Name}}>& value)
{
    std::string result;

    for (auto& v : value)
    {
        auto qs = QStringFrom<{{Interface.Name}}Interface::{{struc.Name}}>(v);
        result += qs.toStdString();
    }
    return QString::fromStdString(result);
}



{% endfor %}

{% include ("patch/" ~ Interface.ClassName ~ "_header.cpp") ignore missing with context %}

using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<{{Interface.ClassName}}*>();

{% include ("patch/" ~ Interface.ClassName ~ "_static.cpp") ignore missing with context %}

{{Interface.ClassName}}::{{Interface.ClassName}}(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);


{% for method in Interface.Methods %}
    // Create button for {{method.Name}}
    button_{{method.Name}} = new QPushButton("{{method.Name}}");
{% if "en" in method.doc %}
    button_{{method.Name}}->setToolTip("{{method.doc['en']}}");
{% endif %}
    QObject::connect(button_{{method.Name}}, SIGNAL(clicked()), this, SLOT(slotClick{{method.Name}}()));
    layout->addWidget(button_{{method.Name}});
{% endfor %}

{% for property in Interface.UserProperties %}
    layout->addWidget(new QLabel("{{property.Name}}"));
    // Create line edit for {{property.Name}}
    edit_{{property.Name}} = new QLineEdit();
{% if "en" in property.doc %}
    edit_{{property.Name}}->setToolTip("{{property.doc['en']}}");
{% endif %}
{% if property.Writable %}
    edit_{{property.Name}}->setReadOnly(false);
    QObject::connect(edit_{{property.Name}}, SIGNAL(returnPressed()), this, SLOT(slotSet{{property.Name}}()));
{% else %}
    edit_{{property.Name}}->setReadOnly(true);
{% endif %}
    layout->addWidget(edit_{{property.Name}});
{% endfor %}

    if (iface)
    {
        controller = iface->CreateInterface<{{Interface.Name}}IntfController>(m_listener);
        if (controller)
        {
            fetchProperties();
        }
        else
        {
            qWarning() << __FUNCTION__ << " No interface controller available!";
        }
    }
    else
    {
        qWarning() << __FUNCTION__ << " No interface available!";
    }
}

{{Interface.ClassName}}::~{{Interface.ClassName}}()
{
    qWarning() << __FUNCTION__;
}



void {{Interface.ClassName}}::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "{{Interface.ClassName}} getting properties";
{% for property in Interface.UserProperties %}

        status = controller->Get{{property.Name}}();
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get {{property.Name}}" << QCC_StatusText(status);
        }
{% endfor %}
    }
}
{% for method in Interface.Methods %}



void {{Interface.ClassName}}::slotClick{{method.Name}}()
{
    qWarning() << __FUNCTION__;

    {% for arg in method.input_args() %}
    {{arg.Type.cpptype()}} {{arg.Name.camel_case()}} {};
    {% endfor %}

    {% include ("patch/" ~ Interface.ClassName ~ "-slotClick" ~ method.Name ~ ".cpp") ignore missing with context %}

    QStatus status = controller->{{method.Name}}({% for arg in method.input_args() %}{{arg.Name.camel_case()}}, {% endfor %}NULL);
    if (status != ER_OK)
    {
        qWarning() << __FUNCTION__ << " Failed to call {{method.Name}}" << QCC_StatusText(status);
    }
}
{% endfor %}
{% for property in Interface.UserProperties %}



void {{Interface.ClassName}}::slotOnResponseGet{{property.Name}}(QStatus status, const {{property.Type.cpptype_arg()}} value)
{
    qWarning() << __FUNCTION__;
    edit_{{property.Name}}->setText(QStringFrom(value));
}

void {{Interface.ClassName}}::slotOn{{property.Name}}Changed(const {{property.Type.cpptype_arg()}} value)
{
    qWarning() << __FUNCTION__;
    edit_{{property.Name}}->setText(QStringFrom(value));
}

{% if property.Writable %}
void {{Interface.ClassName}}::slotOnResponseSet{{property.Name}}(QStatus status)
{
    qWarning() << __FUNCTION__;
}

void {{Interface.ClassName}}::slotSet{{property.Name}}()
{
    qWarning() << __FUNCTION__;

    bool ok = false;
    QString str = edit_{{property.Name}}->text();
    {{property.Type.cpptype()}} value = QStringTo<{{property.Type.cpptype()}}>(str, &ok);
    if (ok)
    {
        QStatus status = controller->Set{{property.Name}}(value);
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get {{property.Name}}" << QCC_StatusText(status);
        }
    }
    else
    {
        qWarning() << __FUNCTION__ << "Failed to convert '" << str << "' to {{property.Type.cpptype()}}";
    }
}

{% endif %}
{% endfor %}
{% for method in Interface.Methods %}



void {{Interface.ClassName}}::slotOnResponseMethod{{method.Name}}(QStatus status, const QString& errorName)
{
    if (status == ER_OK)
    {
        qInfo() << "Received response to method {{method.Name}}";
    }
    else
    {
        qWarning() << "Received an error from method {{method.Name}}, error = " << errorName;
    }
}
{% endfor %}
{% for signal in Interface.Signals %}



void {{Interface.ClassName}}::slotOnSignal{{signal.Name}}()
{
        qInfo() << "Received signal {{signal.Name}}";
}
{% endfor %}