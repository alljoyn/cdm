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
#include "org_alljoyn_SmartSpaces_Operation_RepeatMode.h"
#include "qcUtils.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <sstream>



using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_RepeatMode*>();



org_alljoyn_SmartSpaces_Operation_RepeatMode::org_alljoyn_SmartSpaces_Operation_RepeatMode(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("<b>RepeatMode</b>"));
    // Create the editing widget for RepeatMode
    edit_RepeatMode = new QCheckBox();
    edit_RepeatMode->setEnabled(true);
    QObject::connect(edit_RepeatMode, SIGNAL(stateChanged(int)), this, SLOT(slotSetRepeatMode()));

    layout->addWidget(edit_RepeatMode);

    messages_ = new QLabel();
    layout->addWidget(messages_);

    if (iface)
    {
        controller = iface->CreateInterface<RepeatModeIntfController>(m_listener);
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

org_alljoyn_SmartSpaces_Operation_RepeatMode::~org_alljoyn_SmartSpaces_Operation_RepeatMode()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_RepeatMode::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "RepeatMode getting properties";

        status = controller->GetRepeatMode();
        if (status != ER_OK)
        {
            qWarning() << "RepeatMode::fetchProperties Failed to get RepeatMode" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_RepeatMode::slotOnResponseGetRepeatMode(QStatus status, const bool value)
{
    qWarning() << "RepeatMode::slotOnResponseGetRepeatMode";

    edit_RepeatMode->setChecked(value);
}



void org_alljoyn_SmartSpaces_Operation_RepeatMode::slotOnRepeatModeChanged(const bool value)
{
    qWarning() << "RepeatMode::slotOnRepeatModeChanged";

    edit_RepeatMode->setChecked(value);
}



void org_alljoyn_SmartSpaces_Operation_RepeatMode::slotOnResponseSetRepeatMode(QStatus status)
{
    qWarning() << "RepeatMode::slotOnResponseSetRepeatMode";

    if (status != ER_OK)
    {
        qcShowStatus(this, "Failed to set RepeatMode", status);
        qWarning() << "RepeatMode::slotOnResponseSetRepeatMode Failed to set RepeatMode" << QCC_StatusText(status);
        fetchProperties();      // restore the display of properties
    }
}



void org_alljoyn_SmartSpaces_Operation_RepeatMode::slotSetRepeatMode()
{
    qWarning() << "RepeatMode::slotSetRepeatMode";

    bool ok = false;
    bool value;
    value = edit_RepeatMode->isChecked();
    ok = true;

    if (ok)
    {
        QStatus status = controller->SetRepeatMode(value);

        if (status != ER_OK)
        {
            qWarning() << "RepeatMode::slotSetRepeatMode Failed to get RepeatMode" << QCC_StatusText(status);
        }
    }
}
