/******************************************************************************
 *  * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#ifndef {{Interface.ClassName}}_H_
#define {{Interface.ClassName}}_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <interfaces/common/{{Interface.Category}}/{{Interface.Name}}Interface.h>
#include <interfaces/controller/{{Interface.Category}}/{{Interface.Name}}IntfController.h>
#include <interfaces/controller/{{Interface.Category}}/{{Interface.Name}}IntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class {{Interface.ClassName}} : public QWidget
{
    Q_OBJECT
public:
    Q_INVOKABLE {{Interface.ClassName}}(CommonControllerInterface *iface=NULL);
    ~{{Interface.ClassName}}();

    // Slots mirror the callbacks to avoid threading issues
private slots:
{% for method in Interface.Methods %}
    void slotClick{{method.Name}}();
{% endfor %}

{% for property in Interface.UserProperties %}
    void slotOnResponseGet{{property.Name}}(QStatus status, const {{property.Type.cpptype_arg()}} value);
    void slotOn{{property.Name}}Changed(const {{property.Type.cpptype_arg()}} value);
{% if property.Writable %}
    void slotOnResponseSet{{property.Name}}(QStatus status);
    void slotSet{{property.Name}}();
{% endif %}
{% endfor %}
{% for method in Interface.Methods %}
    void slotOnResponseMethod{{method.Name}}(QStatus status, const QString& errorName);
{% endfor %}
{% for signal in Interface.Signals %}
    void slotOnSignal{{signal.Name}}();
{% endfor %}

public:
    // ajn::services::{{InterfaceName}}IntfControllerListener
    class Listener: public ajn::services::{{Interface.Name}}IntfControllerListener
    {
    public:
        QWidget* m_widget;

        Listener(QWidget* widget)
          : m_widget(widget)
        {
        }

{% for property in Interface.UserProperties %}
        virtual void OnResponseGet{{property.Name}}(QStatus status, const qcc::String& objectPath, const {{property.Type.cpptype_arg()}} value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGet{{property.Name}}", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG({{property.Type.cpptype()}}, value)
                              );
        }
        virtual void On{{property.Name}}Changed(const qcc::String& objectPath, const {{property.Type.cpptype_arg()}} value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOn{{property.Name}}Changed", Qt::QueuedConnection,
                              Q_ARG({{property.Type.cpptype()}}, value)
                              );
        }
{% if property.Writable %}
        virtual void OnResponseSet{{property.Name}}(QStatus status, const qcc::String& objectPath, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseSet{{property.Name}}", Qt::QueuedConnection,
                              Q_ARG(QStatus, status)
                              );
        }
{% endif %}
{% endfor %}
{% for method in Interface.Methods %}
        virtual void OnResponse{{method.Name}}(QStatus status, const qcc::String& objectPath, {% for arg in method.output_args() %}const {{arg.Type.cpptype_arg()}} {{arg.Name.camel_case()}}, {% endfor %}void* context, const char* errorName, const char* errorMessage) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseMethod{{method.Name}}", Qt::QueuedConnection,
                              Q_ARG(QStatus, status), Q_ARG(QString, QString(errorName))
                              );
        }
{% endfor %}
{% for signal in Interface.Signals %}
        virtual void On{{signal.Name}}(const qcc::String& objectPath) override
        {
            QMetaObject::invokeMethod(m_widget, "slotOnSignal{{signal.Name}}", Qt::QueuedConnection);
        }
{% endfor %}
    };

private:
    Ref<ajn::services::{{InterfaceName}}IntfController> controller;
    Ref<Listener> m_listener;

    {% for method in Interface.Methods %}
    QPushButton* button_{{method.Name}};
    {% endfor %}

    {% for property in Interface.UserProperties %}
    QLineEdit* edit_{{property.Name}};
    {% endfor %}

    void    fetchProperties();

protected:
    virtual void showEvent(QShowEvent *event) override
    {
        fetchProperties();
    }
};

}

#endif /* {{Interface.ClassName}}_H_ */