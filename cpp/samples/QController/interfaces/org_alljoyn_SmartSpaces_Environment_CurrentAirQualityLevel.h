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

#ifndef org_alljoyn_SmartSpaces_Environment_CurrentAirQualityLevel_H_
#define org_alljoyn_SmartSpaces_Environment_CurrentAirQualityLevel_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <interfaces/common/environment/CurrentAirQualityLevelInterface.h>
#include <interfaces/controller/environment/CurrentAirQualityLevelIntfController.h>
#include <interfaces/controller/environment/CurrentAirQualityLevelIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Environment_CurrentAirQualityLevel : public QWidget
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Environment_CurrentAirQualityLevel(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Environment_CurrentAirQualityLevel();

    // Slots mirror the callbacks to avoid threading issues
private slots:

    void slotOnResponseGetContaminantType(QStatus status, const CurrentAirQualityLevelInterface::ContaminantType value);
    void slotOnContaminantTypeChanged(const CurrentAirQualityLevelInterface::ContaminantType value);
    void slotOnResponseGetCurrentLevel(QStatus status, const uint8_t value);
    void slotOnCurrentLevelChanged(const uint8_t value);
    void slotOnResponseGetMaxLevel(QStatus status, const uint8_t value);
    void slotOnMaxLevelChanged(const uint8_t value);

public:
    // ajn::services::CurrentAirQualityLevelIntfControllerListener
    class Listener: public ajn::services::CurrentAirQualityLevelIntfControllerListener
    {
    public:
        QWidget* m_widget;

        Listener(QWidget* widget)
          : m_widget(widget)
        {
        }

        virtual void OnResponseGetContaminantType(QStatus status, const qcc::String& objectPath, const CurrentAirQualityLevelInterface::ContaminantType value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetContaminantType", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(CurrentAirQualityLevelInterface::ContaminantType, value)
                              );
        }
        virtual void OnContaminantTypeChanged(const qcc::String& objectPath, const CurrentAirQualityLevelInterface::ContaminantType value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnContaminantTypeChanged", Qt::QueuedConnection,
                              Q_ARG(CurrentAirQualityLevelInterface::ContaminantType, value)
                              );
        }
        virtual void OnResponseGetCurrentLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetCurrentLevel", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(uint8_t, value)
                              );
        }
        virtual void OnCurrentLevelChanged(const qcc::String& objectPath, const uint8_t value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnCurrentLevelChanged", Qt::QueuedConnection,
                              Q_ARG(uint8_t, value)
                              );
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
    };

private:
    Ref<ajn::services::CurrentAirQualityLevelIntfController> controller;
    Ref<Listener> m_listener;


    QLineEdit* edit_ContaminantType;
    QLineEdit* edit_CurrentLevel;
    QLineEdit* edit_MaxLevel;

    void    fetchProperties();

protected:
    virtual void showEvent(QShowEvent *event) override
    {
        fetchProperties();
    }
};

}

#endif /* org_alljoyn_SmartSpaces_Environment_CurrentAirQualityLevel_H_ */