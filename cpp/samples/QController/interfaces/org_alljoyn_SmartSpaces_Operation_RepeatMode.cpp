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

#include "org_alljoyn_SmartSpaces_Operation_RepeatMode.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <sstream>




using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_RepeatMode*>();


org_alljoyn_SmartSpaces_Operation_RepeatMode::org_alljoyn_SmartSpaces_Operation_RepeatMode(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("RepeatMode"));
    // Create line edit for RepeatMode
    edit_RepeatMode = new QLineEdit();
    edit_RepeatMode->setToolTip("True if the device works in repeat mode.");
    edit_RepeatMode->setReadOnly(false);
    QObject::connect(edit_RepeatMode, SIGNAL(returnPressed()), this, SLOT(slotSetRepeatMode()));
    layout->addWidget(edit_RepeatMode);

    if (iface)
    {
        controller = iface->CreateInterface<RepeatModeIntfController>(m_listener);
        if (controller)
        {
            qWarning() << __FUNCTION__ << " Getting properties";

            QStatus status;
            // Get current values
            status = controller->GetRepeatMode();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get RepeatMode" << QCC_StatusText(status);
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

org_alljoyn_SmartSpaces_Operation_RepeatMode::~org_alljoyn_SmartSpaces_Operation_RepeatMode()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_RepeatMode::slotOnResponseGetRepeatMode(QStatus status, const bool value)
{
    qWarning() << __FUNCTION__;
    edit_RepeatMode->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_RepeatMode::slotOnRepeatModeChanged(const bool value)
{
    qWarning() << __FUNCTION__;
    edit_RepeatMode->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_RepeatMode::slotOnResponseSetRepeatMode(QStatus status)
{
    qWarning() << __FUNCTION__;
}

void org_alljoyn_SmartSpaces_Operation_RepeatMode::slotSetRepeatMode()
{
    qWarning() << __FUNCTION__;

    bool ok = false;
    QString str = edit_RepeatMode->text();
    bool value = QStringTo<bool>(str, &ok);
    if (ok)
    {
        QStatus status = controller->SetRepeatMode(value);
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get RepeatMode" << QCC_StatusText(status);
        }
    }
    else
    {
        qWarning() << __FUNCTION__ << "Failed to convert '" << str << "' to bool";
    }
}

