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

#ifndef org_alljoyn_SmartSpaces_Operation_EnergyUsage_H_
#define org_alljoyn_SmartSpaces_Operation_EnergyUsage_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <alljoyn/cdm/interfaces/operation/EnergyUsageInterface.h>
#include <alljoyn/cdm/interfaces/operation/EnergyUsageIntfController.h>
#include <alljoyn/cdm/interfaces/operation/EnergyUsageIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_EnergyUsage : public QWidget, public ajn::services::EnergyUsageIntfControllerListener
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Operation_EnergyUsage(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Operation_EnergyUsage();

    // Slots mirror the callbacks to avoid threading issues
private slots:
    void slotClickResetCumulativeEnergy();

    void slotOnResponseGetCumulativeEnergy(QStatus status, const double value);
    void slotOnCumulativeEnergyChanged(const double value);
    void slotOnResponseGetPrecision(QStatus status, const double value);
    void slotOnPrecisionChanged(const double value);
    void slotOnResponseGetUpdateMinTime(QStatus status, const uint16_t value);
    void slotOnUpdateMinTimeChanged(const uint16_t value);

public:
    // ajn::services::EnergyUsageIntfControllerListener
    void OnResponseGetCumulativeEnergy(QStatus status, const qcc::String& objectPath, const double value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetCumulativeEnergy", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(double, value)
                          );
    }
    void OnCumulativeEnergyChanged(const qcc::String& objectPath, const double value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnCumulativeEnergyChanged", Qt::QueuedConnection,
                          Q_ARG(double, value)
                          );
    }
    void OnResponseGetPrecision(QStatus status, const qcc::String& objectPath, const double value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetPrecision", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(double, value)
                          );
    }
    void OnPrecisionChanged(const qcc::String& objectPath, const double value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnPrecisionChanged", Qt::QueuedConnection,
                          Q_ARG(double, value)
                          );
    }
    void OnResponseGetUpdateMinTime(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetUpdateMinTime", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(uint16_t, value)
                          );
    }
    void OnUpdateMinTimeChanged(const qcc::String& objectPath, const uint16_t value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnUpdateMinTimeChanged", Qt::QueuedConnection,
                          Q_ARG(uint16_t, value)
                          );
    }

private:
    ajn::services::EnergyUsageIntfControllerPtr controller;

    QPushButton* button_ResetCumulativeEnergy;

    QLineEdit* edit_CumulativeEnergy;
    QLineEdit* edit_Precision;
    QLineEdit* edit_UpdateMinTime;
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_EnergyUsage_H_ */
