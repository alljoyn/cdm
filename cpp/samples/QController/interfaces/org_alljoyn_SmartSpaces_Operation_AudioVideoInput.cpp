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
#include "qcUtils.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <sstream>



template<>
QString
QStringFrom<AudioVideoInputInterface::InputSource>(const AudioVideoInputInterface::InputSource& value)
{
    // the QLabel is AutoFmt 
    std::ostringstream strm;

    strm << "<b>id</b>: " << value.id << "\n";
    strm << "<b>sourceType</b>: " << value.sourceType << "\n";
    strm << "<b>signalPresence</b>: " << value.signalPresence << "\n";
    strm << "<b>portNumber</b>: " << value.portNumber << "\n";
    strm << "<b>friendlyName</b>: " << value.friendlyName.c_str() << "\n";

    return QString::fromStdString(strm.str());
}


template<>
QString
QStringFrom<std::vector<AudioVideoInputInterface::InputSource>>(const std::vector<AudioVideoInputInterface::InputSource>& value)
{
    // the QLabel is AutoFmt 
    std::ostringstream strm;

    strm << "<html><body>";
    strm << "<table><thead><tr>";
    strm << "<th bgcolor=\"light blue\">id</th>";
    strm << "<th bgcolor=\"light blue\">sourceType</th>";
    strm << "<th bgcolor=\"light blue\">signalPresence</th>";
    strm << "<th bgcolor=\"light blue\">portNumber</th>";
    strm << "<th bgcolor=\"light blue\">friendlyName</th>";
    strm << "</tr></thead>";

    for (auto& v : value)
    {
        strm << "<tr>";
        strm << "<td>" << v.id << "</td>";
        strm << "<td>" << v.sourceType << "</td>";
        strm << "<td>" << v.signalPresence << "</td>";
        strm << "<td>" << v.portNumber << "</td>";
        strm << "<td>" << v.friendlyName.c_str() << "</td>";
        strm << "</tr>";
    }

    strm << "</table></body></html>";
    return QString::fromStdString(strm.str());
}


template<>
QString
QStringFrom<AudioVideoInputInterface::SourceType>(const AudioVideoInputInterface::SourceType& value)
{
    QString result;

    switch (value)
    {
    case AudioVideoInputInterface::SOURCE_TYPE_UNKNOWN:
        result = "Unknown";
        break;

    case AudioVideoInputInterface::SOURCE_TYPE_TUNER:
        result = "Tuner";
        break;

    case AudioVideoInputInterface::SOURCE_TYPE_COMPONENT:
        result = "Component";
        break;

    case AudioVideoInputInterface::SOURCE_TYPE_COMPOSITE:
        result = "Composite";
        break;

    case AudioVideoInputInterface::SOURCE_TYPE_S_VIDEO:
        result = "S_VIdeo";
        break;

    case AudioVideoInputInterface::SOURCE_TYPE_RGB:
        result = "RGB";
        break;

    case AudioVideoInputInterface::SOURCE_TYPE_SDI:
        result = "SDI";
        break;

    case AudioVideoInputInterface::SOURCE_TYPE_DVI:
        result = "DVI";
        break;

    case AudioVideoInputInterface::SOURCE_TYPE_HDMI:
        result = "HDMI";
        break;

    case AudioVideoInputInterface::SOURCE_TYPE_DISPLAY_PORT:
        result = "DisplayPort";
        break;

    case AudioVideoInputInterface::SOURCE_TYPE_SCART:
        result = "SCART";
        break;

    case AudioVideoInputInterface::SOURCE_TYPE_EXTERNAL_STORAGE:
        result = "ExternalStorage";
        break;

    case AudioVideoInputInterface::SOURCE_TYPE_NETWORK:
        result = "Network";
        break;

    case AudioVideoInputInterface::SOURCE_TYPE_ANALOG:
        result = "Analog";
        break;

    case AudioVideoInputInterface::SOURCE_TYPE_PHONO:
        result = "Phono";
        break;

    case AudioVideoInputInterface::SOURCE_TYPE_SPDIF_COAXIAL:
        result = "SPDIF_Coaxial";
        break;

    case AudioVideoInputInterface::SOURCE_TYPE_SPDIF_OPTICAL:
        result = "SPDIF_Optical";
        break;

    default:
        result = "Unknown";
        break;
    }

    return result;
}



template<>
QString
QStringFrom<std::vector<AudioVideoInputInterface::SourceType>>(const std::vector<AudioVideoInputInterface::SourceType>& value)
{
    // the QLabel is AutoFmt 
    std::ostringstream strm;

    strm << "<html><body>";
    strm << "<table><thead><tr>";
    strm << "<th bgcolor=\"light blue\">SourceType</th>";
    strm << "</tr></thead>";

    for (auto& v : value)
    {
        if (v == AudioVideoInputInterface::SOURCE_TYPE_UNKNOWN)
        {
            strm << "<tr><td>Unknown</td></tr>";
        }
        if (v == AudioVideoInputInterface::SOURCE_TYPE_TUNER)
        {
            strm << "<tr><td>Tuner</td></tr>";
        }
        if (v == AudioVideoInputInterface::SOURCE_TYPE_COMPONENT)
        {
            strm << "<tr><td>Component</td></tr>";
        }
        if (v == AudioVideoInputInterface::SOURCE_TYPE_COMPOSITE)
        {
            strm << "<tr><td>Composite</td></tr>";
        }
        if (v == AudioVideoInputInterface::SOURCE_TYPE_S_VIDEO)
        {
            strm << "<tr><td>S_VIdeo</td></tr>";
        }
        if (v == AudioVideoInputInterface::SOURCE_TYPE_RGB)
        {
            strm << "<tr><td>RGB</td></tr>";
        }
        if (v == AudioVideoInputInterface::SOURCE_TYPE_SDI)
        {
            strm << "<tr><td>SDI</td></tr>";
        }
        if (v == AudioVideoInputInterface::SOURCE_TYPE_DVI)
        {
            strm << "<tr><td>DVI</td></tr>";
        }
        if (v == AudioVideoInputInterface::SOURCE_TYPE_HDMI)
        {
            strm << "<tr><td>HDMI</td></tr>";
        }
        if (v == AudioVideoInputInterface::SOURCE_TYPE_DISPLAY_PORT)
        {
            strm << "<tr><td>DisplayPort</td></tr>";
        }
        if (v == AudioVideoInputInterface::SOURCE_TYPE_SCART)
        {
            strm << "<tr><td>SCART</td></tr>";
        }
        if (v == AudioVideoInputInterface::SOURCE_TYPE_EXTERNAL_STORAGE)
        {
            strm << "<tr><td>ExternalStorage</td></tr>";
        }
        if (v == AudioVideoInputInterface::SOURCE_TYPE_NETWORK)
        {
            strm << "<tr><td>Network</td></tr>";
        }
        if (v == AudioVideoInputInterface::SOURCE_TYPE_ANALOG)
        {
            strm << "<tr><td>Analog</td></tr>";
        }
        if (v == AudioVideoInputInterface::SOURCE_TYPE_PHONO)
        {
            strm << "<tr><td>Phono</td></tr>";
        }
        if (v == AudioVideoInputInterface::SOURCE_TYPE_SPDIF_COAXIAL)
        {
            strm << "<tr><td>SPDIF_Coaxial</td></tr>";
        }
        if (v == AudioVideoInputInterface::SOURCE_TYPE_SPDIF_OPTICAL)
        {
            strm << "<tr><td>SPDIF_Optical</td></tr>";
        }
    }

    strm << "</table></body></html>";
    return QString::fromStdString(strm.str());
}


template<>
QString
QStringFrom<AudioVideoInputInterface::SignalPresence>(const AudioVideoInputInterface::SignalPresence& value)
{
    QString result;

    switch (value)
    {
    case AudioVideoInputInterface::SIGNAL_PRESENCE_UNKNOWN:
        result = "Unknown";
        break;

    case AudioVideoInputInterface::SIGNAL_PRESENCE_SIGNAL_PRESENT:
        result = "SignalPresent";
        break;

    case AudioVideoInputInterface::SIGNAL_PRESENCE_SIGNAL_ABSENT:
        result = "SignalAbsent";
        break;

    default:
        result = "Unknown";
        break;
    }

    return result;
}



template<>
QString
QStringFrom<std::vector<AudioVideoInputInterface::SignalPresence>>(const std::vector<AudioVideoInputInterface::SignalPresence>& value)
{
    // the QLabel is AutoFmt 
    std::ostringstream strm;

    strm << "<html><body>";
    strm << "<table><thead><tr>";
    strm << "<th bgcolor=\"light blue\">SignalPresence</th>";
    strm << "</tr></thead>";

    for (auto& v : value)
    {
        if (v == AudioVideoInputInterface::SIGNAL_PRESENCE_UNKNOWN)
        {
            strm << "<tr><td>Unknown</td></tr>";
        }
        if (v == AudioVideoInputInterface::SIGNAL_PRESENCE_SIGNAL_PRESENT)
        {
            strm << "<tr><td>SignalPresent</td></tr>";
        }
        if (v == AudioVideoInputInterface::SIGNAL_PRESENCE_SIGNAL_ABSENT)
        {
            strm << "<tr><td>SignalAbsent</td></tr>";
        }
    }

    strm << "</table></body></html>";
    return QString::fromStdString(strm.str());
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



    layout->addWidget(new QLabel("<b>InputSourceId</b>"));
    // Create the editing widget for InputSourceId
    edit_InputSourceId = new QLineEdit();
    edit_InputSourceId->setToolTip("Activated input source id.");
    QObject::connect(edit_InputSourceId, SIGNAL(returnPressed()), this, SLOT(slotSetInputSourceId()));

    layout->addWidget(edit_InputSourceId);
    layout->addWidget(new QLabel("<b>SupportedInputSources</b>"));
    // Create the editing widget for SupportedInputSources
    edit_SupportedInputSources = new QLabel();

    layout->addWidget(edit_SupportedInputSources);

    messages_ = new QLabel();
    layout->addWidget(messages_);

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
        qcShowStatus(this, "Failed to set InputSourceId", status);
        qWarning() << "AudioVideoInput::slotOnResponseSetInputSourceId Failed to set InputSourceId" << QCC_StatusText(status);
        fetchProperties();      // restore the display of properties
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



