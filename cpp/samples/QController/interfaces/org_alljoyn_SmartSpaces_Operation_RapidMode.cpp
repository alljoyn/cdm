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

#include "org_alljoyn_SmartSpaces_Operation_RapidMode.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>

using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_RapidMode*>();

org_alljoyn_SmartSpaces_Operation_RapidMode::org_alljoyn_SmartSpaces_Operation_RapidMode(CommonControllerInterface *iface) : controller(NULL)
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("RapidMode"));
    // Create line edit for RapidMode
    edit_RapidMode = new QLineEdit();
    edit_RapidMode->setToolTip("True if the device is currently operating in rapid mode.");
    edit_RapidMode->setReadOnly(false);
    QObject::connect(edit_RapidMode, SIGNAL(returnPressed()), this, SLOT(slotSetRapidMode()));
    layout->addWidget(edit_RapidMode);

    if (iface)
    {
        controller = iface->CreateInterface<RapidModeIntfController>(*this);
        if (controller)
        {
            qWarning() << __FUNCTION__ << " Getting properties";

            QStatus status;
            // Get current values
            status = controller->GetRapidMode();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get RapidMode" << QCC_StatusText(status);
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

org_alljoyn_SmartSpaces_Operation_RapidMode::~org_alljoyn_SmartSpaces_Operation_RapidMode()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_RapidMode::slotOnResponseGetRapidMode(QStatus status, const bool value)
{
    qWarning() << __FUNCTION__;
    edit_RapidMode->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_RapidMode::slotOnRapidModeChanged(const bool value)
{
    qWarning() << __FUNCTION__;
    edit_RapidMode->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_RapidMode::slotOnResponseSetRapidMode(QStatus status)
{
    qWarning() << __FUNCTION__;
}

void org_alljoyn_SmartSpaces_Operation_RapidMode::slotSetRapidMode()
{
    qWarning() << __FUNCTION__;

    bool ok = false;
    QString str = edit_RapidMode->text();
    bool value = QStringTo<bool>(str, &ok);
    if (ok)
    {
        QStatus status = controller->SetRapidMode(value);
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get RapidMode" << QCC_StatusText(status);
        }
    }
    else
    {
        qWarning() << __FUNCTION__ << "Failed to convert '" << str << "' to bool";
    }
}

