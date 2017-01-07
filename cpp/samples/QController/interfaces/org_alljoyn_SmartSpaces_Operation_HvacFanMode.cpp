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
#include "org_alljoyn_SmartSpaces_Operation_HvacFanMode.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <sstream>




using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_HvacFanMode*>();

Q_DECLARE_METATYPE(ajn::services::HvacFanModeInterface::Mode);
Q_DECLARE_METATYPE(std::vector<ajn::services::HvacFanModeInterface::Mode>);
static const int auto_register_enum_Mode = qRegisterMetaType<ajn::services::HvacFanModeInterface::Mode>("HvacFanModeInterface::Mode");
static const int auto_register_enum_v_Mode = qRegisterMetaType<std::vector<ajn::services::HvacFanModeInterface::Mode>>("std::vector<HvacFanModeInterface::Mode>");



org_alljoyn_SmartSpaces_Operation_HvacFanMode::org_alljoyn_SmartSpaces_Operation_HvacFanMode(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("Mode"));
    // Create the editing widget for Mode
    edit_Mode = new QComboBox();
    edit_Mode->setEditable(false);
    edit_Mode->addItem("Auto");
    edit_Mode->addItem("Circulation");
    edit_Mode->addItem("Continuous");
    edit_Mode->setEnabled(true);
    QObject::connect(edit_Mode, SIGNAL(currentTextChanged(const QString &)), this, SLOT(slotSetMode()));

    layout->addWidget(edit_Mode);
    layout->addWidget(new QLabel("SupportedModes"));
    // Create the editing widget for SupportedModes
    edit_SupportedModes = new QLineEdit();
    edit_SupportedModes->setToolTip("Array of supported modes.");
    edit_SupportedModes->setReadOnly(true);

    layout->addWidget(edit_SupportedModes);

    if (iface)
    {
        controller = iface->CreateInterface<HvacFanModeIntfController>(m_listener);
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

org_alljoyn_SmartSpaces_Operation_HvacFanMode::~org_alljoyn_SmartSpaces_Operation_HvacFanMode()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_HvacFanMode::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "HvacFanMode getting properties";

        status = controller->GetMode();
        if (status != ER_OK)
        {
            qWarning() << "HvacFanMode::fetchProperties Failed to get Mode" << QCC_StatusText(status);
        }

        status = controller->GetSupportedModes();
        if (status != ER_OK)
        {
            qWarning() << "HvacFanMode::fetchProperties Failed to get SupportedModes" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_HvacFanMode::slotOnResponseGetMode(QStatus status, const HvacFanModeInterface::Mode value)
{
    qWarning() << "HvacFanMode::slotOnResponseGetMode";

    switch (value)
    {
    case HvacFanModeInterface::MODE_AUTO:
        edit_Mode->setCurrentText("Auto");
        break;

    case HvacFanModeInterface::MODE_CIRCULATION:
        edit_Mode->setCurrentText("Circulation");
        break;

    case HvacFanModeInterface::MODE_CONTINUOUS:
        edit_Mode->setCurrentText("Continuous");
        break;

    default:
        edit_Mode->setCurrentText("");
        break;
    }
}



void org_alljoyn_SmartSpaces_Operation_HvacFanMode::slotOnModeChanged(const HvacFanModeInterface::Mode value)
{
    qWarning() << "HvacFanMode::slotOnModeChanged";

    switch (value)
    {
    case HvacFanModeInterface::MODE_AUTO:
        edit_Mode->setCurrentText("Auto");
        break;

    case HvacFanModeInterface::MODE_CIRCULATION:
        edit_Mode->setCurrentText("Circulation");
        break;

    case HvacFanModeInterface::MODE_CONTINUOUS:
        edit_Mode->setCurrentText("Continuous");
        break;

    default:
        edit_Mode->setCurrentText("");
        break;
    }
}



void org_alljoyn_SmartSpaces_Operation_HvacFanMode::slotOnResponseSetMode(QStatus status)
{
    qWarning() << "HvacFanMode::slotOnResponseSetMode";

    if (status != ER_OK)
    {
        qWarning() << "HvacFanMode::slotOnResponseSetMode Failed to set Mode" << QCC_StatusText(status);
    }
}



void org_alljoyn_SmartSpaces_Operation_HvacFanMode::slotSetMode()
{
    qWarning() << "HvacFanMode::slotSetMode";

    bool ok = false;
    HvacFanModeInterface::Mode value;
    QString str = edit_Mode->currentText();
    if (str == "Auto")
    {
        value = HvacFanModeInterface::MODE_AUTO;
        ok = true;
    }
    else
    if (str == "Circulation")
    {
        value = HvacFanModeInterface::MODE_CIRCULATION;
        ok = true;
    }
    else
    if (str == "Continuous")
    {
        value = HvacFanModeInterface::MODE_CONTINUOUS;
        ok = true;
    }
    else
    if (!str.isEmpty())
    {
        qWarning() << "HvacFanMode::slotSetMode Failed to convert '" << str.constData() << "' to HvacFanModeInterface::Mode";
    }

    if (ok)
    {
        QStatus status = controller->SetMode(value);

        if (status != ER_OK)
        {
            qWarning() << "HvacFanMode::slotSetMode Failed to get Mode" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_HvacFanMode::slotOnResponseGetSupportedModes(QStatus status, const std::vector<HvacFanModeInterface::Mode>& value)
{
    qWarning() << "HvacFanMode::slotOnResponseGetSupportedModes";

    edit_SupportedModes->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_HvacFanMode::slotOnSupportedModesChanged(const std::vector<HvacFanModeInterface::Mode>& value)
{
    qWarning() << "HvacFanMode::slotOnSupportedModesChanged";

    edit_SupportedModes->setText(QStringFrom(value));
}



