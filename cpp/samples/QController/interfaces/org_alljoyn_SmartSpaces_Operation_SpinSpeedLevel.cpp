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
#include "org_alljoyn_SmartSpaces_Operation_SpinSpeedLevel.h"
#include "qcUtils.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <sstream>



using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_SpinSpeedLevel*>();



org_alljoyn_SmartSpaces_Operation_SpinSpeedLevel::org_alljoyn_SmartSpaces_Operation_SpinSpeedLevel(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("<b>MaxLevel</b>"));
    // Create the editing widget for MaxLevel
    edit_MaxLevel = new QLabel();

    layout->addWidget(edit_MaxLevel);
    layout->addWidget(new QLabel("<b>TargetLevel</b>"));
    // Create the editing widget for TargetLevel
    edit_TargetLevel = new QLineEdit();
    edit_TargetLevel->setToolTip("Target set-point value of spin speed level.");
    QObject::connect(edit_TargetLevel, SIGNAL(returnPressed()), this, SLOT(slotSetTargetLevel()));

    layout->addWidget(edit_TargetLevel);
    layout->addWidget(new QLabel("<b>SelectableLevels</b>"));
    // Create the editing widget for SelectableLevels
    edit_SelectableLevels = new QLabel();

    layout->addWidget(edit_SelectableLevels);

    messages_ = new QLabel();
    layout->addWidget(messages_);

    if (iface)
    {
        controller = iface->CreateInterface<SpinSpeedLevelIntfController>(m_listener);
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

org_alljoyn_SmartSpaces_Operation_SpinSpeedLevel::~org_alljoyn_SmartSpaces_Operation_SpinSpeedLevel()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_SpinSpeedLevel::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "SpinSpeedLevel getting properties";

        status = controller->GetMaxLevel();
        if (status != ER_OK)
        {
            qWarning() << "SpinSpeedLevel::fetchProperties Failed to get MaxLevel" << QCC_StatusText(status);
        }

        status = controller->GetTargetLevel();
        if (status != ER_OK)
        {
            qWarning() << "SpinSpeedLevel::fetchProperties Failed to get TargetLevel" << QCC_StatusText(status);
        }

        status = controller->GetSelectableLevels();
        if (status != ER_OK)
        {
            qWarning() << "SpinSpeedLevel::fetchProperties Failed to get SelectableLevels" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_SpinSpeedLevel::slotOnResponseGetMaxLevel(QStatus status, const uint8_t value)
{
    qWarning() << "SpinSpeedLevel::slotOnResponseGetMaxLevel";

    edit_MaxLevel->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_SpinSpeedLevel::slotOnMaxLevelChanged(const uint8_t value)
{
    qWarning() << "SpinSpeedLevel::slotOnMaxLevelChanged";

    edit_MaxLevel->setText(QStringFrom(value));
}






void org_alljoyn_SmartSpaces_Operation_SpinSpeedLevel::slotOnResponseGetTargetLevel(QStatus status, const uint8_t value)
{
    qWarning() << "SpinSpeedLevel::slotOnResponseGetTargetLevel";

    edit_TargetLevel->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_SpinSpeedLevel::slotOnTargetLevelChanged(const uint8_t value)
{
    qWarning() << "SpinSpeedLevel::slotOnTargetLevelChanged";

    edit_TargetLevel->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_SpinSpeedLevel::slotOnResponseSetTargetLevel(QStatus status)
{
    qWarning() << "SpinSpeedLevel::slotOnResponseSetTargetLevel";

    if (status != ER_OK)
    {
        qcShowStatus(this, "Failed to set TargetLevel", status);
        qWarning() << "SpinSpeedLevel::slotOnResponseSetTargetLevel Failed to set TargetLevel" << QCC_StatusText(status);
        fetchProperties();      // restore the display of properties
    }
}



void org_alljoyn_SmartSpaces_Operation_SpinSpeedLevel::slotSetTargetLevel()
{
    qWarning() << "SpinSpeedLevel::slotSetTargetLevel";

    bool ok = false;
    uint8_t value;
    QString str = edit_TargetLevel->text();
    value = QStringTo<uint8_t>(str, &ok);
    if (!ok)
    {
        qWarning() << "SpinSpeedLevel::slotSetTargetLevel Failed to convert '" << str << "' to uint8_t";
    }

    if (ok)
    {
        QStatus status = controller->SetTargetLevel(value);

        if (status != ER_OK)
        {
            qWarning() << "SpinSpeedLevel::slotSetTargetLevel Failed to get TargetLevel" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_SpinSpeedLevel::slotOnResponseGetSelectableLevels(QStatus status, const std::vector<uint8_t>& value)
{
    qWarning() << "SpinSpeedLevel::slotOnResponseGetSelectableLevels";

    edit_SelectableLevels->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_SpinSpeedLevel::slotOnSelectableLevelsChanged(const std::vector<uint8_t>& value)
{
    qWarning() << "SpinSpeedLevel::slotOnSelectableLevelsChanged";

    edit_SelectableLevels->setText(QStringFrom(value));
}



