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

#ifndef org_alljoyn_SmartSpaces_Operation_Color_H_
#define org_alljoyn_SmartSpaces_Operation_Color_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <alljoyn/cdm/interfaces/operation/ColorInterface.h>
#include <alljoyn/cdm/interfaces/operation/ColorIntfController.h>
#include <alljoyn/cdm/interfaces/operation/ColorIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_Color : public QWidget, public ajn::services::ColorIntfControllerListener
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Operation_Color(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Operation_Color();

    // Slots mirror the callbacks to avoid threading issues
private slots:

    void slotOnResponseGetHue(QStatus status, const double value);
    void slotOnHueChanged(const double value);
    void slotOnResponseSetHue(QStatus status);
    void slotSetHue();
    void slotOnResponseGetSaturation(QStatus status, const double value);
    void slotOnSaturationChanged(const double value);
    void slotOnResponseSetSaturation(QStatus status);
    void slotSetSaturation();

public:
    // ajn::services::ColorIntfControllerListener
    void OnResponseGetHue(QStatus status, const qcc::String& objectPath, const double value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetHue", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(double, value)
                          );
    }
    void OnHueChanged(const qcc::String& objectPath, const double value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnHueChanged", Qt::QueuedConnection,
                          Q_ARG(double, value)
                          );
    }
    void OnResponseSetHue(QStatus status, const qcc::String& objectPath, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseSetHue", Qt::QueuedConnection,
                          Q_ARG(QStatus, status)
                          );
    }
    void OnResponseGetSaturation(QStatus status, const qcc::String& objectPath, const double value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetSaturation", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(double, value)
                          );
    }
    void OnSaturationChanged(const qcc::String& objectPath, const double value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnSaturationChanged", Qt::QueuedConnection,
                          Q_ARG(double, value)
                          );
    }
    void OnResponseSetSaturation(QStatus status, const qcc::String& objectPath, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseSetSaturation", Qt::QueuedConnection,
                          Q_ARG(QStatus, status)
                          );
    }

private:
    ajn::services::ColorIntfControllerPtr controller;


    QLineEdit* edit_Hue;
    QLineEdit* edit_Saturation;
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_Color_H_ */
