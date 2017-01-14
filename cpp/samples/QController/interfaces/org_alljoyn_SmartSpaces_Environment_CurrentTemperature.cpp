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
#include "org_alljoyn_SmartSpaces_Environment_CurrentTemperature.h"
#include "qcUtils.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <sstream>



using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Environment_CurrentTemperature*>();



org_alljoyn_SmartSpaces_Environment_CurrentTemperature::org_alljoyn_SmartSpaces_Environment_CurrentTemperature(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("<b>CurrentValue</b>"));
    // Create the editing widget for CurrentValue
    edit_CurrentValue = new QLabel();

    layout->addWidget(edit_CurrentValue);
    layout->addWidget(new QLabel("<b>Precision</b>"));
    // Create the editing widget for Precision
    edit_Precision = new QLabel();

    layout->addWidget(edit_Precision);
    layout->addWidget(new QLabel("<b>UpdateMinTime</b>"));
    // Create the editing widget for UpdateMinTime
    edit_UpdateMinTime = new QLabel();

    layout->addWidget(edit_UpdateMinTime);

    messages_ = new QLabel();
    layout->addWidget(messages_);

    if (iface)
    {
        controller = iface->CreateInterface<CurrentTemperatureIntfController>(m_listener);
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

org_alljoyn_SmartSpaces_Environment_CurrentTemperature::~org_alljoyn_SmartSpaces_Environment_CurrentTemperature()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Environment_CurrentTemperature::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "CurrentTemperature getting properties";

        status = controller->GetCurrentValue();
        if (status != ER_OK)
        {
            qWarning() << "CurrentTemperature::fetchProperties Failed to get CurrentValue" << QCC_StatusText(status);
        }

        status = controller->GetPrecision();
        if (status != ER_OK)
        {
            qWarning() << "CurrentTemperature::fetchProperties Failed to get Precision" << QCC_StatusText(status);
        }

        status = controller->GetUpdateMinTime();
        if (status != ER_OK)
        {
            qWarning() << "CurrentTemperature::fetchProperties Failed to get UpdateMinTime" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Environment_CurrentTemperature::slotOnResponseGetCurrentValue(QStatus status, const double value)
{
    qWarning() << "CurrentTemperature::slotOnResponseGetCurrentValue";

    edit_CurrentValue->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Environment_CurrentTemperature::slotOnCurrentValueChanged(const double value)
{
    qWarning() << "CurrentTemperature::slotOnCurrentValueChanged";

    edit_CurrentValue->setText(QStringFrom(value));
}






void org_alljoyn_SmartSpaces_Environment_CurrentTemperature::slotOnResponseGetPrecision(QStatus status, const double value)
{
    qWarning() << "CurrentTemperature::slotOnResponseGetPrecision";

    edit_Precision->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Environment_CurrentTemperature::slotOnPrecisionChanged(const double value)
{
    qWarning() << "CurrentTemperature::slotOnPrecisionChanged";

    edit_Precision->setText(QStringFrom(value));
}






void org_alljoyn_SmartSpaces_Environment_CurrentTemperature::slotOnResponseGetUpdateMinTime(QStatus status, const uint16_t value)
{
    qWarning() << "CurrentTemperature::slotOnResponseGetUpdateMinTime";

    edit_UpdateMinTime->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Environment_CurrentTemperature::slotOnUpdateMinTimeChanged(const uint16_t value)
{
    qWarning() << "CurrentTemperature::slotOnUpdateMinTimeChanged";

    edit_UpdateMinTime->setText(QStringFrom(value));
}



