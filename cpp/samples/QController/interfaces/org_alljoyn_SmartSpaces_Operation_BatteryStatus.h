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

#ifndef org_alljoyn_SmartSpaces_Operation_BatteryStatus_H_
#define org_alljoyn_SmartSpaces_Operation_BatteryStatus_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <alljoyn/cdm/interfaces/operation/BatteryStatusInterface.h>
#include <alljoyn/cdm/interfaces/operation/BatteryStatusIntfController.h>
#include <alljoyn/cdm/interfaces/operation/BatteryStatusIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_BatteryStatus : public QWidget, public ajn::services::BatteryStatusIntfControllerListener
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Operation_BatteryStatus(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Operation_BatteryStatus();

    // Slots mirror the callbacks to avoid threading issues
private slots:

    void slotOnResponseGetCurrentValue(QStatus status, const uint8_t value);
    void slotOnCurrentValueChanged(const uint8_t value);
    void slotOnResponseGetIsCharging(QStatus status, const bool value);
    void slotOnIsChargingChanged(const bool value);

public:
    // ajn::services::BatteryStatusIntfControllerListener
    void OnResponseGetCurrentValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetCurrentValue", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(uint8_t, value)
                          );
    }
    void OnCurrentValueChanged(const qcc::String& objectPath, const uint8_t value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnCurrentValueChanged", Qt::QueuedConnection,
                          Q_ARG(uint8_t, value)
                          );
    }
    void OnResponseGetIsCharging(QStatus status, const qcc::String& objectPath, const bool value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetIsCharging", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(bool, value)
                          );
    }
    void OnIsChargingChanged(const qcc::String& objectPath, const bool value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnIsChargingChanged", Qt::QueuedConnection,
                          Q_ARG(bool, value)
                          );
    }

private:
    ajn::services::BatteryStatusIntfControllerPtr controller;


    QLineEdit* edit_CurrentValue;
    QLineEdit* edit_IsCharging;
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_BatteryStatus_H_ */
