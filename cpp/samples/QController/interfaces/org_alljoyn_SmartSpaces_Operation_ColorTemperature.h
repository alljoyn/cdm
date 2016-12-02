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

#ifndef org_alljoyn_SmartSpaces_Operation_ColorTemperature_H_
#define org_alljoyn_SmartSpaces_Operation_ColorTemperature_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <alljoyn/cdm/interfaces/operation/ColorTemperatureInterface.h>
#include <alljoyn/cdm/interfaces/operation/ColorTemperatureIntfController.h>
#include <alljoyn/cdm/interfaces/operation/ColorTemperatureIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_ColorTemperature : public QWidget, public ajn::services::ColorTemperatureIntfControllerListener
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Operation_ColorTemperature(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Operation_ColorTemperature();

    // Slots mirror the callbacks to avoid threading issues
private slots:

    void slotOnResponseGetTemperature(QStatus status, const double value);
    void slotOnTemperatureChanged(const double value);
    void slotOnResponseSetTemperature(QStatus status);
    void slotSetTemperature();
    void slotOnResponseGetMinTemperature(QStatus status, const double value);
    void slotOnMinTemperatureChanged(const double value);
    void slotOnResponseGetMaxTemperature(QStatus status, const double value);
    void slotOnMaxTemperatureChanged(const double value);

public:
    // ajn::services::ColorTemperatureIntfControllerListener
    void OnResponseGetTemperature(QStatus status, const qcc::String& objectPath, const double value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetTemperature", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(double, value)
                          );
    }
    void OnTemperatureChanged(const qcc::String& objectPath, const double value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnTemperatureChanged", Qt::QueuedConnection,
                          Q_ARG(double, value)
                          );
    }
    void OnResponseSetTemperature(QStatus status, const qcc::String& objectPath, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseSetTemperature", Qt::QueuedConnection,
                          Q_ARG(QStatus, status)
                          );
    }
    void OnResponseGetMinTemperature(QStatus status, const qcc::String& objectPath, const double value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetMinTemperature", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(double, value)
                          );
    }
    void OnMinTemperatureChanged(const qcc::String& objectPath, const double value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnMinTemperatureChanged", Qt::QueuedConnection,
                          Q_ARG(double, value)
                          );
    }
    void OnResponseGetMaxTemperature(QStatus status, const qcc::String& objectPath, const double value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetMaxTemperature", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(double, value)
                          );
    }
    void OnMaxTemperatureChanged(const qcc::String& objectPath, const double value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnMaxTemperatureChanged", Qt::QueuedConnection,
                          Q_ARG(double, value)
                          );
    }

private:
    ajn::services::ColorTemperatureIntfControllerPtr controller;


    QLineEdit* edit_Temperature;
    QLineEdit* edit_MinTemperature;
    QLineEdit* edit_MaxTemperature;
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_ColorTemperature_H_ */
