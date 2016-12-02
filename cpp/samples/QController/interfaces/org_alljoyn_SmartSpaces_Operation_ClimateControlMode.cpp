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

#include "org_alljoyn_SmartSpaces_Operation_ClimateControlMode.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>

using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_ClimateControlMode*>();

org_alljoyn_SmartSpaces_Operation_ClimateControlMode::org_alljoyn_SmartSpaces_Operation_ClimateControlMode(CommonControllerInterface *iface) : controller(NULL)
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("Mode"));
    // Create line edit for Mode
    edit_Mode = new QLineEdit();
    edit_Mode->setToolTip("Current mode of device.");
    edit_Mode->setReadOnly(false);
    QObject::connect(edit_Mode, SIGNAL(returnPressed()), this, SLOT(slotSetMode()));
    layout->addWidget(edit_Mode);
    layout->addWidget(new QLabel("SupportedModes"));
    // Create line edit for SupportedModes
    edit_SupportedModes = new QLineEdit();
    edit_SupportedModes->setToolTip("Array of supported modes.");
    edit_SupportedModes->setReadOnly(true);
    layout->addWidget(edit_SupportedModes);
    layout->addWidget(new QLabel("OperationalState"));
    // Create line edit for OperationalState
    edit_OperationalState = new QLineEdit();
    edit_OperationalState->setToolTip("Current status of device.");
    edit_OperationalState->setReadOnly(true);
    layout->addWidget(edit_OperationalState);

    if (iface)
    {
        controller = iface->CreateInterface<ClimateControlModeIntfController>(*this);
        if (controller)
        {
            qWarning() << __FUNCTION__ << " Getting properties";

            QStatus status;
            // Get current values
            status = controller->GetMode();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get Mode" << QCC_StatusText(status);
            }
            status = controller->GetSupportedModes();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get SupportedModes" << QCC_StatusText(status);
            }
            status = controller->GetOperationalState();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get OperationalState" << QCC_StatusText(status);
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

org_alljoyn_SmartSpaces_Operation_ClimateControlMode::~org_alljoyn_SmartSpaces_Operation_ClimateControlMode()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_ClimateControlMode::slotOnResponseGetMode(QStatus status, const Mode value)
{
    qWarning() << __FUNCTION__;
    edit_Mode->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_ClimateControlMode::slotOnModeChanged(const Mode value)
{
    qWarning() << __FUNCTION__;
    edit_Mode->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_ClimateControlMode::slotOnResponseSetMode(QStatus status)
{
    qWarning() << __FUNCTION__;
}

void org_alljoyn_SmartSpaces_Operation_ClimateControlMode::slotSetMode()
{
    qWarning() << __FUNCTION__;

    bool ok = false;
    QString str = edit_Mode->text();
    Mode value = QStringTo<Mode>(str, &ok);
    if (ok)
    {
        QStatus status = controller->SetMode(value);
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get Mode" << QCC_StatusText(status);
        }
    }
    else
    {
        qWarning() << __FUNCTION__ << "Failed to convert '" << str << "' to Mode";
    }
}

void org_alljoyn_SmartSpaces_Operation_ClimateControlMode::slotOnResponseGetSupportedModes(QStatus status, const std::vector<Mode>& value)
{
    qWarning() << __FUNCTION__;
    edit_SupportedModes->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_ClimateControlMode::slotOnSupportedModesChanged(const std::vector<Mode>& value)
{
    qWarning() << __FUNCTION__;
    edit_SupportedModes->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_ClimateControlMode::slotOnResponseGetOperationalState(QStatus status, const OperationalState value)
{
    qWarning() << __FUNCTION__;
    edit_OperationalState->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_ClimateControlMode::slotOnOperationalStateChanged(const OperationalState value)
{
    qWarning() << __FUNCTION__;
    edit_OperationalState->setText(QStringFrom(value));
}
