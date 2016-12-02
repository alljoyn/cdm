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

#ifndef org_alljoyn_SmartSpaces_Operation_Timer_H_
#define org_alljoyn_SmartSpaces_Operation_Timer_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <alljoyn/cdm/interfaces/operation/TimerInterface.h>
#include <alljoyn/cdm/interfaces/operation/TimerIntfController.h>
#include <alljoyn/cdm/interfaces/operation/TimerIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_Timer : public QWidget, public ajn::services::TimerIntfControllerListener
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Operation_Timer(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Operation_Timer();

    // Slots mirror the callbacks to avoid threading issues
private slots:
    void slotClickSetTargetTimeToStart();
    void slotClickSetTargetTimeToStop();

    void slotOnResponseGetReferenceTimer(QStatus status, const int32_t value);
    void slotOnReferenceTimerChanged(const int32_t value);
    void slotOnResponseGetTargetTimeToStart(QStatus status, const int32_t value);
    void slotOnTargetTimeToStartChanged(const int32_t value);
    void slotOnResponseGetTargetTimeToStop(QStatus status, const int32_t value);
    void slotOnTargetTimeToStopChanged(const int32_t value);
    void slotOnResponseGetEstimatedTimeToEnd(QStatus status, const int32_t value);
    void slotOnEstimatedTimeToEndChanged(const int32_t value);
    void slotOnResponseGetRunningTime(QStatus status, const int32_t value);
    void slotOnRunningTimeChanged(const int32_t value);
    void slotOnResponseGetTargetDuration(QStatus status, const int32_t value);
    void slotOnTargetDurationChanged(const int32_t value);

public:
    // ajn::services::TimerIntfControllerListener
    void OnResponseGetReferenceTimer(QStatus status, const qcc::String& objectPath, const int32_t value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetReferenceTimer", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(int32_t, value)
                          );
    }
    void OnReferenceTimerChanged(const qcc::String& objectPath, const int32_t value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnReferenceTimerChanged", Qt::QueuedConnection,
                          Q_ARG(int32_t, value)
                          );
    }
    void OnResponseGetTargetTimeToStart(QStatus status, const qcc::String& objectPath, const int32_t value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetTargetTimeToStart", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(int32_t, value)
                          );
    }
    void OnTargetTimeToStartChanged(const qcc::String& objectPath, const int32_t value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnTargetTimeToStartChanged", Qt::QueuedConnection,
                          Q_ARG(int32_t, value)
                          );
    }
    void OnResponseGetTargetTimeToStop(QStatus status, const qcc::String& objectPath, const int32_t value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetTargetTimeToStop", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(int32_t, value)
                          );
    }
    void OnTargetTimeToStopChanged(const qcc::String& objectPath, const int32_t value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnTargetTimeToStopChanged", Qt::QueuedConnection,
                          Q_ARG(int32_t, value)
                          );
    }
    void OnResponseGetEstimatedTimeToEnd(QStatus status, const qcc::String& objectPath, const int32_t value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetEstimatedTimeToEnd", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(int32_t, value)
                          );
    }
    void OnEstimatedTimeToEndChanged(const qcc::String& objectPath, const int32_t value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnEstimatedTimeToEndChanged", Qt::QueuedConnection,
                          Q_ARG(int32_t, value)
                          );
    }
    void OnResponseGetRunningTime(QStatus status, const qcc::String& objectPath, const int32_t value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetRunningTime", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(int32_t, value)
                          );
    }
    void OnRunningTimeChanged(const qcc::String& objectPath, const int32_t value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnRunningTimeChanged", Qt::QueuedConnection,
                          Q_ARG(int32_t, value)
                          );
    }
    void OnResponseGetTargetDuration(QStatus status, const qcc::String& objectPath, const int32_t value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetTargetDuration", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(int32_t, value)
                          );
    }
    void OnTargetDurationChanged(const qcc::String& objectPath, const int32_t value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnTargetDurationChanged", Qt::QueuedConnection,
                          Q_ARG(int32_t, value)
                          );
    }

private:
    ajn::services::TimerIntfControllerPtr controller;

    QPushButton* button_SetTargetTimeToStart;
    QPushButton* button_SetTargetTimeToStop;

    QLineEdit* edit_ReferenceTimer;
    QLineEdit* edit_TargetTimeToStart;
    QLineEdit* edit_TargetTimeToStop;
    QLineEdit* edit_EstimatedTimeToEnd;
    QLineEdit* edit_RunningTime;
    QLineEdit* edit_TargetDuration;
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_Timer_H_ */
