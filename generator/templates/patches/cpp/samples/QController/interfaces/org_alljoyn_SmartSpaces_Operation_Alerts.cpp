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
#include "org_alljoyn_SmartSpaces_Operation_Alerts.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include <sstream>

using namespace std;


template<>
QString
QStringFrom<AlertsInterface::AlertRecord>(const AlertsInterface::AlertRecord& value)
{
    // the QLabel is AutoFmt 
    std::ostringstream strm;

    strm << "<b>severity</b>: " << value.severity << "\n";
    strm << "<b>alertCode</b>: " << value.alertCode << "\n";
    strm << "<b>needAcknowledgement</b>: " << value.needAcknowledgement << "\n";

    return QString::fromStdString(strm.str());
}


template<>
QString
QStringFrom<std::vector<AlertsInterface::AlertRecord>>(const std::vector<AlertsInterface::AlertRecord>& value)
{
    // the QLabel is AutoFmt 
    std::ostringstream strm;

    strm << "<html><body>";
    strm << "<table><thead><tr>";
    strm << "<th bgcolor=\"light blue\">severity</th>";
    strm << "<th bgcolor=\"light blue\">alertCode</th>";
    strm << "<th bgcolor=\"light blue\">needAcknowledgement</th>";
    strm << "</tr></thead>";

    for (auto& v : value)
    {
        strm << "<tr>";
        strm << "<td>" << v.severity << "</td>";
        strm << "<td>" << v.alertCode << "</td>";
        strm << "<td>" << v.needAcknowledgement << "</td>";
        strm << "</tr>";
    }

    strm << "</table></body></html>";
    return QString::fromStdString(strm.str());
}



template<>
QString
QStringFrom<AlertsInterface::AlertCodesDescriptor>(const AlertsInterface::AlertCodesDescriptor& value)
{
    // the QLabel is AutoFmt 
    std::ostringstream strm;

    strm << "<b>alertCode</b>: " << value.alertCode << "\n";
    strm << "<b>description</b>: " << value.description.c_str() << "\n";

    return QString::fromStdString(strm.str());
}


template<>
QString
QStringFrom<std::vector<AlertsInterface::AlertCodesDescriptor>>(const std::vector<AlertsInterface::AlertCodesDescriptor>& value)
{
    // the QLabel is AutoFmt 
    std::ostringstream strm;

    strm << "<html><body>";
    strm << "<table><thead><tr>";
    strm << "<th bgcolor=\"light blue\">alertCode</th>";
    strm << "<th bgcolor=\"light blue\">description</th>";
    strm << "</tr></thead>";

    for (auto& v : value)
    {
        strm << "<tr>";
        strm << "<td>" << v.alertCode << "</td>";
        strm << "<td>" << v.description.c_str() << "</td>";
        strm << "</tr>";
    }

    strm << "</table></body></html>";
    return QString::fromStdString(strm.str());
}



using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_Alerts*>();

Q_DECLARE_METATYPE(ajn::services::AlertsInterface::AlertRecord);
Q_DECLARE_METATYPE(std::vector<ajn::services::AlertsInterface::AlertRecord>);
static const int auto_register_struct_AlertRecord = qRegisterMetaType<ajn::services::AlertsInterface::AlertRecord>("AlertsInterface::AlertRecord");
static const int auto_register_struct_v_AlertRecord = qRegisterMetaType<std::vector<ajn::services::AlertsInterface::AlertRecord>>("std::vector<AlertsInterface::AlertRecord>");

Q_DECLARE_METATYPE(ajn::services::AlertsInterface::AlertCodesDescriptor);
Q_DECLARE_METATYPE(std::vector<ajn::services::AlertsInterface::AlertCodesDescriptor>);
static const int auto_register_struct_AlertCodesDescriptor = qRegisterMetaType<ajn::services::AlertsInterface::AlertCodesDescriptor>("AlertsInterface::AlertCodesDescriptor");
static const int auto_register_struct_v_AlertCodesDescriptor = qRegisterMetaType<std::vector<ajn::services::AlertsInterface::AlertCodesDescriptor>>("std::vector<AlertsInterface::AlertCodesDescriptor>");

Q_DECLARE_METATYPE(ajn::services::AlertsInterface::Severity);
Q_DECLARE_METATYPE(std::vector<ajn::services::AlertsInterface::Severity>);
static const int auto_register_enum_Severity = qRegisterMetaType<ajn::services::AlertsInterface::Severity>("AlertsInterface::Severity");
static const int auto_register_enum_v_Severity = qRegisterMetaType<std::vector<ajn::services::AlertsInterface::Severity>>("std::vector<AlertsInterface::Severity>");



org_alljoyn_SmartSpaces_Operation_Alerts::org_alljoyn_SmartSpaces_Operation_Alerts(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);


    // Create button for GetAlertCodesDescription
    button_GetAlertCodesDescription = new QPushButton("GetAlertCodesDescription");
    button_GetAlertCodesDescription->setToolTip("Get alert codes description.");
    QObject::connect(button_GetAlertCodesDescription, SIGNAL(clicked()), this, SLOT(slotClickGetAlertCodesDescription()));
    layout->addWidget(button_GetAlertCodesDescription);
    // Create button for AcknowledgeAllAlerts
    button_AcknowledgeAllAlerts = new QPushButton("AcknowledgeAllAlerts");
    button_AcknowledgeAllAlerts->setToolTip("Reset the user acknowledgment request of any pending alert.");
    QObject::connect(button_AcknowledgeAllAlerts, SIGNAL(clicked()), this, SLOT(slotClickAcknowledgeAllAlerts()));
    layout->addWidget(button_AcknowledgeAllAlerts);

    layout->addWidget(new QLabel("Alerts"));

    alertList_ = new QTableWidget();
    alertList_->setColumnCount(2);
    QStringList labels{"Code", ""};
    alertList_->setHorizontalHeaderLabels(labels);
    alertList_->verticalHeader()->setVisible(false);
    layout->addWidget(alertList_);

    messages_ = new QLabel();
    layout->addWidget(messages_);

    if (iface)
    {
        controller = iface->CreateInterface<AlertsIntfController>(m_listener);
        if (controller)
        {
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
    QStatus status;

    if (controller)
    {
        qWarning() << "Alerts getting properties";

        status = controller->GetAlerts();
        if (status != ER_OK)
        {
            qWarning() << "Alerts::fetchProperties Failed to get Alerts" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_Alerts::slotClickGetAlertCodesDescription()
{
    qWarning() << "Alerts::slotClickGetAlertCodesDescription";

    qcc::String languageTag {};

    bool ok = true;

    if (ok)
    {
        QStatus status = controller->GetAlertCodesDescription(languageTag, NULL);
        if (status != ER_OK)
        {
            qWarning() << "Alerts::slotClick Failed to call GetAlertCodesDescription" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_Alerts::slotClickAcknowledgeAlert()
{
    qWarning() << "Alerts::slotClickAcknowledgeAlert";

    auto* ackButton = dynamic_cast<QPushButton*>(QObject::sender());
    QVariant var = ackButton->property("alertCode");

    uint16_t alertCode = var.toUInt();
    qWarning() << __FUNCTION__ << " alertCode " << alertCode;

    QStatus status = controller->AcknowledgeAlert(alertCode, NULL);
    if (status != ER_OK)
    {
        qWarning() << "Alerts::slotClick Failed to call AcknowledgeAlert" << QCC_StatusText(status);
    }
}



void org_alljoyn_SmartSpaces_Operation_Alerts::slotClickAcknowledgeAllAlerts()
{
    qWarning() << "Alerts::slotClickAcknowledgeAllAlerts";

    bool ok = true;

    if (ok)
    {
        QStatus status = controller->AcknowledgeAllAlerts(NULL);
        if (status != ER_OK)
        {
            qWarning() << "Alerts::slotClick Failed to call AcknowledgeAllAlerts" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_Alerts::slotOnResponseGetAlerts(QStatus status, const std::vector<AlertsInterface::AlertRecord>& value)
{
    qWarning() << "Alerts::slotOnResponseGetAlerts";
    showAlerts(value);
}



void org_alljoyn_SmartSpaces_Operation_Alerts::slotOnAlertsChanged(const std::vector<AlertsInterface::AlertRecord>& value)
{
    qWarning() << "Alerts::slotOnAlertsChanged";
    showAlerts(value);
}



void    
org_alljoyn_SmartSpaces_Operation_Alerts::showAlerts(const vector<AlertsInterface::AlertRecord>& alerts)
{
    alertList_->clearContents();
    alertList_->setRowCount(alerts.size());

    for (size_t row = 0; row < alerts.size(); ++row)
    {
        auto& alert = alerts[row];
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

        ostringstream codeStrm;
        codeStrm << "<center>";

        switch (alert.severity)
        {
        case AlertsInterface::SEVERITY_ALARM:
            codeStrm << "<font color=\"red\">";
            break;

        case AlertsInterface::SEVERITY_FAULT:
            codeStrm << "<font color=\"orange\">";
            break;

        default:
            codeStrm << "<font>";
            break;
        }

        codeStrm << code << "</font></center>";
        alertList_->setCellWidget(row, 0, new QLabel(QString::fromStdString(codeStrm.str())));

        if (alert.needAcknowledgement)
        {
            auto* ack = new QPushButton("Ack");
            ack->setProperty("alertCode", QVariant(alert.alertCode)); 
            alertList_->setCellWidget(row, 1, ack);

            QObject::connect(ack, SIGNAL(clicked()), this, SLOT(slotClickAcknowledgeAlert()));
        }
    }

    alertList_->show();
}



void org_alljoyn_SmartSpaces_Operation_Alerts::slotOnResponseMethodGetAlertCodesDescription(QStatus status, const std::vector<AlertsInterface::AlertCodesDescriptor>& description, const QString& errorName)
{
    if (status == ER_OK)
    {
        qInfo() << "Alerts::slotOnResponseMethodGetAlertCodesDescription";
        alertDescrs = description;
        messages_->setText(QStringFrom(description));
    }
    else
    {
        qWarning() << "Alerts::slotOnResponseMethodGetAlertCodesDescription Received error = " << errorName;
    }
}



void org_alljoyn_SmartSpaces_Operation_Alerts::slotOnResponseMethodAcknowledgeAlert(QStatus status, const QString& errorName)
{
    if (status == ER_OK)
    {
        qInfo() << "Alerts::slotOnResponseMethodAcknowledgeAlert";
    }
    else
    {
        qWarning() << "Alerts::slotOnResponseMethodAcknowledgeAlert Received error = " << errorName;
    }
}



void org_alljoyn_SmartSpaces_Operation_Alerts::slotOnResponseMethodAcknowledgeAllAlerts(QStatus status, const QString& errorName)
{
    if (status == ER_OK)
    {
        qInfo() << "Alerts::slotOnResponseMethodAcknowledgeAllAlerts";
    }
    else
    {
        qWarning() << "Alerts::slotOnResponseMethodAcknowledgeAllAlerts Received error = " << errorName;
    }
}
