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

#include <interfaces/common/operation/AudioVideoInputInterface.h>
#include <interfaces/controller/operation/AudioVideoInputIntfController.h>
#include <interfaces/controller/operation/AudioVideoInputIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_AudioVideoInput : public QWidget
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Operation_AudioVideoInput(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Operation_AudioVideoInput();

    // Slots mirror the callbacks to avoid threading issues
private slots:

    void slotOnResponseGetInputSourceId(QStatus status, const AudioVideoInputInterface::SourceType value);
    void slotOnInputSourceIdChanged(const AudioVideoInputInterface::SourceType value);
    void slotOnResponseSetInputSourceId(QStatus status);
    void slotSetInputSourceId();
    void slotOnResponseGetSupportedInputSources(QStatus status, const std::vector<AudioVideoInputInterface::InputSource>& value);
    void slotOnSupportedInputSourcesChanged(const std::vector<AudioVideoInputInterface::InputSource>& value);

public:
    // ajn::services::AudioVideoInputIntfControllerListener
    class Listener: public ajn::services::AudioVideoInputIntfControllerListener
    {
    public:
        QWidget* m_widget;

        Listener(QWidget* widget)
          : m_widget(widget)
        {
        }

        virtual void OnResponseGetInputSourceId(QStatus status, const qcc::String& objectPath, const AudioVideoInputInterface::SourceType value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetInputSourceId", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(AudioVideoInputInterface::SourceType, value)
                              );
        }
        virtual void OnInputSourceIdChanged(const qcc::String& objectPath, const AudioVideoInputInterface::SourceType value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnInputSourceIdChanged", Qt::QueuedConnection,
                              Q_ARG(AudioVideoInputInterface::SourceType, value)
                              );
        }
        virtual void OnResponseSetInputSourceId(QStatus status, const qcc::String& objectPath, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseSetInputSourceId", Qt::QueuedConnection,
                              Q_ARG(QStatus, status)
                              );
        }
        virtual void OnResponseGetSupportedInputSources(QStatus status, const qcc::String& objectPath, const std::vector<AudioVideoInputInterface::InputSource>& value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetSupportedInputSources", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(std::vector<AudioVideoInputInterface::InputSource>, value)
                              );
        }
        virtual void OnSupportedInputSourcesChanged(const qcc::String& objectPath, const std::vector<AudioVideoInputInterface::InputSource>& value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnSupportedInputSourcesChanged", Qt::QueuedConnection,
                              Q_ARG(std::vector<AudioVideoInputInterface::InputSource>, value)
                              );
        }
    };

private:
    Ref<ajn::services::AudioVideoInputIntfController> controller;
    Ref<Listener> m_listener;


    QLineEdit* edit_InputSourceId;
    QLineEdit* edit_SupportedInputSources;

    void    fetchProperties();

protected:
    virtual void showEvent(QShowEvent *event) override
    {
        fetchProperties();
    }
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_AudioVideoInput_H_ */
