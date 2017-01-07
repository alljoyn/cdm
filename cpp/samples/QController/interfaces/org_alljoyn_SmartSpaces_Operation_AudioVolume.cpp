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
#include "org_alljoyn_SmartSpaces_Operation_AudioVolume.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <sstream>




using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_AudioVolume*>();



org_alljoyn_SmartSpaces_Operation_AudioVolume::org_alljoyn_SmartSpaces_Operation_AudioVolume(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("Volume"));
    // Create the editing widget for Volume
    edit_Volume = new QLineEdit();
    edit_Volume->setToolTip("Speaker volume index of the device.");
    edit_Volume->setReadOnly(false);
    QObject::connect(edit_Volume, SIGNAL(returnPressed()), this, SLOT(slotSetVolume()));

    layout->addWidget(edit_Volume);
    layout->addWidget(new QLabel("MaxVolume"));
    // Create the editing widget for MaxVolume
    edit_MaxVolume = new QLineEdit();
    edit_MaxVolume->setToolTip("Maximum value allowed for Volume.");
    edit_MaxVolume->setReadOnly(true);

    layout->addWidget(edit_MaxVolume);
    layout->addWidget(new QLabel("Mute"));
    // Create the editing widget for Mute
    edit_Mute = new QCheckBox();
    edit_Mute->setEnabled(true);
    QObject::connect(edit_Mute, SIGNAL(stateChanged(int)), this, SLOT(slotSetMute()));

    layout->addWidget(edit_Mute);

    if (iface)
    {
        controller = iface->CreateInterface<AudioVolumeIntfController>(m_listener);
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

org_alljoyn_SmartSpaces_Operation_AudioVolume::~org_alljoyn_SmartSpaces_Operation_AudioVolume()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_AudioVolume::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "AudioVolume getting properties";

        status = controller->GetVolume();
        if (status != ER_OK)
        {
            qWarning() << "AudioVolume::fetchProperties Failed to get Volume" << QCC_StatusText(status);
        }

        status = controller->GetMaxVolume();
        if (status != ER_OK)
        {
            qWarning() << "AudioVolume::fetchProperties Failed to get MaxVolume" << QCC_StatusText(status);
        }

        status = controller->GetMute();
        if (status != ER_OK)
        {
            qWarning() << "AudioVolume::fetchProperties Failed to get Mute" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_AudioVolume::slotOnResponseGetVolume(QStatus status, const uint8_t value)
{
    qWarning() << "AudioVolume::slotOnResponseGetVolume";

    edit_Volume->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_AudioVolume::slotOnVolumeChanged(const uint8_t value)
{
    qWarning() << "AudioVolume::slotOnVolumeChanged";

    edit_Volume->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_AudioVolume::slotOnResponseSetVolume(QStatus status)
{
    qWarning() << "AudioVolume::slotOnResponseSetVolume";

    if (status != ER_OK)
    {
        qWarning() << "AudioVolume::slotOnResponseSetVolume Failed to set Volume" << QCC_StatusText(status);
    }
}



void org_alljoyn_SmartSpaces_Operation_AudioVolume::slotSetVolume()
{
    qWarning() << "AudioVolume::slotSetVolume";

    bool ok = false;
    uint8_t value;
    QString str = edit_Volume->text();
    value = QStringTo<uint8_t>(str, &ok);
    if (!ok)
    {
        qWarning() << "AudioVolume::slotSetVolume Failed to convert '" << str << "' to uint8_t";
    }

    if (ok)
    {
        QStatus status = controller->SetVolume(value);

        if (status != ER_OK)
        {
            qWarning() << "AudioVolume::slotSetVolume Failed to get Volume" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_AudioVolume::slotOnResponseGetMaxVolume(QStatus status, const uint8_t value)
{
    qWarning() << "AudioVolume::slotOnResponseGetMaxVolume";

    edit_MaxVolume->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_AudioVolume::slotOnMaxVolumeChanged(const uint8_t value)
{
    qWarning() << "AudioVolume::slotOnMaxVolumeChanged";

    edit_MaxVolume->setText(QStringFrom(value));
}






void org_alljoyn_SmartSpaces_Operation_AudioVolume::slotOnResponseGetMute(QStatus status, const bool value)
{
    qWarning() << "AudioVolume::slotOnResponseGetMute";

    edit_Mute->setChecked(value);
}



void org_alljoyn_SmartSpaces_Operation_AudioVolume::slotOnMuteChanged(const bool value)
{
    qWarning() << "AudioVolume::slotOnMuteChanged";

    edit_Mute->setChecked(value);
}



void org_alljoyn_SmartSpaces_Operation_AudioVolume::slotOnResponseSetMute(QStatus status)
{
    qWarning() << "AudioVolume::slotOnResponseSetMute";

    if (status != ER_OK)
    {
        qWarning() << "AudioVolume::slotOnResponseSetMute Failed to set Mute" << QCC_StatusText(status);
    }
}



void org_alljoyn_SmartSpaces_Operation_AudioVolume::slotSetMute()
{
    qWarning() << "AudioVolume::slotSetMute";

    bool ok = false;
    bool value;
    value = edit_Mute->isChecked();
    ok = true;

    if (ok)
    {
        QStatus status = controller->SetMute(value);

        if (status != ER_OK)
        {
            qWarning() << "AudioVolume::slotSetMute Failed to get Mute" << QCC_StatusText(status);
        }
    }
}
