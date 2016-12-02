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

#include "org_alljoyn_SmartSpaces_Operation_CycleControl.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>

using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_CycleControl*>();

org_alljoyn_SmartSpaces_Operation_CycleControl::org_alljoyn_SmartSpaces_Operation_CycleControl(CommonControllerInterface *iface) : controller(NULL)
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);


    // Create button for ExecuteOperationalCommand
    button_ExecuteOperationalCommand = new QPushButton("ExecuteOperationalCommand");
    button_ExecuteOperationalCommand->setToolTip("Execute an operational command.");
    QObject::connect(button_ExecuteOperationalCommand, SIGNAL(clicked()), this, SLOT(slotClickExecuteOperationalCommand()));
    layout->addWidget(button_ExecuteOperationalCommand);

    layout->addWidget(new QLabel("OperationalState"));
    // Create line edit for OperationalState
    edit_OperationalState = new QLineEdit();
    edit_OperationalState->setToolTip("Current operational state of the appliance.");
    edit_OperationalState->setReadOnly(true);
    layout->addWidget(edit_OperationalState);
    layout->addWidget(new QLabel("SupportedOperationalStates"));
    // Create line edit for SupportedOperationalStates
    edit_SupportedOperationalStates = new QLineEdit();
    edit_SupportedOperationalStates->setToolTip("Operational states which are supported by the appliance.");
    edit_SupportedOperationalStates->setReadOnly(true);
    layout->addWidget(edit_SupportedOperationalStates);
    layout->addWidget(new QLabel("SupportedOperationalCommands"));
    // Create line edit for SupportedOperationalCommands
    edit_SupportedOperationalCommands = new QLineEdit();
    edit_SupportedOperationalCommands->setToolTip("Operational commands which are supported by the appliance.");
    edit_SupportedOperationalCommands->setReadOnly(true);
    layout->addWidget(edit_SupportedOperationalCommands);

    if (iface)
    {
        controller = iface->CreateInterface<CycleControlIntfController>(*this);
        if (controller)
        {
            qWarning() << __FUNCTION__ << " Getting properties";

            QStatus status;
            // Get current values
            status = controller->GetOperationalState();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get OperationalState" << QCC_StatusText(status);
            }
            status = controller->GetSupportedOperationalStates();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get SupportedOperationalStates" << QCC_StatusText(status);
            }
            status = controller->GetSupportedOperationalCommands();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get SupportedOperationalCommands" << QCC_StatusText(status);
            }
        }
        else
        {
            qWarning() << __FUNCTION__ << " No interface controller available!";
        }
    }
    else
    {
        qWarning() << __FUNCTION__ << " No interface available!";
    }
}

org_alljoyn_SmartSpaces_Operation_CycleControl::~org_alljoyn_SmartSpaces_Operation_CycleControl()
{
    qWarning() << __FUNCTION__;
}

void org_alljoyn_SmartSpaces_Operation_CycleControl::slotClickExecuteOperationalCommand()
{
    qWarning() << __FUNCTION__;

    OperationalCommands command {};

    QStatus status = controller->ExecuteOperationalCommand(command, NULL);
    if (status != ER_OK)
    {
        qWarning() << __FUNCTION__ << " Failed to call ExecuteOperationalCommand" << QCC_StatusText(status);
    }
}


void org_alljoyn_SmartSpaces_Operation_CycleControl::slotOnResponseGetOperationalState(QStatus status, const OperationalState value)
{
    qWarning() << __FUNCTION__;
    edit_OperationalState->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_CycleControl::slotOnOperationalStateChanged(const OperationalState value)
{
    qWarning() << __FUNCTION__;
    edit_OperationalState->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_CycleControl::slotOnResponseGetSupportedOperationalStates(QStatus status, const std::vector<OperationalState>& value)
{
    qWarning() << __FUNCTION__;
    edit_SupportedOperationalStates->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_CycleControl::slotOnSupportedOperationalStatesChanged(const std::vector<OperationalState>& value)
{
    qWarning() << __FUNCTION__;
    edit_SupportedOperationalStates->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_CycleControl::slotOnResponseGetSupportedOperationalCommands(QStatus status, const std::vector<OperationalCommands>& value)
{
    qWarning() << __FUNCTION__;
    edit_SupportedOperationalCommands->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_CycleControl::slotOnSupportedOperationalCommandsChanged(const std::vector<OperationalCommands>& value)
{
    qWarning() << __FUNCTION__;
    edit_SupportedOperationalCommands->setText(QStringFrom(value));
}

