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

#include "org_alljoyn_SmartSpaces_Operation_HeatingZone.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <sstream>




using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_HeatingZone*>();


org_alljoyn_SmartSpaces_Operation_HeatingZone::org_alljoyn_SmartSpaces_Operation_HeatingZone(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("NumberOfHeatingZones"));
    // Create line edit for NumberOfHeatingZones
    edit_NumberOfHeatingZones = new QLineEdit();
    edit_NumberOfHeatingZones->setToolTip("Number of heating zones.");
    edit_NumberOfHeatingZones->setReadOnly(true);
    layout->addWidget(edit_NumberOfHeatingZones);
    layout->addWidget(new QLabel("MaxHeatingLevels"));
    // Create line edit for MaxHeatingLevels
    edit_MaxHeatingLevels = new QLineEdit();
    edit_MaxHeatingLevels->setToolTip("Max heating levels for each zone.");
    edit_MaxHeatingLevels->setReadOnly(true);
    layout->addWidget(edit_MaxHeatingLevels);
    layout->addWidget(new QLabel("HeatingLevels"));
    // Create line edit for HeatingLevels
    edit_HeatingLevels = new QLineEdit();
    edit_HeatingLevels->setToolTip("Current heating levels for each zone.");
    edit_HeatingLevels->setReadOnly(true);
    layout->addWidget(edit_HeatingLevels);

    if (iface)
    {
        controller = iface->CreateInterface<HeatingZoneIntfController>(m_listener);
        if (controller)
        {
            qWarning() << __FUNCTION__ << " Getting properties";

            QStatus status;
            // Get current values
            status = controller->GetNumberOfHeatingZones();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get NumberOfHeatingZones" << QCC_StatusText(status);
            }
            status = controller->GetMaxHeatingLevels();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get MaxHeatingLevels" << QCC_StatusText(status);
            }
            status = controller->GetHeatingLevels();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get HeatingLevels" << QCC_StatusText(status);
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

org_alljoyn_SmartSpaces_Operation_HeatingZone::~org_alljoyn_SmartSpaces_Operation_HeatingZone()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_HeatingZone::slotOnResponseGetNumberOfHeatingZones(QStatus status, const uint8_t value)
{
    qWarning() << __FUNCTION__;
    edit_NumberOfHeatingZones->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_HeatingZone::slotOnNumberOfHeatingZonesChanged(const uint8_t value)
{
    qWarning() << __FUNCTION__;
    edit_NumberOfHeatingZones->setText(QStringFrom(value));
}




void org_alljoyn_SmartSpaces_Operation_HeatingZone::slotOnResponseGetMaxHeatingLevels(QStatus status, const std::vector<uint8_t>& value)
{
    qWarning() << __FUNCTION__;
    edit_MaxHeatingLevels->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_HeatingZone::slotOnMaxHeatingLevelsChanged(const std::vector<uint8_t>& value)
{
    qWarning() << __FUNCTION__;
    edit_MaxHeatingLevels->setText(QStringFrom(value));
}




void org_alljoyn_SmartSpaces_Operation_HeatingZone::slotOnResponseGetHeatingLevels(QStatus status, const std::vector<uint8_t>& value)
{
    qWarning() << __FUNCTION__;
    edit_HeatingLevels->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_HeatingZone::slotOnHeatingLevelsChanged(const std::vector<uint8_t>& value)
{
    qWarning() << __FUNCTION__;
    edit_HeatingLevels->setText(QStringFrom(value));
}
