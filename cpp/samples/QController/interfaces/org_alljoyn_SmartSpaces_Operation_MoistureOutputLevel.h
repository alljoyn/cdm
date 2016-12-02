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

#ifndef org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel_H_
#define org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <interfaces/common/operation/MoistureOutputLevelInterface.h>
#include <interfaces/controller/operation/MoistureOutputLevelIntfController.h>
#include <interfaces/controller/operation/MoistureOutputLevelIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel : public QWidget
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel();

    // Slots mirror the callbacks to avoid threading issues
private slots:

    void slotOnResponseGetMoistureOutputLevel(QStatus status, const uint8_t value);
    void slotOnMoistureOutputLevelChanged(const uint8_t value);
    void slotOnResponseSetMoistureOutputLevel(QStatus status);
    void slotSetMoistureOutputLevel();
    void slotOnResponseGetMaxMoistureOutputLevel(QStatus status, const uint8_t value);
    void slotOnMaxMoistureOutputLevelChanged(const uint8_t value);
    void slotOnResponseGetAutoMode(QStatus status, const MoistureOutputLevelInterface::AutoMode value);
    void slotOnAutoModeChanged(const MoistureOutputLevelInterface::AutoMode value);
    void slotOnResponseSetAutoMode(QStatus status);
    void slotSetAutoMode();

public:
    // ajn::services::MoistureOutputLevelIntfControllerListener
    class Listener: public ajn::services::MoistureOutputLevelIntfControllerListener
    {
    public:
        QWidget* m_widget;

        Listener(QWidget* widget)
          : m_widget(widget)
        {
        }

        virtual void OnResponseGetMoistureOutputLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetMoistureOutputLevel", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(uint8_t, value)
                              );
        }
        virtual void OnMoistureOutputLevelChanged(const qcc::String& objectPath, const uint8_t value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnMoistureOutputLevelChanged", Qt::QueuedConnection,
                              Q_ARG(uint8_t, value)
                              );
        }
        virtual void OnResponseSetMoistureOutputLevel(QStatus status, const qcc::String& objectPath, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseSetMoistureOutputLevel", Qt::QueuedConnection,
                              Q_ARG(QStatus, status)
                              );
        }
        virtual void OnResponseGetMaxMoistureOutputLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetMaxMoistureOutputLevel", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(uint8_t, value)
                              );
        }
        virtual void OnMaxMoistureOutputLevelChanged(const qcc::String& objectPath, const uint8_t value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnMaxMoistureOutputLevelChanged", Qt::QueuedConnection,
                              Q_ARG(uint8_t, value)
                              );
        }
        virtual void OnResponseGetAutoMode(QStatus status, const qcc::String& objectPath, const MoistureOutputLevelInterface::AutoMode value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetAutoMode", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(MoistureOutputLevelInterface::AutoMode, value)
                              );
        }
        virtual void OnAutoModeChanged(const qcc::String& objectPath, const MoistureOutputLevelInterface::AutoMode value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnAutoModeChanged", Qt::QueuedConnection,
                              Q_ARG(MoistureOutputLevelInterface::AutoMode, value)
                              );
        }
        virtual void OnResponseSetAutoMode(QStatus status, const qcc::String& objectPath, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseSetAutoMode", Qt::QueuedConnection,
                              Q_ARG(QStatus, status)
                              );
        }
    };

private:
    Ref<ajn::services::MoistureOutputLevelIntfController> controller;
    Ref<Listener> m_listener;


    QLineEdit* edit_MoistureOutputLevel;
    QLineEdit* edit_MaxMoistureOutputLevel;
    QLineEdit* edit_AutoMode;
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel_H_ */
