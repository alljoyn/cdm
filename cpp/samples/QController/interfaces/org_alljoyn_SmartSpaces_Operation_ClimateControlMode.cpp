/******************************************************************************
 *  * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#include "org_alljoyn_SmartSpaces_Operation_ClimateControlMode.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <sstream>




using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_ClimateControlMode*>();


org_alljoyn_SmartSpaces_Operation_ClimateControlMode::org_alljoyn_SmartSpaces_Operation_ClimateControlMode(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("Mode"));
    // Create line edit for Mode
    edit_Mode = new QLineEdit();
    edit_Mode->setToolTip("Current mode of device.");
    edit_Mode->setReadOnly(false);
    QObject::connect(edit_Mode, SIGNAL(returnPressed()), this, SLOT(slotSetMode()));
    layout->addWidget(edit_Mode);
    layout->addWidget(new QLabel("SupportedModes"));
    // Create line edit for SupportedModes
    edit_SupportedModes = new QLineEdit();
    edit_SupportedModes->setToolTip("Array of supported modes.");
    edit_SupportedModes->setReadOnly(true);
    layout->addWidget(edit_SupportedModes);
    layout->addWidget(new QLabel("OperationalState"));
    // Create line edit for OperationalState
    edit_OperationalState = new QLineEdit();
    edit_OperationalState->setToolTip("Current status of device.");
    edit_OperationalState->setReadOnly(true);
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
        qWarning() << "org_alljoyn_SmartSpaces_Operation_ClimateControlMode getting properties";

        status = controller->GetMode();
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get Mode" << QCC_StatusText(status);
        }

        status = controller->GetSupportedModes();
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get SupportedModes" << QCC_StatusText(status);
        }

        status = controller->GetOperationalState();
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get OperationalState" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_ClimateControlMode::slotOnResponseGetMode(QStatus status, const ClimateControlModeInterface::Mode value)
{
    qWarning() << __FUNCTION__;
    edit_Mode->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_ClimateControlMode::slotOnModeChanged(const ClimateControlModeInterface::Mode value)
{
    qWarning() << __FUNCTION__;
    edit_Mode->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_ClimateControlMode::slotOnResponseSetMode(QStatus status)
{
    qWarning() << __FUNCTION__;
}

void org_alljoyn_SmartSpaces_Operation_ClimateControlMode::slotSetMode()
{
    qWarning() << __FUNCTION__;

    bool ok = false;
    QString str = edit_Mode->text();
    ClimateControlModeInterface::Mode value = QStringTo<ClimateControlModeInterface::Mode>(str, &ok);
    if (ok)
    {
        QStatus status = controller->SetMode(value);
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get Mode" << QCC_StatusText(status);
        }
    }
    else
    {
        qWarning() << __FUNCTION__ << "Failed to convert '" << str << "' to ClimateControlModeInterface::Mode";
    }
}




void org_alljoyn_SmartSpaces_Operation_ClimateControlMode::slotOnResponseGetSupportedModes(QStatus status, const std::vector<ClimateControlModeInterface::Mode>& value)
{
    qWarning() << __FUNCTION__;
    edit_SupportedModes->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_ClimateControlMode::slotOnSupportedModesChanged(const std::vector<ClimateControlModeInterface::Mode>& value)
{
    qWarning() << __FUNCTION__;
    edit_SupportedModes->setText(QStringFrom(value));
}




void org_alljoyn_SmartSpaces_Operation_ClimateControlMode::slotOnResponseGetOperationalState(QStatus status, const ClimateControlModeInterface::OperationalState value)
{
    qWarning() << __FUNCTION__;
    edit_OperationalState->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_ClimateControlMode::slotOnOperationalStateChanged(const ClimateControlModeInterface::OperationalState value)
{
    qWarning() << __FUNCTION__;
    edit_OperationalState->setText(QStringFrom(value));
}
