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
#include "org_alljoyn_SmartSpaces_Operation_ClimateControlMode.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <sstream>




using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_ClimateControlMode*>();

Q_DECLARE_METATYPE(ajn::services::ClimateControlModeInterface::Mode);
Q_DECLARE_METATYPE(std::vector<ajn::services::ClimateControlModeInterface::Mode>);
static const int auto_register_enum_Mode = qRegisterMetaType<ajn::services::ClimateControlModeInterface::Mode>("ClimateControlModeInterface::Mode");
static const int auto_register_enum_v_Mode = qRegisterMetaType<std::vector<ajn::services::ClimateControlModeInterface::Mode>>("std::vector<ClimateControlModeInterface::Mode>");

Q_DECLARE_METATYPE(ajn::services::ClimateControlModeInterface::OperationalState);
Q_DECLARE_METATYPE(std::vector<ajn::services::ClimateControlModeInterface::OperationalState>);
static const int auto_register_enum_OperationalState = qRegisterMetaType<ajn::services::ClimateControlModeInterface::OperationalState>("ClimateControlModeInterface::OperationalState");
static const int auto_register_enum_v_OperationalState = qRegisterMetaType<std::vector<ajn::services::ClimateControlModeInterface::OperationalState>>("std::vector<ClimateControlModeInterface::OperationalState>");



org_alljoyn_SmartSpaces_Operation_ClimateControlMode::org_alljoyn_SmartSpaces_Operation_ClimateControlMode(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("Mode"));
    // Create the editing widget for Mode
    edit_Mode = new QComboBox();
    edit_Mode->setEditable(false);
    edit_Mode->addItem("Off");
    edit_Mode->addItem("Heat");
    edit_Mode->addItem("Cool");
    edit_Mode->addItem("Auto");
    edit_Mode->addItem("AuxiliaryHeat");
    edit_Mode->addItem("Dry");
    edit_Mode->addItem("ContinuousDry");
    edit_Mode->setEnabled(true);
    QObject::connect(edit_Mode, SIGNAL(currentTextChanged(const QString &)), this, SLOT(slotSetMode()));

    layout->addWidget(edit_Mode);
    layout->addWidget(new QLabel("SupportedModes"));
    // Create the editing widget for SupportedModes
    edit_SupportedModes = new QLineEdit();
    edit_SupportedModes->setToolTip("Array of supported modes.");
    edit_SupportedModes->setReadOnly(true);

    layout->addWidget(edit_SupportedModes);
    layout->addWidget(new QLabel("OperationalState"));
    // Create the editing widget for OperationalState
    edit_OperationalState = new QComboBox();
    edit_OperationalState->setEditable(false);
    edit_OperationalState->addItem("Idle");
    edit_OperationalState->addItem("Heating");
    edit_OperationalState->addItem("Cooling");
    edit_OperationalState->addItem("PendingHeat");
    edit_OperationalState->addItem("PendingCool");
    edit_OperationalState->addItem("AuxilliaryHeat");
    edit_OperationalState->setEnabled(false);

    layout->addWidget(edit_OperationalState);

    if (iface)
    {
        controller = iface->CreateInterface<ClimateControlModeIntfController>(m_listener);
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

org_alljoyn_SmartSpaces_Operation_ClimateControlMode::~org_alljoyn_SmartSpaces_Operation_ClimateControlMode()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_ClimateControlMode::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "ClimateControlMode getting properties";

        status = controller->GetMode();
        if (status != ER_OK)
        {
            qWarning() << "ClimateControlMode::fetchProperties Failed to get Mode" << QCC_StatusText(status);
        }

        status = controller->GetSupportedModes();
        if (status != ER_OK)
        {
            qWarning() << "ClimateControlMode::fetchProperties Failed to get SupportedModes" << QCC_StatusText(status);
        }

        status = controller->GetOperationalState();
        if (status != ER_OK)
        {
            qWarning() << "ClimateControlMode::fetchProperties Failed to get OperationalState" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_ClimateControlMode::slotOnResponseGetMode(QStatus status, const ClimateControlModeInterface::Mode value)
{
    qWarning() << "ClimateControlMode::slotOnResponseGetMode";

    switch (value)
    {
    case ClimateControlModeInterface::MODE_OFF:
        edit_Mode->setCurrentText("Off");
        break;

    case ClimateControlModeInterface::MODE_HEAT:
        edit_Mode->setCurrentText("Heat");
        break;

    case ClimateControlModeInterface::MODE_COOL:
        edit_Mode->setCurrentText("Cool");
        break;

    case ClimateControlModeInterface::MODE_AUTO:
        edit_Mode->setCurrentText("Auto");
        break;

    case ClimateControlModeInterface::MODE_AUXILIARY_HEAT:
        edit_Mode->setCurrentText("AuxiliaryHeat");
        break;

    case ClimateControlModeInterface::MODE_DRY:
        edit_Mode->setCurrentText("Dry");
        break;

    case ClimateControlModeInterface::MODE_CONTINUOUS_DRY:
        edit_Mode->setCurrentText("ContinuousDry");
        break;

    default:
        edit_Mode->setCurrentText("");
        break;
    }
}



void org_alljoyn_SmartSpaces_Operation_ClimateControlMode::slotOnModeChanged(const ClimateControlModeInterface::Mode value)
{
    qWarning() << "ClimateControlMode::slotOnModeChanged";

    switch (value)
    {
    case ClimateControlModeInterface::MODE_OFF:
        edit_Mode->setCurrentText("Off");
        break;

    case ClimateControlModeInterface::MODE_HEAT:
        edit_Mode->setCurrentText("Heat");
        break;

    case ClimateControlModeInterface::MODE_COOL:
        edit_Mode->setCurrentText("Cool");
        break;

    case ClimateControlModeInterface::MODE_AUTO:
        edit_Mode->setCurrentText("Auto");
        break;

    case ClimateControlModeInterface::MODE_AUXILIARY_HEAT:
        edit_Mode->setCurrentText("AuxiliaryHeat");
        break;

    case ClimateControlModeInterface::MODE_DRY:
        edit_Mode->setCurrentText("Dry");
        break;

    case ClimateControlModeInterface::MODE_CONTINUOUS_DRY:
        edit_Mode->setCurrentText("ContinuousDry");
        break;

    default:
        edit_Mode->setCurrentText("");
        break;
    }
}



void org_alljoyn_SmartSpaces_Operation_ClimateControlMode::slotOnResponseSetMode(QStatus status)
{
    qWarning() << "ClimateControlMode::slotOnResponseSetMode";

    if (status != ER_OK)
    {
        qWarning() << "ClimateControlMode::slotOnResponseSetMode Failed to set Mode" << QCC_StatusText(status);
    }
}



void org_alljoyn_SmartSpaces_Operation_ClimateControlMode::slotSetMode()
{
    qWarning() << "ClimateControlMode::slotSetMode";

    bool ok = false;
    ClimateControlModeInterface::Mode value;
    QString str = edit_Mode->currentText();
    if (str == "Off")
    {
        value = ClimateControlModeInterface::MODE_OFF;
        ok = true;
    }
    else
    if (str == "Heat")
    {
        value = ClimateControlModeInterface::MODE_HEAT;
        ok = true;
    }
    else
    if (str == "Cool")
    {
        value = ClimateControlModeInterface::MODE_COOL;
        ok = true;
    }
    else
    if (str == "Auto")
    {
        value = ClimateControlModeInterface::MODE_AUTO;
        ok = true;
    }
    else
    if (str == "AuxiliaryHeat")
    {
        value = ClimateControlModeInterface::MODE_AUXILIARY_HEAT;
        ok = true;
    }
    else
    if (str == "Dry")
    {
        value = ClimateControlModeInterface::MODE_DRY;
        ok = true;
    }
    else
    if (str == "ContinuousDry")
    {
        value = ClimateControlModeInterface::MODE_CONTINUOUS_DRY;
        ok = true;
    }
    else
    if (!str.isEmpty())
    {
        qWarning() << "ClimateControlMode::slotSetMode Failed to convert '" << str.constData() << "' to ClimateControlModeInterface::Mode";
    }

    if (ok)
    {
        QStatus status = controller->SetMode(value);

        if (status != ER_OK)
        {
            qWarning() << "ClimateControlMode::slotSetMode Failed to get Mode" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_ClimateControlMode::slotOnResponseGetSupportedModes(QStatus status, const std::vector<ClimateControlModeInterface::Mode>& value)
{
    qWarning() << "ClimateControlMode::slotOnResponseGetSupportedModes";

    edit_SupportedModes->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_ClimateControlMode::slotOnSupportedModesChanged(const std::vector<ClimateControlModeInterface::Mode>& value)
{
    qWarning() << "ClimateControlMode::slotOnSupportedModesChanged";

    edit_SupportedModes->setText(QStringFrom(value));
}






void org_alljoyn_SmartSpaces_Operation_ClimateControlMode::slotOnResponseGetOperationalState(QStatus status, const ClimateControlModeInterface::OperationalState value)
{
    qWarning() << "ClimateControlMode::slotOnResponseGetOperationalState";

    switch (value)
    {
    case ClimateControlModeInterface::OPERATIONAL_STATE_IDLE:
        edit_OperationalState->setCurrentText("Idle");
        break;

    case ClimateControlModeInterface::OPERATIONAL_STATE_HEATING:
        edit_OperationalState->setCurrentText("Heating");
        break;

    case ClimateControlModeInterface::OPERATIONAL_STATE_COOLING:
        edit_OperationalState->setCurrentText("Cooling");
        break;

    case ClimateControlModeInterface::OPERATIONAL_STATE_PENDING_HEAT:
        edit_OperationalState->setCurrentText("PendingHeat");
        break;

    case ClimateControlModeInterface::OPERATIONAL_STATE_PENDING_COOL:
        edit_OperationalState->setCurrentText("PendingCool");
        break;

    case ClimateControlModeInterface::OPERATIONAL_STATE_AUXILLIARY_HEAT:
        edit_OperationalState->setCurrentText("AuxilliaryHeat");
        break;

    default:
        edit_OperationalState->setCurrentText("");
        break;
    }
}



void org_alljoyn_SmartSpaces_Operation_ClimateControlMode::slotOnOperationalStateChanged(const ClimateControlModeInterface::OperationalState value)
{
    qWarning() << "ClimateControlMode::slotOnOperationalStateChanged";

    switch (value)
    {
    case ClimateControlModeInterface::OPERATIONAL_STATE_IDLE:
        edit_OperationalState->setCurrentText("Idle");
        break;

    case ClimateControlModeInterface::OPERATIONAL_STATE_HEATING:
        edit_OperationalState->setCurrentText("Heating");
        break;

    case ClimateControlModeInterface::OPERATIONAL_STATE_COOLING:
        edit_OperationalState->setCurrentText("Cooling");
        break;

    case ClimateControlModeInterface::OPERATIONAL_STATE_PENDING_HEAT:
        edit_OperationalState->setCurrentText("PendingHeat");
        break;

    case ClimateControlModeInterface::OPERATIONAL_STATE_PENDING_COOL:
        edit_OperationalState->setCurrentText("PendingCool");
        break;

    case ClimateControlModeInterface::OPERATIONAL_STATE_AUXILLIARY_HEAT:
        edit_OperationalState->setCurrentText("AuxilliaryHeat");
        break;

    default:
        edit_OperationalState->setCurrentText("");
        break;
    }
}



