/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#ifndef org_alljoyn_SmartSpaces_Environment_TargetTemperatureLevel_H_
#define org_alljoyn_SmartSpaces_Environment_TargetTemperatureLevel_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <interfaces/common/environment/TargetTemperatureLevelInterface.h>
#include <interfaces/controller/environment/TargetTemperatureLevelIntfController.h>
#include <interfaces/controller/environment/TargetTemperatureLevelIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Environment_TargetTemperatureLevel : public QWidget
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Environment_TargetTemperatureLevel(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Environment_TargetTemperatureLevel();

    // Slots mirror the callbacks to avoid threading issues
private slots:

    void slotOnResponseGetMaxLevel(QStatus status, const uint8_t value);
    void slotOnMaxLevelChanged(const uint8_t value);
    void slotOnResponseGetTargetLevel(QStatus status, const uint8_t value);
    void slotOnTargetLevelChanged(const uint8_t value);
    void slotOnResponseSetTargetLevel(QStatus status);
    void slotSetTargetLevel();
    void slotOnResponseGetSelectableTemperatureLevels(QStatus status, const std::vector<uint8_t>& value);
    void slotOnSelectableTemperatureLevelsChanged(const std::vector<uint8_t>& value);

public:
    // ajn::services::TargetTemperatureLevelIntfControllerListener
    class Listener: public ajn::services::TargetTemperatureLevelIntfControllerListener
    {
    public:
        QWidget* m_widget;

        Listener(QWidget* widget)
          : m_widget(widget)
        {
        }

        virtual void OnResponseGetMaxLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetMaxLevel", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(uint8_t, value)
                              );
        }
        virtual void OnMaxLevelChanged(const qcc::String& objectPath, const uint8_t value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnMaxLevelChanged", Qt::QueuedConnection,
                              Q_ARG(uint8_t, value)
                              );
        }
        virtual void OnResponseGetTargetLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetTargetLevel", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(uint8_t, value)
                              );
        }
        virtual void OnTargetLevelChanged(const qcc::String& objectPath, const uint8_t value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnTargetLevelChanged", Qt::QueuedConnection,
                              Q_ARG(uint8_t, value)
                              );
        }
        virtual void OnResponseSetTargetLevel(QStatus status, const qcc::String& objectPath, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseSetTargetLevel", Qt::QueuedConnection,
                              Q_ARG(QStatus, status)
                              );
        }
        virtual void OnResponseGetSelectableTemperatureLevels(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetSelectableTemperatureLevels", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(std::vector<uint8_t>, value)
                              );
        }
        virtual void OnSelectableTemperatureLevelsChanged(const qcc::String& objectPath, const std::vector<uint8_t>& value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnSelectableTemperatureLevelsChanged", Qt::QueuedConnection,
                              Q_ARG(std::vector<uint8_t>, value)
                              );
        }
    };

private:
    Ref<ajn::services::TargetTemperatureLevelIntfController> controller;
    Ref<Listener> m_listener;


    QLineEdit* edit_MaxLevel;
    QLineEdit* edit_TargetLevel;
    QLineEdit* edit_SelectableTemperatureLevels;

    void    fetchProperties();

protected:
    virtual void showEvent(QShowEvent *event) override
    {
        fetchProperties();
    }
};

}

#endif /* org_alljoyn_SmartSpaces_Environment_TargetTemperatureLevel_H_ */