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
#include "qcUtils.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
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

    layout->addWidget(new QLabel("<b>CumulativeEnergy</b>"));
    // Create the editing widget for CumulativeEnergy
    edit_CumulativeEnergy = new QLabel();

    layout->addWidget(edit_CumulativeEnergy);
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
        controller = iface->CreateInterface<EnergyUsageIntfController>(m_listener);
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

org_alljoyn_SmartSpaces_Operation_EnergyUsage::~org_alljoyn_SmartSpaces_Operation_EnergyUsage()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_EnergyUsage::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "EnergyUsage getting properties";

        status = controller->GetCumulativeEnergy();
        if (status != ER_OK)
        {
            qWarning() << "EnergyUsage::fetchProperties Failed to get CumulativeEnergy" << QCC_StatusText(status);
        }

        status = controller->GetPrecision();
        if (status != ER_OK)
        {
            qWarning() << "EnergyUsage::fetchProperties Failed to get Precision" << QCC_StatusText(status);
        }

        status = controller->GetUpdateMinTime();
        if (status != ER_OK)
        {
            qWarning() << "EnergyUsage::fetchProperties Failed to get UpdateMinTime" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_EnergyUsage::slotClickResetCumulativeEnergy()
{
    qWarning() << "EnergyUsage::slotClickResetCumulativeEnergy";


    bool ok = true;

    if (ok)
    {
        QStatus status = controller->ResetCumulativeEnergy(NULL);
        if (status != ER_OK)
        {
            qWarning() << "EnergyUsage::slotClick Failed to call ResetCumulativeEnergy" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_EnergyUsage::slotOnResponseGetCumulativeEnergy(QStatus status, const double value)
{
    qWarning() << "EnergyUsage::slotOnResponseGetCumulativeEnergy";

    edit_CumulativeEnergy->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_EnergyUsage::slotOnCumulativeEnergyChanged(const double value)
{
    qWarning() << "EnergyUsage::slotOnCumulativeEnergyChanged";

    edit_CumulativeEnergy->setText(QStringFrom(value));
}






void org_alljoyn_SmartSpaces_Operation_EnergyUsage::slotOnResponseGetPrecision(QStatus status, const double value)
{
    qWarning() << "EnergyUsage::slotOnResponseGetPrecision";

    edit_Precision->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_EnergyUsage::slotOnPrecisionChanged(const double value)
{
    qWarning() << "EnergyUsage::slotOnPrecisionChanged";

    edit_Precision->setText(QStringFrom(value));
}






void org_alljoyn_SmartSpaces_Operation_EnergyUsage::slotOnResponseGetUpdateMinTime(QStatus status, const uint16_t value)
{
    qWarning() << "EnergyUsage::slotOnResponseGetUpdateMinTime";

    edit_UpdateMinTime->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_EnergyUsage::slotOnUpdateMinTimeChanged(const uint16_t value)
{
    qWarning() << "EnergyUsage::slotOnUpdateMinTimeChanged";

    edit_UpdateMinTime->setText(QStringFrom(value));
}






void org_alljoyn_SmartSpaces_Operation_EnergyUsage::slotOnResponseMethodResetCumulativeEnergy(QStatus status, const QString& errorName)
{
    if (status == ER_OK)
    {
        qInfo() << "EnergyUsage::slotOnResponseMethodResetCumulativeEnergy";
    }
    else
    {
        qWarning() << "EnergyUsage::slotOnResponseMethodResetCumulativeEnergy Received error = " << errorName;
    }
}
