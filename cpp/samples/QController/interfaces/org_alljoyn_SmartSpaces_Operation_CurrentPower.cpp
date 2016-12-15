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

#include "org_alljoyn_SmartSpaces_Operation_CurrentPower.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <sstream>




using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_CurrentPower*>();


org_alljoyn_SmartSpaces_Operation_CurrentPower::org_alljoyn_SmartSpaces_Operation_CurrentPower(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("CurrentPower"));
    // Create line edit for CurrentPower
    edit_CurrentPower = new QLineEdit();
    edit_CurrentPower->setToolTip("The instantaneous power consumption of the device ");
    edit_CurrentPower->setReadOnly(true);
    layout->addWidget(edit_CurrentPower);
    layout->addWidget(new QLabel("Precision"));
    // Create line edit for Precision
    edit_Precision = new QLineEdit();
    edit_Precision->setToolTip("The precision of the CurrentPower property; i.e., the value actual power consumption must change before CurrentPower is updated.");
    edit_Precision->setReadOnly(true);
    layout->addWidget(edit_Precision);
    layout->addWidget(new QLabel("UpdateMinTime"));
    // Create line edit for UpdateMinTime
    edit_UpdateMinTime = new QLineEdit();
    edit_UpdateMinTime->setToolTip("The minimum time between updates of the CurrentPower");
    edit_UpdateMinTime->setReadOnly(true);
    layout->addWidget(edit_UpdateMinTime);

    if (iface)
    {
        controller = iface->CreateInterface<CurrentPowerIntfController>(m_listener);
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

org_alljoyn_SmartSpaces_Operation_CurrentPower::~org_alljoyn_SmartSpaces_Operation_CurrentPower()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_CurrentPower::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "org_alljoyn_SmartSpaces_Operation_CurrentPower getting properties";

        status = controller->GetCurrentPower();
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get CurrentPower" << QCC_StatusText(status);
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



void org_alljoyn_SmartSpaces_Operation_CurrentPower::slotOnResponseGetCurrentPower(QStatus status, const double value)
{
    qWarning() << __FUNCTION__;
    edit_CurrentPower->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_CurrentPower::slotOnCurrentPowerChanged(const double value)
{
    qWarning() << __FUNCTION__;
    edit_CurrentPower->setText(QStringFrom(value));
}




void org_alljoyn_SmartSpaces_Operation_CurrentPower::slotOnResponseGetPrecision(QStatus status, const double value)
{
    qWarning() << __FUNCTION__;
    edit_Precision->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_CurrentPower::slotOnPrecisionChanged(const double value)
{
    qWarning() << __FUNCTION__;
    edit_Precision->setText(QStringFrom(value));
}




void org_alljoyn_SmartSpaces_Operation_CurrentPower::slotOnResponseGetUpdateMinTime(QStatus status, const uint16_t value)
{
    qWarning() << __FUNCTION__;
    edit_UpdateMinTime->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_CurrentPower::slotOnUpdateMinTimeChanged(const uint16_t value)
{
    qWarning() << __FUNCTION__;
    edit_UpdateMinTime->setText(QStringFrom(value));
}
