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

#ifndef org_alljoyn_SmartSpaces_Operation_CycleControl_H_
#define org_alljoyn_SmartSpaces_Operation_CycleControl_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <interfaces/common/operation/CycleControlInterface.h>
#include <interfaces/controller/operation/CycleControlIntfController.h>
#include <interfaces/controller/operation/CycleControlIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_CycleControl : public QWidget
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Operation_CycleControl(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Operation_CycleControl();

    // Slots mirror the callbacks to avoid threading issues
private slots:
    void slotClickExecuteOperationalCommand();

    void slotOnResponseGetOperationalState(QStatus status, const CycleControlInterface::OperationalState value);
    void slotOnOperationalStateChanged(const CycleControlInterface::OperationalState value);
    void slotOnResponseGetSupportedOperationalStates(QStatus status, const std::vector<CycleControlInterface::OperationalState>& value);
    void slotOnSupportedOperationalStatesChanged(const std::vector<CycleControlInterface::OperationalState>& value);
    void slotOnResponseGetSupportedOperationalCommands(QStatus status, const std::vector<CycleControlInterface::OperationalCommands>& value);
    void slotOnSupportedOperationalCommandsChanged(const std::vector<CycleControlInterface::OperationalCommands>& value);
    void slotOnResponseMethodExecuteOperationalCommand(QStatus status);

public:
    // ajn::services::CycleControlIntfControllerListener
    class Listener: public ajn::services::CycleControlIntfControllerListener
    {
    public:
        QWidget* m_widget;

        Listener(QWidget* widget)
          : m_widget(widget)
        {
        }

        virtual void OnResponseGetOperationalState(QStatus status, const qcc::String& objectPath, const CycleControlInterface::OperationalState value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetOperationalState", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(CycleControlInterface::OperationalState, value)
                              );
        }
        virtual void OnOperationalStateChanged(const qcc::String& objectPath, const CycleControlInterface::OperationalState value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnOperationalStateChanged", Qt::QueuedConnection,
                              Q_ARG(CycleControlInterface::OperationalState, value)
                              );
        }
        virtual void OnResponseGetSupportedOperationalStates(QStatus status, const qcc::String& objectPath, const std::vector<CycleControlInterface::OperationalState>& value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetSupportedOperationalStates", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(std::vector<CycleControlInterface::OperationalState>, value)
                              );
        }
        virtual void OnSupportedOperationalStatesChanged(const qcc::String& objectPath, const std::vector<CycleControlInterface::OperationalState>& value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnSupportedOperationalStatesChanged", Qt::QueuedConnection,
                              Q_ARG(std::vector<CycleControlInterface::OperationalState>, value)
                              );
        }
        virtual void OnResponseGetSupportedOperationalCommands(QStatus status, const qcc::String& objectPath, const std::vector<CycleControlInterface::OperationalCommands>& value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetSupportedOperationalCommands", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(std::vector<CycleControlInterface::OperationalCommands>, value)
                              );
        }
        virtual void OnSupportedOperationalCommandsChanged(const qcc::String& objectPath, const std::vector<CycleControlInterface::OperationalCommands>& value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnSupportedOperationalCommandsChanged", Qt::QueuedConnection,
                              Q_ARG(std::vector<CycleControlInterface::OperationalCommands>, value)
                              );
        }
        virtual void OnResponseExecuteOperationalCommand(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseMethodExecuteOperationalCommand", Qt::QueuedConnection,
                              Q_ARG(QStatus, status)
                              );
        }
    };

private:
    Ref<ajn::services::CycleControlIntfController> controller;
    Ref<Listener> m_listener;

    QPushButton* button_ExecuteOperationalCommand;

    QLineEdit* edit_OperationalState;
    QLineEdit* edit_SupportedOperationalStates;
    QLineEdit* edit_SupportedOperationalCommands;
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_CycleControl_H_ */