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

#include "org_alljoyn_SmartSpaces_Operation_Channel.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <sstream>


template<>
QString
QStringFrom<ChannelInterface::ChannelInfoRecord>(const ChannelInterface::ChannelInfoRecord& value)
{
    std::ostringstream strm;
    strm << "{";
    strm << "channelID=" << value.channelID.c_str();
    strm << " ";
    strm << "channelNumber=" << value.channelNumber.c_str();
    strm << " ";
    strm << "channelName=" << value.channelName.c_str();
    strm << "}";

    return QString::fromStdString(strm.str());
}


template<>
QString
QStringFrom<std::vector<ChannelInterface::ChannelInfoRecord>>(const std::vector<ChannelInterface::ChannelInfoRecord>& value)
{
    std::string result;

    for (auto& v : value)
    {
        auto qs = QStringFrom<ChannelInterface::ChannelInfoRecord>(v);
        result += qs.toStdString();
    }
    return QString::fromStdString(result);
}





using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_Channel*>();


org_alljoyn_SmartSpaces_Operation_Channel::org_alljoyn_SmartSpaces_Operation_Channel(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);


    // Create button for GetChannelList
    button_GetChannelList = new QPushButton("GetChannelList");
    button_GetChannelList->setToolTip("Retrieve the list of channels.");
    QObject::connect(button_GetChannelList, SIGNAL(clicked()), this, SLOT(slotClickGetChannelList()));
    layout->addWidget(button_GetChannelList);

    layout->addWidget(new QLabel("ChannelId"));
    // Create line edit for ChannelId
    edit_ChannelId = new QLineEdit();
    edit_ChannelId->setToolTip("Current channel id.");
    edit_ChannelId->setReadOnly(false);
    QObject::connect(edit_ChannelId, SIGNAL(returnPressed()), this, SLOT(slotSetChannelId()));
    layout->addWidget(edit_ChannelId);
    layout->addWidget(new QLabel("TotalNumberOfChannels"));
    // Create line edit for TotalNumberOfChannels
    edit_TotalNumberOfChannels = new QLineEdit();
    edit_TotalNumberOfChannels->setToolTip("Total number of scanned channels.");
    edit_TotalNumberOfChannels->setReadOnly(true);
    layout->addWidget(edit_TotalNumberOfChannels);

    if (iface)
    {
        controller = iface->CreateInterface<ChannelIntfController>(m_listener);
        if (controller)
        {
            qWarning() << __FUNCTION__ << " Getting properties";

            QStatus status;
            // Get current values
            status = controller->GetChannelId();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get ChannelId" << QCC_StatusText(status);
            }
            status = controller->GetTotalNumberOfChannels();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get TotalNumberOfChannels" << QCC_StatusText(status);
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

org_alljoyn_SmartSpaces_Operation_Channel::~org_alljoyn_SmartSpaces_Operation_Channel()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_Channel::slotClickGetChannelList()
{
    qWarning() << __FUNCTION__;

    uint16_t startingRecord {};
    uint16_t numRecords {};

    startingRecord = 0;
    numRecords = 100;

    QStatus status = controller->GetChannelList(startingRecord, numRecords, NULL);
    if (status != ER_OK)
    {
        qWarning() << __FUNCTION__ << " Failed to call GetChannelList" << QCC_StatusText(status);
    }
}



void org_alljoyn_SmartSpaces_Operation_Channel::slotOnResponseGetChannelId(QStatus status, const qcc::String& value)
{
    qWarning() << __FUNCTION__;
    edit_ChannelId->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_Channel::slotOnChannelIdChanged(const qcc::String& value)
{
    qWarning() << __FUNCTION__;
    edit_ChannelId->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_Channel::slotOnResponseSetChannelId(QStatus status)
{
    qWarning() << __FUNCTION__;
}

void org_alljoyn_SmartSpaces_Operation_Channel::slotSetChannelId()
{
    qWarning() << __FUNCTION__;

    bool ok = false;
    QString str = edit_ChannelId->text();
    qcc::String value = QStringTo<qcc::String>(str, &ok);
    if (ok)
    {
        QStatus status = controller->SetChannelId(value);
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get ChannelId" << QCC_StatusText(status);
        }
    }
    else
    {
        qWarning() << __FUNCTION__ << "Failed to convert '" << str << "' to qcc::String";
    }
}




void org_alljoyn_SmartSpaces_Operation_Channel::slotOnResponseGetTotalNumberOfChannels(QStatus status, const uint16_t value)
{
    qWarning() << __FUNCTION__;
    edit_TotalNumberOfChannels->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_Channel::slotOnTotalNumberOfChannelsChanged(const uint16_t value)
{
    qWarning() << __FUNCTION__;
    edit_TotalNumberOfChannels->setText(QStringFrom(value));
}




void org_alljoyn_SmartSpaces_Operation_Channel::slotOnResponseMethodGetChannelList(QStatus status, const QString& errorName)
{
    if (status == ER_OK)
    {
        qInfo() << "Received response to method GetChannelList";
    }
    else
    {
        qWarning() << "Received an error from method GetChannelList, error = " << errorName;
    }
}



void org_alljoyn_SmartSpaces_Operation_Channel::slotOnSignalChannelListChanged()
{
        qInfo() << "Received signal ChannelListChanged";
}