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
#include "org_alljoyn_SmartSpaces_Operation_LockControl.h"
#include "qcUtils.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <sstream>



using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_LockControl*>();



org_alljoyn_SmartSpaces_Operation_LockControl::org_alljoyn_SmartSpaces_Operation_LockControl(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);


    // Create button for Lock
    button_Lock = new QPushButton("Lock");
    button_Lock->setToolTip("Engage the locking mechanism.");
    QObject::connect(button_Lock, SIGNAL(clicked()), this, SLOT(slotClickLock()));
    layout->addWidget(button_Lock);


    messages_ = new QLabel();
    layout->addWidget(messages_);

    if (iface)
    {
        controller = iface->CreateInterface<LockControlIntfController>(m_listener);
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

org_alljoyn_SmartSpaces_Operation_LockControl::~org_alljoyn_SmartSpaces_Operation_LockControl()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_LockControl::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "LockControl getting properties";
    }
}



void org_alljoyn_SmartSpaces_Operation_LockControl::slotClickLock()
{
    qWarning() << "LockControl::slotClickLock";


    bool ok = true;

    if (ok)
    {
        QStatus status = controller->Lock(NULL);
        if (status != ER_OK)
        {
            qWarning() << "LockControl::slotClick Failed to call Lock" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_LockControl::slotOnResponseMethodLock(QStatus status, const QString& errorName)
{
    if (status == ER_OK)
    {
        qInfo() << "LockControl::slotOnResponseMethodLock";
    }
    else
    {
        qWarning() << "LockControl::slotOnResponseMethodLock Received error = " << errorName;
    }
}
