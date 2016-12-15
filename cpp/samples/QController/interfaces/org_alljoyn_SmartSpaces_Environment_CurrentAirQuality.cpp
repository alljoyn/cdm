/******************************************************************************
 * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#include "org_alljoyn_SmartSpaces_Environment_CurrentAirQuality.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <sstream>




using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Environment_CurrentAirQuality*>();


org_alljoyn_SmartSpaces_Environment_CurrentAirQuality::org_alljoyn_SmartSpaces_Environment_CurrentAirQuality(CommonControllerInterface *iface)
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
    layout->addWidget(new QLabel("CurrentValue"));
    // Create line edit for CurrentValue
    edit_CurrentValue = new QLineEdit();
    edit_CurrentValue->setToolTip("The current value of air quality.");
    edit_CurrentValue->setReadOnly(true);
    layout->addWidget(edit_CurrentValue);
    layout->addWidget(new QLabel("MinValue"));
    // Create line edit for MinValue
    edit_MinValue = new QLineEdit();
    edit_MinValue->setToolTip("The minimum value allowed for CurrentValue.");
    edit_MinValue->setReadOnly(true);
    layout->addWidget(edit_MinValue);
    layout->addWidget(new QLabel("MaxValue"));
    // Create line edit for MaxValue
    edit_MaxValue = new QLineEdit();
    edit_MaxValue->setToolTip("The maximum value allowed for CurrentValue.");
    edit_MaxValue->setReadOnly(true);
    layout->addWidget(edit_MaxValue);
    layout->addWidget(new QLabel("Precision"));
    // Create line edit for Precision
    edit_Precision = new QLineEdit();
    edit_Precision->setToolTip("The precision of the CurrentValue property.");
    edit_Precision->setReadOnly(true);
    layout->addWidget(edit_Precision);
    layout->addWidget(new QLabel("UpdateMinTime"));
    // Create line edit for UpdateMinTime
    edit_UpdateMinTime = new QLineEdit();
    edit_UpdateMinTime->setToolTip("The minimum time between updates of the CurrentValue property in milliseconds.");
    edit_UpdateMinTime->setReadOnly(true);
    layout->addWidget(edit_UpdateMinTime);

    if (iface)
    {
        controller = iface->CreateInterface<CurrentAirQualityIntfController>(m_listener);
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

org_alljoyn_SmartSpaces_Environment_CurrentAirQuality::~org_alljoyn_SmartSpaces_Environment_CurrentAirQuality()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Environment_CurrentAirQuality::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "org_alljoyn_SmartSpaces_Environment_CurrentAirQuality getting properties";

        status = controller->GetContaminantType();
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get ContaminantType" << QCC_StatusText(status);
        }

        status = controller->GetCurrentValue();
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get CurrentValue" << QCC_StatusText(status);
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

        status = controller->GetPrecision();
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get Precision" << QCC_StatusText(status);
        }

        status = controller->GetUpdateMinTime();
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get UpdateMinTime" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Environment_CurrentAirQuality::slotOnResponseGetContaminantType(QStatus status, const CurrentAirQualityInterface::ContaminantType value)
{
    qWarning() << __FUNCTION__;
    edit_ContaminantType->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Environment_CurrentAirQuality::slotOnContaminantTypeChanged(const CurrentAirQualityInterface::ContaminantType value)
{
    qWarning() << __FUNCTION__;
    edit_ContaminantType->setText(QStringFrom(value));
}




void org_alljoyn_SmartSpaces_Environment_CurrentAirQuality::slotOnResponseGetCurrentValue(QStatus status, const double value)
{
    qWarning() << __FUNCTION__;
    edit_CurrentValue->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Environment_CurrentAirQuality::slotOnCurrentValueChanged(const double value)
{
    qWarning() << __FUNCTION__;
    edit_CurrentValue->setText(QStringFrom(value));
}




void org_alljoyn_SmartSpaces_Environment_CurrentAirQuality::slotOnResponseGetMinValue(QStatus status, const double value)
{
    qWarning() << __FUNCTION__;
    edit_MinValue->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Environment_CurrentAirQuality::slotOnMinValueChanged(const double value)
{
    qWarning() << __FUNCTION__;
    edit_MinValue->setText(QStringFrom(value));
}




void org_alljoyn_SmartSpaces_Environment_CurrentAirQuality::slotOnResponseGetMaxValue(QStatus status, const double value)
{
    qWarning() << __FUNCTION__;
    edit_MaxValue->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Environment_CurrentAirQuality::slotOnMaxValueChanged(const double value)
{
    qWarning() << __FUNCTION__;
    edit_MaxValue->setText(QStringFrom(value));
}




void org_alljoyn_SmartSpaces_Environment_CurrentAirQuality::slotOnResponseGetPrecision(QStatus status, const double value)
{
    qWarning() << __FUNCTION__;
    edit_Precision->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Environment_CurrentAirQuality::slotOnPrecisionChanged(const double value)
{
    qWarning() << __FUNCTION__;
    edit_Precision->setText(QStringFrom(value));
}




void org_alljoyn_SmartSpaces_Environment_CurrentAirQuality::slotOnResponseGetUpdateMinTime(QStatus status, const uint16_t value)
{
    qWarning() << __FUNCTION__;
    edit_UpdateMinTime->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Environment_CurrentAirQuality::slotOnUpdateMinTimeChanged(const uint16_t value)
{
    qWarning() << __FUNCTION__;
    edit_UpdateMinTime->setText(QStringFrom(value));
}
