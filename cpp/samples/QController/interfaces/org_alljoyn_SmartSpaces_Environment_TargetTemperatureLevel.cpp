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

#include "org_alljoyn_SmartSpaces_Environment_TargetTemperatureLevel.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <sstream>




using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Environment_TargetTemperatureLevel*>();


org_alljoyn_SmartSpaces_Environment_TargetTemperatureLevel::org_alljoyn_SmartSpaces_Environment_TargetTemperatureLevel(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("MaxLevel"));
    // Create line edit for MaxLevel
    edit_MaxLevel = new QLineEdit();
    edit_MaxLevel->setToolTip("Maximum value allowed for target temperature level setting.");
    edit_MaxLevel->setReadOnly(true);
    layout->addWidget(edit_MaxLevel);
    layout->addWidget(new QLabel("TargetLevel"));
    // Create line edit for TargetLevel
    edit_TargetLevel = new QLineEdit();
    edit_TargetLevel->setToolTip("Target set-point value of temperature level.");
    edit_TargetLevel->setReadOnly(false);
    QObject::connect(edit_TargetLevel, SIGNAL(returnPressed()), this, SLOT(slotSetTargetLevel()));
    layout->addWidget(edit_TargetLevel);
    layout->addWidget(new QLabel("SelectableTemperatureLevels"));
    // Create line edit for SelectableTemperatureLevels
    edit_SelectableTemperatureLevels = new QLineEdit();
    edit_SelectableTemperatureLevels->setToolTip("List of the values of temperature level which can be selected.");
    edit_SelectableTemperatureLevels->setReadOnly(true);
    layout->addWidget(edit_SelectableTemperatureLevels);

    if (iface)
    {
        controller = iface->CreateInterface<TargetTemperatureLevelIntfController>(m_listener);
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

org_alljoyn_SmartSpaces_Environment_TargetTemperatureLevel::~org_alljoyn_SmartSpaces_Environment_TargetTemperatureLevel()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Environment_TargetTemperatureLevel::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "org_alljoyn_SmartSpaces_Environment_TargetTemperatureLevel getting properties";

        status = controller->GetMaxLevel();
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get MaxLevel" << QCC_StatusText(status);
        }

        status = controller->GetTargetLevel();
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get TargetLevel" << QCC_StatusText(status);
        }

        status = controller->GetSelectableTemperatureLevels();
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get SelectableTemperatureLevels" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Environment_TargetTemperatureLevel::slotOnResponseGetMaxLevel(QStatus status, const uint8_t value)
{
    qWarning() << __FUNCTION__;
    edit_MaxLevel->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Environment_TargetTemperatureLevel::slotOnMaxLevelChanged(const uint8_t value)
{
    qWarning() << __FUNCTION__;
    edit_MaxLevel->setText(QStringFrom(value));
}




void org_alljoyn_SmartSpaces_Environment_TargetTemperatureLevel::slotOnResponseGetTargetLevel(QStatus status, const uint8_t value)
{
    qWarning() << __FUNCTION__;
    edit_TargetLevel->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Environment_TargetTemperatureLevel::slotOnTargetLevelChanged(const uint8_t value)
{
    qWarning() << __FUNCTION__;
    edit_TargetLevel->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Environment_TargetTemperatureLevel::slotOnResponseSetTargetLevel(QStatus status)
{
    qWarning() << __FUNCTION__;
}

void org_alljoyn_SmartSpaces_Environment_TargetTemperatureLevel::slotSetTargetLevel()
{
    qWarning() << __FUNCTION__;

    bool ok = false;
    QString str = edit_TargetLevel->text();
    uint8_t value = QStringTo<uint8_t>(str, &ok);
    if (ok)
    {
        QStatus status = controller->SetTargetLevel(value);
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get TargetLevel" << QCC_StatusText(status);
        }
    }
    else
    {
        qWarning() << __FUNCTION__ << "Failed to convert '" << str << "' to uint8_t";
    }
}




void org_alljoyn_SmartSpaces_Environment_TargetTemperatureLevel::slotOnResponseGetSelectableTemperatureLevels(QStatus status, const std::vector<uint8_t>& value)
{
    qWarning() << __FUNCTION__;
    edit_SelectableTemperatureLevels->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Environment_TargetTemperatureLevel::slotOnSelectableTemperatureLevelsChanged(const std::vector<uint8_t>& value)
{
    qWarning() << __FUNCTION__;
    edit_SelectableTemperatureLevels->setText(QStringFrom(value));
}
