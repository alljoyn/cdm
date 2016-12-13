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

#include "org_alljoyn_SmartSpaces_Operation_EnergyUsage.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <sstream>




using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_EnergyUsage*>();


org_alljoyn_SmartSpaces_Operation_EnergyUsage::org_alljoyn_SmartSpaces_Operation_EnergyUsage(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);


    // Create button for ResetCumulativeEnergy
    button_ResetCumulativeEnergy = new QPushButton("ResetCumulativeEnergy");
    button_ResetCumulativeEnergy->setToolTip("Resets the value of CumulativeEnergy to 0.");
    QObject::connect(button_ResetCumulativeEnergy, SIGNAL(clicked()), this, SLOT(slotClickResetCumulativeEnergy()));
    layout->addWidget(button_ResetCumulativeEnergy);

    layout->addWidget(new QLabel("CumulativeEnergy"));
    // Create line edit for CumulativeEnergy
    edit_CumulativeEnergy = new QLineEdit();
    edit_CumulativeEnergy->setToolTip("The cumulative energy consumption of the device");
    edit_CumulativeEnergy->setReadOnly(true);
    layout->addWidget(edit_CumulativeEnergy);
    layout->addWidget(new QLabel("Precision"));
    // Create line edit for Precision
    edit_Precision = new QLineEdit();
    edit_Precision->setToolTip("The precision of the CumulativeEnergy property; i.e., the value the actual energy consumption must change before CumulativeEnergy is updated");
    edit_Precision->setReadOnly(true);
    layout->addWidget(edit_Precision);
    layout->addWidget(new QLabel("UpdateMinTime"));
    // Create line edit for UpdateMinTime
    edit_UpdateMinTime = new QLineEdit();
    edit_UpdateMinTime->setToolTip("The minimum time between updates of the CumulativeEnergy property");
    edit_UpdateMinTime->setReadOnly(true);
    layout->addWidget(edit_UpdateMinTime);

    if (iface)
    {
        controller = iface->CreateInterface<EnergyUsageIntfController>(m_listener);
        if (controller)
        {
            qWarning() << __FUNCTION__ << " Getting properties";

            QStatus status;
            // Get current values
            status = controller->GetCumulativeEnergy();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get CumulativeEnergy" << QCC_StatusText(status);
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

org_alljoyn_SmartSpaces_Operation_EnergyUsage::~org_alljoyn_SmartSpaces_Operation_EnergyUsage()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_EnergyUsage::slotClickResetCumulativeEnergy()
{
    qWarning() << __FUNCTION__;



    QStatus status = controller->ResetCumulativeEnergy(NULL);
    if (status != ER_OK)
    {
        qWarning() << __FUNCTION__ << " Failed to call ResetCumulativeEnergy" << QCC_StatusText(status);
    }
}



void org_alljoyn_SmartSpaces_Operation_EnergyUsage::slotOnResponseGetCumulativeEnergy(QStatus status, const double value)
{
    qWarning() << __FUNCTION__;
    edit_CumulativeEnergy->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_EnergyUsage::slotOnCumulativeEnergyChanged(const double value)
{
    qWarning() << __FUNCTION__;
    edit_CumulativeEnergy->setText(QStringFrom(value));
}




void org_alljoyn_SmartSpaces_Operation_EnergyUsage::slotOnResponseGetPrecision(QStatus status, const double value)
{
    qWarning() << __FUNCTION__;
    edit_Precision->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_EnergyUsage::slotOnPrecisionChanged(const double value)
{
    qWarning() << __FUNCTION__;
    edit_Precision->setText(QStringFrom(value));
}




void org_alljoyn_SmartSpaces_Operation_EnergyUsage::slotOnResponseGetUpdateMinTime(QStatus status, const uint16_t value)
{
    qWarning() << __FUNCTION__;
    edit_UpdateMinTime->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_EnergyUsage::slotOnUpdateMinTimeChanged(const uint16_t value)
{
    qWarning() << __FUNCTION__;
    edit_UpdateMinTime->setText(QStringFrom(value));
}




void org_alljoyn_SmartSpaces_Operation_EnergyUsage::slotOnResponseMethodResetCumulativeEnergy(QStatus status, const QString& errorName)
{
    if (status == ER_OK)
    {
        qInfo() << "Received response to method ResetCumulativeEnergy";
    }
    else
    {
        qWarning() << "Received an error from method ResetCumulativeEnergy, error = " << errorName;
    }
}