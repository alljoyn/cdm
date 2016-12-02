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

#include "org_alljoyn_SmartSpaces_Operation_PlugInUnits.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>

using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_PlugInUnits*>();

org_alljoyn_SmartSpaces_Operation_PlugInUnits::org_alljoyn_SmartSpaces_Operation_PlugInUnits(CommonControllerInterface *iface) : controller(NULL)
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("PlugInUnits"));
    // Create line edit for PlugInUnits
    edit_PlugInUnits = new QLineEdit();
    edit_PlugInUnits->setToolTip("The lists of all the possible hot pluggable devices and the associated status.");
    edit_PlugInUnits->setReadOnly(true);
    layout->addWidget(edit_PlugInUnits);

    if (iface)
    {
        controller = iface->CreateInterface<PlugInUnitsIntfController>(*this);
        if (controller)
        {
            qWarning() << __FUNCTION__ << " Getting properties";

            QStatus status;
            // Get current values
            status = controller->GetPlugInUnits();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get PlugInUnits" << QCC_StatusText(status);
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

org_alljoyn_SmartSpaces_Operation_PlugInUnits::~org_alljoyn_SmartSpaces_Operation_PlugInUnits()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_PlugInUnits::slotOnResponseGetPlugInUnits(QStatus status, const std::vector<PlugInInfo>& value)
{
    qWarning() << __FUNCTION__;
    edit_PlugInUnits->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_PlugInUnits::slotOnPlugInUnitsChanged(const std::vector<PlugInInfo>& value)
{
    qWarning() << __FUNCTION__;
    edit_PlugInUnits->setText(QStringFrom(value));
}

