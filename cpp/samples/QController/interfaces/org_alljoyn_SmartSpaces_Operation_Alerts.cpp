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

#include "org_alljoyn_SmartSpaces_Operation_Alerts.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QFrame>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableWidgetItem>
#include <sstream>

using namespace std;

// This is the replaced whole file

static const char* DefaultLanguageTag = "en";


template<>
QString
QStringFrom<AlertsInterface::AlertRecord>(const AlertsInterface::AlertRecord& value)
{
    ostringstream strm;
    strm << "{";
    strm << "severity=" << value.severity;
    strm << " ";
    strm << "alertCode=" << value.alertCode;
    strm << " ";
    strm << "needAcknowledgement=" << value.needAcknowledgement;
    strm << "}";

    return QString::fromStdString(strm.str());
}


template<>
QString
QStringFrom<vector<AlertsInterface::AlertRecord>>(const vector<AlertsInterface::AlertRecord>& value)
{
    string result;

    for (auto& v : value)
    {
        auto qs = QStringFrom<AlertsInterface::AlertRecord>(v);
        result += qs.toStdString();
    }
    return QString::fromStdString(result);
}



template<>
QString
QStringFrom<AlertsInterface::AlertCodesDescriptor>(const AlertsInterface::AlertCodesDescriptor& value)
{
    ostringstream strm;
    strm << "{";
    strm << "alertCode=" << value.alertCode;
    strm << " ";
    strm << "description=" << value.description.c_str();
    strm << "}";

    return QString::fromStdString(strm.str());
}


template<>
QString
QStringFrom<vector<AlertsInterface::AlertCodesDescriptor>>(const vector<AlertsInterface::AlertCodesDescriptor>& value)
{
    string result;

    for (auto& v : value)
    {
        auto qs = QStringFrom<AlertsInterface::AlertCodesDescriptor>(v);
        result += qs.toStdString();
    }
    return QString::fromStdString(result);
}


static void clearChildren(QWidget* parent)
{
    qDeleteAll(parent->findChildren<QWidget*>("", Qt::FindDirectChildrenOnly));
}

//======================================================================



using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_Alerts*>();


org_alljoyn_SmartSpaces_Operation_Alerts::org_alljoyn_SmartSpaces_Operation_Alerts(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(new QLabel("Alerts"));

    // Create a table for the Alerts
    {
        auto* frame = new QFrame();
        auto flayout = new QVBoxLayout();
        frame->setLayout(flayout);
        flayout->setContentsMargins(0, 0, 0, 0);
        flayout->setSpacing(0);
        alertsList = frame;
        alertsList->setObjectName("alertsList");
        layout->addWidget(frame);
    }

    // Create a centred button for AcknowledgeAllAlerts
    {
        auto* frame = new QFrame();
        auto flayout = new QHBoxLayout();
        auto* button = new QPushButton("AcknowledgeAllAlerts");
        frame->setLayout(flayout);
        flayout->addStretch(1);
        flayout->addWidget(button, 0);
        flayout->addStretch(1);

        button->setToolTip("Reset the user acknowledgment request of any pending alert.");
        QObject::connect(button, SIGNAL(clicked()), this, SLOT(slotClickAcknowledgeAllAlerts()));
        layout->addWidget(frame);
    }

    if (iface)
    {
        controller = iface->CreateInterface<AlertsIntfController>(m_listener);
        if (controller)
        {
            qWarning() << __FUNCTION__ << " Getting properties";

            QStatus status;

            // Get the descriptions first.
            status = controller->GetAlertCodesDescription(DefaultLanguageTag);
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get AlertCodesDescription" << QCC_StatusText(status);
            }

            fetchProperties();
        }
        else
        {
            qWarning() << __FUNCTION__ << " No interface controller available!";
        }
    }
    else
    {
        qWarning() << __FUNCTION__ << " No interface available!";
    }
}

org_alljoyn_SmartSpaces_Operation_Alerts::~org_alljoyn_SmartSpaces_Operation_Alerts()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_Alerts::fetchProperties()
{
    // Get current values
    if (controller)
    {
        qWarning() << __FUNCTION__ << " Getting properties";

        auto status = controller->GetAlertCodesDescription(DefaultLanguageTag);
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get AlertCodesDescription" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_Alerts::slotClickGetAlertCodesDescription()
{
    qWarning() << __FUNCTION__;

    QStatus status = controller->GetAlertCodesDescription(DefaultLanguageTag, NULL);
    if (status != ER_OK)
    {
        qWarning() << __FUNCTION__ << " Failed to call GetAlertCodesDescription" << QCC_StatusText(status);
    }
}



void org_alljoyn_SmartSpaces_Operation_Alerts::slotClickAcknowledgeAlert()
{
    qWarning() << __FUNCTION__;
    auto* ackButton = dynamic_cast<QPushButton*>(QObject::sender());
    QVariant var = ackButton->property("alertCode");

    uint16_t alertCode = var.toUInt();
    qWarning() << __FUNCTION__ << " alertCode " << alertCode;

    QStatus status = controller->AcknowledgeAlert(alertCode, NULL);
    if (status != ER_OK)
    {
        qWarning() << __FUNCTION__ << " Failed to call AcknowledgeAlert" << QCC_StatusText(status);
    }
}



void org_alljoyn_SmartSpaces_Operation_Alerts::slotClickAcknowledgeAllAlerts()
{
    qWarning() << __FUNCTION__;

    QStatus status = controller->AcknowledgeAllAlerts(NULL);
    if (status != ER_OK)
    {
        qWarning() << __FUNCTION__ << " Failed to call AcknowledgeAllAlerts" << QCC_StatusText(status);
    }
}



void org_alljoyn_SmartSpaces_Operation_Alerts::slotOnResponseGetAlerts(QStatus status, vector<AlertsInterface::AlertRecord> value)
{
    qWarning() << __FUNCTION__;
    showAlerts(value);
}



void org_alljoyn_SmartSpaces_Operation_Alerts::slotOnAlertsChanged(vector<AlertsInterface::AlertRecord> value)
{
    qWarning() << __FUNCTION__;
    showAlerts(value);
}



void    
org_alljoyn_SmartSpaces_Operation_Alerts::showAlerts(const vector<AlertsInterface::AlertRecord>& alerts)
{
    clearChildren(alertsList);

    for (size_t i = 0; i < alerts.size(); ++i)
    {
        auto& alert = alerts[i];
        const char* sev = "";

        // See if we can translate the code to a description
        string code;

        for (auto& d : alertDescrs)
        {
            if (d.alertCode == alert.alertCode)
            {
                code = d.description.c_str();
                break;
            }
        }

        if (code.empty())
        {
            ostringstream strm;
            strm << alert.alertCode;
            code = strm.str();
        }

        auto* box = new QWidget();
        auto* layout = new QHBoxLayout();
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);
        box->setLayout(layout);
        box->setProperty("class", "alert");

        auto* item = new QLabel(QString::fromStdString(code));
        layout->addWidget(item, 1);             // stretch of 1

        item->setProperty("class", "alertDescription");
        item->setProperty("severity", QVariant(static_cast<int>(alert.severity)));

        if (alert.needAcknowledgement)
        {
            auto* ack = new QPushButton("Ack");
            ack->setProperty("alertCode", QVariant(alert.alertCode)); 
            layout->addWidget(ack, 0);          // stretch of 0

            QObject::connect(ack, SIGNAL(clicked()), this, SLOT(slotClickAcknowledgeAlert()));
        }

        alertsList->layout()->addWidget(box);
    }

    alertsList->show();
}



void org_alljoyn_SmartSpaces_Operation_Alerts::slotOnResponseMethodGetAlertCodesDescription(std::vector<AlertsInterface::AlertCodesDescriptor> description, QStatus status, const QString& errorName)
{
    if (status == ER_OK)
    {
        qInfo() << "Received response to method GetAlertCodesDescription";
        alertDescrs = description;
    }
    else
    {
        qWarning() << "Received an error from method GetAlertCodesDescription, error = " << errorName;
    }
}



void org_alljoyn_SmartSpaces_Operation_Alerts::slotOnResponseMethodAcknowledgeAlert(QStatus status, const QString& errorName)
{
    if (status == ER_OK)
    {
        qInfo() << "Received response to method AcknowledgeAlert";
    }
    else
    {
        qWarning() << "Received an error from method AcknowledgeAlert, error = " << errorName;
    }
}



void org_alljoyn_SmartSpaces_Operation_Alerts::slotOnResponseMethodAcknowledgeAllAlerts(QStatus status, const QString& errorName)
{
    if (status == ER_OK)
    {
        qInfo() << "Received response to method AcknowledgeAllAlerts";
    }
    else
    {
        qWarning() << "Received an error from method AcknowledgeAllAlerts, error = " << errorName;
    }
}