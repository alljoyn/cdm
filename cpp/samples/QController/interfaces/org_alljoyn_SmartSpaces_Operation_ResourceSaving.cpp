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

#include "org_alljoyn_SmartSpaces_Operation_ResourceSaving.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>

using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_ResourceSaving*>();

org_alljoyn_SmartSpaces_Operation_ResourceSaving::org_alljoyn_SmartSpaces_Operation_ResourceSaving(CommonControllerInterface *iface) : controller(NULL)
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("ResourceSavingMode"));
    // Create line edit for ResourceSavingMode
    edit_ResourceSavingMode = new QLineEdit();
    edit_ResourceSavingMode->setToolTip("The current resource saving mode of the device; true if device in saving mode.");
    edit_ResourceSavingMode->setReadOnly(false);
    QObject::connect(edit_ResourceSavingMode, SIGNAL(returnPressed()), this, SLOT(slotSetResourceSavingMode()));
    layout->addWidget(edit_ResourceSavingMode);

    if (iface)
    {
        controller = iface->CreateInterface<ResourceSavingIntfController>(*this);
        if (controller)
        {
            qWarning() << __FUNCTION__ << " Getting properties";

            QStatus status;
            // Get current values
            status = controller->GetResourceSavingMode();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get ResourceSavingMode" << QCC_StatusText(status);
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

org_alljoyn_SmartSpaces_Operation_ResourceSaving::~org_alljoyn_SmartSpaces_Operation_ResourceSaving()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_ResourceSaving::slotOnResponseGetResourceSavingMode(QStatus status, const bool value)
{
    qWarning() << __FUNCTION__;
    edit_ResourceSavingMode->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_ResourceSaving::slotOnResourceSavingModeChanged(const bool value)
{
    qWarning() << __FUNCTION__;
    edit_ResourceSavingMode->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_ResourceSaving::slotOnResponseSetResourceSavingMode(QStatus status)
{
    qWarning() << __FUNCTION__;
}

void org_alljoyn_SmartSpaces_Operation_ResourceSaving::slotSetResourceSavingMode()
{
    qWarning() << __FUNCTION__;

    bool ok = false;
    QString str = edit_ResourceSavingMode->text();
    bool value = QStringTo<bool>(str, &ok);
    if (ok)
    {
        QStatus status = controller->SetResourceSavingMode(value);
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get ResourceSavingMode" << QCC_StatusText(status);
        }
    }
    else
    {
        qWarning() << __FUNCTION__ << "Failed to convert '" << str << "' to bool";
    }
}
