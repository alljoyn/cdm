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

#ifndef org_alljoyn_SmartSpaces_Operation_AirRecirculationMode_H_
#define org_alljoyn_SmartSpaces_Operation_AirRecirculationMode_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <alljoyn/cdm/interfaces/operation/AirRecirculationModeInterface.h>
#include <alljoyn/cdm/interfaces/operation/AirRecirculationModeIntfController.h>
#include <alljoyn/cdm/interfaces/operation/AirRecirculationModeIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_AirRecirculationMode : public QWidget, public ajn::services::AirRecirculationModeIntfControllerListener
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Operation_AirRecirculationMode(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Operation_AirRecirculationMode();

    // Slots mirror the callbacks to avoid threading issues
private slots:

    void slotOnResponseGetIsRecirculating(QStatus status, const bool value);
    void slotOnIsRecirculatingChanged(const bool value);
    void slotOnResponseSetIsRecirculating(QStatus status);
    void slotSetIsRecirculating();

public:
    // ajn::services::AirRecirculationModeIntfControllerListener
    void OnResponseGetIsRecirculating(QStatus status, const qcc::String& objectPath, const bool value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetIsRecirculating", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(bool, value)
                          );
    }
    void OnIsRecirculatingChanged(const qcc::String& objectPath, const bool value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnIsRecirculatingChanged", Qt::QueuedConnection,
                          Q_ARG(bool, value)
                          );
    }
    void OnResponseSetIsRecirculating(QStatus status, const qcc::String& objectPath, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseSetIsRecirculating", Qt::QueuedConnection,
                          Q_ARG(QStatus, status)
                          );
    }

private:
    ajn::services::AirRecirculationModeIntfControllerPtr controller;


    QLineEdit* edit_IsRecirculating;
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_AirRecirculationMode_H_ */
