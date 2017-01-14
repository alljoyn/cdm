/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
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
{% import "macros" as macros with context %}
#include "{{Interface.ClassName}}.h"
#include "qcUtils.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <sstream>

{% for struc in Interface.Structs %}


template<>
QString
QStringFrom<{{Interface.Name}}Interface::{{struc.Name}}>(const {{Interface.Name}}Interface::{{struc.Name}}& value)
{
    // the QLabel is AutoFmt 
    std::ostringstream strm;

{% for field in struc.Fields %}
    strm << "<b>{{field.Name}}</b>: " << {{field.Type.toMsgArg("value."~field.Name)}} << "\n";
{% endfor %}

    return QString::fromStdString(strm.str());
}


template<>
QString
QStringFrom<std::vector<{{Interface.Name}}Interface::{{struc.Name}}>>(const std::vector<{{Interface.Name}}Interface::{{struc.Name}}>& value)
{
    // the QLabel is AutoFmt 
    std::ostringstream strm;

    strm << "<html><body>";
    strm << "<table><thead><tr>";
{% for field in struc.Fields %}
    strm << "<th bgcolor=\"light blue\">{{field.Name}}</th>";
{% endfor %}
    strm << "</tr></thead>";

    for (auto& v : value)
    {
        strm << "<tr>";
{% for field in struc.Fields %}
        strm << "<td>" << {{field.Type.toStreamArg("v."~field.Name)}} << "</td>";
{% endfor %}
        strm << "</tr>";
    }

    strm << "</table></body></html>";
    return QString::fromStdString(strm.str());
}
{% endfor %}
{% for enum in Interface.Enums %}


template<>
QString
QStringFrom<{{Interface.Name}}Interface::{{enum.Name}}>(const {{Interface.Name}}Interface::{{enum.Name}}& value)
{
    QString result;

    switch (value)
    {
{% for item in enum.Values %}
    case {{Interface.Name ~ "Interface::" ~ macros.enumName(enum, item)}}:
        result = "{{item.Name}}";
        break;

{% endfor %}
    default:
        result = "Unknown";
        break;
    }

    return result;
}



template<>
QString
QStringFrom<std::vector<{{Interface.Name}}Interface::{{enum.Name}}>>(const std::vector<{{Interface.Name}}Interface::{{enum.Name}}>& value)
{
    // the QLabel is AutoFmt 
    std::ostringstream strm;

    strm << "<html><body>";
    strm << "<table><thead><tr>";
    strm << "<th bgcolor=\"light blue\">{{enum.Name}}</th>";
    strm << "</tr></thead>";

    for (auto& v : value)
    {
{% for item in enum.Values %}
        if (v == {{Interface.Name ~ "Interface::" ~ macros.enumName(enum, item)}})
        {
            strm << "<tr><td>{{item.Name}}</td></tr>";
        }
{% endfor %}
    }

    strm << "</table></body></html>";
    return QString::fromStdString(strm.str());
}
{% endfor %}

{% include ("patch/" ~ Interface.ClassName ~ "-header.cpp") ignore missing with context %}

using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<{{Interface.ClassName}}*>();
{% for struc in Interface.Structs %}

Q_DECLARE_METATYPE(ajn::services::{{Interface.Name}}Interface::{{struc.Name}});
Q_DECLARE_METATYPE(std::vector<ajn::services::{{Interface.Name}}Interface::{{struc.Name}}>);
static const int auto_register_struct_{{struc.Name}} = qRegisterMetaType<ajn::services::{{Interface.Name}}Interface::{{struc.Name}}>("{{Interface.Name}}Interface::{{struc.Name}}");
static const int auto_register_struct_v_{{struc.Name}} = qRegisterMetaType<std::vector<ajn::services::{{Interface.Name}}Interface::{{struc.Name}}>>("std::vector<{{Interface.Name}}Interface::{{struc.Name}}>");
{% endfor %}
{% for enum in Interface.Enums %}

Q_DECLARE_METATYPE(ajn::services::{{Interface.Name}}Interface::{{enum.Name}});
Q_DECLARE_METATYPE(std::vector<ajn::services::{{Interface.Name}}Interface::{{enum.Name}}>);
static const int auto_register_enum_{{enum.Name}} = qRegisterMetaType<ajn::services::{{Interface.Name}}Interface::{{enum.Name}}>("{{Interface.Name}}Interface::{{enum.Name}}");
static const int auto_register_enum_v_{{enum.Name}} = qRegisterMetaType<std::vector<ajn::services::{{Interface.Name}}Interface::{{enum.Name}}>>("std::vector<{{Interface.Name}}Interface::{{enum.Name}}>");
{% endfor %}


{% include ("patch/" ~ Interface.ClassName ~ "-static.cpp") ignore missing with context %}

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
    layout->addWidget(new QLabel("<b>{{property.Name}}</b>"));
    // Create the editing widget for {{property.Name}}
{% if property.Type.ajtype() == "bool" %}
    {# ==================================== #}
    {# Use a checkbox for bool properties #}
    edit_{{property.Name}} = new QCheckBox();
{% if property.Writable %}
    edit_{{property.Name}}->setEnabled(true);
    QObject::connect(edit_{{property.Name}}, SIGNAL(stateChanged(int)), this, SLOT(slotSet{{property.Name}}()));
{% else %}
    edit_{{property.Name}}->setEnabled(false);
{% endif %}
{% elif property.Type.ajtypeIsEnum() %}
    {# ==================================== #}
    {# A combo box for enums #}
{%     set enum = property.Type.ajtypeIsEnum() %}
    edit_{{property.Name}} = new QComboBox();
    edit_{{property.Name}}->setEditable(false);
{%     for item in enum.Values %}
    edit_{{property.Name}}->addItem("{{item.Name}}");
{%     endfor %}
{%     if property.Writable %}
    edit_{{property.Name}}->setEnabled(true);
    QObject::connect(edit_{{property.Name}}, SIGNAL(currentTextChanged(const QString &)), this, SLOT(slotSet{{property.Name}}()));
{%     else %}
    edit_{{property.Name}}->setEnabled(false);
{%     endif %}
{% else %}
    {# ==================================== #}
    {# Default to a simple line edit or label widget #}
{% if property.Writable %}
    edit_{{property.Name}} = new QLineEdit();
{%  if "en" in property.doc %}
    edit_{{property.Name}}->setToolTip("{{property.doc['en']}}");
{%  endif %}
    QObject::connect(edit_{{property.Name}}, SIGNAL(returnPressed()), this, SLOT(slotSet{{property.Name}}()));
{% else %}
    edit_{{property.Name}} = new QLabel();
{% endif %}
{% endif %}{# end of the branch on property type to decide the widget #}

    layout->addWidget(edit_{{property.Name}});
{% endfor %}

    messages_ = new QLabel();
    layout->addWidget(messages_);

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
        qWarning() << "{{Interface.Name}} getting properties";
{% for property in Interface.UserProperties %}

        status = controller->Get{{property.Name}}();
        if (status != ER_OK)
        {
            qWarning() << "{{Interface.Name}}::fetchProperties Failed to get {{property.Name}}" << QCC_StatusText(status);
        }
{% endfor %}
    }
}
{% for method in Interface.Methods %}



void {{Interface.ClassName}}::slotClick{{method.Name}}()
{
    qWarning() << "{{Interface.Name}}::slotClick{{method.Name}}";

    {% for arg in method.input_args() %}
    {{arg.Type.cpptype()}} {{arg.Name.camel_case()}} {};
    {% endfor %}

    bool ok = true;
    {% include ("patch/" ~ Interface.ClassName ~ "-slotClick" ~ method.Name ~ ".cpp") ignore missing with context %}

    if (ok)
    {
        QStatus status = controller->{{method.Name}}({% for arg in method.input_args() %}{{arg.Name.camel_case()}}, {% endfor %}NULL);
        if (status != ER_OK)
        {
            qWarning() << "{{Interface.Name}}::slotClick Failed to call {{method.Name}}" << QCC_StatusText(status);
        }
    }
}
{% endfor %}
{% for property in Interface.UserProperties %}



void {{Interface.ClassName}}::slotOnResponseGet{{property.Name}}(QStatus status, const {{property.Type.cpptype_arg()}} value)
{
    qWarning() << "{{Interface.Name}}::slotOnResponseGet{{property.Name}}";

{% if property.Type.ajtype() == "bool" %}
    edit_{{property.Name}}->setChecked(value);
{% elif property.Type.ajtypeIsEnum() %}
{% set enum = property.Type.ajtypeIsEnum() %}
    switch (value)
    {
{% for item in enum.Values %}
    case {{Interface.Name ~ "Interface::" ~ macros.enumName(enum, item)}}:
        edit_{{property.Name}}->setCurrentText("{{item.Name}}");
        break;

{% endfor %}
    default:
        edit_{{property.Name}}->setCurrentText("");
        break;
    }
{% else %}
    edit_{{property.Name}}->setText(QStringFrom(value));
{% endif %}
}



void {{Interface.ClassName}}::slotOn{{property.Name}}Changed(const {{property.Type.cpptype_arg()}} value)
{
    qWarning() << "{{Interface.Name}}::slotOn{{property.Name}}Changed";

{% if property.Type.ajtype() == "bool" %}
    edit_{{property.Name}}->setChecked(value);
{% elif property.Type.ajtypeIsEnum() %}
{% set enum = property.Type.ajtypeIsEnum() %}
    switch (value)
    {
{% for item in enum.Values %}
    case {{Interface.Name ~ "Interface::" ~ macros.enumName(enum, item)}}:
        edit_{{property.Name}}->setCurrentText("{{item.Name}}");
        break;

{% endfor %}
    default:
        edit_{{property.Name}}->setCurrentText("");
        break;
    }
{% else %}
    edit_{{property.Name}}->setText(QStringFrom(value));
{% endif %}
}



{% if property.Writable %}
void {{Interface.ClassName}}::slotOnResponseSet{{property.Name}}(QStatus status)
{
    qWarning() << "{{Interface.Name}}::slotOnResponseSet{{property.Name}}";

    if (status != ER_OK)
    {
        qcShowStatus(this, "Failed to set {{property.Name}}", status);
        qWarning() << "{{Interface.Name}}::slotOnResponseSet{{property.Name}} Failed to set {{property.Name}}" << QCC_StatusText(status);
        fetchProperties();      // restore the display of properties
    }
}



void {{Interface.ClassName}}::slotSet{{property.Name}}()
{
    qWarning() << "{{Interface.Name}}::slotSet{{property.Name}}";

    bool ok = false;
    {{property.Type.cpptype()}} value;
{% if property.Type.ajtype() == "bool" %}
    value = edit_{{property.Name}}->isChecked();
    ok = true;
{% elif property.Type.ajtypeIsEnum() %}
{% set enum = property.Type.ajtypeIsEnum() %}
    QString str = edit_{{property.Name}}->currentText();
{%     for item in enum.Values %}
    if (str == "{{item.Name}}")
    {
        value = {{Interface.Name ~ "Interface::" ~ macros.enumName(enum, item)}};
        ok = true;
    }
    else
{%     endfor %}
    if (!str.isEmpty())
    {
        qWarning() << "{{Interface.Name}}::slotSet{{property.Name}} Failed to convert '" << str.constData() << "' to {{property.Type.cpptype()}}";
    }
{% else %}
    QString str = edit_{{property.Name}}->text();
    value = QStringTo<{{property.Type.cpptype()}}>(str, &ok);
    if (!ok)
    {
        qWarning() << "{{Interface.Name}}::slotSet{{property.Name}} Failed to convert '" << str << "' to {{property.Type.cpptype()}}";
    }
{% endif %}

    if (ok)
    {
        QStatus status = controller->Set{{property.Name}}(value);

        if (status != ER_OK)
        {
            qWarning() << "{{Interface.Name}}::slotSet{{property.Name}} Failed to get {{property.Name}}" << QCC_StatusText(status);
        }
    }
}
{% endif %}
{% endfor %}
{% for method in Interface.Methods %}



void {{Interface.ClassName}}::slotOnResponseMethod{{method.Name}}(QStatus status
        {%- for arg in method.output_args() %}, const {{arg.Type.cpptype_arg()}} {{arg.Name.camel_case()}}{% endfor -%}
        , const QString& errorName)
{
    if (status == ER_OK)
    {
        qInfo() << "{{Interface.Name}}::slotOnResponseMethod{{method.Name}}";
    }
    else
    {
        qWarning() << "{{Interface.Name}}::slotOnResponseMethod{{method.Name}} Received error = " << errorName;
    }
    {% include ("patch/" ~ Interface.ClassName ~ "-slotOnResponseMethod" ~ method.Name ~ ".cpp") ignore missing with context %}
}
{% endfor %}
{% for signal in Interface.Signals %}



void {{Interface.ClassName}}::slotOnSignal{{signal.Name}}()
{
        qInfo() << "Received signal {{signal.Name}}";
}
{% endfor %}
