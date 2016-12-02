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

#include <alljoyn/cdm/interfaces/operation/MoistureOutputLevelInterface.h>
#include <alljoyn/cdm/interfaces/operation/MoistureOutputLevelIntfController.h>
#include <alljoyn/cdm/interfaces/operation/MoistureOutputLevelIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel : public QWidget, public ajn::services::MoistureOutputLevelIntfControllerListener
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
    void slotOnResponseGetAutoMode(QStatus status, const AutoMode value);
    void slotOnAutoModeChanged(const AutoMode value);
    void slotOnResponseSetAutoMode(QStatus status);
    void slotSetAutoMode();

public:
    // ajn::services::MoistureOutputLevelIntfControllerListener
    void OnResponseGetMoistureOutputLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetMoistureOutputLevel", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(uint8_t, value)
                          );
    }
    void OnMoistureOutputLevelChanged(const qcc::String& objectPath, const uint8_t value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnMoistureOutputLevelChanged", Qt::QueuedConnection,
                          Q_ARG(uint8_t, value)
                          );
    }
    void OnResponseSetMoistureOutputLevel(QStatus status, const qcc::String& objectPath, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseSetMoistureOutputLevel", Qt::QueuedConnection,
                          Q_ARG(QStatus, status)
                          );
    }
    void OnResponseGetMaxMoistureOutputLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetMaxMoistureOutputLevel", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(uint8_t, value)
                          );
    }
    void OnMaxMoistureOutputLevelChanged(const qcc::String& objectPath, const uint8_t value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnMaxMoistureOutputLevelChanged", Qt::QueuedConnection,
                          Q_ARG(uint8_t, value)
                          );
    }
    void OnResponseGetAutoMode(QStatus status, const qcc::String& objectPath, const AutoMode value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetAutoMode", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(AutoMode, value)
                          );
    }
    void OnAutoModeChanged(const qcc::String& objectPath, const AutoMode value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnAutoModeChanged", Qt::QueuedConnection,
                          Q_ARG(AutoMode, value)
                          );
    }
    void OnResponseSetAutoMode(QStatus status, const qcc::String& objectPath, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseSetAutoMode", Qt::QueuedConnection,
                          Q_ARG(QStatus, status)
                          );
    }

private:
    ajn::services::MoistureOutputLevelIntfControllerPtr controller;


    QLineEdit* edit_MoistureOutputLevel;
    QLineEdit* edit_MaxMoistureOutputLevel;
    QLineEdit* edit_AutoMode;
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel_H_ */
