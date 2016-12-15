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

#ifndef org_alljoyn_SmartSpaces_Environment_CurrentTemperature_H_
#define org_alljoyn_SmartSpaces_Environment_CurrentTemperature_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <interfaces/common/environment/CurrentTemperatureInterface.h>
#include <interfaces/controller/environment/CurrentTemperatureIntfController.h>
#include <interfaces/controller/environment/CurrentTemperatureIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Environment_CurrentTemperature : public QWidget
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Environment_CurrentTemperature(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Environment_CurrentTemperature();

    // Slots mirror the callbacks to avoid threading issues
private slots:

    void slotOnResponseGetCurrentValue(QStatus status, const double value);
    void slotOnCurrentValueChanged(const double value);
    void slotOnResponseGetPrecision(QStatus status, const double value);
    void slotOnPrecisionChanged(const double value);
    void slotOnResponseGetUpdateMinTime(QStatus status, const uint16_t value);
    void slotOnUpdateMinTimeChanged(const uint16_t value);

public:
    // ajn::services::CurrentTemperatureIntfControllerListener
    class Listener: public ajn::services::CurrentTemperatureIntfControllerListener
    {
    public:
        QWidget* m_widget;

        Listener(QWidget* widget)
          : m_widget(widget)
        {
        }

        virtual void OnResponseGetCurrentValue(QStatus status, const qcc::String& objectPath, const double value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetCurrentValue", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(double, value)
                              );
        }
        virtual void OnCurrentValueChanged(const qcc::String& objectPath, const double value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnCurrentValueChanged", Qt::QueuedConnection,
                              Q_ARG(double, value)
                              );
        }
        virtual void OnResponseGetPrecision(QStatus status, const qcc::String& objectPath, const double value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetPrecision", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(double, value)
                              );
        }
        virtual void OnPrecisionChanged(const qcc::String& objectPath, const double value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnPrecisionChanged", Qt::QueuedConnection,
                              Q_ARG(double, value)
                              );
        }
        virtual void OnResponseGetUpdateMinTime(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetUpdateMinTime", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(uint16_t, value)
                              );
        }
        virtual void OnUpdateMinTimeChanged(const qcc::String& objectPath, const uint16_t value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnUpdateMinTimeChanged", Qt::QueuedConnection,
                              Q_ARG(uint16_t, value)
                              );
        }
    };

private:
    Ref<ajn::services::CurrentTemperatureIntfController> controller;
    Ref<Listener> m_listener;


    QLineEdit* edit_CurrentValue;
    QLineEdit* edit_Precision;
    QLineEdit* edit_UpdateMinTime;

    void    fetchProperties();

protected:
    virtual void showEvent(QShowEvent *event) override
    {
        fetchProperties();
    }
};

}

#endif /* org_alljoyn_SmartSpaces_Environment_CurrentTemperature_H_ */