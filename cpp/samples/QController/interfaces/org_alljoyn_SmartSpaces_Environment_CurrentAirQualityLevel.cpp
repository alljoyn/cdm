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

#include "org_alljoyn_SmartSpaces_Environment_CurrentAirQualityLevel.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <sstream>




using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Environment_CurrentAirQualityLevel*>();


org_alljoyn_SmartSpaces_Environment_CurrentAirQualityLevel::org_alljoyn_SmartSpaces_Environment_CurrentAirQualityLevel(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("ContaminantType"));
    // Create line edit for ContaminantType
    edit_ContaminantType = new QLineEdit();
    edit_ContaminantType->setToolTip("The contaminant type.");
    edit_ContaminantType->setReadOnly(true);
    layout->addWidget(edit_ContaminantType);
    layout->addWidget(new QLabel("CurrentLevel"));
    // Create line edit for CurrentLevel
    edit_CurrentLevel = new QLineEdit();
    edit_CurrentLevel->setToolTip("The qualitative representation of current air quality level.");
    edit_CurrentLevel->setReadOnly(true);
    layout->addWidget(edit_CurrentLevel);
    layout->addWidget(new QLabel("MaxLevel"));
    // Create line edit for MaxLevel
    edit_MaxLevel = new QLineEdit();
    edit_MaxLevel->setToolTip("Maximum level allowed for represented air quality level.");
    edit_MaxLevel->setReadOnly(true);
    layout->addWidget(edit_MaxLevel);

    if (iface)
    {
        controller = iface->CreateInterface<CurrentAirQualityLevelIntfController>(m_listener);
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

org_alljoyn_SmartSpaces_Environment_CurrentAirQualityLevel::~org_alljoyn_SmartSpaces_Environment_CurrentAirQualityLevel()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Environment_CurrentAirQualityLevel::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "org_alljoyn_SmartSpaces_Environment_CurrentAirQualityLevel getting properties";

        status = controller->GetContaminantType();
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get ContaminantType" << QCC_StatusText(status);
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
}



void org_alljoyn_SmartSpaces_Environment_CurrentAirQualityLevel::slotOnResponseGetContaminantType(QStatus status, const CurrentAirQualityLevelInterface::ContaminantType value)
{
    qWarning() << __FUNCTION__;
    edit_ContaminantType->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Environment_CurrentAirQualityLevel::slotOnContaminantTypeChanged(const CurrentAirQualityLevelInterface::ContaminantType value)
{
    qWarning() << __FUNCTION__;
    edit_ContaminantType->setText(QStringFrom(value));
}




void org_alljoyn_SmartSpaces_Environment_CurrentAirQualityLevel::slotOnResponseGetCurrentLevel(QStatus status, const uint8_t value)
{
    qWarning() << __FUNCTION__;
    edit_CurrentLevel->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Environment_CurrentAirQualityLevel::slotOnCurrentLevelChanged(const uint8_t value)
{
    qWarning() << __FUNCTION__;
    edit_CurrentLevel->setText(QStringFrom(value));
}




void org_alljoyn_SmartSpaces_Environment_CurrentAirQualityLevel::slotOnResponseGetMaxLevel(QStatus status, const uint8_t value)
{
    qWarning() << __FUNCTION__;
    edit_MaxLevel->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Environment_CurrentAirQualityLevel::slotOnMaxLevelChanged(const uint8_t value)
{
    qWarning() << __FUNCTION__;
    edit_MaxLevel->setText(QStringFrom(value));
}

