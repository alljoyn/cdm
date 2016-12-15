/******************************************************************************
 * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include "org_alljoyn_SmartSpaces_Operation_CycleControl.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <sstream>




using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_CycleControl*>();


org_alljoyn_SmartSpaces_Operation_CycleControl::org_alljoyn_SmartSpaces_Operation_CycleControl(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
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
        controller = iface->CreateInterface<CycleControlIntfController>(m_listener);
        if (controller)
        {
            fetchProperties();
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



void org_alljoyn_SmartSpaces_Operation_CycleControl::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "org_alljoyn_SmartSpaces_Operation_CycleControl getting properties";

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
}



void org_alljoyn_SmartSpaces_Operation_CycleControl::slotClickExecuteOperationalCommand()
{
    qWarning() << __FUNCTION__;

    CycleControlInterface::OperationalCommands command {};


    QStatus status = controller->ExecuteOperationalCommand(command, NULL);
    if (status != ER_OK)
    {
        qWarning() << __FUNCTION__ << " Failed to call ExecuteOperationalCommand" << QCC_StatusText(status);
    }
}



void org_alljoyn_SmartSpaces_Operation_CycleControl::slotOnResponseGetOperationalState(QStatus status, const CycleControlInterface::OperationalState value)
{
    qWarning() << __FUNCTION__;
    edit_OperationalState->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_CycleControl::slotOnOperationalStateChanged(const CycleControlInterface::OperationalState value)
{
    qWarning() << __FUNCTION__;
    edit_OperationalState->setText(QStringFrom(value));
}




void org_alljoyn_SmartSpaces_Operation_CycleControl::slotOnResponseGetSupportedOperationalStates(QStatus status, const std::vector<CycleControlInterface::OperationalState>& value)
{
    qWarning() << __FUNCTION__;
    edit_SupportedOperationalStates->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_CycleControl::slotOnSupportedOperationalStatesChanged(const std::vector<CycleControlInterface::OperationalState>& value)
{
    qWarning() << __FUNCTION__;
    edit_SupportedOperationalStates->setText(QStringFrom(value));
}




void org_alljoyn_SmartSpaces_Operation_CycleControl::slotOnResponseGetSupportedOperationalCommands(QStatus status, const std::vector<CycleControlInterface::OperationalCommands>& value)
{
    qWarning() << __FUNCTION__;
    edit_SupportedOperationalCommands->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_CycleControl::slotOnSupportedOperationalCommandsChanged(const std::vector<CycleControlInterface::OperationalCommands>& value)
{
    qWarning() << __FUNCTION__;
    edit_SupportedOperationalCommands->setText(QStringFrom(value));
}




void org_alljoyn_SmartSpaces_Operation_CycleControl::slotOnResponseMethodExecuteOperationalCommand(QStatus status, const QString& errorName)
{
    if (status == ER_OK)
    {
        qInfo() << "Received response to method ExecuteOperationalCommand";
    }
    else
    {
        qWarning() << "Received an error from method ExecuteOperationalCommand, error = " << errorName;
    }
}