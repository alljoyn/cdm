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
#include "qcUtils.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <sstream>



template<>
QString
QStringFrom<CycleControlInterface::OperationalState>(const CycleControlInterface::OperationalState& value)
{
    QString result;

    switch (value)
    {
    case CycleControlInterface::OPERATIONAL_STATE_IDLE:
        result = "Idle";
        break;

    case CycleControlInterface::OPERATIONAL_STATE_WORKING:
        result = "Working";
        break;

    case CycleControlInterface::OPERATIONAL_STATE_READY_TO_START:
        result = "ReadyToStart";
        break;

    case CycleControlInterface::OPERATIONAL_STATE_DELAYED_START:
        result = "DelayedStart";
        break;

    case CycleControlInterface::OPERATIONAL_STATE_PAUSED:
        result = "Paused";
        break;

    case CycleControlInterface::OPERATIONAL_STATE_END_OF_CYCLE:
        result = "EndOfCycle";
        break;

    default:
        result = "Unknown";
        break;
    }

    return result;
}



template<>
QString
QStringFrom<std::vector<CycleControlInterface::OperationalState>>(const std::vector<CycleControlInterface::OperationalState>& value)
{
    // the QLabel is AutoFmt 
    std::ostringstream strm;

    strm << "<html><body>";
    strm << "<table><thead><tr>";
    strm << "<th bgcolor=\"light blue\">OperationalState</th>";
    strm << "</tr></thead>";

    for (auto& v : value)
    {
        if (v == CycleControlInterface::OPERATIONAL_STATE_IDLE)
        {
            strm << "<tr><td>Idle</td></tr>";
        }
        if (v == CycleControlInterface::OPERATIONAL_STATE_WORKING)
        {
            strm << "<tr><td>Working</td></tr>";
        }
        if (v == CycleControlInterface::OPERATIONAL_STATE_READY_TO_START)
        {
            strm << "<tr><td>ReadyToStart</td></tr>";
        }
        if (v == CycleControlInterface::OPERATIONAL_STATE_DELAYED_START)
        {
            strm << "<tr><td>DelayedStart</td></tr>";
        }
        if (v == CycleControlInterface::OPERATIONAL_STATE_PAUSED)
        {
            strm << "<tr><td>Paused</td></tr>";
        }
        if (v == CycleControlInterface::OPERATIONAL_STATE_END_OF_CYCLE)
        {
            strm << "<tr><td>EndOfCycle</td></tr>";
        }
    }

    strm << "</table></body></html>";
    return QString::fromStdString(strm.str());
}


template<>
QString
QStringFrom<CycleControlInterface::OperationalCommands>(const CycleControlInterface::OperationalCommands& value)
{
    QString result;

    switch (value)
    {
    case CycleControlInterface::OPERATIONAL_COMMANDS_START:
        result = "Start";
        break;

    case CycleControlInterface::OPERATIONAL_COMMANDS_STOP:
        result = "Stop";
        break;

    case CycleControlInterface::OPERATIONAL_COMMANDS_PAUSE:
        result = "Pause";
        break;

    case CycleControlInterface::OPERATIONAL_COMMANDS_RESUME:
        result = "Resume";
        break;

    default:
        result = "Unknown";
        break;
    }

    return result;
}



template<>
QString
QStringFrom<std::vector<CycleControlInterface::OperationalCommands>>(const std::vector<CycleControlInterface::OperationalCommands>& value)
{
    // the QLabel is AutoFmt 
    std::ostringstream strm;

    strm << "<html><body>";
    strm << "<table><thead><tr>";
    strm << "<th bgcolor=\"light blue\">OperationalCommands</th>";
    strm << "</tr></thead>";

    for (auto& v : value)
    {
        if (v == CycleControlInterface::OPERATIONAL_COMMANDS_START)
        {
            strm << "<tr><td>Start</td></tr>";
        }
        if (v == CycleControlInterface::OPERATIONAL_COMMANDS_STOP)
        {
            strm << "<tr><td>Stop</td></tr>";
        }
        if (v == CycleControlInterface::OPERATIONAL_COMMANDS_PAUSE)
        {
            strm << "<tr><td>Pause</td></tr>";
        }
        if (v == CycleControlInterface::OPERATIONAL_COMMANDS_RESUME)
        {
            strm << "<tr><td>Resume</td></tr>";
        }
    }

    strm << "</table></body></html>";
    return QString::fromStdString(strm.str());
}


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


#include <QDialogButtonBox>
#include <QVBoxLayout>


org_alljoyn_SmartSpaces_Operation_CycleControl_Execute::org_alljoyn_SmartSpaces_Operation_CycleControl_Execute(QWidget* parent)
{
    command_ = CycleControlInterface::OPERATIONAL_COMMANDS_START;

    dialog_ = new QDialog(parent);
    auto* dlgLayout_ = new QVBoxLayout(dialog_);

    dlgLayout_->addWidget(new QLabel("Command"));

    commandBox_ = new QComboBox();
    commandBox_->setEditable(false);

    commandBox_->addItem("Start", QVariant(CycleControlInterface::OPERATIONAL_COMMANDS_START));
    commandBox_->addItem("Stop", QVariant(CycleControlInterface::OPERATIONAL_COMMANDS_STOP));
    commandBox_->addItem("Pause", QVariant(CycleControlInterface::OPERATIONAL_COMMANDS_PAUSE));
    commandBox_->addItem("Resume", QVariant(CycleControlInterface::OPERATIONAL_COMMANDS_RESUME));

    dlgLayout_->addWidget(commandBox_);
    QObject::connect(commandBox_, SIGNAL(currentIndexChanged(int)), this, SLOT(changed()));

    auto* buttons = new QDialogButtonBox();
    dlgLayout_->addWidget(buttons);

    auto* cancel = buttons->addButton(QDialogButtonBox::Cancel);
    QObject::connect(cancel, SIGNAL(clicked(bool)), dialog_, SLOT(reject()));

    auto* ok = buttons->addButton(QDialogButtonBox::Ok);
    QObject::connect(ok, SIGNAL(clicked(bool)), dialog_, SLOT(accept()));
}



org_alljoyn_SmartSpaces_Operation_CycleControl_Execute::~org_alljoyn_SmartSpaces_Operation_CycleControl_Execute()
{
    delete dialog_;
}



int org_alljoyn_SmartSpaces_Operation_CycleControl_Execute::run()
{
    // This is always modal
    return dialog_->exec();
}



void org_alljoyn_SmartSpaces_Operation_CycleControl_Execute::changed()
{
    QVariant var = commandBox_->currentData();
    command_ = static_cast<CycleControlInterface::OperationalCommands>(var.toInt());
}



static bool DialogGetCommand(QWidget* parent, CycleControlInterface::OperationalCommands& command)
{
    auto* dialog = new org_alljoyn_SmartSpaces_Operation_CycleControl_Execute(parent);
    auto code = dialog->run();
    bool ok = code == QDialog::Accepted;

    if (ok)
    {
        command = dialog->command_;
    }

    delete dialog;
    return ok;
}

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

    layout->addWidget(new QLabel("<b>OperationalState</b>"));
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
    layout->addWidget(new QLabel("<b>SupportedOperationalStates</b>"));
    // Create the editing widget for SupportedOperationalStates
    edit_SupportedOperationalStates = new QLabel();

    layout->addWidget(edit_SupportedOperationalStates);
    layout->addWidget(new QLabel("<b>SupportedOperationalCommands</b>"));
    // Create the editing widget for SupportedOperationalCommands
    edit_SupportedOperationalCommands = new QLabel();

    layout->addWidget(edit_SupportedOperationalCommands);

    messages_ = new QLabel();
    layout->addWidget(messages_);

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
    ok = DialogGetCommand(this, command);

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
