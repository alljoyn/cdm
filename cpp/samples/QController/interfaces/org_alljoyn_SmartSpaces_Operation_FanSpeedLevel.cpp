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

#include "org_alljoyn_SmartSpaces_Operation_FanSpeedLevel.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <sstream>




using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_FanSpeedLevel*>();


org_alljoyn_SmartSpaces_Operation_FanSpeedLevel::org_alljoyn_SmartSpaces_Operation_FanSpeedLevel(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("FanSpeedLevel"));
    // Create line edit for FanSpeedLevel
    edit_FanSpeedLevel = new QLineEdit();
    edit_FanSpeedLevel->setToolTip("Fan speed level of a device. Special value: 0x00 - Fan operation is turned off and controller shall not set 0x00. Turning on/off shall be operated by a different interface (OnOff).");
    edit_FanSpeedLevel->setReadOnly(false);
    QObject::connect(edit_FanSpeedLevel, SIGNAL(returnPressed()), this, SLOT(slotSetFanSpeedLevel()));
    layout->addWidget(edit_FanSpeedLevel);
    layout->addWidget(new QLabel("MaxFanSpeedLevel"));
    // Create line edit for MaxFanSpeedLevel
    edit_MaxFanSpeedLevel = new QLineEdit();
    edit_MaxFanSpeedLevel->setToolTip("Maximum level allowed for target fan speed level.");
    edit_MaxFanSpeedLevel->setReadOnly(true);
    layout->addWidget(edit_MaxFanSpeedLevel);
    layout->addWidget(new QLabel("AutoMode"));
    // Create line edit for AutoMode
    edit_AutoMode = new QLineEdit();
    edit_AutoMode->setToolTip("Enabled/disabled state of the auto mode.");
    edit_AutoMode->setReadOnly(false);
    QObject::connect(edit_AutoMode, SIGNAL(returnPressed()), this, SLOT(slotSetAutoMode()));
    layout->addWidget(edit_AutoMode);

    if (iface)
    {
        controller = iface->CreateInterface<FanSpeedLevelIntfController>(m_listener);
        if (controller)
        {
            qWarning() << __FUNCTION__ << " Getting properties";

            QStatus status;
            // Get current values
            status = controller->GetFanSpeedLevel();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get FanSpeedLevel" << QCC_StatusText(status);
            }
            status = controller->GetMaxFanSpeedLevel();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get MaxFanSpeedLevel" << QCC_StatusText(status);
            }
            status = controller->GetAutoMode();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get AutoMode" << QCC_StatusText(status);
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

org_alljoyn_SmartSpaces_Operation_FanSpeedLevel::~org_alljoyn_SmartSpaces_Operation_FanSpeedLevel()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_FanSpeedLevel::slotOnResponseGetFanSpeedLevel(QStatus status, const uint8_t value)
{
    qWarning() << __FUNCTION__;
    edit_FanSpeedLevel->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_FanSpeedLevel::slotOnFanSpeedLevelChanged(const uint8_t value)
{
    qWarning() << __FUNCTION__;
    edit_FanSpeedLevel->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_FanSpeedLevel::slotOnResponseSetFanSpeedLevel(QStatus status)
{
    qWarning() << __FUNCTION__;
}

void org_alljoyn_SmartSpaces_Operation_FanSpeedLevel::slotSetFanSpeedLevel()
{
    qWarning() << __FUNCTION__;

    bool ok = false;
    QString str = edit_FanSpeedLevel->text();
    uint8_t value = QStringTo<uint8_t>(str, &ok);
    if (ok)
    {
        QStatus status = controller->SetFanSpeedLevel(value);
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get FanSpeedLevel" << QCC_StatusText(status);
        }
    }
    else
    {
        qWarning() << __FUNCTION__ << "Failed to convert '" << str << "' to uint8_t";
    }
}




void org_alljoyn_SmartSpaces_Operation_FanSpeedLevel::slotOnResponseGetMaxFanSpeedLevel(QStatus status, const uint8_t value)
{
    qWarning() << __FUNCTION__;
    edit_MaxFanSpeedLevel->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_FanSpeedLevel::slotOnMaxFanSpeedLevelChanged(const uint8_t value)
{
    qWarning() << __FUNCTION__;
    edit_MaxFanSpeedLevel->setText(QStringFrom(value));
}




void org_alljoyn_SmartSpaces_Operation_FanSpeedLevel::slotOnResponseGetAutoMode(QStatus status, const FanSpeedLevelInterface::AutoMode value)
{
    qWarning() << __FUNCTION__;
    edit_AutoMode->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_FanSpeedLevel::slotOnAutoModeChanged(const FanSpeedLevelInterface::AutoMode value)
{
    qWarning() << __FUNCTION__;
    edit_AutoMode->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_FanSpeedLevel::slotOnResponseSetAutoMode(QStatus status)
{
    qWarning() << __FUNCTION__;
}

void org_alljoyn_SmartSpaces_Operation_FanSpeedLevel::slotSetAutoMode()
{
    qWarning() << __FUNCTION__;

    bool ok = false;
    QString str = edit_AutoMode->text();
    FanSpeedLevelInterface::AutoMode value = QStringTo<FanSpeedLevelInterface::AutoMode>(str, &ok);
    if (ok)
    {
        QStatus status = controller->SetAutoMode(value);
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get AutoMode" << QCC_StatusText(status);
        }
    }
    else
    {
        qWarning() << __FUNCTION__ << "Failed to convert '" << str << "' to FanSpeedLevelInterface::AutoMode";
    }
}

