/******************************************************************************
 *  *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#ifndef org_alljoyn_SmartSpaces_Operation_FilterStatus_H_
#define org_alljoyn_SmartSpaces_Operation_FilterStatus_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <interfaces/common/operation/FilterStatusInterface.h>
#include <interfaces/controller/operation/FilterStatusIntfController.h>
#include <interfaces/controller/operation/FilterStatusIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_FilterStatus : public QWidget
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
    class Listener: public ajn::services::FilterStatusIntfControllerListener
    {
    public:
        QWidget* m_widget;

        Listener(QWidget* widget)
          : m_widget(widget)
        {
        }

        virtual void OnResponseGetExpectedLifeInDays(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetExpectedLifeInDays", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(uint16_t, value)
                              );
        }
        virtual void OnExpectedLifeInDaysChanged(const qcc::String& objectPath, const uint16_t value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnExpectedLifeInDaysChanged", Qt::QueuedConnection,
                              Q_ARG(uint16_t, value)
                              );
        }
        virtual void OnResponseGetIsCleanable(QStatus status, const qcc::String& objectPath, const bool value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetIsCleanable", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(bool, value)
                              );
        }
        virtual void OnIsCleanableChanged(const qcc::String& objectPath, const bool value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnIsCleanableChanged", Qt::QueuedConnection,
                              Q_ARG(bool, value)
                              );
        }
        virtual void OnResponseGetOrderPercentage(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetOrderPercentage", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(uint8_t, value)
                              );
        }
        virtual void OnOrderPercentageChanged(const qcc::String& objectPath, const uint8_t value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnOrderPercentageChanged", Qt::QueuedConnection,
                              Q_ARG(uint8_t, value)
                              );
        }
        virtual void OnResponseGetManufacturer(QStatus status, const qcc::String& objectPath, const qcc::String& value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetManufacturer", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(qcc::String, value)
                              );
        }
        virtual void OnManufacturerChanged(const qcc::String& objectPath, const qcc::String& value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnManufacturerChanged", Qt::QueuedConnection,
                              Q_ARG(qcc::String, value)
                              );
        }
        virtual void OnResponseGetPartNumber(QStatus status, const qcc::String& objectPath, const qcc::String& value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetPartNumber", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(qcc::String, value)
                              );
        }
        virtual void OnPartNumberChanged(const qcc::String& objectPath, const qcc::String& value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnPartNumberChanged", Qt::QueuedConnection,
                              Q_ARG(qcc::String, value)
                              );
        }
        virtual void OnResponseGetUrl(QStatus status, const qcc::String& objectPath, const qcc::String& value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetUrl", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(qcc::String, value)
                              );
        }
        virtual void OnUrlChanged(const qcc::String& objectPath, const qcc::String& value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnUrlChanged", Qt::QueuedConnection,
                              Q_ARG(qcc::String, value)
                              );
        }
        virtual void OnResponseGetLifeRemaining(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetLifeRemaining", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(uint8_t, value)
                              );
        }
        virtual void OnLifeRemainingChanged(const qcc::String& objectPath, const uint8_t value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnLifeRemainingChanged", Qt::QueuedConnection,
                              Q_ARG(uint8_t, value)
                              );
        }
    };

private:
    Ref<ajn::services::FilterStatusIntfController> controller;
    Ref<Listener> m_listener;


    QLineEdit* edit_ExpectedLifeInDays;
    QLineEdit* edit_IsCleanable;
    QLineEdit* edit_OrderPercentage;
    QLineEdit* edit_Manufacturer;
    QLineEdit* edit_PartNumber;
    QLineEdit* edit_Url;
    QLineEdit* edit_LifeRemaining;

    void    fetchProperties();

protected:
    virtual void showEvent(QShowEvent *event) override
    {
        fetchProperties();
    }
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_FilterStatus_H_ */