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
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <sstream>




using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Environment_TargetTemperature*>();


org_alljoyn_SmartSpaces_Environment_TargetTemperature::org_alljoyn_SmartSpaces_Environment_TargetTemperature(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("TargetValue"));
    // Create line edit for TargetValue
    edit_TargetValue = new QLineEdit();
    edit_TargetValue->setToolTip("Target temperature expressed in Celsius.");
    edit_TargetValue->setReadOnly(false);
    QObject::connect(edit_TargetValue, SIGNAL(returnPressed()), this, SLOT(slotSetTargetValue()));
    layout->addWidget(edit_TargetValue);
    layout->addWidget(new QLabel("MinValue"));
    // Create line edit for MinValue
    edit_MinValue = new QLineEdit();
    edit_MinValue->setToolTip("Minimum value of target temperature.");
    edit_MinValue->setReadOnly(true);
    layout->addWidget(edit_MinValue);
    layout->addWidget(new QLabel("MaxValue"));
    // Create line edit for MaxValue
    edit_MaxValue = new QLineEdit();
    edit_MaxValue->setToolTip("Maximum value of target temperature.");
    edit_MaxValue->setReadOnly(true);
    layout->addWidget(edit_MaxValue);
    layout->addWidget(new QLabel("StepValue"));
    // Create line edit for StepValue
    edit_StepValue = new QLineEdit();
    edit_StepValue->setToolTip("Step value allowed for the TargetTemperature setting.");
    edit_StepValue->setReadOnly(true);
    layout->addWidget(edit_StepValue);

    if (iface)
    {
        controller = iface->CreateInterface<TargetTemperatureIntfController>(m_listener);
        if (controller)
        {
            qWarning() << __FUNCTION__ << " Getting properties";

            QStatus status;
            // Get current values
            status = controller->GetTargetValue();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get TargetValue" << QCC_StatusText(status);
            }
            status = controller->GetMinValue();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get MinValue" << QCC_StatusText(status);
            }
            status = controller->GetMaxValue();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get MaxValue" << QCC_StatusText(status);
            }
            status = controller->GetStepValue();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get StepValue" << QCC_StatusText(status);
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

org_alljoyn_SmartSpaces_Environment_TargetTemperature::~org_alljoyn_SmartSpaces_Environment_TargetTemperature()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Environment_TargetTemperature::slotOnResponseGetTargetValue(QStatus status, const double value)
{
    qWarning() << __FUNCTION__;
    edit_TargetValue->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Environment_TargetTemperature::slotOnTargetValueChanged(const double value)
{
    qWarning() << __FUNCTION__;
    edit_TargetValue->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Environment_TargetTemperature::slotOnResponseSetTargetValue(QStatus status)
{
    qWarning() << __FUNCTION__;
}

void org_alljoyn_SmartSpaces_Environment_TargetTemperature::slotSetTargetValue()
{
    qWarning() << __FUNCTION__;

    bool ok = false;
    QString str = edit_TargetValue->text();
    double value = QStringTo<double>(str, &ok);
    if (ok)
    {
        QStatus status = controller->SetTargetValue(value);
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get TargetValue" << QCC_StatusText(status);
        }
    }
    else
    {
        qWarning() << __FUNCTION__ << "Failed to convert '" << str << "' to double";
    }
}




void org_alljoyn_SmartSpaces_Environment_TargetTemperature::slotOnResponseGetMinValue(QStatus status, const double value)
{
    qWarning() << __FUNCTION__;
    edit_MinValue->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Environment_TargetTemperature::slotOnMinValueChanged(const double value)
{
    qWarning() << __FUNCTION__;
    edit_MinValue->setText(QStringFrom(value));
}




void org_alljoyn_SmartSpaces_Environment_TargetTemperature::slotOnResponseGetMaxValue(QStatus status, const double value)
{
    qWarning() << __FUNCTION__;
    edit_MaxValue->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Environment_TargetTemperature::slotOnMaxValueChanged(const double value)
{
    qWarning() << __FUNCTION__;
    edit_MaxValue->setText(QStringFrom(value));
}




void org_alljoyn_SmartSpaces_Environment_TargetTemperature::slotOnResponseGetStepValue(QStatus status, const double value)
{
    qWarning() << __FUNCTION__;
    edit_StepValue->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Environment_TargetTemperature::slotOnStepValueChanged(const double value)
{
    qWarning() << __FUNCTION__;
    edit_StepValue->setText(QStringFrom(value));
}
