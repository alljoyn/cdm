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

#ifndef org_alljoyn_SmartSpaces_Environment_TargetHumidity_H_
#define org_alljoyn_SmartSpaces_Environment_TargetHumidity_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <interfaces/common/environment/TargetHumidityInterface.h>
#include <interfaces/controller/environment/TargetHumidityIntfController.h>
#include <interfaces/controller/environment/TargetHumidityIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Environment_TargetHumidity : public QWidget
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Environment_TargetHumidity(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Environment_TargetHumidity();

    // Slots mirror the callbacks to avoid threading issues
private slots:

    void slotOnResponseGetTargetValue(QStatus status, const uint8_t value);
    void slotOnTargetValueChanged(const uint8_t value);
    void slotOnResponseSetTargetValue(QStatus status);
    void slotSetTargetValue();
    void slotOnResponseGetMinValue(QStatus status, const uint8_t value);
    void slotOnMinValueChanged(const uint8_t value);
    void slotOnResponseGetMaxValue(QStatus status, const uint8_t value);
    void slotOnMaxValueChanged(const uint8_t value);
    void slotOnResponseGetStepValue(QStatus status, const uint8_t value);
    void slotOnStepValueChanged(const uint8_t value);
    void slotOnResponseGetSelectableHumidityLevels(QStatus status, const std::vector<uint8_t>& value);
    void slotOnSelectableHumidityLevelsChanged(const std::vector<uint8_t>& value);

public:
    // ajn::services::TargetHumidityIntfControllerListener
    class Listener: public ajn::services::TargetHumidityIntfControllerListener
    {
    public:
        QWidget* m_widget;

        Listener(QWidget* widget)
          : m_widget(widget)
        {
        }

        virtual void OnResponseGetTargetValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetTargetValue", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(uint8_t, value)
                              );
        }
        virtual void OnTargetValueChanged(const qcc::String& objectPath, const uint8_t value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnTargetValueChanged", Qt::QueuedConnection,
                              Q_ARG(uint8_t, value)
                              );
        }
        virtual void OnResponseSetTargetValue(QStatus status, const qcc::String& objectPath, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseSetTargetValue", Qt::QueuedConnection,
                              Q_ARG(QStatus, status)
                              );
        }
        virtual void OnResponseGetMinValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetMinValue", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(uint8_t, value)
                              );
        }
        virtual void OnMinValueChanged(const qcc::String& objectPath, const uint8_t value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnMinValueChanged", Qt::QueuedConnection,
                              Q_ARG(uint8_t, value)
                              );
        }
        virtual void OnResponseGetMaxValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetMaxValue", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(uint8_t, value)
                              );
        }
        virtual void OnMaxValueChanged(const qcc::String& objectPath, const uint8_t value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnMaxValueChanged", Qt::QueuedConnection,
                              Q_ARG(uint8_t, value)
                              );
        }
        virtual void OnResponseGetStepValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetStepValue", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(uint8_t, value)
                              );
        }
        virtual void OnStepValueChanged(const qcc::String& objectPath, const uint8_t value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnStepValueChanged", Qt::QueuedConnection,
                              Q_ARG(uint8_t, value)
                              );
        }
        virtual void OnResponseGetSelectableHumidityLevels(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetSelectableHumidityLevels", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(std::vector<uint8_t>, value)
                              );
        }
        virtual void OnSelectableHumidityLevelsChanged(const qcc::String& objectPath, const std::vector<uint8_t>& value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnSelectableHumidityLevelsChanged", Qt::QueuedConnection,
                              Q_ARG(std::vector<uint8_t>, value)
                              );
        }
    };

private:
    Ref<ajn::services::TargetHumidityIntfController> controller;
    Ref<Listener> m_listener;


    QLineEdit* edit_TargetValue;
    QLineEdit* edit_MinValue;
    QLineEdit* edit_MaxValue;
    QLineEdit* edit_StepValue;
    QLineEdit* edit_SelectableHumidityLevels;

    void    fetchProperties();

protected:
    virtual void showEvent(QShowEvent *event) override
    {
        fetchProperties();
    }
};

}

#endif /* org_alljoyn_SmartSpaces_Environment_TargetHumidity_H_ */
