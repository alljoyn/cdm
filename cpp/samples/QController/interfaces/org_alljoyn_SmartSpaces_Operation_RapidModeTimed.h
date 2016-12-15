/******************************************************************************
 * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#ifndef org_alljoyn_SmartSpaces_Operation_RapidModeTimed_H_
#define org_alljoyn_SmartSpaces_Operation_RapidModeTimed_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <interfaces/common/operation/RapidModeTimedInterface.h>
#include <interfaces/controller/operation/RapidModeTimedIntfController.h>
#include <interfaces/controller/operation/RapidModeTimedIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_RapidModeTimed : public QWidget
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Operation_RapidModeTimed(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Operation_RapidModeTimed();

    // Slots mirror the callbacks to avoid threading issues
private slots:

    void slotOnResponseGetRapidModeMinutesRemaining(QStatus status, const uint16_t value);
    void slotOnRapidModeMinutesRemainingChanged(const uint16_t value);
    void slotOnResponseSetRapidModeMinutesRemaining(QStatus status);
    void slotSetRapidModeMinutesRemaining();
    void slotOnResponseGetMaxSetMinutes(QStatus status, const uint16_t value);
    void slotOnMaxSetMinutesChanged(const uint16_t value);

public:
    // ajn::services::RapidModeTimedIntfControllerListener
    class Listener: public ajn::services::RapidModeTimedIntfControllerListener
    {
    public:
        QWidget* m_widget;

        Listener(QWidget* widget)
          : m_widget(widget)
        {
        }

        virtual void OnResponseGetRapidModeMinutesRemaining(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetRapidModeMinutesRemaining", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(uint16_t, value)
                              );
        }
        virtual void OnRapidModeMinutesRemainingChanged(const qcc::String& objectPath, const uint16_t value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnRapidModeMinutesRemainingChanged", Qt::QueuedConnection,
                              Q_ARG(uint16_t, value)
                              );
        }
        virtual void OnResponseSetRapidModeMinutesRemaining(QStatus status, const qcc::String& objectPath, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseSetRapidModeMinutesRemaining", Qt::QueuedConnection,
                              Q_ARG(QStatus, status)
                              );
        }
        virtual void OnResponseGetMaxSetMinutes(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetMaxSetMinutes", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(uint16_t, value)
                              );
        }
        virtual void OnMaxSetMinutesChanged(const qcc::String& objectPath, const uint16_t value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnMaxSetMinutesChanged", Qt::QueuedConnection,
                              Q_ARG(uint16_t, value)
                              );
        }
    };

private:
    Ref<ajn::services::RapidModeTimedIntfController> controller;
    Ref<Listener> m_listener;


    QLineEdit* edit_RapidModeMinutesRemaining;
    QLineEdit* edit_MaxSetMinutes;

    void    fetchProperties();

protected:
    virtual void showEvent(QShowEvent *event) override
    {
        fetchProperties();
    }
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_RapidModeTimed_H_ */