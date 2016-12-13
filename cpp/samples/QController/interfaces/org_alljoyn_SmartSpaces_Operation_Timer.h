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

#include <interfaces/common/operation/TimerInterface.h>
#include <interfaces/controller/operation/TimerIntfController.h>
#include <interfaces/controller/operation/TimerIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_Timer : public QWidget
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
    void slotOnResponseMethodSetTargetTimeToStart(QStatus status, const QString& errorName);
    void slotOnResponseMethodSetTargetTimeToStop(QStatus status, const QString& errorName);

public:
    // ajn::services::TimerIntfControllerListener
    class Listener: public ajn::services::TimerIntfControllerListener
    {
    public:
        QWidget* m_widget;

        Listener(QWidget* widget)
          : m_widget(widget)
        {
        }

        virtual void OnResponseGetReferenceTimer(QStatus status, const qcc::String& objectPath, const int32_t value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetReferenceTimer", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(int32_t, value)
                              );
        }
        virtual void OnReferenceTimerChanged(const qcc::String& objectPath, const int32_t value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnReferenceTimerChanged", Qt::QueuedConnection,
                              Q_ARG(int32_t, value)
                              );
        }
        virtual void OnResponseGetTargetTimeToStart(QStatus status, const qcc::String& objectPath, const int32_t value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetTargetTimeToStart", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(int32_t, value)
                              );
        }
        virtual void OnTargetTimeToStartChanged(const qcc::String& objectPath, const int32_t value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnTargetTimeToStartChanged", Qt::QueuedConnection,
                              Q_ARG(int32_t, value)
                              );
        }
        virtual void OnResponseGetTargetTimeToStop(QStatus status, const qcc::String& objectPath, const int32_t value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetTargetTimeToStop", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(int32_t, value)
                              );
        }
        virtual void OnTargetTimeToStopChanged(const qcc::String& objectPath, const int32_t value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnTargetTimeToStopChanged", Qt::QueuedConnection,
                              Q_ARG(int32_t, value)
                              );
        }
        virtual void OnResponseGetEstimatedTimeToEnd(QStatus status, const qcc::String& objectPath, const int32_t value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetEstimatedTimeToEnd", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(int32_t, value)
                              );
        }
        virtual void OnEstimatedTimeToEndChanged(const qcc::String& objectPath, const int32_t value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnEstimatedTimeToEndChanged", Qt::QueuedConnection,
                              Q_ARG(int32_t, value)
                              );
        }
        virtual void OnResponseGetRunningTime(QStatus status, const qcc::String& objectPath, const int32_t value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetRunningTime", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(int32_t, value)
                              );
        }
        virtual void OnRunningTimeChanged(const qcc::String& objectPath, const int32_t value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnRunningTimeChanged", Qt::QueuedConnection,
                              Q_ARG(int32_t, value)
                              );
        }
        virtual void OnResponseGetTargetDuration(QStatus status, const qcc::String& objectPath, const int32_t value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetTargetDuration", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(int32_t, value)
                              );
        }
        virtual void OnTargetDurationChanged(const qcc::String& objectPath, const int32_t value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnTargetDurationChanged", Qt::QueuedConnection,
                              Q_ARG(int32_t, value)
                              );
        }
        virtual void OnResponseSetTargetTimeToStart(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseMethodSetTargetTimeToStart", Qt::QueuedConnection,
                              Q_ARG(QStatus, status), Q_ARG(QString, QString(errorName))
                              );
        }
        virtual void OnResponseSetTargetTimeToStop(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseMethodSetTargetTimeToStop", Qt::QueuedConnection,
                              Q_ARG(QStatus, status), Q_ARG(QString, QString(errorName))
                              );
        }
    };

private:
    Ref<ajn::services::TimerIntfController> controller;
    Ref<Listener> m_listener;

    QPushButton* button_SetTargetTimeToStart;
    QPushButton* button_SetTargetTimeToStop;

    QLineEdit* edit_ReferenceTimer;
    QLineEdit* edit_TargetTimeToStart;
    QLineEdit* edit_TargetTimeToStop;
    QLineEdit* edit_EstimatedTimeToEnd;
    QLineEdit* edit_RunningTime;
    QLineEdit* edit_TargetDuration;

    void    fetchProperties();

protected:
    virtual void showEvent(QShowEvent *event) override
    {
        fetchProperties();
    }
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_Timer_H_ */
