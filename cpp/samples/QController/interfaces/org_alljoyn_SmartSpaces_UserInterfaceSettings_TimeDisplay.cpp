/******************************************************************************
 *  * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#include "org_alljoyn_SmartSpaces_UserInterfaceSettings_TimeDisplay.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <sstream>




using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_UserInterfaceSettings_TimeDisplay*>();


org_alljoyn_SmartSpaces_UserInterfaceSettings_TimeDisplay::org_alljoyn_SmartSpaces_UserInterfaceSettings_TimeDisplay(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("DisplayTimeFormat"));
    // Create line edit for DisplayTimeFormat
    edit_DisplayTimeFormat = new QLineEdit();
    edit_DisplayTimeFormat->setToolTip("The clock format which is currently used to display time (0=12-hour, 1=24-hour)");
    edit_DisplayTimeFormat->setReadOnly(false);
    QObject::connect(edit_DisplayTimeFormat, SIGNAL(returnPressed()), this, SLOT(slotSetDisplayTimeFormat()));
    layout->addWidget(edit_DisplayTimeFormat);
    layout->addWidget(new QLabel("SupportedDisplayTimeFormats"));
    // Create line edit for SupportedDisplayTimeFormats
    edit_SupportedDisplayTimeFormats = new QLineEdit();
    edit_SupportedDisplayTimeFormats->setToolTip("List of supported clock formats");
    edit_SupportedDisplayTimeFormats->setReadOnly(true);
    layout->addWidget(edit_SupportedDisplayTimeFormats);

    if (iface)
    {
        controller = iface->CreateInterface<TimeDisplayIntfController>(m_listener);
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

org_alljoyn_SmartSpaces_UserInterfaceSettings_TimeDisplay::~org_alljoyn_SmartSpaces_UserInterfaceSettings_TimeDisplay()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_UserInterfaceSettings_TimeDisplay::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "org_alljoyn_SmartSpaces_UserInterfaceSettings_TimeDisplay getting properties";

        status = controller->GetDisplayTimeFormat();
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get DisplayTimeFormat" << QCC_StatusText(status);
        }

        status = controller->GetSupportedDisplayTimeFormats();
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get SupportedDisplayTimeFormats" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_UserInterfaceSettings_TimeDisplay::slotOnResponseGetDisplayTimeFormat(QStatus status, const uint8_t value)
{
    qWarning() << __FUNCTION__;
    edit_DisplayTimeFormat->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_UserInterfaceSettings_TimeDisplay::slotOnDisplayTimeFormatChanged(const uint8_t value)
{
    qWarning() << __FUNCTION__;
    edit_DisplayTimeFormat->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_UserInterfaceSettings_TimeDisplay::slotOnResponseSetDisplayTimeFormat(QStatus status)
{
    qWarning() << __FUNCTION__;
}

void org_alljoyn_SmartSpaces_UserInterfaceSettings_TimeDisplay::slotSetDisplayTimeFormat()
{
    qWarning() << __FUNCTION__;

    bool ok = false;
    QString str = edit_DisplayTimeFormat->text();
    uint8_t value = QStringTo<uint8_t>(str, &ok);
    if (ok)
    {
        QStatus status = controller->SetDisplayTimeFormat(value);
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get DisplayTimeFormat" << QCC_StatusText(status);
        }
    }
    else
    {
        qWarning() << __FUNCTION__ << "Failed to convert '" << str << "' to uint8_t";
    }
}




void org_alljoyn_SmartSpaces_UserInterfaceSettings_TimeDisplay::slotOnResponseGetSupportedDisplayTimeFormats(QStatus status, const std::vector<uint8_t>& value)
{
    qWarning() << __FUNCTION__;
    edit_SupportedDisplayTimeFormats->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_UserInterfaceSettings_TimeDisplay::slotOnSupportedDisplayTimeFormatsChanged(const std::vector<uint8_t>& value)
{
    qWarning() << __FUNCTION__;
    edit_SupportedDisplayTimeFormats->setText(QStringFrom(value));
}
