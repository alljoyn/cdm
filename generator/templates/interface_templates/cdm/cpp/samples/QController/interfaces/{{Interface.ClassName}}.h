/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
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

#ifndef {{Interface.ClassName}}_H_
#define {{Interface.ClassName}}_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <alljoyn/cdm/interfaces/{{Interface.Category}}/{{Interface.Name}}Interface.h>
#include <alljoyn/cdm/interfaces/{{Interface.Category}}/{{Interface.Name}}IntfController.h>
#include <alljoyn/cdm/interfaces/{{Interface.Category}}/{{Interface.Name}}IntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class {{Interface.ClassName}} : public QWidget, public ajn::services::{{Interface.Name}}IntfControllerListener
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
    void slotOnResponseGet{{property.Name}}(QStatus status, const {{property.Type.ctype_arg()}} value);
    void slotOn{{property.Name}}Changed(const {{property.Type.ctype_arg()}} value);
    {% if property.Writable %}
    void slotOnResponseSet{{property.Name}}(QStatus status);
    void slotSet{{property.Name}}();
    {% endif %}
    {% endfor %}

public:
    // ajn::services::{{InterfaceName}}IntfControllerListener
    {% for property in Interface.UserProperties %}
    void OnResponseGet{{property.Name}}(QStatus status, const qcc::String& objectPath, const {{property.Type.ctype_arg()}} value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGet{{property.Name}}", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG({{property.Type.ctype()}}, value)
                          );
    }
    void On{{property.Name}}Changed(const qcc::String& objectPath, const {{property.Type.ctype_arg()}} value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOn{{property.Name}}Changed", Qt::QueuedConnection,
                          Q_ARG({{property.Type.ctype()}}, value)
                          );
    }
    {% if property.Writable %}
    void OnResponseSet{{property.Name}}(QStatus status, const qcc::String& objectPath, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseSet{{property.Name}}", Qt::QueuedConnection,
                          Q_ARG(QStatus, status)
                          );
    }
    {% endif %}
    {% endfor %}

private:
    ajn::services::{{InterfaceName}}IntfControllerPtr controller;

    {% for method in Interface.Methods %}
    QPushButton* button_{{method.Name}};
    {% endfor %}

    {% for property in Interface.UserProperties %}
    QLineEdit* edit_{{property.Name}};
    {% endfor %}
};

}

#endif /* {{Interface.ClassName}}_H_ */
