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

#include "org_alljoyn_SmartSpaces_UserInterfaceSettings_TemperatureDisplay.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <sstream>




using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_UserInterfaceSettings_TemperatureDisplay*>();


org_alljoyn_SmartSpaces_UserInterfaceSettings_TemperatureDisplay::org_alljoyn_SmartSpaces_UserInterfaceSettings_TemperatureDisplay(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("DisplayTemperatureUnit"));
    // Create line edit for DisplayTemperatureUnit
    edit_DisplayTemperatureUnit = new QLineEdit();
    edit_DisplayTemperatureUnit->setToolTip("The unit being used to display temperature (0=C, 1=F, 2 =K)");
    edit_DisplayTemperatureUnit->setReadOnly(false);
    QObject::connect(edit_DisplayTemperatureUnit, SIGNAL(returnPressed()), this, SLOT(slotSetDisplayTemperatureUnit()));
    layout->addWidget(edit_DisplayTemperatureUnit);
    layout->addWidget(new QLabel("SupportedDisplayTemperatureUnits"));
    // Create line edit for SupportedDisplayTemperatureUnits
    edit_SupportedDisplayTemperatureUnits = new QLineEdit();
    edit_SupportedDisplayTemperatureUnits->setToolTip("List of supported temperature units");
    edit_SupportedDisplayTemperatureUnits->setReadOnly(true);
    layout->addWidget(edit_SupportedDisplayTemperatureUnits);

    if (iface)
    {
        controller = iface->CreateInterface<TemperatureDisplayIntfController>(m_listener);
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

org_alljoyn_SmartSpaces_UserInterfaceSettings_TemperatureDisplay::~org_alljoyn_SmartSpaces_UserInterfaceSettings_TemperatureDisplay()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_UserInterfaceSettings_TemperatureDisplay::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "org_alljoyn_SmartSpaces_UserInterfaceSettings_TemperatureDisplay getting properties";

        status = controller->GetDisplayTemperatureUnit();
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get DisplayTemperatureUnit" << QCC_StatusText(status);
        }

        status = controller->GetSupportedDisplayTemperatureUnits();
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get SupportedDisplayTemperatureUnits" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_UserInterfaceSettings_TemperatureDisplay::slotOnResponseGetDisplayTemperatureUnit(QStatus status, const uint8_t value)
{
    qWarning() << __FUNCTION__;
    edit_DisplayTemperatureUnit->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_UserInterfaceSettings_TemperatureDisplay::slotOnDisplayTemperatureUnitChanged(const uint8_t value)
{
    qWarning() << __FUNCTION__;
    edit_DisplayTemperatureUnit->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_UserInterfaceSettings_TemperatureDisplay::slotOnResponseSetDisplayTemperatureUnit(QStatus status)
{
    qWarning() << __FUNCTION__;
}

void org_alljoyn_SmartSpaces_UserInterfaceSettings_TemperatureDisplay::slotSetDisplayTemperatureUnit()
{
    qWarning() << __FUNCTION__;

    bool ok = false;
    QString str = edit_DisplayTemperatureUnit->text();
    uint8_t value = QStringTo<uint8_t>(str, &ok);
    if (ok)
    {
        QStatus status = controller->SetDisplayTemperatureUnit(value);
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get DisplayTemperatureUnit" << QCC_StatusText(status);
        }
    }
    else
    {
        qWarning() << __FUNCTION__ << "Failed to convert '" << str << "' to uint8_t";
    }
}




void org_alljoyn_SmartSpaces_UserInterfaceSettings_TemperatureDisplay::slotOnResponseGetSupportedDisplayTemperatureUnits(QStatus status, const std::vector<uint8_t>& value)
{
    qWarning() << __FUNCTION__;
    edit_SupportedDisplayTemperatureUnits->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_UserInterfaceSettings_TemperatureDisplay::slotOnSupportedDisplayTemperatureUnitsChanged(const std::vector<uint8_t>& value)
{
    qWarning() << __FUNCTION__;
    edit_SupportedDisplayTemperatureUnits->setText(QStringFrom(value));
}

