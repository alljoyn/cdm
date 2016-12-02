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

#ifndef org_alljoyn_SmartSpaces_Operation_ClimateControlMode_H_
#define org_alljoyn_SmartSpaces_Operation_ClimateControlMode_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <alljoyn/cdm/interfaces/operation/ClimateControlModeInterface.h>
#include <alljoyn/cdm/interfaces/operation/ClimateControlModeIntfController.h>
#include <alljoyn/cdm/interfaces/operation/ClimateControlModeIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_ClimateControlMode : public QWidget, public ajn::services::ClimateControlModeIntfControllerListener
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Operation_ClimateControlMode(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Operation_ClimateControlMode();

    // Slots mirror the callbacks to avoid threading issues
private slots:

    void slotOnResponseGetMode(QStatus status, const Mode value);
    void slotOnModeChanged(const Mode value);
    void slotOnResponseSetMode(QStatus status);
    void slotSetMode();
    void slotOnResponseGetSupportedModes(QStatus status, const std::vector<Mode>& value);
    void slotOnSupportedModesChanged(const std::vector<Mode>& value);
    void slotOnResponseGetOperationalState(QStatus status, const OperationalState value);
    void slotOnOperationalStateChanged(const OperationalState value);

public:
    // ajn::services::ClimateControlModeIntfControllerListener
    void OnResponseGetMode(QStatus status, const qcc::String& objectPath, const Mode value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetMode", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(Mode, value)
                          );
    }
    void OnModeChanged(const qcc::String& objectPath, const Mode value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnModeChanged", Qt::QueuedConnection,
                          Q_ARG(Mode, value)
                          );
    }
    void OnResponseSetMode(QStatus status, const qcc::String& objectPath, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseSetMode", Qt::QueuedConnection,
                          Q_ARG(QStatus, status)
                          );
    }
    void OnResponseGetSupportedModes(QStatus status, const qcc::String& objectPath, const std::vector<Mode>& value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetSupportedModes", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(std::vector<Mode>, value)
                          );
    }
    void OnSupportedModesChanged(const qcc::String& objectPath, const std::vector<Mode>& value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnSupportedModesChanged", Qt::QueuedConnection,
                          Q_ARG(std::vector<Mode>, value)
                          );
    }
    void OnResponseGetOperationalState(QStatus status, const qcc::String& objectPath, const OperationalState value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetOperationalState", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(OperationalState, value)
                          );
    }
    void OnOperationalStateChanged(const qcc::String& objectPath, const OperationalState value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnOperationalStateChanged", Qt::QueuedConnection,
                          Q_ARG(OperationalState, value)
                          );
    }

private:
    ajn::services::ClimateControlModeIntfControllerPtr controller;


    QLineEdit* edit_Mode;
    QLineEdit* edit_SupportedModes;
    QLineEdit* edit_OperationalState;
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_ClimateControlMode_H_ */
