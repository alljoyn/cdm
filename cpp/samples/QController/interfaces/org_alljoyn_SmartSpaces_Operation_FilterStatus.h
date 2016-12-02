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

#ifndef org_alljoyn_SmartSpaces_Operation_FilterStatus_H_
#define org_alljoyn_SmartSpaces_Operation_FilterStatus_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <alljoyn/cdm/interfaces/operation/FilterStatusInterface.h>
#include <alljoyn/cdm/interfaces/operation/FilterStatusIntfController.h>
#include <alljoyn/cdm/interfaces/operation/FilterStatusIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_FilterStatus : public QWidget, public ajn::services::FilterStatusIntfControllerListener
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Operation_FilterStatus(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Operation_FilterStatus();

    // Slots mirror the callbacks to avoid threading issues
private slots:

    void slotOnResponseGetExpectedLifeInDays(QStatus status, const uint16_t value);
    void slotOnExpectedLifeInDaysChanged(const uint16_t value);
    void slotOnResponseGetIsCleanable(QStatus status, const bool value);
    void slotOnIsCleanableChanged(const bool value);
    void slotOnResponseGetOrderPercentage(QStatus status, const uint8_t value);
    void slotOnOrderPercentageChanged(const uint8_t value);
    void slotOnResponseGetManufacturer(QStatus status, const qcc::String& value);
    void slotOnManufacturerChanged(const qcc::String& value);
    void slotOnResponseGetPartNumber(QStatus status, const qcc::String& value);
    void slotOnPartNumberChanged(const qcc::String& value);
    void slotOnResponseGetUrl(QStatus status, const qcc::String& value);
    void slotOnUrlChanged(const qcc::String& value);
    void slotOnResponseGetLifeRemaining(QStatus status, const uint8_t value);
    void slotOnLifeRemainingChanged(const uint8_t value);

public:
    // ajn::services::FilterStatusIntfControllerListener
    void OnResponseGetExpectedLifeInDays(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetExpectedLifeInDays", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(uint16_t, value)
                          );
    }
    void OnExpectedLifeInDaysChanged(const qcc::String& objectPath, const uint16_t value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnExpectedLifeInDaysChanged", Qt::QueuedConnection,
                          Q_ARG(uint16_t, value)
                          );
    }
    void OnResponseGetIsCleanable(QStatus status, const qcc::String& objectPath, const bool value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetIsCleanable", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(bool, value)
                          );
    }
    void OnIsCleanableChanged(const qcc::String& objectPath, const bool value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnIsCleanableChanged", Qt::QueuedConnection,
                          Q_ARG(bool, value)
                          );
    }
    void OnResponseGetOrderPercentage(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetOrderPercentage", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(uint8_t, value)
                          );
    }
    void OnOrderPercentageChanged(const qcc::String& objectPath, const uint8_t value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnOrderPercentageChanged", Qt::QueuedConnection,
                          Q_ARG(uint8_t, value)
                          );
    }
    void OnResponseGetManufacturer(QStatus status, const qcc::String& objectPath, const qcc::String& value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetManufacturer", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(qcc::String, value)
                          );
    }
    void OnManufacturerChanged(const qcc::String& objectPath, const qcc::String& value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnManufacturerChanged", Qt::QueuedConnection,
                          Q_ARG(qcc::String, value)
                          );
    }
    void OnResponseGetPartNumber(QStatus status, const qcc::String& objectPath, const qcc::String& value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetPartNumber", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(qcc::String, value)
                          );
    }
    void OnPartNumberChanged(const qcc::String& objectPath, const qcc::String& value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnPartNumberChanged", Qt::QueuedConnection,
                          Q_ARG(qcc::String, value)
                          );
    }
    void OnResponseGetUrl(QStatus status, const qcc::String& objectPath, const qcc::String& value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetUrl", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(qcc::String, value)
                          );
    }
    void OnUrlChanged(const qcc::String& objectPath, const qcc::String& value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnUrlChanged", Qt::QueuedConnection,
                          Q_ARG(qcc::String, value)
                          );
    }
    void OnResponseGetLifeRemaining(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetLifeRemaining", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(uint8_t, value)
                          );
    }
    void OnLifeRemainingChanged(const qcc::String& objectPath, const uint8_t value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnLifeRemainingChanged", Qt::QueuedConnection,
                          Q_ARG(uint8_t, value)
                          );
    }

private:
    ajn::services::FilterStatusIntfControllerPtr controller;


    QLineEdit* edit_ExpectedLifeInDays;
    QLineEdit* edit_IsCleanable;
    QLineEdit* edit_OrderPercentage;
    QLineEdit* edit_Manufacturer;
    QLineEdit* edit_PartNumber;
    QLineEdit* edit_Url;
    QLineEdit* edit_LifeRemaining;
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_FilterStatus_H_ */
