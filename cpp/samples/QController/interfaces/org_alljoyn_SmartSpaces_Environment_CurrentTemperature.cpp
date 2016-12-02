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

#include "org_alljoyn_SmartSpaces_Environment_CurrentTemperature.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <sstream>




using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Environment_CurrentTemperature*>();


org_alljoyn_SmartSpaces_Environment_CurrentTemperature::org_alljoyn_SmartSpaces_Environment_CurrentTemperature(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("CurrentValue"));
    // Create line edit for CurrentValue
    edit_CurrentValue = new QLineEdit();
    edit_CurrentValue->setToolTip("Current temperature expressed in Celsius.");
    edit_CurrentValue->setReadOnly(true);
    layout->addWidget(edit_CurrentValue);
    layout->addWidget(new QLabel("Precision"));
    // Create line edit for Precision
    edit_Precision = new QLineEdit();
    edit_Precision->setToolTip("The precision of the CurrentValue property.");
    edit_Precision->setReadOnly(true);
    layout->addWidget(edit_Precision);
    layout->addWidget(new QLabel("UpdateMinTime"));
    // Create line edit for UpdateMinTime
    edit_UpdateMinTime = new QLineEdit();
    edit_UpdateMinTime->setToolTip("The minimum time between updates of the CurrentValue property in milliseconds.");
    edit_UpdateMinTime->setReadOnly(true);
    layout->addWidget(edit_UpdateMinTime);

    if (iface)
    {
        controller = iface->CreateInterface<CurrentTemperatureIntfController>(m_listener);
        if (controller)
        {
            qWarning() << __FUNCTION__ << " Getting properties";

            QStatus status;
            // Get current values
            status = controller->GetCurrentValue();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get CurrentValue" << QCC_StatusText(status);
            }
            status = controller->GetPrecision();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get Precision" << QCC_StatusText(status);
            }
            status = controller->GetUpdateMinTime();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get UpdateMinTime" << QCC_StatusText(status);
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

org_alljoyn_SmartSpaces_Environment_CurrentTemperature::~org_alljoyn_SmartSpaces_Environment_CurrentTemperature()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Environment_CurrentTemperature::slotOnResponseGetCurrentValue(QStatus status, const double value)
{
    qWarning() << __FUNCTION__;
    edit_CurrentValue->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Environment_CurrentTemperature::slotOnCurrentValueChanged(const double value)
{
    qWarning() << __FUNCTION__;
    edit_CurrentValue->setText(QStringFrom(value));
}




void org_alljoyn_SmartSpaces_Environment_CurrentTemperature::slotOnResponseGetPrecision(QStatus status, const double value)
{
    qWarning() << __FUNCTION__;
    edit_Precision->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Environment_CurrentTemperature::slotOnPrecisionChanged(const double value)
{
    qWarning() << __FUNCTION__;
    edit_Precision->setText(QStringFrom(value));
}




void org_alljoyn_SmartSpaces_Environment_CurrentTemperature::slotOnResponseGetUpdateMinTime(QStatus status, const uint16_t value)
{
    qWarning() << __FUNCTION__;
    edit_UpdateMinTime->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Environment_CurrentTemperature::slotOnUpdateMinTimeChanged(const uint16_t value)
{
    qWarning() << __FUNCTION__;
    edit_UpdateMinTime->setText(QStringFrom(value));
}

