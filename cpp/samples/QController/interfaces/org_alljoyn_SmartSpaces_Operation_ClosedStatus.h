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

#ifndef org_alljoyn_SmartSpaces_Operation_ClosedStatus_H_
#define org_alljoyn_SmartSpaces_Operation_ClosedStatus_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <alljoyn/cdm/interfaces/operation/ClosedStatusInterface.h>
#include <alljoyn/cdm/interfaces/operation/ClosedStatusIntfController.h>
#include <alljoyn/cdm/interfaces/operation/ClosedStatusIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_ClosedStatus : public QWidget, public ajn::services::ClosedStatusIntfControllerListener
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Operation_ClosedStatus(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Operation_ClosedStatus();

    // Slots mirror the callbacks to avoid threading issues
private slots:

    void slotOnResponseGetIsClosed(QStatus status, const bool value);
    void slotOnIsClosedChanged(const bool value);

public:
    // ajn::services::ClosedStatusIntfControllerListener
    void OnResponseGetIsClosed(QStatus status, const qcc::String& objectPath, const bool value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetIsClosed", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(bool, value)
                          );
    }
    void OnIsClosedChanged(const qcc::String& objectPath, const bool value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnIsClosedChanged", Qt::QueuedConnection,
                          Q_ARG(bool, value)
                          );
    }

private:
    ajn::services::ClosedStatusIntfControllerPtr controller;


    QLineEdit* edit_IsClosed;
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_ClosedStatus_H_ */
