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

#include "org_alljoyn_SmartSpaces_Operation_ClosedStatus.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <sstream>




using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_ClosedStatus*>();


org_alljoyn_SmartSpaces_Operation_ClosedStatus::org_alljoyn_SmartSpaces_Operation_ClosedStatus(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("IsClosed"));
    // Create line edit for IsClosed
    edit_IsClosed = new QLineEdit();
    edit_IsClosed->setToolTip("If true, object is closed.");
    edit_IsClosed->setReadOnly(true);
    layout->addWidget(edit_IsClosed);

    if (iface)
    {
        controller = iface->CreateInterface<ClosedStatusIntfController>(m_listener);
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

org_alljoyn_SmartSpaces_Operation_ClosedStatus::~org_alljoyn_SmartSpaces_Operation_ClosedStatus()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_ClosedStatus::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "org_alljoyn_SmartSpaces_Operation_ClosedStatus getting properties";

        status = controller->GetIsClosed();
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get IsClosed" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_ClosedStatus::slotOnResponseGetIsClosed(QStatus status, const bool value)
{
    qWarning() << __FUNCTION__;
    edit_IsClosed->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_ClosedStatus::slotOnIsClosedChanged(const bool value)
{
    qWarning() << __FUNCTION__;
    edit_IsClosed->setText(QStringFrom(value));
}

