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

#ifndef org_alljoyn_SmartSpaces_Operation_CurrentPower_H_
#define org_alljoyn_SmartSpaces_Operation_CurrentPower_H_

#include <QWidget>
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

#include <interfaces/common/operation/CurrentPowerInterface.h>
#include <interfaces/controller/operation/CurrentPowerIntfController.h>
#include <interfaces/controller/operation/CurrentPowerIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;


namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_CurrentPower : public QWidget
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Operation_CurrentPower(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Operation_CurrentPower();

    // Slots mirror the callbacks to avoid threading issues
private slots:

    void slotOnResponseGetCurrentPower(QStatus status, const double value);
    void slotOnCurrentPowerChanged(const double value);
    void slotOnResponseGetPrecision(QStatus status, const double value);
    void slotOnPrecisionChanged(const double value);
    void slotOnResponseGetUpdateMinTime(QStatus status, const uint16_t value);
    void slotOnUpdateMinTimeChanged(const uint16_t value);

public:
    // ajn::services::CurrentPowerIntfControllerListener
    class Listener: public ajn::services::CurrentPowerIntfControllerListener
    {
    public:
        QWidget* m_widget;

        Listener(QWidget* widget)
          : m_widget(widget)
        {
        }

        virtual void OnResponseGetCurrentPower(QStatus status, const qcc::String& objectPath, const double value, void* context) override
        {
            qWarning() << "CurrentPower::OnResponseGetCurrentPower";
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetCurrentPower", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(double, value)
                              );
        }
        virtual void OnCurrentPowerChanged(const qcc::String& objectPath, const double value) override
        {
            qWarning() << "CurrentPower::OnCurrentPowerChanged";
            QMetaObject::invokeMethod(m_widget, "slotOnCurrentPowerChanged", Qt::QueuedConnection,
                              Q_ARG(double, value)
                              );
        }
        virtual void OnResponseGetPrecision(QStatus status, const qcc::String& objectPath, const double value, void* context) override
        {
            qWarning() << "CurrentPower::OnResponseGetPrecision";
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetPrecision", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(double, value)
                              );
        }
        virtual void OnPrecisionChanged(const qcc::String& objectPath, const double value) override
        {
            qWarning() << "CurrentPower::OnPrecisionChanged";
            QMetaObject::invokeMethod(m_widget, "slotOnPrecisionChanged", Qt::QueuedConnection,
                              Q_ARG(double, value)
                              );
        }
        virtual void OnResponseGetUpdateMinTime(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context) override
        {
            qWarning() << "CurrentPower::OnResponseGetUpdateMinTime";
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetUpdateMinTime", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(uint16_t, value)
                              );
        }
        virtual void OnUpdateMinTimeChanged(const qcc::String& objectPath, const uint16_t value) override
        {
            qWarning() << "CurrentPower::OnUpdateMinTimeChanged";
            QMetaObject::invokeMethod(m_widget, "slotOnUpdateMinTimeChanged", Qt::QueuedConnection,
                              Q_ARG(uint16_t, value)
                              );
        }
    };

private:
    Ref<ajn::services::CurrentPowerIntfController> controller;
    Ref<Listener> m_listener;


    QLabel* edit_CurrentPower;
    QLabel* edit_Precision;
    QLabel* edit_UpdateMinTime;

    QLabel* messages_;
    void    fetchProperties();

protected:
    virtual void showEvent(QShowEvent *event) override
    {
        fetchProperties();
    }
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_CurrentPower_H_ */
