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

#ifndef org_GalaxyClass_Engineering_WarpCore_H_
#define org_GalaxyClass_Engineering_WarpCore_H_

#include <QWidget>
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

#include "WarpCore/WarpCoreInterface.h"
#include "WarpCore/WarpCoreIntfController.h"
#include "WarpCore/WarpCoreIntfControllerListener.h"
#include "commoncontrollerimpl.h"

using namespace ajn::services;


namespace CDMQtWidgets
{

class org_GalaxyClass_Engineering_WarpCore : public QWidget
{
    Q_OBJECT
public:
    Q_INVOKABLE org_GalaxyClass_Engineering_WarpCore(CommonControllerInterface *iface=NULL);
    ~org_GalaxyClass_Engineering_WarpCore();

    // Slots mirror the callbacks to avoid threading issues
private slots:
    void slotClickEngage();
    void slotClickDisengage();

    void slotOnResponseGetWarpFactor(QStatus status, const double value);
    void slotOnWarpFactorChanged(const double value);
    void slotOnResponseSetWarpFactor(QStatus status);
    void slotSetWarpFactor();
    void slotOnResponseGetCurrentWarpFactor(QStatus status, const double value);
    void slotOnCurrentWarpFactorChanged(const double value);
    void slotOnResponseGetIsEngaged(QStatus status, const bool value);
    void slotOnIsEngagedChanged(const bool value);
    void slotOnResponseMethodEngage(QStatus status, const QString& errorName);
    void slotOnResponseMethodDisengage(QStatus status, const QString& errorName);

public:
    // ajn::services::WarpCoreIntfControllerListener
    class Listener: public ajn::services::WarpCoreIntfControllerListener
    {
    public:
        QWidget* m_widget;

        Listener(QWidget* widget)
          : m_widget(widget)
        {
        }

        virtual void OnResponseGetWarpFactor(QStatus status, const qcc::String& objectPath, const double value, void* context) override
        {
            qWarning() << "WarpCore::OnResponseGetWarpFactor";
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetWarpFactor", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(double, value)
                              );
        }
        virtual void OnWarpFactorChanged(const qcc::String& objectPath, const double value) override
        {
            qWarning() << "WarpCore::OnWarpFactorChanged";
            QMetaObject::invokeMethod(m_widget, "slotOnWarpFactorChanged", Qt::QueuedConnection,
                              Q_ARG(double, value)
                              );
        }
        virtual void OnResponseSetWarpFactor(QStatus status, const qcc::String& objectPath, void* context) override
        {
            qWarning() << "WarpCore::OnResponseSetWarpFactor";
            QMetaObject::invokeMethod(m_widget, "slotOnResponseSetWarpFactor", Qt::QueuedConnection,
                              Q_ARG(QStatus, status)
                              );
        }
        virtual void OnResponseGetCurrentWarpFactor(QStatus status, const qcc::String& objectPath, const double value, void* context) override
        {
            qWarning() << "WarpCore::OnResponseGetCurrentWarpFactor";
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetCurrentWarpFactor", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(double, value)
                              );
        }
        virtual void OnCurrentWarpFactorChanged(const qcc::String& objectPath, const double value) override
        {
            qWarning() << "WarpCore::OnCurrentWarpFactorChanged";
            QMetaObject::invokeMethod(m_widget, "slotOnCurrentWarpFactorChanged", Qt::QueuedConnection,
                              Q_ARG(double, value)
                              );
        }
        virtual void OnResponseGetIsEngaged(QStatus status, const qcc::String& objectPath, const bool value, void* context) override
        {
            qWarning() << "WarpCore::OnResponseGetIsEngaged";
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetIsEngaged", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(bool, value)
                              );
        }
        virtual void OnIsEngagedChanged(const qcc::String& objectPath, const bool value) override
        {
            qWarning() << "WarpCore::OnIsEngagedChanged";
            QMetaObject::invokeMethod(m_widget, "slotOnIsEngagedChanged", Qt::QueuedConnection,
                              Q_ARG(bool, value)
                              );
        }
        virtual void OnResponseEngage(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage) override
        {
            qWarning() << "WarpCore::OnResponseEngage";
            QMetaObject::invokeMethod(m_widget, "slotOnResponseMethodEngage", Qt::QueuedConnection,
                              Q_ARG(QStatus, status), Q_ARG(QString, QString(errorName))
                              );
        }
        virtual void OnResponseDisengage(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage) override
        {
            qWarning() << "WarpCore::OnResponseDisengage";
            QMetaObject::invokeMethod(m_widget, "slotOnResponseMethodDisengage", Qt::QueuedConnection,
                              Q_ARG(QStatus, status), Q_ARG(QString, QString(errorName))
                              );
        }
    };

private:
    Ref<ajn::services::WarpCoreIntfController> controller;
    Ref<Listener> m_listener;

    QPushButton* button_Engage;
    QPushButton* button_Disengage;

    QLineEdit* edit_WarpFactor;
    QLabel* edit_CurrentWarpFactor;
    QCheckBox* edit_IsEngaged;

    QLabel* messages_;
    void    fetchProperties();

protected:
    virtual void showEvent(QShowEvent *event) override
    {
        fetchProperties();
    }
};

}

#endif /* org_GalaxyClass_Engineering_WarpCore_H_ */
