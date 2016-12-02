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

#include "org_alljoyn_SmartSpaces_Environment_CurrentHumidity.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <sstream>




using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Environment_CurrentHumidity*>();


org_alljoyn_SmartSpaces_Environment_CurrentHumidity::org_alljoyn_SmartSpaces_Environment_CurrentHumidity(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("CurrentValue"));
    // Create line edit for CurrentValue
    edit_CurrentValue = new QLineEdit();
    edit_CurrentValue->setToolTip("Current relative humidity value");
    edit_CurrentValue->setReadOnly(true);
    layout->addWidget(edit_CurrentValue);
    layout->addWidget(new QLabel("MaxValue"));
    // Create line edit for MaxValue
    edit_MaxValue = new QLineEdit();
    edit_MaxValue->setToolTip("Maximum value allowed for represented relative humidity");
    edit_MaxValue->setReadOnly(true);
    layout->addWidget(edit_MaxValue);

    if (iface)
    {
        controller = iface->CreateInterface<CurrentHumidityIntfController>(m_listener);
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
            status = controller->GetMaxValue();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get MaxValue" << QCC_StatusText(status);
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

org_alljoyn_SmartSpaces_Environment_CurrentHumidity::~org_alljoyn_SmartSpaces_Environment_CurrentHumidity()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Environment_CurrentHumidity::slotOnResponseGetCurrentValue(QStatus status, const uint8_t value)
{
    qWarning() << __FUNCTION__;
    edit_CurrentValue->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Environment_CurrentHumidity::slotOnCurrentValueChanged(const uint8_t value)
{
    qWarning() << __FUNCTION__;
    edit_CurrentValue->setText(QStringFrom(value));
}




void org_alljoyn_SmartSpaces_Environment_CurrentHumidity::slotOnResponseGetMaxValue(QStatus status, const uint8_t value)
{
    qWarning() << __FUNCTION__;
    edit_MaxValue->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Environment_CurrentHumidity::slotOnMaxValueChanged(const uint8_t value)
{
    qWarning() << __FUNCTION__;
    edit_MaxValue->setText(QStringFrom(value));
}

