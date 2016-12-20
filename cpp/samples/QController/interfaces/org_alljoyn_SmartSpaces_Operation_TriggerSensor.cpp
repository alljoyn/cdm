/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include "org_alljoyn_SmartSpaces_Operation_TriggerSensor.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <sstream>




using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_TriggerSensor*>();


org_alljoyn_SmartSpaces_Operation_TriggerSensor::org_alljoyn_SmartSpaces_Operation_TriggerSensor(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("CurrentlyTriggered"));
    // Create line edit for CurrentlyTriggered
    edit_CurrentlyTriggered = new QLineEdit();
    edit_CurrentlyTriggered->setToolTip("The current status of the sensor's trigger.");
    edit_CurrentlyTriggered->setReadOnly(true);
    layout->addWidget(edit_CurrentlyTriggered);

    if (iface)
    {
        controller = iface->CreateInterface<TriggerSensorIntfController>(m_listener);
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

org_alljoyn_SmartSpaces_Operation_TriggerSensor::~org_alljoyn_SmartSpaces_Operation_TriggerSensor()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_TriggerSensor::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "org_alljoyn_SmartSpaces_Operation_TriggerSensor getting properties";

        status = controller->GetCurrentlyTriggered();
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get CurrentlyTriggered" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_TriggerSensor::slotOnResponseGetCurrentlyTriggered(QStatus status, const bool value)
{
    qWarning() << __FUNCTION__;
    edit_CurrentlyTriggered->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_TriggerSensor::slotOnCurrentlyTriggeredChanged(const bool value)
{
    qWarning() << __FUNCTION__;
    edit_CurrentlyTriggered->setText(QStringFrom(value));
}