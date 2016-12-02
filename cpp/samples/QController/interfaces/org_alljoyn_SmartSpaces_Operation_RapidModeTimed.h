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

#ifndef org_alljoyn_SmartSpaces_Operation_RapidModeTimed_H_
#define org_alljoyn_SmartSpaces_Operation_RapidModeTimed_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <alljoyn/cdm/interfaces/operation/RapidModeTimedInterface.h>
#include <alljoyn/cdm/interfaces/operation/RapidModeTimedIntfController.h>
#include <alljoyn/cdm/interfaces/operation/RapidModeTimedIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_RapidModeTimed : public QWidget, public ajn::services::RapidModeTimedIntfControllerListener
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Operation_RapidModeTimed(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Operation_RapidModeTimed();

    // Slots mirror the callbacks to avoid threading issues
private slots:

    void slotOnResponseGetRapidModeMinutesRemaining(QStatus status, const uint16_t value);
    void slotOnRapidModeMinutesRemainingChanged(const uint16_t value);
    void slotOnResponseSetRapidModeMinutesRemaining(QStatus status);
    void slotSetRapidModeMinutesRemaining();
    void slotOnResponseGetMaxSetMinutes(QStatus status, const uint16_t value);
    void slotOnMaxSetMinutesChanged(const uint16_t value);

public:
    // ajn::services::RapidModeTimedIntfControllerListener
    void OnResponseGetRapidModeMinutesRemaining(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetRapidModeMinutesRemaining", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(uint16_t, value)
                          );
    }
    void OnRapidModeMinutesRemainingChanged(const qcc::String& objectPath, const uint16_t value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnRapidModeMinutesRemainingChanged", Qt::QueuedConnection,
                          Q_ARG(uint16_t, value)
                          );
    }
    void OnResponseSetRapidModeMinutesRemaining(QStatus status, const qcc::String& objectPath, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseSetRapidModeMinutesRemaining", Qt::QueuedConnection,
                          Q_ARG(QStatus, status)
                          );
    }
    void OnResponseGetMaxSetMinutes(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetMaxSetMinutes", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(uint16_t, value)
                          );
    }
    void OnMaxSetMinutesChanged(const qcc::String& objectPath, const uint16_t value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnMaxSetMinutesChanged", Qt::QueuedConnection,
                          Q_ARG(uint16_t, value)
                          );
    }

private:
    ajn::services::RapidModeTimedIntfControllerPtr controller;


    QLineEdit* edit_RapidModeMinutesRemaining;
    QLineEdit* edit_MaxSetMinutes;
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_RapidModeTimed_H_ */
