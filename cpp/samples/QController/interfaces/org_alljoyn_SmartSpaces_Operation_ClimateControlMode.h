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

#ifndef org_alljoyn_SmartSpaces_Operation_ClimateControlMode_H_
#define org_alljoyn_SmartSpaces_Operation_ClimateControlMode_H_

#include <QWidget>
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <interfaces/common/operation/ClimateControlModeInterface.h>
#include <interfaces/controller/operation/ClimateControlModeIntfController.h>
#include <interfaces/controller/operation/ClimateControlModeIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;


namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_ClimateControlMode : public QWidget
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Operation_ClimateControlMode(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Operation_ClimateControlMode();

    // Slots mirror the callbacks to avoid threading issues
private slots:

    void slotOnResponseGetMode(QStatus status, const ClimateControlModeInterface::Mode value);
    void slotOnModeChanged(const ClimateControlModeInterface::Mode value);
    void slotOnResponseSetMode(QStatus status);
    void slotSetMode();
    void slotOnResponseGetSupportedModes(QStatus status, const std::vector<ClimateControlModeInterface::Mode>& value);
    void slotOnSupportedModesChanged(const std::vector<ClimateControlModeInterface::Mode>& value);
    void slotOnResponseGetOperationalState(QStatus status, const ClimateControlModeInterface::OperationalState value);
    void slotOnOperationalStateChanged(const ClimateControlModeInterface::OperationalState value);

public:
    // ajn::services::ClimateControlModeIntfControllerListener
    class Listener: public ajn::services::ClimateControlModeIntfControllerListener
    {
    public:
        QWidget* m_widget;

        Listener(QWidget* widget)
          : m_widget(widget)
        {
        }

        virtual void OnResponseGetMode(QStatus status, const qcc::String& objectPath, const ClimateControlModeInterface::Mode value, void* context) override
        {
            qWarning() << "ClimateControlMode::OnResponseGetMode";
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetMode", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(ClimateControlModeInterface::Mode, value)
                              );
        }
        virtual void OnModeChanged(const qcc::String& objectPath, const ClimateControlModeInterface::Mode value) override
        {
            qWarning() << "ClimateControlMode::OnModeChanged";
            QMetaObject::invokeMethod(m_widget, "slotOnModeChanged", Qt::QueuedConnection,
                              Q_ARG(ClimateControlModeInterface::Mode, value)
                              );
        }
        virtual void OnResponseSetMode(QStatus status, const qcc::String& objectPath, void* context) override
        {
            qWarning() << "ClimateControlMode::OnResponseSetMode";
            QMetaObject::invokeMethod(m_widget, "slotOnResponseSetMode", Qt::QueuedConnection,
                              Q_ARG(QStatus, status)
                              );
        }
        virtual void OnResponseGetSupportedModes(QStatus status, const qcc::String& objectPath, const std::vector<ClimateControlModeInterface::Mode>& value, void* context) override
        {
            qWarning() << "ClimateControlMode::OnResponseGetSupportedModes";
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetSupportedModes", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(std::vector<ClimateControlModeInterface::Mode>, value)
                              );
        }
        virtual void OnSupportedModesChanged(const qcc::String& objectPath, const std::vector<ClimateControlModeInterface::Mode>& value) override
        {
            qWarning() << "ClimateControlMode::OnSupportedModesChanged";
            QMetaObject::invokeMethod(m_widget, "slotOnSupportedModesChanged", Qt::QueuedConnection,
                              Q_ARG(std::vector<ClimateControlModeInterface::Mode>, value)
                              );
        }
        virtual void OnResponseGetOperationalState(QStatus status, const qcc::String& objectPath, const ClimateControlModeInterface::OperationalState value, void* context) override
        {
            qWarning() << "ClimateControlMode::OnResponseGetOperationalState";
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetOperationalState", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(ClimateControlModeInterface::OperationalState, value)
                              );
        }
        virtual void OnOperationalStateChanged(const qcc::String& objectPath, const ClimateControlModeInterface::OperationalState value) override
        {
            qWarning() << "ClimateControlMode::OnOperationalStateChanged";
            QMetaObject::invokeMethod(m_widget, "slotOnOperationalStateChanged", Qt::QueuedConnection,
                              Q_ARG(ClimateControlModeInterface::OperationalState, value)
                              );
        }
    };

private:
    Ref<ajn::services::ClimateControlModeIntfController> controller;
    Ref<Listener> m_listener;


    QComboBox* edit_Mode;
    QLineEdit* edit_SupportedModes;
    QComboBox* edit_OperationalState;

    void    fetchProperties();

protected:
    virtual void showEvent(QShowEvent *event) override
    {
        fetchProperties();
    }
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_ClimateControlMode_H_ */
