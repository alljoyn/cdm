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

#include "org_alljoyn_SmartSpaces_Operation_LockedStatus.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <sstream>




using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_LockedStatus*>();


org_alljoyn_SmartSpaces_Operation_LockedStatus::org_alljoyn_SmartSpaces_Operation_LockedStatus(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("IsLocked"));
    // Create line edit for IsLocked
    edit_IsLocked = new QLineEdit();
    edit_IsLocked->setToolTip("The status of the locking mechanism.");
    edit_IsLocked->setReadOnly(true);
    layout->addWidget(edit_IsLocked);

    if (iface)
    {
        controller = iface->CreateInterface<LockedStatusIntfController>(m_listener);
        if (controller)
        {
            qWarning() << __FUNCTION__ << " Getting properties";

            QStatus status;
            // Get current values
            status = controller->GetIsLocked();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get IsLocked" << QCC_StatusText(status);
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

org_alljoyn_SmartSpaces_Operation_LockedStatus::~org_alljoyn_SmartSpaces_Operation_LockedStatus()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_LockedStatus::slotOnResponseGetIsLocked(QStatus status, const bool value)
{
    qWarning() << __FUNCTION__;
    edit_IsLocked->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_LockedStatus::slotOnIsLockedChanged(const bool value)
{
    qWarning() << __FUNCTION__;
    edit_IsLocked->setText(QStringFrom(value));
}
