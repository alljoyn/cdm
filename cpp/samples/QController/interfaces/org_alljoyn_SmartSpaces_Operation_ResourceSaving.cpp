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
#include "org_alljoyn_SmartSpaces_Operation_ResourceSaving.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <sstream>




using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_ResourceSaving*>();



org_alljoyn_SmartSpaces_Operation_ResourceSaving::org_alljoyn_SmartSpaces_Operation_ResourceSaving(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("ResourceSavingMode"));
    // Create the editing widget for ResourceSavingMode
    edit_ResourceSavingMode = new QCheckBox();
    edit_ResourceSavingMode->setEnabled(true);
    QObject::connect(edit_ResourceSavingMode, SIGNAL(stateChanged(int)), this, SLOT(slotSetResourceSavingMode()));

    layout->addWidget(edit_ResourceSavingMode);

    if (iface)
    {
        controller = iface->CreateInterface<ResourceSavingIntfController>(m_listener);
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

org_alljoyn_SmartSpaces_Operation_ResourceSaving::~org_alljoyn_SmartSpaces_Operation_ResourceSaving()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_ResourceSaving::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "ResourceSaving getting properties";

        status = controller->GetResourceSavingMode();
        if (status != ER_OK)
        {
            qWarning() << "ResourceSaving::fetchProperties Failed to get ResourceSavingMode" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_ResourceSaving::slotOnResponseGetResourceSavingMode(QStatus status, const bool value)
{
    qWarning() << "ResourceSaving::slotOnResponseGetResourceSavingMode";

    edit_ResourceSavingMode->setChecked(value);
}



void org_alljoyn_SmartSpaces_Operation_ResourceSaving::slotOnResourceSavingModeChanged(const bool value)
{
    qWarning() << "ResourceSaving::slotOnResourceSavingModeChanged";

    edit_ResourceSavingMode->setChecked(value);
}



void org_alljoyn_SmartSpaces_Operation_ResourceSaving::slotOnResponseSetResourceSavingMode(QStatus status)
{
    qWarning() << "ResourceSaving::slotOnResponseSetResourceSavingMode";

    if (status != ER_OK)
    {
        qWarning() << "ResourceSaving::slotOnResponseSetResourceSavingMode Failed to set ResourceSavingMode" << QCC_StatusText(status);
    }
}



void org_alljoyn_SmartSpaces_Operation_ResourceSaving::slotSetResourceSavingMode()
{
    qWarning() << "ResourceSaving::slotSetResourceSavingMode";

    bool ok = false;
    bool value;
    value = edit_ResourceSavingMode->isChecked();
    ok = true;

    if (ok)
    {
        QStatus status = controller->SetResourceSavingMode(value);

        if (status != ER_OK)
        {
            qWarning() << "ResourceSaving::slotSetResourceSavingMode Failed to get ResourceSavingMode" << QCC_StatusText(status);
        }
    }
}
