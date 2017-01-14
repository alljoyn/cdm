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
#include "org_alljoyn_SmartSpaces_Environment_TargetHumidity.h"
#include "qcUtils.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <sstream>



using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Environment_TargetHumidity*>();



org_alljoyn_SmartSpaces_Environment_TargetHumidity::org_alljoyn_SmartSpaces_Environment_TargetHumidity(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("<b>TargetValue</b>"));
    // Create the editing widget for TargetValue
    edit_TargetValue = new QLineEdit();
    edit_TargetValue->setToolTip("Target set-point value of relative humidity.");
    QObject::connect(edit_TargetValue, SIGNAL(returnPressed()), this, SLOT(slotSetTargetValue()));

    layout->addWidget(edit_TargetValue);
    layout->addWidget(new QLabel("<b>MinValue</b>"));
    // Create the editing widget for MinValue
    edit_MinValue = new QLabel();

    layout->addWidget(edit_MinValue);
    layout->addWidget(new QLabel("<b>MaxValue</b>"));
    // Create the editing widget for MaxValue
    edit_MaxValue = new QLabel();

    layout->addWidget(edit_MaxValue);
    layout->addWidget(new QLabel("<b>StepValue</b>"));
    // Create the editing widget for StepValue
    edit_StepValue = new QLabel();

    layout->addWidget(edit_StepValue);
    layout->addWidget(new QLabel("<b>SelectableHumidityLevels</b>"));
    // Create the editing widget for SelectableHumidityLevels
    edit_SelectableHumidityLevels = new QLabel();

    layout->addWidget(edit_SelectableHumidityLevels);

    messages_ = new QLabel();
    layout->addWidget(messages_);

    if (iface)
    {
        controller = iface->CreateInterface<TargetHumidityIntfController>(m_listener);
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

org_alljoyn_SmartSpaces_Environment_TargetHumidity::~org_alljoyn_SmartSpaces_Environment_TargetHumidity()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Environment_TargetHumidity::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "TargetHumidity getting properties";

        status = controller->GetTargetValue();
        if (status != ER_OK)
        {
            qWarning() << "TargetHumidity::fetchProperties Failed to get TargetValue" << QCC_StatusText(status);
        }

        status = controller->GetMinValue();
        if (status != ER_OK)
        {
            qWarning() << "TargetHumidity::fetchProperties Failed to get MinValue" << QCC_StatusText(status);
        }

        status = controller->GetMaxValue();
        if (status != ER_OK)
        {
            qWarning() << "TargetHumidity::fetchProperties Failed to get MaxValue" << QCC_StatusText(status);
        }

        status = controller->GetStepValue();
        if (status != ER_OK)
        {
            qWarning() << "TargetHumidity::fetchProperties Failed to get StepValue" << QCC_StatusText(status);
        }

        status = controller->GetSelectableHumidityLevels();
        if (status != ER_OK)
        {
            qWarning() << "TargetHumidity::fetchProperties Failed to get SelectableHumidityLevels" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Environment_TargetHumidity::slotOnResponseGetTargetValue(QStatus status, const uint8_t value)
{
    qWarning() << "TargetHumidity::slotOnResponseGetTargetValue";

    edit_TargetValue->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Environment_TargetHumidity::slotOnTargetValueChanged(const uint8_t value)
{
    qWarning() << "TargetHumidity::slotOnTargetValueChanged";

    edit_TargetValue->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Environment_TargetHumidity::slotOnResponseSetTargetValue(QStatus status)
{
    qWarning() << "TargetHumidity::slotOnResponseSetTargetValue";

    if (status != ER_OK)
    {
        qcShowStatus(this, "Failed to set TargetValue", status);
        qWarning() << "TargetHumidity::slotOnResponseSetTargetValue Failed to set TargetValue" << QCC_StatusText(status);
        fetchProperties();      // restore the display of properties
    }
}



void org_alljoyn_SmartSpaces_Environment_TargetHumidity::slotSetTargetValue()
{
    qWarning() << "TargetHumidity::slotSetTargetValue";

    bool ok = false;
    uint8_t value;
    QString str = edit_TargetValue->text();
    value = QStringTo<uint8_t>(str, &ok);
    if (!ok)
    {
        qWarning() << "TargetHumidity::slotSetTargetValue Failed to convert '" << str << "' to uint8_t";
    }

    if (ok)
    {
        QStatus status = controller->SetTargetValue(value);

        if (status != ER_OK)
        {
            qWarning() << "TargetHumidity::slotSetTargetValue Failed to get TargetValue" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Environment_TargetHumidity::slotOnResponseGetMinValue(QStatus status, const uint8_t value)
{
    qWarning() << "TargetHumidity::slotOnResponseGetMinValue";

    edit_MinValue->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Environment_TargetHumidity::slotOnMinValueChanged(const uint8_t value)
{
    qWarning() << "TargetHumidity::slotOnMinValueChanged";

    edit_MinValue->setText(QStringFrom(value));
}






void org_alljoyn_SmartSpaces_Environment_TargetHumidity::slotOnResponseGetMaxValue(QStatus status, const uint8_t value)
{
    qWarning() << "TargetHumidity::slotOnResponseGetMaxValue";

    edit_MaxValue->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Environment_TargetHumidity::slotOnMaxValueChanged(const uint8_t value)
{
    qWarning() << "TargetHumidity::slotOnMaxValueChanged";

    edit_MaxValue->setText(QStringFrom(value));
}






void org_alljoyn_SmartSpaces_Environment_TargetHumidity::slotOnResponseGetStepValue(QStatus status, const uint8_t value)
{
    qWarning() << "TargetHumidity::slotOnResponseGetStepValue";

    edit_StepValue->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Environment_TargetHumidity::slotOnStepValueChanged(const uint8_t value)
{
    qWarning() << "TargetHumidity::slotOnStepValueChanged";

    edit_StepValue->setText(QStringFrom(value));
}






void org_alljoyn_SmartSpaces_Environment_TargetHumidity::slotOnResponseGetSelectableHumidityLevels(QStatus status, const std::vector<uint8_t>& value)
{
    qWarning() << "TargetHumidity::slotOnResponseGetSelectableHumidityLevels";

    edit_SelectableHumidityLevels->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Environment_TargetHumidity::slotOnSelectableHumidityLevelsChanged(const std::vector<uint8_t>& value)
{
    qWarning() << "TargetHumidity::slotOnSelectableHumidityLevelsChanged";

    edit_SelectableHumidityLevels->setText(QStringFrom(value));
}



