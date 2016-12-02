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

#include "org_alljoyn_SmartSpaces_Environment_WindDirection.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <sstream>




using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Environment_WindDirection*>();


org_alljoyn_SmartSpaces_Environment_WindDirection::org_alljoyn_SmartSpaces_Environment_WindDirection(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("HorizontalDirection"));
    // Create line edit for HorizontalDirection
    edit_HorizontalDirection = new QLineEdit();
    edit_HorizontalDirection->setToolTip("Horizontal wind direction of a device.");
    edit_HorizontalDirection->setReadOnly(false);
    QObject::connect(edit_HorizontalDirection, SIGNAL(returnPressed()), this, SLOT(slotSetHorizontalDirection()));
    layout->addWidget(edit_HorizontalDirection);
    layout->addWidget(new QLabel("HorizontalMax"));
    // Create line edit for HorizontalMax
    edit_HorizontalMax = new QLineEdit();
    edit_HorizontalMax->setToolTip("Maximum value allowed for a target horizontal wind direction.");
    edit_HorizontalMax->setReadOnly(true);
    layout->addWidget(edit_HorizontalMax);
    layout->addWidget(new QLabel("HorizontalAutoMode"));
    // Create line edit for HorizontalAutoMode
    edit_HorizontalAutoMode = new QLineEdit();
    edit_HorizontalAutoMode->setToolTip("Represent enabled/disabled state of the horizontal auto mode. HorizontalAutoMode is for controlling horizontal wind direction automatically.");
    edit_HorizontalAutoMode->setReadOnly(false);
    QObject::connect(edit_HorizontalAutoMode, SIGNAL(returnPressed()), this, SLOT(slotSetHorizontalAutoMode()));
    layout->addWidget(edit_HorizontalAutoMode);
    layout->addWidget(new QLabel("VerticalDirection"));
    // Create line edit for VerticalDirection
    edit_VerticalDirection = new QLineEdit();
    edit_VerticalDirection->setToolTip("Vertical wind direction of a device.");
    edit_VerticalDirection->setReadOnly(false);
    QObject::connect(edit_VerticalDirection, SIGNAL(returnPressed()), this, SLOT(slotSetVerticalDirection()));
    layout->addWidget(edit_VerticalDirection);
    layout->addWidget(new QLabel("VerticalMax"));
    // Create line edit for VerticalMax
    edit_VerticalMax = new QLineEdit();
    edit_VerticalMax->setToolTip("Maximum value allowed for a target vertical wind direction.");
    edit_VerticalMax->setReadOnly(true);
    layout->addWidget(edit_VerticalMax);
    layout->addWidget(new QLabel("VerticalAutoMode"));
    // Create line edit for VerticalAutoMode
    edit_VerticalAutoMode = new QLineEdit();
    edit_VerticalAutoMode->setToolTip("Represent enabled/disabled state of the vertical auto mode. VerticalAutoMode is for controlling vertical wind direction automatically.");
    edit_VerticalAutoMode->setReadOnly(false);
    QObject::connect(edit_VerticalAutoMode, SIGNAL(returnPressed()), this, SLOT(slotSetVerticalAutoMode()));
    layout->addWidget(edit_VerticalAutoMode);

    if (iface)
    {
        controller = iface->CreateInterface<WindDirectionIntfController>(m_listener);
        if (controller)
        {
            qWarning() << __FUNCTION__ << " Getting properties";

            QStatus status;
            // Get current values
            status = controller->GetHorizontalDirection();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get HorizontalDirection" << QCC_StatusText(status);
            }
            status = controller->GetHorizontalMax();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get HorizontalMax" << QCC_StatusText(status);
            }
            status = controller->GetHorizontalAutoMode();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get HorizontalAutoMode" << QCC_StatusText(status);
            }
            status = controller->GetVerticalDirection();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get VerticalDirection" << QCC_StatusText(status);
            }
            status = controller->GetVerticalMax();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get VerticalMax" << QCC_StatusText(status);
            }
            status = controller->GetVerticalAutoMode();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get VerticalAutoMode" << QCC_StatusText(status);
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

org_alljoyn_SmartSpaces_Environment_WindDirection::~org_alljoyn_SmartSpaces_Environment_WindDirection()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Environment_WindDirection::slotOnResponseGetHorizontalDirection(QStatus status, const uint16_t value)
{
    qWarning() << __FUNCTION__;
    edit_HorizontalDirection->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Environment_WindDirection::slotOnHorizontalDirectionChanged(const uint16_t value)
{
    qWarning() << __FUNCTION__;
    edit_HorizontalDirection->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Environment_WindDirection::slotOnResponseSetHorizontalDirection(QStatus status)
{
    qWarning() << __FUNCTION__;
}

void org_alljoyn_SmartSpaces_Environment_WindDirection::slotSetHorizontalDirection()
{
    qWarning() << __FUNCTION__;

    bool ok = false;
    QString str = edit_HorizontalDirection->text();
    uint16_t value = QStringTo<uint16_t>(str, &ok);
    if (ok)
    {
        QStatus status = controller->SetHorizontalDirection(value);
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get HorizontalDirection" << QCC_StatusText(status);
        }
    }
    else
    {
        qWarning() << __FUNCTION__ << "Failed to convert '" << str << "' to uint16_t";
    }
}




void org_alljoyn_SmartSpaces_Environment_WindDirection::slotOnResponseGetHorizontalMax(QStatus status, const uint16_t value)
{
    qWarning() << __FUNCTION__;
    edit_HorizontalMax->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Environment_WindDirection::slotOnHorizontalMaxChanged(const uint16_t value)
{
    qWarning() << __FUNCTION__;
    edit_HorizontalMax->setText(QStringFrom(value));
}




void org_alljoyn_SmartSpaces_Environment_WindDirection::slotOnResponseGetHorizontalAutoMode(QStatus status, const WindDirectionInterface::AutoMode value)
{
    qWarning() << __FUNCTION__;
    edit_HorizontalAutoMode->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Environment_WindDirection::slotOnHorizontalAutoModeChanged(const WindDirectionInterface::AutoMode value)
{
    qWarning() << __FUNCTION__;
    edit_HorizontalAutoMode->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Environment_WindDirection::slotOnResponseSetHorizontalAutoMode(QStatus status)
{
    qWarning() << __FUNCTION__;
}

void org_alljoyn_SmartSpaces_Environment_WindDirection::slotSetHorizontalAutoMode()
{
    qWarning() << __FUNCTION__;

    bool ok = false;
    QString str = edit_HorizontalAutoMode->text();
    WindDirectionInterface::AutoMode value = QStringTo<WindDirectionInterface::AutoMode>(str, &ok);
    if (ok)
    {
        QStatus status = controller->SetHorizontalAutoMode(value);
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get HorizontalAutoMode" << QCC_StatusText(status);
        }
    }
    else
    {
        qWarning() << __FUNCTION__ << "Failed to convert '" << str << "' to WindDirectionInterface::AutoMode";
    }
}




void org_alljoyn_SmartSpaces_Environment_WindDirection::slotOnResponseGetVerticalDirection(QStatus status, const uint16_t value)
{
    qWarning() << __FUNCTION__;
    edit_VerticalDirection->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Environment_WindDirection::slotOnVerticalDirectionChanged(const uint16_t value)
{
    qWarning() << __FUNCTION__;
    edit_VerticalDirection->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Environment_WindDirection::slotOnResponseSetVerticalDirection(QStatus status)
{
    qWarning() << __FUNCTION__;
}

void org_alljoyn_SmartSpaces_Environment_WindDirection::slotSetVerticalDirection()
{
    qWarning() << __FUNCTION__;

    bool ok = false;
    QString str = edit_VerticalDirection->text();
    uint16_t value = QStringTo<uint16_t>(str, &ok);
    if (ok)
    {
        QStatus status = controller->SetVerticalDirection(value);
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get VerticalDirection" << QCC_StatusText(status);
        }
    }
    else
    {
        qWarning() << __FUNCTION__ << "Failed to convert '" << str << "' to uint16_t";
    }
}




void org_alljoyn_SmartSpaces_Environment_WindDirection::slotOnResponseGetVerticalMax(QStatus status, const uint16_t value)
{
    qWarning() << __FUNCTION__;
    edit_VerticalMax->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Environment_WindDirection::slotOnVerticalMaxChanged(const uint16_t value)
{
    qWarning() << __FUNCTION__;
    edit_VerticalMax->setText(QStringFrom(value));
}




void org_alljoyn_SmartSpaces_Environment_WindDirection::slotOnResponseGetVerticalAutoMode(QStatus status, const WindDirectionInterface::AutoMode value)
{
    qWarning() << __FUNCTION__;
    edit_VerticalAutoMode->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Environment_WindDirection::slotOnVerticalAutoModeChanged(const WindDirectionInterface::AutoMode value)
{
    qWarning() << __FUNCTION__;
    edit_VerticalAutoMode->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Environment_WindDirection::slotOnResponseSetVerticalAutoMode(QStatus status)
{
    qWarning() << __FUNCTION__;
}

void org_alljoyn_SmartSpaces_Environment_WindDirection::slotSetVerticalAutoMode()
{
    qWarning() << __FUNCTION__;

    bool ok = false;
    QString str = edit_VerticalAutoMode->text();
    WindDirectionInterface::AutoMode value = QStringTo<WindDirectionInterface::AutoMode>(str, &ok);
    if (ok)
    {
        QStatus status = controller->SetVerticalAutoMode(value);
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get VerticalAutoMode" << QCC_StatusText(status);
        }
    }
    else
    {
        qWarning() << __FUNCTION__ << "Failed to convert '" << str << "' to WindDirectionInterface::AutoMode";
    }
}

