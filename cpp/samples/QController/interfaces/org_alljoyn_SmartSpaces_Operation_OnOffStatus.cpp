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

#include "org_alljoyn_SmartSpaces_Operation_OnOffStatus.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>

using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_OnOffStatus*>();

org_alljoyn_SmartSpaces_Operation_OnOffStatus::org_alljoyn_SmartSpaces_Operation_OnOffStatus(CommonControllerInterface *iface) : controller(NULL)
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("IsOn"));
    // Create line edit for IsOn
    edit_IsOn = new QLineEdit();
    edit_IsOn->setToolTip("Current on/off state of the appliance. If true, the device is on state.");
    edit_IsOn->setReadOnly(true);
    layout->addWidget(edit_IsOn);

    if (iface)
    {
        controller = iface->CreateInterface<OnOffStatusIntfController>(*this);
        if (controller)
        {
            qWarning() << __FUNCTION__ << " Getting properties";

            QStatus status;
            // Get current values
            status = controller->GetIsOn();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get IsOn" << QCC_StatusText(status);
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

org_alljoyn_SmartSpaces_Operation_OnOffStatus::~org_alljoyn_SmartSpaces_Operation_OnOffStatus()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_OnOffStatus::slotOnResponseGetIsOn(QStatus status, const bool value)
{
    qWarning() << __FUNCTION__;
    edit_IsOn->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_OnOffStatus::slotOnIsOnChanged(const bool value)
{
    qWarning() << __FUNCTION__;
    edit_IsOn->setText(QStringFrom(value));
}

