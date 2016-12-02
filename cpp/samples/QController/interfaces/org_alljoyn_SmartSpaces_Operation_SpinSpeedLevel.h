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

#ifndef org_alljoyn_SmartSpaces_Operation_SpinSpeedLevel_H_
#define org_alljoyn_SmartSpaces_Operation_SpinSpeedLevel_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <alljoyn/cdm/interfaces/operation/SpinSpeedLevelInterface.h>
#include <alljoyn/cdm/interfaces/operation/SpinSpeedLevelIntfController.h>
#include <alljoyn/cdm/interfaces/operation/SpinSpeedLevelIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_SpinSpeedLevel : public QWidget, public ajn::services::SpinSpeedLevelIntfControllerListener
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Operation_SpinSpeedLevel(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Operation_SpinSpeedLevel();

    // Slots mirror the callbacks to avoid threading issues
private slots:

    void slotOnResponseGetMaxLevel(QStatus status, const uint8_t value);
    void slotOnMaxLevelChanged(const uint8_t value);
    void slotOnResponseGetTargetLevel(QStatus status, const uint8_t value);
    void slotOnTargetLevelChanged(const uint8_t value);
    void slotOnResponseSetTargetLevel(QStatus status);
    void slotSetTargetLevel();
    void slotOnResponseGetSelectableLevels(QStatus status, const std::vector<uint8_t>& value);
    void slotOnSelectableLevelsChanged(const std::vector<uint8_t>& value);

public:
    // ajn::services::SpinSpeedLevelIntfControllerListener
    void OnResponseGetMaxLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetMaxLevel", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(uint8_t, value)
                          );
    }
    void OnMaxLevelChanged(const qcc::String& objectPath, const uint8_t value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnMaxLevelChanged", Qt::QueuedConnection,
                          Q_ARG(uint8_t, value)
                          );
    }
    void OnResponseGetTargetLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetTargetLevel", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(uint8_t, value)
                          );
    }
    void OnTargetLevelChanged(const qcc::String& objectPath, const uint8_t value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnTargetLevelChanged", Qt::QueuedConnection,
                          Q_ARG(uint8_t, value)
                          );
    }
    void OnResponseSetTargetLevel(QStatus status, const qcc::String& objectPath, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseSetTargetLevel", Qt::QueuedConnection,
                          Q_ARG(QStatus, status)
                          );
    }
    void OnResponseGetSelectableLevels(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetSelectableLevels", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(std::vector<uint8_t>, value)
                          );
    }
    void OnSelectableLevelsChanged(const qcc::String& objectPath, const std::vector<uint8_t>& value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnSelectableLevelsChanged", Qt::QueuedConnection,
                          Q_ARG(std::vector<uint8_t>, value)
                          );
    }

private:
    ajn::services::SpinSpeedLevelIntfControllerPtr controller;


    QLineEdit* edit_MaxLevel;
    QLineEdit* edit_TargetLevel;
    QLineEdit* edit_SelectableLevels;
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_SpinSpeedLevel_H_ */
