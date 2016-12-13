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

#include <interfaces/common/operation/EnergyUsageInterface.h>
#include <interfaces/controller/operation/EnergyUsageIntfController.h>
#include <interfaces/controller/operation/EnergyUsageIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_EnergyUsage : public QWidget
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
    void slotOnResponseMethodResetCumulativeEnergy(QStatus status, const QString& errorName);

public:
    // ajn::services::EnergyUsageIntfControllerListener
    class Listener: public ajn::services::EnergyUsageIntfControllerListener
    {
    public:
        QWidget* m_widget;

        Listener(QWidget* widget)
          : m_widget(widget)
        {
        }

        virtual void OnResponseGetCumulativeEnergy(QStatus status, const qcc::String& objectPath, const double value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetCumulativeEnergy", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(double, value)
                              );
        }
        virtual void OnCumulativeEnergyChanged(const qcc::String& objectPath, const double value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnCumulativeEnergyChanged", Qt::QueuedConnection,
                              Q_ARG(double, value)
                              );
        }
        virtual void OnResponseGetPrecision(QStatus status, const qcc::String& objectPath, const double value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetPrecision", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(double, value)
                              );
        }
        virtual void OnPrecisionChanged(const qcc::String& objectPath, const double value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnPrecisionChanged", Qt::QueuedConnection,
                              Q_ARG(double, value)
                              );
        }
        virtual void OnResponseGetUpdateMinTime(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetUpdateMinTime", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(uint16_t, value)
                              );
        }
        virtual void OnUpdateMinTimeChanged(const qcc::String& objectPath, const uint16_t value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnUpdateMinTimeChanged", Qt::QueuedConnection,
                              Q_ARG(uint16_t, value)
                              );
        }
        virtual void OnResponseResetCumulativeEnergy(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseMethodResetCumulativeEnergy", Qt::QueuedConnection,
                              Q_ARG(QStatus, status), Q_ARG(QString, QString(errorName))
                              );
        }
    };

private:
    Ref<ajn::services::EnergyUsageIntfController> controller;
    Ref<Listener> m_listener;

    QPushButton* button_ResetCumulativeEnergy;

    QLineEdit* edit_CumulativeEnergy;
    QLineEdit* edit_Precision;
    QLineEdit* edit_UpdateMinTime;

    void    fetchProperties();

protected:
    virtual void showEvent(QShowEvent *event) override
    {
        fetchProperties();
    }
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_EnergyUsage_H_ */
