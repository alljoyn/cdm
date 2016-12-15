/******************************************************************************
 *  * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#ifndef org_alljoyn_SmartSpaces_Operation_Alerts_H_
#define org_alljoyn_SmartSpaces_Operation_Alerts_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTableWidget>

#include <interfaces/common/operation/AlertsInterface.h>
#include <interfaces/controller/operation/AlertsIntfController.h>
#include <interfaces/controller/operation/AlertsIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_Alerts : public QWidget
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Operation_Alerts(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Operation_Alerts();

    // Slots mirror the callbacks to avoid threading issues
private slots:
    void slotClickGetAlertCodesDescription();
    void slotClickAcknowledgeAlert();
    void slotClickAcknowledgeAllAlerts();

    void slotOnResponseGetAlerts(QStatus status, std::vector<AlertsInterface::AlertRecord> value);
    void slotOnAlertsChanged(std::vector<AlertsInterface::AlertRecord> value);
    void slotOnResponseMethodGetAlertCodesDescription(std::vector<AlertsInterface::AlertCodesDescriptor> description, QStatus status, const QString& errorName);
    void slotOnResponseMethodAcknowledgeAlert(QStatus status, const QString& errorName);
    void slotOnResponseMethodAcknowledgeAllAlerts(QStatus status, const QString& errorName);

public:
    // ajn::services::AlertsIntfControllerListener
    class Listener: public ajn::services::AlertsIntfControllerListener
    {
    public:
        QWidget* m_widget;

        Listener(QWidget* widget)
          : m_widget(widget)
        {
        }

        virtual void OnResponseGetAlerts(QStatus status, const qcc::String& objectPath, const std::vector<AlertsInterface::AlertRecord>& value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetAlerts", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(std::vector<AlertsInterface::AlertRecord>, value)
                              );
        }
        virtual void OnAlertsChanged(const qcc::String& objectPath, const std::vector<AlertsInterface::AlertRecord>& value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnAlertsChanged", Qt::QueuedConnection,
                              Q_ARG(std::vector<AlertsInterface::AlertRecord>, value)
                              );
        }
        virtual void OnResponseGetAlertCodesDescription(QStatus status, const qcc::String& objectPath, const std::vector<AlertsInterface::AlertCodesDescriptor>& description, void* context, const char* errorName, const char* errorMessage) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseMethodGetAlertCodesDescription", Qt::QueuedConnection,
                              Q_ARG(std::vector<AlertsInterface::AlertCodesDescriptor>, description), Q_ARG(QStatus, status), Q_ARG(QString, QString(errorName))
                              );
        }
        virtual void OnResponseAcknowledgeAlert(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseMethodAcknowledgeAlert", Qt::QueuedConnection,
                              Q_ARG(QStatus, status), Q_ARG(QString, QString(errorName))
                              );
        }
        virtual void OnResponseAcknowledgeAllAlerts(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseMethodAcknowledgeAllAlerts", Qt::QueuedConnection,
                              Q_ARG(QStatus, status), Q_ARG(QString, QString(errorName))
                              );
        }
    };

private:
    Ref<ajn::services::AlertsIntfController> controller;
    Ref<Listener> m_listener;

    std::vector<AlertsInterface::AlertCodesDescriptor> alertDescrs;
    std::vector<AlertsInterface::AlertRecord> alertRecords;

    QWidget* alertsList;

    void    showAlerts(const std::vector<AlertsInterface::AlertRecord>& alerts);
    void    fetchProperties();

protected:
    virtual void showEvent(QShowEvent *event) override
    {
        fetchProperties();
    }
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_Alerts_H_ */