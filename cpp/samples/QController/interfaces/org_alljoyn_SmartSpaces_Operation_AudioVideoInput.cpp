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

#include "org_alljoyn_SmartSpaces_Operation_AudioVideoInput.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <sstream>


template<>
QString
QStringFrom<AudioVideoInputInterface::InputSource>(const AudioVideoInputInterface::InputSource& value)
{
    std::ostringstream strm;
    strm << "{";
    strm << "id=" << value.id;
    strm << " ";
    strm << "sourceType=" << value.sourceType;
    strm << " ";
    strm << "signalPresence=" << value.signalPresence;
    strm << " ";
    strm << "portNumber=" << value.portNumber;
    strm << " ";
    strm << "friendlyName=" << value.friendlyName.c_str();
    strm << "}";

    return QString::fromStdString(strm.str());
}


template<>
QString
QStringFrom<std::vector<AudioVideoInputInterface::InputSource>>(const std::vector<AudioVideoInputInterface::InputSource>& value)
{
    std::string result;

    for (auto& v : value)
    {
        auto qs = QStringFrom<AudioVideoInputInterface::InputSource>(v);
        result += qs.toStdString();
    }
    return QString::fromStdString(result);
}





using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_AudioVideoInput*>();


org_alljoyn_SmartSpaces_Operation_AudioVideoInput::org_alljoyn_SmartSpaces_Operation_AudioVideoInput(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("InputSourceId"));
    // Create line edit for InputSourceId
    edit_InputSourceId = new QLineEdit();
    edit_InputSourceId->setToolTip("Activated input source id.");
    edit_InputSourceId->setReadOnly(false);
    QObject::connect(edit_InputSourceId, SIGNAL(returnPressed()), this, SLOT(slotSetInputSourceId()));
    layout->addWidget(edit_InputSourceId);
    layout->addWidget(new QLabel("SupportedInputSources"));
    // Create line edit for SupportedInputSources
    edit_SupportedInputSources = new QLineEdit();
    edit_SupportedInputSources->setToolTip("Array of supported input sources.");
    edit_SupportedInputSources->setReadOnly(true);
    layout->addWidget(edit_SupportedInputSources);

    if (iface)
    {
        controller = iface->CreateInterface<AudioVideoInputIntfController>(m_listener);
        if (controller)
        {
            qWarning() << __FUNCTION__ << " Getting properties";

            QStatus status;
            // Get current values
            status = controller->GetInputSourceId();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get InputSourceId" << QCC_StatusText(status);
            }
            status = controller->GetSupportedInputSources();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get SupportedInputSources" << QCC_StatusText(status);
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

org_alljoyn_SmartSpaces_Operation_AudioVideoInput::~org_alljoyn_SmartSpaces_Operation_AudioVideoInput()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_AudioVideoInput::slotOnResponseGetInputSourceId(QStatus status, const AudioVideoInputInterface::SourceType value)
{
    qWarning() << __FUNCTION__;
    edit_InputSourceId->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_AudioVideoInput::slotOnInputSourceIdChanged(const AudioVideoInputInterface::SourceType value)
{
    qWarning() << __FUNCTION__;
    edit_InputSourceId->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_AudioVideoInput::slotOnResponseSetInputSourceId(QStatus status)
{
    qWarning() << __FUNCTION__;
}

void org_alljoyn_SmartSpaces_Operation_AudioVideoInput::slotSetInputSourceId()
{
    qWarning() << __FUNCTION__;

    bool ok = false;
    QString str = edit_InputSourceId->text();
    AudioVideoInputInterface::SourceType value = QStringTo<AudioVideoInputInterface::SourceType>(str, &ok);
    if (ok)
    {
        QStatus status = controller->SetInputSourceId(value);
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get InputSourceId" << QCC_StatusText(status);
        }
    }
    else
    {
        qWarning() << __FUNCTION__ << "Failed to convert '" << str << "' to AudioVideoInputInterface::SourceType";
    }
}




void org_alljoyn_SmartSpaces_Operation_AudioVideoInput::slotOnResponseGetSupportedInputSources(QStatus status, const std::vector<AudioVideoInputInterface::InputSource>& value)
{
    qWarning() << __FUNCTION__;
    edit_SupportedInputSources->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_AudioVideoInput::slotOnSupportedInputSourcesChanged(const std::vector<AudioVideoInputInterface::InputSource>& value)
{
    qWarning() << __FUNCTION__;
    edit_SupportedInputSources->setText(QStringFrom(value));
}

