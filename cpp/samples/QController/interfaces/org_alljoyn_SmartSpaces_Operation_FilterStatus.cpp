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
#include "org_alljoyn_SmartSpaces_Operation_FilterStatus.h"
#include "qcUtils.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <sstream>



using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_FilterStatus*>();



org_alljoyn_SmartSpaces_Operation_FilterStatus::org_alljoyn_SmartSpaces_Operation_FilterStatus(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("<b>ExpectedLifeInDays</b>"));
    // Create the editing widget for ExpectedLifeInDays
    edit_ExpectedLifeInDays = new QLabel();

    layout->addWidget(edit_ExpectedLifeInDays);
    layout->addWidget(new QLabel("<b>IsCleanable</b>"));
    // Create the editing widget for IsCleanable
    edit_IsCleanable = new QCheckBox();
    edit_IsCleanable->setEnabled(false);

    layout->addWidget(edit_IsCleanable);
    layout->addWidget(new QLabel("<b>OrderPercentage</b>"));
    // Create the editing widget for OrderPercentage
    edit_OrderPercentage = new QLabel();

    layout->addWidget(edit_OrderPercentage);
    layout->addWidget(new QLabel("<b>Manufacturer</b>"));
    // Create the editing widget for Manufacturer
    edit_Manufacturer = new QLabel();

    layout->addWidget(edit_Manufacturer);
    layout->addWidget(new QLabel("<b>PartNumber</b>"));
    // Create the editing widget for PartNumber
    edit_PartNumber = new QLabel();

    layout->addWidget(edit_PartNumber);
    layout->addWidget(new QLabel("<b>Url</b>"));
    // Create the editing widget for Url
    edit_Url = new QLabel();

    layout->addWidget(edit_Url);
    layout->addWidget(new QLabel("<b>LifeRemaining</b>"));
    // Create the editing widget for LifeRemaining
    edit_LifeRemaining = new QLabel();

    layout->addWidget(edit_LifeRemaining);

    messages_ = new QLabel();
    layout->addWidget(messages_);

    if (iface)
    {
        controller = iface->CreateInterface<FilterStatusIntfController>(m_listener);
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

org_alljoyn_SmartSpaces_Operation_FilterStatus::~org_alljoyn_SmartSpaces_Operation_FilterStatus()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_FilterStatus::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "FilterStatus getting properties";

        status = controller->GetExpectedLifeInDays();
        if (status != ER_OK)
        {
            qWarning() << "FilterStatus::fetchProperties Failed to get ExpectedLifeInDays" << QCC_StatusText(status);
        }

        status = controller->GetIsCleanable();
        if (status != ER_OK)
        {
            qWarning() << "FilterStatus::fetchProperties Failed to get IsCleanable" << QCC_StatusText(status);
        }

        status = controller->GetOrderPercentage();
        if (status != ER_OK)
        {
            qWarning() << "FilterStatus::fetchProperties Failed to get OrderPercentage" << QCC_StatusText(status);
        }

        status = controller->GetManufacturer();
        if (status != ER_OK)
        {
            qWarning() << "FilterStatus::fetchProperties Failed to get Manufacturer" << QCC_StatusText(status);
        }

        status = controller->GetPartNumber();
        if (status != ER_OK)
        {
            qWarning() << "FilterStatus::fetchProperties Failed to get PartNumber" << QCC_StatusText(status);
        }

        status = controller->GetUrl();
        if (status != ER_OK)
        {
            qWarning() << "FilterStatus::fetchProperties Failed to get Url" << QCC_StatusText(status);
        }

        status = controller->GetLifeRemaining();
        if (status != ER_OK)
        {
            qWarning() << "FilterStatus::fetchProperties Failed to get LifeRemaining" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_FilterStatus::slotOnResponseGetExpectedLifeInDays(QStatus status, const uint16_t value)
{
    qWarning() << "FilterStatus::slotOnResponseGetExpectedLifeInDays";

    edit_ExpectedLifeInDays->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_FilterStatus::slotOnExpectedLifeInDaysChanged(const uint16_t value)
{
    qWarning() << "FilterStatus::slotOnExpectedLifeInDaysChanged";

    edit_ExpectedLifeInDays->setText(QStringFrom(value));
}






void org_alljoyn_SmartSpaces_Operation_FilterStatus::slotOnResponseGetIsCleanable(QStatus status, const bool value)
{
    qWarning() << "FilterStatus::slotOnResponseGetIsCleanable";

    edit_IsCleanable->setChecked(value);
}



void org_alljoyn_SmartSpaces_Operation_FilterStatus::slotOnIsCleanableChanged(const bool value)
{
    qWarning() << "FilterStatus::slotOnIsCleanableChanged";

    edit_IsCleanable->setChecked(value);
}






void org_alljoyn_SmartSpaces_Operation_FilterStatus::slotOnResponseGetOrderPercentage(QStatus status, const uint8_t value)
{
    qWarning() << "FilterStatus::slotOnResponseGetOrderPercentage";

    edit_OrderPercentage->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_FilterStatus::slotOnOrderPercentageChanged(const uint8_t value)
{
    qWarning() << "FilterStatus::slotOnOrderPercentageChanged";

    edit_OrderPercentage->setText(QStringFrom(value));
}






void org_alljoyn_SmartSpaces_Operation_FilterStatus::slotOnResponseGetManufacturer(QStatus status, const qcc::String& value)
{
    qWarning() << "FilterStatus::slotOnResponseGetManufacturer";

    edit_Manufacturer->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_FilterStatus::slotOnManufacturerChanged(const qcc::String& value)
{
    qWarning() << "FilterStatus::slotOnManufacturerChanged";

    edit_Manufacturer->setText(QStringFrom(value));
}






void org_alljoyn_SmartSpaces_Operation_FilterStatus::slotOnResponseGetPartNumber(QStatus status, const qcc::String& value)
{
    qWarning() << "FilterStatus::slotOnResponseGetPartNumber";

    edit_PartNumber->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_FilterStatus::slotOnPartNumberChanged(const qcc::String& value)
{
    qWarning() << "FilterStatus::slotOnPartNumberChanged";

    edit_PartNumber->setText(QStringFrom(value));
}






void org_alljoyn_SmartSpaces_Operation_FilterStatus::slotOnResponseGetUrl(QStatus status, const qcc::String& value)
{
    qWarning() << "FilterStatus::slotOnResponseGetUrl";

    edit_Url->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_FilterStatus::slotOnUrlChanged(const qcc::String& value)
{
    qWarning() << "FilterStatus::slotOnUrlChanged";

    edit_Url->setText(QStringFrom(value));
}






void org_alljoyn_SmartSpaces_Operation_FilterStatus::slotOnResponseGetLifeRemaining(QStatus status, const uint8_t value)
{
    qWarning() << "FilterStatus::slotOnResponseGetLifeRemaining";

    edit_LifeRemaining->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_FilterStatus::slotOnLifeRemainingChanged(const uint8_t value)
{
    qWarning() << "FilterStatus::slotOnLifeRemainingChanged";

    edit_LifeRemaining->setText(QStringFrom(value));
}



