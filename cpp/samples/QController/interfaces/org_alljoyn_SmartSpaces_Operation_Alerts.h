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

#ifndef org_alljoyn_SmartSpaces_Operation_Alerts_H_
#define org_alljoyn_SmartSpaces_Operation_Alerts_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <alljoyn/cdm/interfaces/operation/AlertsInterface.h>
#include <alljoyn/cdm/interfaces/operation/AlertsIntfController.h>
#include <alljoyn/cdm/interfaces/operation/AlertsIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_Alerts : public QWidget, public ajn::services::AlertsIntfControllerListener
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

    void slotOnResponseGetAlerts(QStatus status, const std::vector<AlertRecord>& value);
    void slotOnAlertsChanged(const std::vector<AlertRecord>& value);

public:
    // ajn::services::AlertsIntfControllerListener
    void OnResponseGetAlerts(QStatus status, const qcc::String& objectPath, const std::vector<AlertRecord>& value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetAlerts", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(std::vector<AlertRecord>, value)
                          );
    }
    void OnAlertsChanged(const qcc::String& objectPath, const std::vector<AlertRecord>& value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnAlertsChanged", Qt::QueuedConnection,
                          Q_ARG(std::vector<AlertRecord>, value)
                          );
    }

private:
    ajn::services::AlertsIntfControllerPtr controller;

    QPushButton* button_GetAlertCodesDescription;
    QPushButton* button_AcknowledgeAlert;
    QPushButton* button_AcknowledgeAllAlerts;

    QLineEdit* edit_Alerts;
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_Alerts_H_ */
