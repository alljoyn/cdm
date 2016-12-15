/******************************************************************************
 *  *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#ifndef org_alljoyn_SmartSpaces_Operation_ColorTemperature_H_
#define org_alljoyn_SmartSpaces_Operation_ColorTemperature_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <interfaces/common/operation/ColorTemperatureInterface.h>
#include <interfaces/controller/operation/ColorTemperatureIntfController.h>
#include <interfaces/controller/operation/ColorTemperatureIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_ColorTemperature : public QWidget
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
    class Listener: public ajn::services::ColorTemperatureIntfControllerListener
    {
    public:
        QWidget* m_widget;

        Listener(QWidget* widget)
          : m_widget(widget)
        {
        }

        virtual void OnResponseGetTemperature(QStatus status, const qcc::String& objectPath, const double value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetTemperature", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(double, value)
                              );
        }
        virtual void OnTemperatureChanged(const qcc::String& objectPath, const double value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnTemperatureChanged", Qt::QueuedConnection,
                              Q_ARG(double, value)
                              );
        }
        virtual void OnResponseSetTemperature(QStatus status, const qcc::String& objectPath, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseSetTemperature", Qt::QueuedConnection,
                              Q_ARG(QStatus, status)
                              );
        }
        virtual void OnResponseGetMinTemperature(QStatus status, const qcc::String& objectPath, const double value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetMinTemperature", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(double, value)
                              );
        }
        virtual void OnMinTemperatureChanged(const qcc::String& objectPath, const double value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnMinTemperatureChanged", Qt::QueuedConnection,
                              Q_ARG(double, value)
                              );
        }
        virtual void OnResponseGetMaxTemperature(QStatus status, const qcc::String& objectPath, const double value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetMaxTemperature", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(double, value)
                              );
        }
        virtual void OnMaxTemperatureChanged(const qcc::String& objectPath, const double value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnMaxTemperatureChanged", Qt::QueuedConnection,
                              Q_ARG(double, value)
                              );
        }
    };

private:
    Ref<ajn::services::ColorTemperatureIntfController> controller;
    Ref<Listener> m_listener;


    QLineEdit* edit_Temperature;
    QLineEdit* edit_MinTemperature;
    QLineEdit* edit_MaxTemperature;

    void    fetchProperties();

protected:
    virtual void showEvent(QShowEvent *event) override
    {
        fetchProperties();
    }
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_ColorTemperature_H_ */