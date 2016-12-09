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

#include "org_alljoyn_SmartSpaces_Operation_RapidModeTimed.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <sstream>




using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_RapidModeTimed*>();


org_alljoyn_SmartSpaces_Operation_RapidModeTimed::org_alljoyn_SmartSpaces_Operation_RapidModeTimed(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("RapidModeMinutesRemaining"));
    // Create line edit for RapidModeMinutesRemaining
    edit_RapidModeMinutesRemaining = new QLineEdit();
    edit_RapidModeMinutesRemaining->setToolTip("Time remaining in rapid mode. Zero indicates not in rapid mode.");
    edit_RapidModeMinutesRemaining->setReadOnly(false);
    QObject::connect(edit_RapidModeMinutesRemaining, SIGNAL(returnPressed()), this, SLOT(slotSetRapidModeMinutesRemaining()));
    layout->addWidget(edit_RapidModeMinutesRemaining);
    layout->addWidget(new QLabel("MaxSetMinutes"));
    // Create line edit for MaxSetMinutes
    edit_MaxSetMinutes = new QLineEdit();
    edit_MaxSetMinutes->setToolTip("Maximum rapid mode set time. It does not change to accomodate already in rapid mode.");
    edit_MaxSetMinutes->setReadOnly(true);
    layout->addWidget(edit_MaxSetMinutes);

    if (iface)
    {
        controller = iface->CreateInterface<RapidModeTimedIntfController>(m_listener);
        if (controller)
        {
            qWarning() << __FUNCTION__ << " Getting properties";

            QStatus status;
            // Get current values
            status = controller->GetRapidModeMinutesRemaining();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get RapidModeMinutesRemaining" << QCC_StatusText(status);
            }
            status = controller->GetMaxSetMinutes();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get MaxSetMinutes" << QCC_StatusText(status);
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

org_alljoyn_SmartSpaces_Operation_RapidModeTimed::~org_alljoyn_SmartSpaces_Operation_RapidModeTimed()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_RapidModeTimed::slotOnResponseGetRapidModeMinutesRemaining(QStatus status, const uint16_t value)
{
    qWarning() << __FUNCTION__;
    edit_RapidModeMinutesRemaining->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_RapidModeTimed::slotOnRapidModeMinutesRemainingChanged(const uint16_t value)
{
    qWarning() << __FUNCTION__;
    edit_RapidModeMinutesRemaining->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_RapidModeTimed::slotOnResponseSetRapidModeMinutesRemaining(QStatus status)
{
    qWarning() << __FUNCTION__;
}

void org_alljoyn_SmartSpaces_Operation_RapidModeTimed::slotSetRapidModeMinutesRemaining()
{
    qWarning() << __FUNCTION__;

    bool ok = false;
    QString str = edit_RapidModeMinutesRemaining->text();
    uint16_t value = QStringTo<uint16_t>(str, &ok);
    if (ok)
    {
        QStatus status = controller->SetRapidModeMinutesRemaining(value);
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get RapidModeMinutesRemaining" << QCC_StatusText(status);
        }
    }
    else
    {
        qWarning() << __FUNCTION__ << "Failed to convert '" << str << "' to uint16_t";
    }
}




void org_alljoyn_SmartSpaces_Operation_RapidModeTimed::slotOnResponseGetMaxSetMinutes(QStatus status, const uint16_t value)
{
    qWarning() << __FUNCTION__;
    edit_MaxSetMinutes->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_RapidModeTimed::slotOnMaxSetMinutesChanged(const uint16_t value)
{
    qWarning() << __FUNCTION__;
    edit_MaxSetMinutes->setText(QStringFrom(value));
}
