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

#include "org_alljoyn_SmartSpaces_Environment_WaterLevel.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <sstream>




using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Environment_WaterLevel*>();


org_alljoyn_SmartSpaces_Environment_WaterLevel::org_alljoyn_SmartSpaces_Environment_WaterLevel(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("SupplySource"));
    // Create line edit for SupplySource
    edit_SupplySource = new QLineEdit();
    edit_SupplySource->setToolTip("The supply source of water.");
    edit_SupplySource->setReadOnly(true);
    layout->addWidget(edit_SupplySource);
    layout->addWidget(new QLabel("CurrentLevel"));
    // Create line edit for CurrentLevel
    edit_CurrentLevel = new QLineEdit();
    edit_CurrentLevel->setToolTip("The current level of water in the tank.");
    edit_CurrentLevel->setReadOnly(true);
    layout->addWidget(edit_CurrentLevel);
    layout->addWidget(new QLabel("MaxLevel"));
    // Create line edit for MaxLevel
    edit_MaxLevel = new QLineEdit();
    edit_MaxLevel->setToolTip("Maximum level allowed for water level.");
    edit_MaxLevel->setReadOnly(true);
    layout->addWidget(edit_MaxLevel);

    if (iface)
    {
        controller = iface->CreateInterface<WaterLevelIntfController>(m_listener);
        if (controller)
        {
            qWarning() << __FUNCTION__ << " Getting properties";

            QStatus status;
            // Get current values
            status = controller->GetSupplySource();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get SupplySource" << QCC_StatusText(status);
            }
            status = controller->GetCurrentLevel();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get CurrentLevel" << QCC_StatusText(status);
            }
            status = controller->GetMaxLevel();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get MaxLevel" << QCC_StatusText(status);
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

org_alljoyn_SmartSpaces_Environment_WaterLevel::~org_alljoyn_SmartSpaces_Environment_WaterLevel()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Environment_WaterLevel::slotOnResponseGetSupplySource(QStatus status, const WaterLevelInterface::SupplySource value)
{
    qWarning() << __FUNCTION__;
    edit_SupplySource->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Environment_WaterLevel::slotOnSupplySourceChanged(const WaterLevelInterface::SupplySource value)
{
    qWarning() << __FUNCTION__;
    edit_SupplySource->setText(QStringFrom(value));
}




void org_alljoyn_SmartSpaces_Environment_WaterLevel::slotOnResponseGetCurrentLevel(QStatus status, const uint8_t value)
{
    qWarning() << __FUNCTION__;
    edit_CurrentLevel->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Environment_WaterLevel::slotOnCurrentLevelChanged(const uint8_t value)
{
    qWarning() << __FUNCTION__;
    edit_CurrentLevel->setText(QStringFrom(value));
}




void org_alljoyn_SmartSpaces_Environment_WaterLevel::slotOnResponseGetMaxLevel(QStatus status, const uint8_t value)
{
    qWarning() << __FUNCTION__;
    edit_MaxLevel->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Environment_WaterLevel::slotOnMaxLevelChanged(const uint8_t value)
{
    qWarning() << __FUNCTION__;
    edit_MaxLevel->setText(QStringFrom(value));
}
