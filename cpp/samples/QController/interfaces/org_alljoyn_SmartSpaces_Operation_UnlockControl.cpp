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

#include "org_alljoyn_SmartSpaces_Operation_UnlockControl.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <sstream>




using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_UnlockControl*>();


org_alljoyn_SmartSpaces_Operation_UnlockControl::org_alljoyn_SmartSpaces_Operation_UnlockControl(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);


    // Create button for Unlock
    button_Unlock = new QPushButton("Unlock");
    button_Unlock->setToolTip("Disengage the locking mechanism.");
    QObject::connect(button_Unlock, SIGNAL(clicked()), this, SLOT(slotClickUnlock()));
    layout->addWidget(button_Unlock);


    if (iface)
    {
        controller = iface->CreateInterface<UnlockControlIntfController>(m_listener);
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

org_alljoyn_SmartSpaces_Operation_UnlockControl::~org_alljoyn_SmartSpaces_Operation_UnlockControl()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_UnlockControl::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "org_alljoyn_SmartSpaces_Operation_UnlockControl getting properties";
    }
}



void org_alljoyn_SmartSpaces_Operation_UnlockControl::slotClickUnlock()
{
    qWarning() << __FUNCTION__;



    QStatus status = controller->Unlock(NULL);
    if (status != ER_OK)
    {
        qWarning() << __FUNCTION__ << " Failed to call Unlock" << QCC_StatusText(status);
    }
}



void org_alljoyn_SmartSpaces_Operation_UnlockControl::slotOnResponseMethodUnlock(QStatus status, const QString& errorName)
{
    if (status == ER_OK)
    {
        qInfo() << "Received response to method Unlock";
    }
    else
    {
        qWarning() << "Received an error from method Unlock, error = " << errorName;
    }
}