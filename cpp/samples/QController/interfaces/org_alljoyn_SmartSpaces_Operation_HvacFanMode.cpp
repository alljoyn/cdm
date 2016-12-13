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


org_alljoyn_SmartSpaces_Operation_HvacFanMode::org_alljoyn_SmartSpaces_Operation_HvacFanMode(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("Mode"));
    // Create line edit for Mode
    edit_Mode = new QLineEdit();
    edit_Mode->setToolTip("Current mode of device.");
    edit_Mode->setReadOnly(false);
    QObject::connect(edit_Mode, SIGNAL(returnPressed()), this, SLOT(slotSetMode()));
    layout->addWidget(edit_Mode);
    layout->addWidget(new QLabel("SupportedModes"));
    // Create line edit for SupportedModes
    edit_SupportedModes = new QLineEdit();
    edit_SupportedModes->setToolTip("Array of supported modes.");
    edit_SupportedModes->setReadOnly(true);
    layout->addWidget(edit_SupportedModes);

    if (iface)
    {
        controller = iface->CreateInterface<HvacFanModeIntfController>(m_listener);
        if (controller)
        {
            qWarning() << __FUNCTION__ << " Getting properties";

            QStatus status;
            // Get current values
            status = controller->GetMode();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get Mode" << QCC_StatusText(status);
            }
            status = controller->GetSupportedModes();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get SupportedModes" << QCC_StatusText(status);
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

org_alljoyn_SmartSpaces_Operation_HvacFanMode::~org_alljoyn_SmartSpaces_Operation_HvacFanMode()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_HvacFanMode::slotOnResponseGetMode(QStatus status, const HvacFanModeInterface::Mode value)
{
    qWarning() << __FUNCTION__;
    edit_Mode->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_HvacFanMode::slotOnModeChanged(const HvacFanModeInterface::Mode value)
{
    qWarning() << __FUNCTION__;
    edit_Mode->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_HvacFanMode::slotOnResponseSetMode(QStatus status)
{
    qWarning() << __FUNCTION__;
}

void org_alljoyn_SmartSpaces_Operation_HvacFanMode::slotSetMode()
{
    qWarning() << __FUNCTION__;

    bool ok = false;
    QString str = edit_Mode->text();
    HvacFanModeInterface::Mode value = QStringTo<HvacFanModeInterface::Mode>(str, &ok);
    if (ok)
    {
        QStatus status = controller->SetMode(value);
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get Mode" << QCC_StatusText(status);
        }
    }
    else
    {
        qWarning() << __FUNCTION__ << "Failed to convert '" << str << "' to HvacFanModeInterface::Mode";
    }
}




void org_alljoyn_SmartSpaces_Operation_HvacFanMode::slotOnResponseGetSupportedModes(QStatus status, const std::vector<HvacFanModeInterface::Mode>& value)
{
    qWarning() << __FUNCTION__;
    edit_SupportedModes->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_HvacFanMode::slotOnSupportedModesChanged(const std::vector<HvacFanModeInterface::Mode>& value)
{
    qWarning() << __FUNCTION__;
    edit_SupportedModes->setText(QStringFrom(value));
}
