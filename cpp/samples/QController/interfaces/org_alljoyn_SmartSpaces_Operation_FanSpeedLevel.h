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

#ifndef org_alljoyn_SmartSpaces_Operation_FanSpeedLevel_H_
#define org_alljoyn_SmartSpaces_Operation_FanSpeedLevel_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <alljoyn/cdm/interfaces/operation/FanSpeedLevelInterface.h>
#include <alljoyn/cdm/interfaces/operation/FanSpeedLevelIntfController.h>
#include <alljoyn/cdm/interfaces/operation/FanSpeedLevelIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_FanSpeedLevel : public QWidget, public ajn::services::FanSpeedLevelIntfControllerListener
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Operation_FanSpeedLevel(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Operation_FanSpeedLevel();

    // Slots mirror the callbacks to avoid threading issues
private slots:

    void slotOnResponseGetFanSpeedLevel(QStatus status, const uint8_t value);
    void slotOnFanSpeedLevelChanged(const uint8_t value);
    void slotOnResponseSetFanSpeedLevel(QStatus status);
    void slotSetFanSpeedLevel();
    void slotOnResponseGetMaxFanSpeedLevel(QStatus status, const uint8_t value);
    void slotOnMaxFanSpeedLevelChanged(const uint8_t value);
    void slotOnResponseGetAutoMode(QStatus status, const AutoMode value);
    void slotOnAutoModeChanged(const AutoMode value);
    void slotOnResponseSetAutoMode(QStatus status);
    void slotSetAutoMode();

public:
    // ajn::services::FanSpeedLevelIntfControllerListener
    void OnResponseGetFanSpeedLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetFanSpeedLevel", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(uint8_t, value)
                          );
    }
    void OnFanSpeedLevelChanged(const qcc::String& objectPath, const uint8_t value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnFanSpeedLevelChanged", Qt::QueuedConnection,
                          Q_ARG(uint8_t, value)
                          );
    }
    void OnResponseSetFanSpeedLevel(QStatus status, const qcc::String& objectPath, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseSetFanSpeedLevel", Qt::QueuedConnection,
                          Q_ARG(QStatus, status)
                          );
    }
    void OnResponseGetMaxFanSpeedLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetMaxFanSpeedLevel", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(uint8_t, value)
                          );
    }
    void OnMaxFanSpeedLevelChanged(const qcc::String& objectPath, const uint8_t value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnMaxFanSpeedLevelChanged", Qt::QueuedConnection,
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
    ajn::services::FanSpeedLevelIntfControllerPtr controller;


    QLineEdit* edit_FanSpeedLevel;
    QLineEdit* edit_MaxFanSpeedLevel;
    QLineEdit* edit_AutoMode;
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_FanSpeedLevel_H_ */
