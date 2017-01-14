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
#include "org_alljoyn_SmartSpaces_UserInterfaceSettings_TimeDisplay.h"
#include "qcUtils.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <sstream>



using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_UserInterfaceSettings_TimeDisplay*>();



org_alljoyn_SmartSpaces_UserInterfaceSettings_TimeDisplay::org_alljoyn_SmartSpaces_UserInterfaceSettings_TimeDisplay(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("<b>DisplayTimeFormat</b>"));
    // Create the editing widget for DisplayTimeFormat
    edit_DisplayTimeFormat = new QLineEdit();
    edit_DisplayTimeFormat->setToolTip("The clock format which is currently used to display time (0=12-hour, 1=24-hour)");
    QObject::connect(edit_DisplayTimeFormat, SIGNAL(returnPressed()), this, SLOT(slotSetDisplayTimeFormat()));

    layout->addWidget(edit_DisplayTimeFormat);
    layout->addWidget(new QLabel("<b>SupportedDisplayTimeFormats</b>"));
    // Create the editing widget for SupportedDisplayTimeFormats
    edit_SupportedDisplayTimeFormats = new QLabel();

    layout->addWidget(edit_SupportedDisplayTimeFormats);

    messages_ = new QLabel();
    layout->addWidget(messages_);

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
        qWarning() << "TimeDisplay getting properties";

        status = controller->GetDisplayTimeFormat();
        if (status != ER_OK)
        {
            qWarning() << "TimeDisplay::fetchProperties Failed to get DisplayTimeFormat" << QCC_StatusText(status);
        }

        status = controller->GetSupportedDisplayTimeFormats();
        if (status != ER_OK)
        {
            qWarning() << "TimeDisplay::fetchProperties Failed to get SupportedDisplayTimeFormats" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_UserInterfaceSettings_TimeDisplay::slotOnResponseGetDisplayTimeFormat(QStatus status, const uint8_t value)
{
    qWarning() << "TimeDisplay::slotOnResponseGetDisplayTimeFormat";

    edit_DisplayTimeFormat->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_UserInterfaceSettings_TimeDisplay::slotOnDisplayTimeFormatChanged(const uint8_t value)
{
    qWarning() << "TimeDisplay::slotOnDisplayTimeFormatChanged";

    edit_DisplayTimeFormat->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_UserInterfaceSettings_TimeDisplay::slotOnResponseSetDisplayTimeFormat(QStatus status)
{
    qWarning() << "TimeDisplay::slotOnResponseSetDisplayTimeFormat";

    if (status != ER_OK)
    {
        qcShowStatus(this, "Failed to set DisplayTimeFormat", status);
        qWarning() << "TimeDisplay::slotOnResponseSetDisplayTimeFormat Failed to set DisplayTimeFormat" << QCC_StatusText(status);
        fetchProperties();      // restore the display of properties
    }
}



void org_alljoyn_SmartSpaces_UserInterfaceSettings_TimeDisplay::slotSetDisplayTimeFormat()
{
    qWarning() << "TimeDisplay::slotSetDisplayTimeFormat";

    bool ok = false;
    uint8_t value;
    QString str = edit_DisplayTimeFormat->text();
    value = QStringTo<uint8_t>(str, &ok);
    if (!ok)
    {
        qWarning() << "TimeDisplay::slotSetDisplayTimeFormat Failed to convert '" << str << "' to uint8_t";
    }

    if (ok)
    {
        QStatus status = controller->SetDisplayTimeFormat(value);

        if (status != ER_OK)
        {
            qWarning() << "TimeDisplay::slotSetDisplayTimeFormat Failed to get DisplayTimeFormat" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_UserInterfaceSettings_TimeDisplay::slotOnResponseGetSupportedDisplayTimeFormats(QStatus status, const std::vector<uint8_t>& value)
{
    qWarning() << "TimeDisplay::slotOnResponseGetSupportedDisplayTimeFormats";

    edit_SupportedDisplayTimeFormats->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_UserInterfaceSettings_TimeDisplay::slotOnSupportedDisplayTimeFormatsChanged(const std::vector<uint8_t>& value)
{
    qWarning() << "TimeDisplay::slotOnSupportedDisplayTimeFormatsChanged";

    edit_SupportedDisplayTimeFormats->setText(QStringFrom(value));
}



