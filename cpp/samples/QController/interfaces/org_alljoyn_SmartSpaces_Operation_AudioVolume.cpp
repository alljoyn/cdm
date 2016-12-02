/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include "org_alljoyn_SmartSpaces_Operation_AudioVolume.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>

using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_AudioVolume*>();

org_alljoyn_SmartSpaces_Operation_AudioVolume::org_alljoyn_SmartSpaces_Operation_AudioVolume(CommonControllerInterface *iface) : controller(NULL)
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("Volume"));
    // Create line edit for Volume
    edit_Volume = new QLineEdit();
    edit_Volume->setToolTip("Speaker volume index of the device.");
    edit_Volume->setReadOnly(false);
    QObject::connect(edit_Volume, SIGNAL(returnPressed()), this, SLOT(slotSetVolume()));
    layout->addWidget(edit_Volume);
    layout->addWidget(new QLabel("MaxVolume"));
    // Create line edit for MaxVolume
    edit_MaxVolume = new QLineEdit();
    edit_MaxVolume->setToolTip("Maximum value allowed for Volume.");
    edit_MaxVolume->setReadOnly(true);
    layout->addWidget(edit_MaxVolume);
    layout->addWidget(new QLabel("Mute"));
    // Create line edit for Mute
    edit_Mute = new QLineEdit();
    edit_Mute->setToolTip("If true, state of volume is muted.");
    edit_Mute->setReadOnly(false);
    QObject::connect(edit_Mute, SIGNAL(returnPressed()), this, SLOT(slotSetMute()));
    layout->addWidget(edit_Mute);

    if (iface)
    {
        controller = iface->CreateInterface<AudioVolumeIntfController>(*this);
        if (controller)
        {
            qWarning() << __FUNCTION__ << " Getting properties";

            QStatus status;
            // Get current values
            status = controller->GetVolume();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get Volume" << QCC_StatusText(status);
            }
            status = controller->GetMaxVolume();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get MaxVolume" << QCC_StatusText(status);
            }
            status = controller->GetMute();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get Mute" << QCC_StatusText(status);
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

org_alljoyn_SmartSpaces_Operation_AudioVolume::~org_alljoyn_SmartSpaces_Operation_AudioVolume()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_AudioVolume::slotOnResponseGetVolume(QStatus status, const uint8_t value)
{
    qWarning() << __FUNCTION__;
    edit_Volume->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_AudioVolume::slotOnVolumeChanged(const uint8_t value)
{
    qWarning() << __FUNCTION__;
    edit_Volume->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_AudioVolume::slotOnResponseSetVolume(QStatus status)
{
    qWarning() << __FUNCTION__;
}

void org_alljoyn_SmartSpaces_Operation_AudioVolume::slotSetVolume()
{
    qWarning() << __FUNCTION__;

    bool ok = false;
    QString str = edit_Volume->text();
    uint8_t value = QStringTo<uint8_t>(str, &ok);
    if (ok)
    {
        QStatus status = controller->SetVolume(value);
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get Volume" << QCC_StatusText(status);
        }
    }
    else
    {
        qWarning() << __FUNCTION__ << "Failed to convert '" << str << "' to uint8_t";
    }
}

void org_alljoyn_SmartSpaces_Operation_AudioVolume::slotOnResponseGetMaxVolume(QStatus status, const uint8_t value)
{
    qWarning() << __FUNCTION__;
    edit_MaxVolume->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_AudioVolume::slotOnMaxVolumeChanged(const uint8_t value)
{
    qWarning() << __FUNCTION__;
    edit_MaxVolume->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_AudioVolume::slotOnResponseGetMute(QStatus status, const bool value)
{
    qWarning() << __FUNCTION__;
    edit_Mute->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_AudioVolume::slotOnMuteChanged(const bool value)
{
    qWarning() << __FUNCTION__;
    edit_Mute->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_AudioVolume::slotOnResponseSetMute(QStatus status)
{
    qWarning() << __FUNCTION__;
}

void org_alljoyn_SmartSpaces_Operation_AudioVolume::slotSetMute()
{
    qWarning() << __FUNCTION__;

    bool ok = false;
    QString str = edit_Mute->text();
    bool value = QStringTo<bool>(str, &ok);
    if (ok)
    {
        QStatus status = controller->SetMute(value);
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get Mute" << QCC_StatusText(status);
        }
    }
    else
    {
        qWarning() << __FUNCTION__ << "Failed to convert '" << str << "' to bool";
    }
}

