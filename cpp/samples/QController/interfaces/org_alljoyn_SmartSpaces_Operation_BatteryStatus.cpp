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
#include "org_alljoyn_SmartSpaces_Operation_BatteryStatus.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <sstream>




using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_BatteryStatus*>();



org_alljoyn_SmartSpaces_Operation_BatteryStatus::org_alljoyn_SmartSpaces_Operation_BatteryStatus(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("CurrentValue"));
    // Create the editing widget for CurrentValue
    edit_CurrentValue = new QLineEdit();
    edit_CurrentValue->setToolTip("This interface provides capability to represent remaining battery status.");
    edit_CurrentValue->setReadOnly(true);

    layout->addWidget(edit_CurrentValue);
    layout->addWidget(new QLabel("IsCharging"));
    // Create the editing widget for IsCharging
    edit_IsCharging = new QCheckBox();
    edit_IsCharging->setEnabled(false);

    layout->addWidget(edit_IsCharging);

    if (iface)
    {
        controller = iface->CreateInterface<BatteryStatusIntfController>(m_listener);
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

org_alljoyn_SmartSpaces_Operation_BatteryStatus::~org_alljoyn_SmartSpaces_Operation_BatteryStatus()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_BatteryStatus::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "BatteryStatus getting properties";

        status = controller->GetCurrentValue();
        if (status != ER_OK)
        {
            qWarning() << "BatteryStatus::fetchProperties Failed to get CurrentValue" << QCC_StatusText(status);
        }

        status = controller->GetIsCharging();
        if (status != ER_OK)
        {
            qWarning() << "BatteryStatus::fetchProperties Failed to get IsCharging" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_BatteryStatus::slotOnResponseGetCurrentValue(QStatus status, const uint8_t value)
{
    qWarning() << "BatteryStatus::slotOnResponseGetCurrentValue";

    edit_CurrentValue->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_BatteryStatus::slotOnCurrentValueChanged(const uint8_t value)
{
    qWarning() << "BatteryStatus::slotOnCurrentValueChanged";

    edit_CurrentValue->setText(QStringFrom(value));
}






void org_alljoyn_SmartSpaces_Operation_BatteryStatus::slotOnResponseGetIsCharging(QStatus status, const bool value)
{
    qWarning() << "BatteryStatus::slotOnResponseGetIsCharging";

    edit_IsCharging->setChecked(value);
}



void org_alljoyn_SmartSpaces_Operation_BatteryStatus::slotOnIsChargingChanged(const bool value)
{
    qWarning() << "BatteryStatus::slotOnIsChargingChanged";

    edit_IsCharging->setChecked(value);
}



