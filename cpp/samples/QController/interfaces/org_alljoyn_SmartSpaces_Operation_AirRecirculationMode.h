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

#include <interfaces/common/operation/AirRecirculationModeInterface.h>
#include <interfaces/controller/operation/AirRecirculationModeIntfController.h>
#include <interfaces/controller/operation/AirRecirculationModeIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_AirRecirculationMode : public QWidget
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
    class Listener: public ajn::services::AirRecirculationModeIntfControllerListener
    {
    public:
        QWidget* m_widget;

        Listener(QWidget* widget)
          : m_widget(widget)
        {
        }

        virtual void OnResponseGetIsRecirculating(QStatus status, const qcc::String& objectPath, const bool value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetIsRecirculating", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(bool, value)
                              );
        }
        virtual void OnIsRecirculatingChanged(const qcc::String& objectPath, const bool value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnIsRecirculatingChanged", Qt::QueuedConnection,
                              Q_ARG(bool, value)
                              );
        }
        virtual void OnResponseSetIsRecirculating(QStatus status, const qcc::String& objectPath, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseSetIsRecirculating", Qt::QueuedConnection,
                              Q_ARG(QStatus, status)
                              );
        }
    };

private:
    Ref<ajn::services::AirRecirculationModeIntfController> controller;
    Ref<Listener> m_listener;


    QLineEdit* edit_IsRecirculating;

    void    fetchProperties();

protected:
    virtual void showEvent(QShowEvent *event) override
    {
        fetchProperties();
    }
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_AirRecirculationMode_H_ */
