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

#ifndef org_alljoyn_SmartSpaces_Operation_AudioVideoInput_H_
#define org_alljoyn_SmartSpaces_Operation_AudioVideoInput_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <alljoyn/cdm/interfaces/operation/AudioVideoInputInterface.h>
#include <alljoyn/cdm/interfaces/operation/AudioVideoInputIntfController.h>
#include <alljoyn/cdm/interfaces/operation/AudioVideoInputIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_AudioVideoInput : public QWidget, public ajn::services::AudioVideoInputIntfControllerListener
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Operation_AudioVideoInput(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Operation_AudioVideoInput();

    // Slots mirror the callbacks to avoid threading issues
private slots:

    void slotOnResponseGetInputSourceId(QStatus status, const SourceType value);
    void slotOnInputSourceIdChanged(const SourceType value);
    void slotOnResponseSetInputSourceId(QStatus status);
    void slotSetInputSourceId();
    void slotOnResponseGetSupportedInputSources(QStatus status, const std::vector<InputSource>& value);
    void slotOnSupportedInputSourcesChanged(const std::vector<InputSource>& value);

public:
    // ajn::services::AudioVideoInputIntfControllerListener
    void OnResponseGetInputSourceId(QStatus status, const qcc::String& objectPath, const SourceType value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetInputSourceId", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(SourceType, value)
                          );
    }
    void OnInputSourceIdChanged(const qcc::String& objectPath, const SourceType value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnInputSourceIdChanged", Qt::QueuedConnection,
                          Q_ARG(SourceType, value)
                          );
    }
    void OnResponseSetInputSourceId(QStatus status, const qcc::String& objectPath, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseSetInputSourceId", Qt::QueuedConnection,
                          Q_ARG(QStatus, status)
                          );
    }
    void OnResponseGetSupportedInputSources(QStatus status, const qcc::String& objectPath, const std::vector<InputSource>& value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetSupportedInputSources", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(std::vector<InputSource>, value)
                          );
    }
    void OnSupportedInputSourcesChanged(const qcc::String& objectPath, const std::vector<InputSource>& value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnSupportedInputSourcesChanged", Qt::QueuedConnection,
                          Q_ARG(std::vector<InputSource>, value)
                          );
    }

private:
    ajn::services::AudioVideoInputIntfControllerPtr controller;


    QLineEdit* edit_InputSourceId;
    QLineEdit* edit_SupportedInputSources;
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_AudioVideoInput_H_ */