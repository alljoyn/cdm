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

#include "org_alljoyn_SmartSpaces_Operation_ColorTemperature.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <sstream>




using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_ColorTemperature*>();


org_alljoyn_SmartSpaces_Operation_ColorTemperature::org_alljoyn_SmartSpaces_Operation_ColorTemperature(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("Temperature"));
    // Create line edit for Temperature
    edit_Temperature = new QLineEdit();
    edit_Temperature->setToolTip("Color temperature of the device.");
    edit_Temperature->setReadOnly(false);
    QObject::connect(edit_Temperature, SIGNAL(returnPressed()), this, SLOT(slotSetTemperature()));
    layout->addWidget(edit_Temperature);
    layout->addWidget(new QLabel("MinTemperature"));
    // Create line edit for MinTemperature
    edit_MinTemperature = new QLineEdit();
    edit_MinTemperature->setToolTip("The minimum color temperature supported by the device.");
    edit_MinTemperature->setReadOnly(true);
    layout->addWidget(edit_MinTemperature);
    layout->addWidget(new QLabel("MaxTemperature"));
    // Create line edit for MaxTemperature
    edit_MaxTemperature = new QLineEdit();
    edit_MaxTemperature->setToolTip("The maximum color temperature supported by the device.");
    edit_MaxTemperature->setReadOnly(true);
    layout->addWidget(edit_MaxTemperature);

    if (iface)
    {
        controller = iface->CreateInterface<ColorTemperatureIntfController>(m_listener);
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

org_alljoyn_SmartSpaces_Operation_ColorTemperature::~org_alljoyn_SmartSpaces_Operation_ColorTemperature()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_ColorTemperature::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "org_alljoyn_SmartSpaces_Operation_ColorTemperature getting properties";

        status = controller->GetTemperature();
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get Temperature" << QCC_StatusText(status);
        }

        status = controller->GetMinTemperature();
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get MinTemperature" << QCC_StatusText(status);
        }

        status = controller->GetMaxTemperature();
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get MaxTemperature" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_ColorTemperature::slotOnResponseGetTemperature(QStatus status, const double value)
{
    qWarning() << __FUNCTION__;
    edit_Temperature->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_ColorTemperature::slotOnTemperatureChanged(const double value)
{
    qWarning() << __FUNCTION__;
    edit_Temperature->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_ColorTemperature::slotOnResponseSetTemperature(QStatus status)
{
    qWarning() << __FUNCTION__;
}

void org_alljoyn_SmartSpaces_Operation_ColorTemperature::slotSetTemperature()
{
    qWarning() << __FUNCTION__;

    bool ok = false;
    QString str = edit_Temperature->text();
    double value = QStringTo<double>(str, &ok);
    if (ok)
    {
        QStatus status = controller->SetTemperature(value);
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get Temperature" << QCC_StatusText(status);
        }
    }
    else
    {
        qWarning() << __FUNCTION__ << "Failed to convert '" << str << "' to double";
    }
}




void org_alljoyn_SmartSpaces_Operation_ColorTemperature::slotOnResponseGetMinTemperature(QStatus status, const double value)
{
    qWarning() << __FUNCTION__;
    edit_MinTemperature->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_ColorTemperature::slotOnMinTemperatureChanged(const double value)
{
    qWarning() << __FUNCTION__;
    edit_MinTemperature->setText(QStringFrom(value));
}




void org_alljoyn_SmartSpaces_Operation_ColorTemperature::slotOnResponseGetMaxTemperature(QStatus status, const double value)
{
    qWarning() << __FUNCTION__;
    edit_MaxTemperature->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_ColorTemperature::slotOnMaxTemperatureChanged(const double value)
{
    qWarning() << __FUNCTION__;
    edit_MaxTemperature->setText(QStringFrom(value));
}

