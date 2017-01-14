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
#include "org_alljoyn_SmartSpaces_Environment_TargetTemperature.h"
#include "qcUtils.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <sstream>



using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Environment_TargetTemperature*>();



org_alljoyn_SmartSpaces_Environment_TargetTemperature::org_alljoyn_SmartSpaces_Environment_TargetTemperature(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("<b>TargetValue</b>"));
    // Create the editing widget for TargetValue
    edit_TargetValue = new QLineEdit();
    edit_TargetValue->setToolTip("Target temperature expressed in Celsius.");
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

    messages_ = new QLabel();
    layout->addWidget(messages_);

    if (iface)
    {
        controller = iface->CreateInterface<TargetTemperatureIntfController>(m_listener);
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

org_alljoyn_SmartSpaces_Environment_TargetTemperature::~org_alljoyn_SmartSpaces_Environment_TargetTemperature()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Environment_TargetTemperature::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "TargetTemperature getting properties";

        status = controller->GetTargetValue();
        if (status != ER_OK)
        {
            qWarning() << "TargetTemperature::fetchProperties Failed to get TargetValue" << QCC_StatusText(status);
        }

        status = controller->GetMinValue();
        if (status != ER_OK)
        {
            qWarning() << "TargetTemperature::fetchProperties Failed to get MinValue" << QCC_StatusText(status);
        }

        status = controller->GetMaxValue();
        if (status != ER_OK)
        {
            qWarning() << "TargetTemperature::fetchProperties Failed to get MaxValue" << QCC_StatusText(status);
        }

        status = controller->GetStepValue();
        if (status != ER_OK)
        {
            qWarning() << "TargetTemperature::fetchProperties Failed to get StepValue" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Environment_TargetTemperature::slotOnResponseGetTargetValue(QStatus status, const double value)
{
    qWarning() << "TargetTemperature::slotOnResponseGetTargetValue";

    edit_TargetValue->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Environment_TargetTemperature::slotOnTargetValueChanged(const double value)
{
    qWarning() << "TargetTemperature::slotOnTargetValueChanged";

    edit_TargetValue->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Environment_TargetTemperature::slotOnResponseSetTargetValue(QStatus status)
{
    qWarning() << "TargetTemperature::slotOnResponseSetTargetValue";

    if (status != ER_OK)
    {
        qcShowStatus(this, "Failed to set TargetValue", status);
        qWarning() << "TargetTemperature::slotOnResponseSetTargetValue Failed to set TargetValue" << QCC_StatusText(status);
        fetchProperties();      // restore the display of properties
    }
}



void org_alljoyn_SmartSpaces_Environment_TargetTemperature::slotSetTargetValue()
{
    qWarning() << "TargetTemperature::slotSetTargetValue";

    bool ok = false;
    double value;
    QString str = edit_TargetValue->text();
    value = QStringTo<double>(str, &ok);
    if (!ok)
    {
        qWarning() << "TargetTemperature::slotSetTargetValue Failed to convert '" << str << "' to double";
    }

    if (ok)
    {
        QStatus status = controller->SetTargetValue(value);

        if (status != ER_OK)
        {
            qWarning() << "TargetTemperature::slotSetTargetValue Failed to get TargetValue" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Environment_TargetTemperature::slotOnResponseGetMinValue(QStatus status, const double value)
{
    qWarning() << "TargetTemperature::slotOnResponseGetMinValue";

    edit_MinValue->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Environment_TargetTemperature::slotOnMinValueChanged(const double value)
{
    qWarning() << "TargetTemperature::slotOnMinValueChanged";

    edit_MinValue->setText(QStringFrom(value));
}






void org_alljoyn_SmartSpaces_Environment_TargetTemperature::slotOnResponseGetMaxValue(QStatus status, const double value)
{
    qWarning() << "TargetTemperature::slotOnResponseGetMaxValue";

    edit_MaxValue->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Environment_TargetTemperature::slotOnMaxValueChanged(const double value)
{
    qWarning() << "TargetTemperature::slotOnMaxValueChanged";

    edit_MaxValue->setText(QStringFrom(value));
}






void org_alljoyn_SmartSpaces_Environment_TargetTemperature::slotOnResponseGetStepValue(QStatus status, const double value)
{
    qWarning() << "TargetTemperature::slotOnResponseGetStepValue";

    edit_StepValue->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Environment_TargetTemperature::slotOnStepValueChanged(const double value)
{
    qWarning() << "TargetTemperature::slotOnStepValueChanged";

    edit_StepValue->setText(QStringFrom(value));
}



