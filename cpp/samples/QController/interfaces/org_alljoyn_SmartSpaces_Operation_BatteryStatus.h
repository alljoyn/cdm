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

#ifndef org_alljoyn_SmartSpaces_Operation_BatteryStatus_H_
#define org_alljoyn_SmartSpaces_Operation_BatteryStatus_H_

#include <QWidget>
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

#include <interfaces/common/operation/BatteryStatusInterface.h>
#include <interfaces/controller/operation/BatteryStatusIntfController.h>
#include <interfaces/controller/operation/BatteryStatusIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;


namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_BatteryStatus : public QWidget
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Operation_BatteryStatus(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Operation_BatteryStatus();

    // Slots mirror the callbacks to avoid threading issues
private slots:

    void slotOnResponseGetCurrentValue(QStatus status, const uint8_t value);
    void slotOnCurrentValueChanged(const uint8_t value);
    void slotOnResponseGetIsCharging(QStatus status, const bool value);
    void slotOnIsChargingChanged(const bool value);

public:
    // ajn::services::BatteryStatusIntfControllerListener
    class Listener: public ajn::services::BatteryStatusIntfControllerListener
    {
    public:
        QWidget* m_widget;

        Listener(QWidget* widget)
          : m_widget(widget)
        {
        }

        virtual void OnResponseGetCurrentValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) override
        {
            qWarning() << "BatteryStatus::OnResponseGetCurrentValue";
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetCurrentValue", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(uint8_t, value)
                              );
        }
        virtual void OnCurrentValueChanged(const qcc::String& objectPath, const uint8_t value) override
        {
            qWarning() << "BatteryStatus::OnCurrentValueChanged";
            QMetaObject::invokeMethod(m_widget, "slotOnCurrentValueChanged", Qt::QueuedConnection,
                              Q_ARG(uint8_t, value)
                              );
        }
        virtual void OnResponseGetIsCharging(QStatus status, const qcc::String& objectPath, const bool value, void* context) override
        {
            qWarning() << "BatteryStatus::OnResponseGetIsCharging";
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetIsCharging", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(bool, value)
                              );
        }
        virtual void OnIsChargingChanged(const qcc::String& objectPath, const bool value) override
        {
            qWarning() << "BatteryStatus::OnIsChargingChanged";
            QMetaObject::invokeMethod(m_widget, "slotOnIsChargingChanged", Qt::QueuedConnection,
                              Q_ARG(bool, value)
                              );
        }
    };

private:
    Ref<ajn::services::BatteryStatusIntfController> controller;
    Ref<Listener> m_listener;


    QLabel* edit_CurrentValue;
    QCheckBox* edit_IsCharging;

    QLabel* messages_;
    void    fetchProperties();

protected:
    virtual void showEvent(QShowEvent *event) override
    {
        fetchProperties();
    }
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_BatteryStatus_H_ */
