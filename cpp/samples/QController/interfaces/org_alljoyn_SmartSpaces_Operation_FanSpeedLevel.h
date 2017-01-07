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

#ifndef org_alljoyn_SmartSpaces_Operation_FanSpeedLevel_H_
#define org_alljoyn_SmartSpaces_Operation_FanSpeedLevel_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <interfaces/common/operation/FanSpeedLevelInterface.h>
#include <interfaces/controller/operation/FanSpeedLevelIntfController.h>
#include <interfaces/controller/operation/FanSpeedLevelIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_FanSpeedLevel : public QWidget
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Operation_FanSpeedLevel(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Operation_FanSpeedLevel();

    // Slots mirror the callbacks to avoid threading issues
private slots:

    void slotOnResponseGetFanSpeedLevel(QStatus status, const uint8_t value);
    void slotOnFanSpeedLevelChanged(const uint8_t value);
    void slotOnResponseSetFanSpeedLevel(QStatus status);
    void slotSetFanSpeedLevel();
    void slotOnResponseGetMaxFanSpeedLevel(QStatus status, const uint8_t value);
    void slotOnMaxFanSpeedLevelChanged(const uint8_t value);
    void slotOnResponseGetAutoMode(QStatus status, const FanSpeedLevelInterface::AutoMode value);
    void slotOnAutoModeChanged(const FanSpeedLevelInterface::AutoMode value);
    void slotOnResponseSetAutoMode(QStatus status);
    void slotSetAutoMode();

public:
    // ajn::services::FanSpeedLevelIntfControllerListener
    class Listener: public ajn::services::FanSpeedLevelIntfControllerListener
    {
    public:
        QWidget* m_widget;

        Listener(QWidget* widget)
          : m_widget(widget)
        {
        }

        virtual void OnResponseGetFanSpeedLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetFanSpeedLevel", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(uint8_t, value)
                              );
        }
        virtual void OnFanSpeedLevelChanged(const qcc::String& objectPath, const uint8_t value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnFanSpeedLevelChanged", Qt::QueuedConnection,
                              Q_ARG(uint8_t, value)
                              );
        }
        virtual void OnResponseSetFanSpeedLevel(QStatus status, const qcc::String& objectPath, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseSetFanSpeedLevel", Qt::QueuedConnection,
                              Q_ARG(QStatus, status)
                              );
        }
        virtual void OnResponseGetMaxFanSpeedLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetMaxFanSpeedLevel", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(uint8_t, value)
                              );
        }
        virtual void OnMaxFanSpeedLevelChanged(const qcc::String& objectPath, const uint8_t value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnMaxFanSpeedLevelChanged", Qt::QueuedConnection,
                              Q_ARG(uint8_t, value)
                              );
        }
        virtual void OnResponseGetAutoMode(QStatus status, const qcc::String& objectPath, const FanSpeedLevelInterface::AutoMode value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetAutoMode", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(FanSpeedLevelInterface::AutoMode, value)
                              );
        }
        virtual void OnAutoModeChanged(const qcc::String& objectPath, const FanSpeedLevelInterface::AutoMode value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnAutoModeChanged", Qt::QueuedConnection,
                              Q_ARG(FanSpeedLevelInterface::AutoMode, value)
                              );
        }
        virtual void OnResponseSetAutoMode(QStatus status, const qcc::String& objectPath, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseSetAutoMode", Qt::QueuedConnection,
                              Q_ARG(QStatus, status)
                              );
        }
    };

private:
    Ref<ajn::services::FanSpeedLevelIntfController> controller;
    Ref<Listener> m_listener;


    QLineEdit* edit_FanSpeedLevel;
    QLineEdit* edit_MaxFanSpeedLevel;
    QLineEdit* edit_AutoMode;

    void    fetchProperties();

protected:
    virtual void showEvent(QShowEvent *event) override
    {
        fetchProperties();
    }
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_FanSpeedLevel_H_ */
