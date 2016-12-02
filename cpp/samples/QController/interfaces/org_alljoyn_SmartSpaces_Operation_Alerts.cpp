/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include "org_alljoyn_SmartSpaces_Operation_Alerts.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>

using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_Alerts*>();

org_alljoyn_SmartSpaces_Operation_Alerts::org_alljoyn_SmartSpaces_Operation_Alerts(CommonControllerInterface *iface) : controller(NULL)
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);


    // Create button for GetAlertCodesDescription
    button_GetAlertCodesDescription = new QPushButton("GetAlertCodesDescription");
    button_GetAlertCodesDescription->setToolTip("Get alert codes description.");
    QObject::connect(button_GetAlertCodesDescription, SIGNAL(clicked()), this, SLOT(slotClickGetAlertCodesDescription()));
    layout->addWidget(button_GetAlertCodesDescription);
    // Create button for AcknowledgeAlert
    button_AcknowledgeAlert = new QPushButton("AcknowledgeAlert");
    button_AcknowledgeAlert->setToolTip("Reset the user acknowledgment request of a specific pending alert.");
    QObject::connect(button_AcknowledgeAlert, SIGNAL(clicked()), this, SLOT(slotClickAcknowledgeAlert()));
    layout->addWidget(button_AcknowledgeAlert);
    // Create button for AcknowledgeAllAlerts
    button_AcknowledgeAllAlerts = new QPushButton("AcknowledgeAllAlerts");
    button_AcknowledgeAllAlerts->setToolTip("Reset the user acknowledgment request of any pending alert.");
    QObject::connect(button_AcknowledgeAllAlerts, SIGNAL(clicked()), this, SLOT(slotClickAcknowledgeAllAlerts()));
    layout->addWidget(button_AcknowledgeAllAlerts);

    layout->addWidget(new QLabel("Alerts"));
    // Create line edit for Alerts
    edit_Alerts = new QLineEdit();
    edit_Alerts->setToolTip("List of current pending alerts.");
    edit_Alerts->setReadOnly(true);
    layout->addWidget(edit_Alerts);

    if (iface)
    {
        controller = iface->CreateInterface<AlertsIntfController>(*this);
        if (controller)
        {
            qWarning() << __FUNCTION__ << " Getting properties";

            QStatus status;
            // Get current values
            status = controller->GetAlerts();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get Alerts" << QCC_StatusText(status);
            }
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

void org_alljoyn_SmartSpaces_Operation_Alerts::slotClickGetAlertCodesDescription()
{
    qWarning() << __FUNCTION__;

    qcc::String languageTag {};

    QStatus status = controller->GetAlertCodesDescription(languageTag, NULL);
    if (status != ER_OK)
    {
        qWarning() << __FUNCTION__ << " Failed to call GetAlertCodesDescription" << QCC_StatusText(status);
    }
}
void org_alljoyn_SmartSpaces_Operation_Alerts::slotClickAcknowledgeAlert()
{
    qWarning() << __FUNCTION__;

    uint16_t alertCode {};

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


void org_alljoyn_SmartSpaces_Operation_Alerts::slotOnResponseGetAlerts(QStatus status, const std::vector<AlertRecord>& value)
{
    qWarning() << __FUNCTION__;
    edit_Alerts->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_Alerts::slotOnAlertsChanged(const std::vector<AlertRecord>& value)
{
    qWarning() << __FUNCTION__;
    edit_Alerts->setText(QStringFrom(value));
}

