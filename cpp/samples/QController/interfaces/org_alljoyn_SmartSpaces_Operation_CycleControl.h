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

#ifndef org_alljoyn_SmartSpaces_Operation_CycleControl_H_
#define org_alljoyn_SmartSpaces_Operation_CycleControl_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <alljoyn/cdm/interfaces/operation/CycleControlInterface.h>
#include <alljoyn/cdm/interfaces/operation/CycleControlIntfController.h>
#include <alljoyn/cdm/interfaces/operation/CycleControlIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_CycleControl : public QWidget, public ajn::services::CycleControlIntfControllerListener
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Operation_CycleControl(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Operation_CycleControl();

    // Slots mirror the callbacks to avoid threading issues
private slots:
    void slotClickExecuteOperationalCommand();

    void slotOnResponseGetOperationalState(QStatus status, const OperationalState value);
    void slotOnOperationalStateChanged(const OperationalState value);
    void slotOnResponseGetSupportedOperationalStates(QStatus status, const std::vector<OperationalState>& value);
    void slotOnSupportedOperationalStatesChanged(const std::vector<OperationalState>& value);
    void slotOnResponseGetSupportedOperationalCommands(QStatus status, const std::vector<OperationalCommands>& value);
    void slotOnSupportedOperationalCommandsChanged(const std::vector<OperationalCommands>& value);

public:
    // ajn::services::CycleControlIntfControllerListener
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
    void OnResponseGetSupportedOperationalStates(QStatus status, const qcc::String& objectPath, const std::vector<OperationalState>& value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetSupportedOperationalStates", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(std::vector<OperationalState>, value)
                          );
    }
    void OnSupportedOperationalStatesChanged(const qcc::String& objectPath, const std::vector<OperationalState>& value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnSupportedOperationalStatesChanged", Qt::QueuedConnection,
                          Q_ARG(std::vector<OperationalState>, value)
                          );
    }
    void OnResponseGetSupportedOperationalCommands(QStatus status, const qcc::String& objectPath, const std::vector<OperationalCommands>& value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetSupportedOperationalCommands", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(std::vector<OperationalCommands>, value)
                          );
    }
    void OnSupportedOperationalCommandsChanged(const qcc::String& objectPath, const std::vector<OperationalCommands>& value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnSupportedOperationalCommandsChanged", Qt::QueuedConnection,
                          Q_ARG(std::vector<OperationalCommands>, value)
                          );
    }

private:
    ajn::services::CycleControlIntfControllerPtr controller;

    QPushButton* button_ExecuteOperationalCommand;

    QLineEdit* edit_OperationalState;
    QLineEdit* edit_SupportedOperationalStates;
    QLineEdit* edit_SupportedOperationalCommands;
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_CycleControl_H_ */
