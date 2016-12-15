/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include "org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <sstream>




using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel*>();


org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel::org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("MoistureOutputLevel"));
    // Create line edit for MoistureOutputLevel
    edit_MoistureOutputLevel = new QLineEdit();
    edit_MoistureOutputLevel->setToolTip("Current level of moisture output.");
    edit_MoistureOutputLevel->setReadOnly(false);
    QObject::connect(edit_MoistureOutputLevel, SIGNAL(returnPressed()), this, SLOT(slotSetMoistureOutputLevel()));
    layout->addWidget(edit_MoistureOutputLevel);
    layout->addWidget(new QLabel("MaxMoistureOutputLevel"));
    // Create line edit for MaxMoistureOutputLevel
    edit_MaxMoistureOutputLevel = new QLineEdit();
    edit_MaxMoistureOutputLevel->setToolTip("Maximum level of moisture output.");
    edit_MaxMoistureOutputLevel->setReadOnly(true);
    layout->addWidget(edit_MaxMoistureOutputLevel);
    layout->addWidget(new QLabel("AutoMode"));
    // Create line edit for AutoMode
    edit_AutoMode = new QLineEdit();
    edit_AutoMode->setToolTip("Represent enabled/disabled state of the auto mode. The device decides the moisture output level for providing comfortable surroundings automatically.");
    edit_AutoMode->setReadOnly(false);
    QObject::connect(edit_AutoMode, SIGNAL(returnPressed()), this, SLOT(slotSetAutoMode()));
    layout->addWidget(edit_AutoMode);

    if (iface)
    {
        controller = iface->CreateInterface<MoistureOutputLevelIntfController>(m_listener);
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

org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel::~org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel getting properties";

        status = controller->GetMoistureOutputLevel();
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get MoistureOutputLevel" << QCC_StatusText(status);
        }

        status = controller->GetMaxMoistureOutputLevel();
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get MaxMoistureOutputLevel" << QCC_StatusText(status);
        }

        status = controller->GetAutoMode();
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get AutoMode" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel::slotOnResponseGetMoistureOutputLevel(QStatus status, const uint8_t value)
{
    qWarning() << __FUNCTION__;
    edit_MoistureOutputLevel->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel::slotOnMoistureOutputLevelChanged(const uint8_t value)
{
    qWarning() << __FUNCTION__;
    edit_MoistureOutputLevel->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel::slotOnResponseSetMoistureOutputLevel(QStatus status)
{
    qWarning() << __FUNCTION__;
}

void org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel::slotSetMoistureOutputLevel()
{
    qWarning() << __FUNCTION__;

    bool ok = false;
    QString str = edit_MoistureOutputLevel->text();
    uint8_t value = QStringTo<uint8_t>(str, &ok);
    if (ok)
    {
        QStatus status = controller->SetMoistureOutputLevel(value);
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get MoistureOutputLevel" << QCC_StatusText(status);
        }
    }
    else
    {
        qWarning() << __FUNCTION__ << "Failed to convert '" << str << "' to uint8_t";
    }
}




void org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel::slotOnResponseGetMaxMoistureOutputLevel(QStatus status, const uint8_t value)
{
    qWarning() << __FUNCTION__;
    edit_MaxMoistureOutputLevel->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel::slotOnMaxMoistureOutputLevelChanged(const uint8_t value)
{
    qWarning() << __FUNCTION__;
    edit_MaxMoistureOutputLevel->setText(QStringFrom(value));
}




void org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel::slotOnResponseGetAutoMode(QStatus status, const MoistureOutputLevelInterface::AutoMode value)
{
    qWarning() << __FUNCTION__;
    edit_AutoMode->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel::slotOnAutoModeChanged(const MoistureOutputLevelInterface::AutoMode value)
{
    qWarning() << __FUNCTION__;
    edit_AutoMode->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel::slotOnResponseSetAutoMode(QStatus status)
{
    qWarning() << __FUNCTION__;
}

void org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel::slotSetAutoMode()
{
    qWarning() << __FUNCTION__;

    bool ok = false;
    QString str = edit_AutoMode->text();
    MoistureOutputLevelInterface::AutoMode value = QStringTo<MoistureOutputLevelInterface::AutoMode>(str, &ok);
    if (ok)
    {
        QStatus status = controller->SetAutoMode(value);
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get AutoMode" << QCC_StatusText(status);
        }
    }
    else
    {
        qWarning() << __FUNCTION__ << "Failed to convert '" << str << "' to MoistureOutputLevelInterface::AutoMode";
    }
}
