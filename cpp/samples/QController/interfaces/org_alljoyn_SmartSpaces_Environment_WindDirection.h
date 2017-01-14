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

#ifndef org_alljoyn_SmartSpaces_Environment_WindDirection_H_
#define org_alljoyn_SmartSpaces_Environment_WindDirection_H_

#include <QWidget>
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

#include <interfaces/common/environment/WindDirectionInterface.h>
#include <interfaces/controller/environment/WindDirectionIntfController.h>
#include <interfaces/controller/environment/WindDirectionIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;


namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Environment_WindDirection : public QWidget
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Environment_WindDirection(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Environment_WindDirection();

    // Slots mirror the callbacks to avoid threading issues
private slots:

    void slotOnResponseGetHorizontalDirection(QStatus status, const uint16_t value);
    void slotOnHorizontalDirectionChanged(const uint16_t value);
    void slotOnResponseSetHorizontalDirection(QStatus status);
    void slotSetHorizontalDirection();
    void slotOnResponseGetHorizontalMax(QStatus status, const uint16_t value);
    void slotOnHorizontalMaxChanged(const uint16_t value);
    void slotOnResponseGetHorizontalAutoMode(QStatus status, const WindDirectionInterface::AutoMode value);
    void slotOnHorizontalAutoModeChanged(const WindDirectionInterface::AutoMode value);
    void slotOnResponseSetHorizontalAutoMode(QStatus status);
    void slotSetHorizontalAutoMode();
    void slotOnResponseGetVerticalDirection(QStatus status, const uint16_t value);
    void slotOnVerticalDirectionChanged(const uint16_t value);
    void slotOnResponseSetVerticalDirection(QStatus status);
    void slotSetVerticalDirection();
    void slotOnResponseGetVerticalMax(QStatus status, const uint16_t value);
    void slotOnVerticalMaxChanged(const uint16_t value);
    void slotOnResponseGetVerticalAutoMode(QStatus status, const WindDirectionInterface::AutoMode value);
    void slotOnVerticalAutoModeChanged(const WindDirectionInterface::AutoMode value);
    void slotOnResponseSetVerticalAutoMode(QStatus status);
    void slotSetVerticalAutoMode();

public:
    // ajn::services::WindDirectionIntfControllerListener
    class Listener: public ajn::services::WindDirectionIntfControllerListener
    {
    public:
        QWidget* m_widget;

        Listener(QWidget* widget)
          : m_widget(widget)
        {
        }

        virtual void OnResponseGetHorizontalDirection(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context) override
        {
            qWarning() << "WindDirection::OnResponseGetHorizontalDirection";
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetHorizontalDirection", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(uint16_t, value)
                              );
        }
        virtual void OnHorizontalDirectionChanged(const qcc::String& objectPath, const uint16_t value) override
        {
            qWarning() << "WindDirection::OnHorizontalDirectionChanged";
            QMetaObject::invokeMethod(m_widget, "slotOnHorizontalDirectionChanged", Qt::QueuedConnection,
                              Q_ARG(uint16_t, value)
                              );
        }
        virtual void OnResponseSetHorizontalDirection(QStatus status, const qcc::String& objectPath, void* context) override
        {
            qWarning() << "WindDirection::OnResponseSetHorizontalDirection";
            QMetaObject::invokeMethod(m_widget, "slotOnResponseSetHorizontalDirection", Qt::QueuedConnection,
                              Q_ARG(QStatus, status)
                              );
        }
        virtual void OnResponseGetHorizontalMax(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context) override
        {
            qWarning() << "WindDirection::OnResponseGetHorizontalMax";
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetHorizontalMax", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(uint16_t, value)
                              );
        }
        virtual void OnHorizontalMaxChanged(const qcc::String& objectPath, const uint16_t value) override
        {
            qWarning() << "WindDirection::OnHorizontalMaxChanged";
            QMetaObject::invokeMethod(m_widget, "slotOnHorizontalMaxChanged", Qt::QueuedConnection,
                              Q_ARG(uint16_t, value)
                              );
        }
        virtual void OnResponseGetHorizontalAutoMode(QStatus status, const qcc::String& objectPath, const WindDirectionInterface::AutoMode value, void* context) override
        {
            qWarning() << "WindDirection::OnResponseGetHorizontalAutoMode";
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetHorizontalAutoMode", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(WindDirectionInterface::AutoMode, value)
                              );
        }
        virtual void OnHorizontalAutoModeChanged(const qcc::String& objectPath, const WindDirectionInterface::AutoMode value) override
        {
            qWarning() << "WindDirection::OnHorizontalAutoModeChanged";
            QMetaObject::invokeMethod(m_widget, "slotOnHorizontalAutoModeChanged", Qt::QueuedConnection,
                              Q_ARG(WindDirectionInterface::AutoMode, value)
                              );
        }
        virtual void OnResponseSetHorizontalAutoMode(QStatus status, const qcc::String& objectPath, void* context) override
        {
            qWarning() << "WindDirection::OnResponseSetHorizontalAutoMode";
            QMetaObject::invokeMethod(m_widget, "slotOnResponseSetHorizontalAutoMode", Qt::QueuedConnection,
                              Q_ARG(QStatus, status)
                              );
        }
        virtual void OnResponseGetVerticalDirection(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context) override
        {
            qWarning() << "WindDirection::OnResponseGetVerticalDirection";
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetVerticalDirection", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(uint16_t, value)
                              );
        }
        virtual void OnVerticalDirectionChanged(const qcc::String& objectPath, const uint16_t value) override
        {
            qWarning() << "WindDirection::OnVerticalDirectionChanged";
            QMetaObject::invokeMethod(m_widget, "slotOnVerticalDirectionChanged", Qt::QueuedConnection,
                              Q_ARG(uint16_t, value)
                              );
        }
        virtual void OnResponseSetVerticalDirection(QStatus status, const qcc::String& objectPath, void* context) override
        {
            qWarning() << "WindDirection::OnResponseSetVerticalDirection";
            QMetaObject::invokeMethod(m_widget, "slotOnResponseSetVerticalDirection", Qt::QueuedConnection,
                              Q_ARG(QStatus, status)
                              );
        }
        virtual void OnResponseGetVerticalMax(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context) override
        {
            qWarning() << "WindDirection::OnResponseGetVerticalMax";
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetVerticalMax", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(uint16_t, value)
                              );
        }
        virtual void OnVerticalMaxChanged(const qcc::String& objectPath, const uint16_t value) override
        {
            qWarning() << "WindDirection::OnVerticalMaxChanged";
            QMetaObject::invokeMethod(m_widget, "slotOnVerticalMaxChanged", Qt::QueuedConnection,
                              Q_ARG(uint16_t, value)
                              );
        }
        virtual void OnResponseGetVerticalAutoMode(QStatus status, const qcc::String& objectPath, const WindDirectionInterface::AutoMode value, void* context) override
        {
            qWarning() << "WindDirection::OnResponseGetVerticalAutoMode";
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetVerticalAutoMode", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(WindDirectionInterface::AutoMode, value)
                              );
        }
        virtual void OnVerticalAutoModeChanged(const qcc::String& objectPath, const WindDirectionInterface::AutoMode value) override
        {
            qWarning() << "WindDirection::OnVerticalAutoModeChanged";
            QMetaObject::invokeMethod(m_widget, "slotOnVerticalAutoModeChanged", Qt::QueuedConnection,
                              Q_ARG(WindDirectionInterface::AutoMode, value)
                              );
        }
        virtual void OnResponseSetVerticalAutoMode(QStatus status, const qcc::String& objectPath, void* context) override
        {
            qWarning() << "WindDirection::OnResponseSetVerticalAutoMode";
            QMetaObject::invokeMethod(m_widget, "slotOnResponseSetVerticalAutoMode", Qt::QueuedConnection,
                              Q_ARG(QStatus, status)
                              );
        }
    };

private:
    Ref<ajn::services::WindDirectionIntfController> controller;
    Ref<Listener> m_listener;


    QLineEdit* edit_HorizontalDirection;
    QLabel* edit_HorizontalMax;
    QComboBox* edit_HorizontalAutoMode;
    QLineEdit* edit_VerticalDirection;
    QLabel* edit_VerticalMax;
    QComboBox* edit_VerticalAutoMode;

    QLabel* messages_;
    void    fetchProperties();

protected:
    virtual void showEvent(QShowEvent *event) override
    {
        fetchProperties();
    }
};

}

#endif /* org_alljoyn_SmartSpaces_Environment_WindDirection_H_ */
