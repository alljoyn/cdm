/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
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

Q_DECLARE_METATYPE(ajn::services::AudioVideoInputInterface::InputSource);
Q_DECLARE_METATYPE(std::vector<ajn::services::AudioVideoInputInterface::InputSource>);
static const int auto_register_struct_InputSource = qRegisterMetaType<ajn::services::AudioVideoInputInterface::InputSource>("AudioVideoInputInterface::InputSource");
static const int auto_register_struct_v_InputSource = qRegisterMetaType<std::vector<ajn::services::AudioVideoInputInterface::InputSource>>("std::vector<AudioVideoInputInterface::InputSource>");

Q_DECLARE_METATYPE(ajn::services::AudioVideoInputInterface::SourceType);
Q_DECLARE_METATYPE(std::vector<ajn::services::AudioVideoInputInterface::SourceType>);
static const int auto_register_enum_SourceType = qRegisterMetaType<ajn::services::AudioVideoInputInterface::SourceType>("AudioVideoInputInterface::SourceType");
static const int auto_register_enum_v_SourceType = qRegisterMetaType<std::vector<ajn::services::AudioVideoInputInterface::SourceType>>("std::vector<AudioVideoInputInterface::SourceType>");

Q_DECLARE_METATYPE(ajn::services::AudioVideoInputInterface::SignalPresence);
Q_DECLARE_METATYPE(std::vector<ajn::services::AudioVideoInputInterface::SignalPresence>);
static const int auto_register_enum_SignalPresence = qRegisterMetaType<ajn::services::AudioVideoInputInterface::SignalPresence>("AudioVideoInputInterface::SignalPresence");
static const int auto_register_enum_v_SignalPresence = qRegisterMetaType<std::vector<ajn::services::AudioVideoInputInterface::SignalPresence>>("std::vector<AudioVideoInputInterface::SignalPresence>");



org_alljoyn_SmartSpaces_Operation_AudioVideoInput::org_alljoyn_SmartSpaces_Operation_AudioVideoInput(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("InputSourceId"));
    // Create the editing widget for InputSourceId
    edit_InputSourceId = new QLineEdit();
    edit_InputSourceId->setToolTip("Activated input source id.");
    edit_InputSourceId->setReadOnly(false);
    QObject::connect(edit_InputSourceId, SIGNAL(returnPressed()), this, SLOT(slotSetInputSourceId()));

    layout->addWidget(edit_InputSourceId);
    layout->addWidget(new QLabel("SupportedInputSources"));
    // Create the editing widget for SupportedInputSources
    edit_SupportedInputSources = new QLineEdit();
    edit_SupportedInputSources->setToolTip("Array of supported input sources.");
    edit_SupportedInputSources->setReadOnly(true);

    layout->addWidget(edit_SupportedInputSources);

    if (iface)
    {
        controller = iface->CreateInterface<AudioVideoInputIntfController>(m_listener);
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

org_alljoyn_SmartSpaces_Operation_AudioVideoInput::~org_alljoyn_SmartSpaces_Operation_AudioVideoInput()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_AudioVideoInput::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "AudioVideoInput getting properties";

        status = controller->GetInputSourceId();
        if (status != ER_OK)
        {
            qWarning() << "AudioVideoInput::fetchProperties Failed to get InputSourceId" << QCC_StatusText(status);
        }

        status = controller->GetSupportedInputSources();
        if (status != ER_OK)
        {
            qWarning() << "AudioVideoInput::fetchProperties Failed to get SupportedInputSources" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_AudioVideoInput::slotOnResponseGetInputSourceId(QStatus status, const uint16_t value)
{
    qWarning() << "AudioVideoInput::slotOnResponseGetInputSourceId";

    edit_InputSourceId->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_AudioVideoInput::slotOnInputSourceIdChanged(const uint16_t value)
{
    qWarning() << "AudioVideoInput::slotOnInputSourceIdChanged";

    edit_InputSourceId->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_AudioVideoInput::slotOnResponseSetInputSourceId(QStatus status)
{
    qWarning() << "AudioVideoInput::slotOnResponseSetInputSourceId";

    if (status != ER_OK)
    {
        qWarning() << "AudioVideoInput::slotOnResponseSetInputSourceId Failed to set InputSourceId" << QCC_StatusText(status);
    }
}



void org_alljoyn_SmartSpaces_Operation_AudioVideoInput::slotSetInputSourceId()
{
    qWarning() << "AudioVideoInput::slotSetInputSourceId";

    bool ok = false;
    uint16_t value;
    QString str = edit_InputSourceId->text();
    value = QStringTo<uint16_t>(str, &ok);
    if (!ok)
    {
        qWarning() << "AudioVideoInput::slotSetInputSourceId Failed to convert '" << str << "' to uint16_t";
    }

    if (ok)
    {
        QStatus status = controller->SetInputSourceId(value);

        if (status != ER_OK)
        {
            qWarning() << "AudioVideoInput::slotSetInputSourceId Failed to get InputSourceId" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_AudioVideoInput::slotOnResponseGetSupportedInputSources(QStatus status, const std::vector<AudioVideoInputInterface::InputSource>& value)
{
    qWarning() << "AudioVideoInput::slotOnResponseGetSupportedInputSources";

    edit_SupportedInputSources->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_AudioVideoInput::slotOnSupportedInputSourcesChanged(const std::vector<AudioVideoInputInterface::InputSource>& value)
{
    qWarning() << "AudioVideoInput::slotOnSupportedInputSourcesChanged";

    edit_SupportedInputSources->setText(QStringFrom(value));
}



