/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
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

Q_DECLARE_METATYPE(ajn::services::CycleControlInterface::OperationalState);
Q_DECLARE_METATYPE(std::vector<ajn::services::CycleControlInterface::OperationalState>);
static const int auto_register_enum_OperationalState = qRegisterMetaType<ajn::services::CycleControlInterface::OperationalState>("CycleControlInterface::OperationalState");
static const int auto_register_enum_v_OperationalState = qRegisterMetaType<std::vector<ajn::services::CycleControlInterface::OperationalState>>("std::vector<CycleControlInterface::OperationalState>");

Q_DECLARE_METATYPE(ajn::services::CycleControlInterface::OperationalCommands);
Q_DECLARE_METATYPE(std::vector<ajn::services::CycleControlInterface::OperationalCommands>);
static const int auto_register_enum_OperationalCommands = qRegisterMetaType<ajn::services::CycleControlInterface::OperationalCommands>("CycleControlInterface::OperationalCommands");
static const int auto_register_enum_v_OperationalCommands = qRegisterMetaType<std::vector<ajn::services::CycleControlInterface::OperationalCommands>>("std::vector<CycleControlInterface::OperationalCommands>");



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
    // Create the editing widget for OperationalState
    edit_OperationalState = new QComboBox();
    edit_OperationalState->setEditable(false);
    edit_OperationalState->addItem("Idle");
    edit_OperationalState->addItem("Working");
    edit_OperationalState->addItem("ReadyToStart");
    edit_OperationalState->addItem("DelayedStart");
    edit_OperationalState->addItem("Paused");
    edit_OperationalState->addItem("EndOfCycle");
    edit_OperationalState->setEnabled(false);

    layout->addWidget(edit_OperationalState);
    layout->addWidget(new QLabel("SupportedOperationalStates"));
    // Create the editing widget for SupportedOperationalStates
    edit_SupportedOperationalStates = new QLineEdit();
    edit_SupportedOperationalStates->setToolTip("Operational states which are supported by the appliance.");
    edit_SupportedOperationalStates->setReadOnly(true);

    layout->addWidget(edit_SupportedOperationalStates);
    layout->addWidget(new QLabel("SupportedOperationalCommands"));
    // Create the editing widget for SupportedOperationalCommands
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
        qWarning() << "CycleControl getting properties";

        status = controller->GetOperationalState();
        if (status != ER_OK)
        {
            qWarning() << "CycleControl::fetchProperties Failed to get OperationalState" << QCC_StatusText(status);
        }

        status = controller->GetSupportedOperationalStates();
        if (status != ER_OK)
        {
            qWarning() << "CycleControl::fetchProperties Failed to get SupportedOperationalStates" << QCC_StatusText(status);
        }

        status = controller->GetSupportedOperationalCommands();
        if (status != ER_OK)
        {
            qWarning() << "CycleControl::fetchProperties Failed to get SupportedOperationalCommands" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_CycleControl::slotClickExecuteOperationalCommand()
{
    qWarning() << "CycleControl::slotClickExecuteOperationalCommand";

    CycleControlInterface::OperationalCommands command {};

    bool ok = true;

    if (ok)
    {
        QStatus status = controller->ExecuteOperationalCommand(command, NULL);
        if (status != ER_OK)
        {
            qWarning() << "CycleControl::slotClick Failed to call ExecuteOperationalCommand" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_CycleControl::slotOnResponseGetOperationalState(QStatus status, const CycleControlInterface::OperationalState value)
{
    qWarning() << "CycleControl::slotOnResponseGetOperationalState";

    switch (value)
    {
    case CycleControlInterface::OPERATIONAL_STATE_IDLE:
        edit_OperationalState->setCurrentText("Idle");
        break;

    case CycleControlInterface::OPERATIONAL_STATE_WORKING:
        edit_OperationalState->setCurrentText("Working");
        break;

    case CycleControlInterface::OPERATIONAL_STATE_READY_TO_START:
        edit_OperationalState->setCurrentText("ReadyToStart");
        break;

    case CycleControlInterface::OPERATIONAL_STATE_DELAYED_START:
        edit_OperationalState->setCurrentText("DelayedStart");
        break;

    case CycleControlInterface::OPERATIONAL_STATE_PAUSED:
        edit_OperationalState->setCurrentText("Paused");
        break;

    case CycleControlInterface::OPERATIONAL_STATE_END_OF_CYCLE:
        edit_OperationalState->setCurrentText("EndOfCycle");
        break;

    default:
        edit_OperationalState->setCurrentText("");
        break;
    }
}



void org_alljoyn_SmartSpaces_Operation_CycleControl::slotOnOperationalStateChanged(const CycleControlInterface::OperationalState value)
{
    qWarning() << "CycleControl::slotOnOperationalStateChanged";

    switch (value)
    {
    case CycleControlInterface::OPERATIONAL_STATE_IDLE:
        edit_OperationalState->setCurrentText("Idle");
        break;

    case CycleControlInterface::OPERATIONAL_STATE_WORKING:
        edit_OperationalState->setCurrentText("Working");
        break;

    case CycleControlInterface::OPERATIONAL_STATE_READY_TO_START:
        edit_OperationalState->setCurrentText("ReadyToStart");
        break;

    case CycleControlInterface::OPERATIONAL_STATE_DELAYED_START:
        edit_OperationalState->setCurrentText("DelayedStart");
        break;

    case CycleControlInterface::OPERATIONAL_STATE_PAUSED:
        edit_OperationalState->setCurrentText("Paused");
        break;

    case CycleControlInterface::OPERATIONAL_STATE_END_OF_CYCLE:
        edit_OperationalState->setCurrentText("EndOfCycle");
        break;

    default:
        edit_OperationalState->setCurrentText("");
        break;
    }
}






void org_alljoyn_SmartSpaces_Operation_CycleControl::slotOnResponseGetSupportedOperationalStates(QStatus status, const std::vector<CycleControlInterface::OperationalState>& value)
{
    qWarning() << "CycleControl::slotOnResponseGetSupportedOperationalStates";

    edit_SupportedOperationalStates->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_CycleControl::slotOnSupportedOperationalStatesChanged(const std::vector<CycleControlInterface::OperationalState>& value)
{
    qWarning() << "CycleControl::slotOnSupportedOperationalStatesChanged";

    edit_SupportedOperationalStates->setText(QStringFrom(value));
}






void org_alljoyn_SmartSpaces_Operation_CycleControl::slotOnResponseGetSupportedOperationalCommands(QStatus status, const std::vector<CycleControlInterface::OperationalCommands>& value)
{
    qWarning() << "CycleControl::slotOnResponseGetSupportedOperationalCommands";

    edit_SupportedOperationalCommands->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_CycleControl::slotOnSupportedOperationalCommandsChanged(const std::vector<CycleControlInterface::OperationalCommands>& value)
{
    qWarning() << "CycleControl::slotOnSupportedOperationalCommandsChanged";

    edit_SupportedOperationalCommands->setText(QStringFrom(value));
}






void org_alljoyn_SmartSpaces_Operation_CycleControl::slotOnResponseMethodExecuteOperationalCommand(QStatus status, const QString& errorName)
{
    if (status == ER_OK)
    {
        qInfo() << "CycleControl::slotOnResponseMethodExecuteOperationalCommand";
    }
    else
    {
        qWarning() << "CycleControl::slotOnResponseMethodExecuteOperationalCommand Received error = " << errorName;
    }
}
