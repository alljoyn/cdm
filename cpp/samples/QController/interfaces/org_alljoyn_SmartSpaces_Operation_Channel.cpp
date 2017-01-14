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
#include "qcUtils.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <sstream>



template<>
QString
QStringFrom<ChannelInterface::ChannelInfoRecord>(const ChannelInterface::ChannelInfoRecord& value)
{
    // the QLabel is AutoFmt 
    std::ostringstream strm;

    strm << "<b>channelID</b>: " << value.channelID.c_str() << "\n";
    strm << "<b>channelNumber</b>: " << value.channelNumber.c_str() << "\n";
    strm << "<b>channelName</b>: " << value.channelName.c_str() << "\n";

    return QString::fromStdString(strm.str());
}


template<>
QString
QStringFrom<std::vector<ChannelInterface::ChannelInfoRecord>>(const std::vector<ChannelInterface::ChannelInfoRecord>& value)
{
    // the QLabel is AutoFmt 
    std::ostringstream strm;

    strm << "<html><body>";
    strm << "<table><thead><tr>";
    strm << "<th bgcolor=\"light blue\">channelID</th>";
    strm << "<th bgcolor=\"light blue\">channelNumber</th>";
    strm << "<th bgcolor=\"light blue\">channelName</th>";
    strm << "</tr></thead>";

    for (auto& v : value)
    {
        strm << "<tr>";
        strm << "<td>" << v.channelID.c_str() << "</td>";
        strm << "<td>" << v.channelNumber.c_str() << "</td>";
        strm << "<td>" << v.channelName.c_str() << "</td>";
        strm << "</tr>";
    }

    strm << "</table></body></html>";
    return QString::fromStdString(strm.str());
}


using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_Channel*>();

Q_DECLARE_METATYPE(ajn::services::ChannelInterface::ChannelInfoRecord);
Q_DECLARE_METATYPE(std::vector<ajn::services::ChannelInterface::ChannelInfoRecord>);
static const int auto_register_struct_ChannelInfoRecord = qRegisterMetaType<ajn::services::ChannelInterface::ChannelInfoRecord>("ChannelInterface::ChannelInfoRecord");
static const int auto_register_struct_v_ChannelInfoRecord = qRegisterMetaType<std::vector<ajn::services::ChannelInterface::ChannelInfoRecord>>("std::vector<ChannelInterface::ChannelInfoRecord>");


#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <alljoyn/cdm/common/LogModule.h>
#include <sstream>


org_alljoyn_SmartSpaces_Operation_Channel_GetChannelList::org_alljoyn_SmartSpaces_Operation_Channel_GetChannelList(QWidget* parent, uint16_t startingRecord, uint16_t numRecords)
{
    startingRecord_ = startingRecord;
    numRecords_ = numRecords;

    dialog_ = new QDialog(parent);
    auto* dlgLayout_ = new QVBoxLayout(dialog_);

    auto* top = new QWidget();
    dlgLayout_->addWidget(top);

    auto* topLayout_ = new QGridLayout(top);

    auto* startLabel = new QLabel("Starting Record");
    topLayout_->addWidget(startLabel, 0, 0);

    startSpin_ = new QSpinBox();
    topLayout_->addWidget(startSpin_, 0, 1);
    startSpin_->setValue(startingRecord_);
    QObject::connect(startSpin_, SIGNAL(valueChanged(int)), this, SLOT(changed()));

    auto* numLabel = new QLabel("Num Records");
    topLayout_->addWidget(numLabel, 1, 0);

    numSpin_ = new QSpinBox();
    topLayout_->addWidget(numSpin_, 1, 1);
    numSpin_->setValue(numRecords_);
    QObject::connect(numSpin_, SIGNAL(valueChanged(int)), this, SLOT(changed()));

    auto* buttons = new QDialogButtonBox();
    dlgLayout_->addWidget(buttons);

    auto* cancel = buttons->addButton(QDialogButtonBox::Cancel);
    QObject::connect(cancel, SIGNAL(clicked(bool)), dialog_, SLOT(reject()));

    auto* ok = buttons->addButton(QDialogButtonBox::Ok);
    QObject::connect(ok, SIGNAL(clicked(bool)), dialog_, SLOT(accept()));
}



org_alljoyn_SmartSpaces_Operation_Channel_GetChannelList::~org_alljoyn_SmartSpaces_Operation_Channel_GetChannelList()
{
    delete dialog_;
}



int org_alljoyn_SmartSpaces_Operation_Channel_GetChannelList::run()
{
    // This is always modal
    return dialog_->exec();
}



void org_alljoyn_SmartSpaces_Operation_Channel_GetChannelList::changed()
{
    startingRecord_ = startSpin_->value();
    numRecords_ = numSpin_->value();
}



static bool DialogGetChannelList(QWidget* parent, uint16_t& startingRecord, uint16_t& numRecords)
{
    auto* dialog = new org_alljoyn_SmartSpaces_Operation_Channel_GetChannelList(parent, startingRecord, numRecords);
    auto code = dialog->run();
    bool ok = code == QDialog::Accepted;

    if (ok)
    {
        startingRecord = dialog->startingRecord_;
        numRecords = dialog->numRecords_;
    }

    delete dialog;
    return ok;
}

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

    layout->addWidget(new QLabel("<b>ChannelId</b>"));
    // Create the editing widget for ChannelId
    edit_ChannelId = new QLineEdit();
    edit_ChannelId->setToolTip("Current channel id.");
    QObject::connect(edit_ChannelId, SIGNAL(returnPressed()), this, SLOT(slotSetChannelId()));

    layout->addWidget(edit_ChannelId);
    layout->addWidget(new QLabel("<b>TotalNumberOfChannels</b>"));
    // Create the editing widget for TotalNumberOfChannels
    edit_TotalNumberOfChannels = new QLabel();

    layout->addWidget(edit_TotalNumberOfChannels);

    messages_ = new QLabel();
    layout->addWidget(messages_);

    if (iface)
    {
        controller = iface->CreateInterface<ChannelIntfController>(m_listener);
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

org_alljoyn_SmartSpaces_Operation_Channel::~org_alljoyn_SmartSpaces_Operation_Channel()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_Channel::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "Channel getting properties";

        status = controller->GetChannelId();
        if (status != ER_OK)
        {
            qWarning() << "Channel::fetchProperties Failed to get ChannelId" << QCC_StatusText(status);
        }

        status = controller->GetTotalNumberOfChannels();
        if (status != ER_OK)
        {
            qWarning() << "Channel::fetchProperties Failed to get TotalNumberOfChannels" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_Channel::slotClickGetChannelList()
{
    qWarning() << "Channel::slotClickGetChannelList";

    uint16_t startingRecord {};
    uint16_t numRecords {};

    bool ok = true;
    startingRecord = 0;
    numRecords = 100;
    ok = DialogGetChannelList(this, startingRecord, numRecords);

    if (ok)
    {
        QStatus status = controller->GetChannelList(startingRecord, numRecords, NULL);
        if (status != ER_OK)
        {
            qWarning() << "Channel::slotClick Failed to call GetChannelList" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_Channel::slotOnResponseGetChannelId(QStatus status, const qcc::String& value)
{
    qWarning() << "Channel::slotOnResponseGetChannelId";

    edit_ChannelId->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_Channel::slotOnChannelIdChanged(const qcc::String& value)
{
    qWarning() << "Channel::slotOnChannelIdChanged";

    edit_ChannelId->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_Channel::slotOnResponseSetChannelId(QStatus status)
{
    qWarning() << "Channel::slotOnResponseSetChannelId";

    if (status != ER_OK)
    {
        qcShowStatus(this, "Failed to set ChannelId", status);
        qWarning() << "Channel::slotOnResponseSetChannelId Failed to set ChannelId" << QCC_StatusText(status);
        fetchProperties();      // restore the display of properties
    }
}



void org_alljoyn_SmartSpaces_Operation_Channel::slotSetChannelId()
{
    qWarning() << "Channel::slotSetChannelId";

    bool ok = false;
    qcc::String value;
    QString str = edit_ChannelId->text();
    value = QStringTo<qcc::String>(str, &ok);
    if (!ok)
    {
        qWarning() << "Channel::slotSetChannelId Failed to convert '" << str << "' to qcc::String";
    }

    if (ok)
    {
        QStatus status = controller->SetChannelId(value);

        if (status != ER_OK)
        {
            qWarning() << "Channel::slotSetChannelId Failed to get ChannelId" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_Channel::slotOnResponseGetTotalNumberOfChannels(QStatus status, const uint16_t value)
{
    qWarning() << "Channel::slotOnResponseGetTotalNumberOfChannels";

    edit_TotalNumberOfChannels->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_Channel::slotOnTotalNumberOfChannelsChanged(const uint16_t value)
{
    qWarning() << "Channel::slotOnTotalNumberOfChannelsChanged";

    edit_TotalNumberOfChannels->setText(QStringFrom(value));
}






void org_alljoyn_SmartSpaces_Operation_Channel::slotOnResponseMethodGetChannelList(QStatus status, const std::vector<ChannelInterface::ChannelInfoRecord>& listOfChannelInfoRecords, const QString& errorName)
{
    if (status == ER_OK)
    {
        qInfo() << "Channel::slotOnResponseMethodGetChannelList";
    }
    else
    {
        qWarning() << "Channel::slotOnResponseMethodGetChannelList Received error = " << errorName;
    }
    std::ostringstream strm;

    strm << "<html><body>"
         << "<h1>Channels</h1>\n"
         << "<table>\n"
         << "<thead><tr><th bgcolor=\"lightblue\">ID</th><th bgcolor=\"lightblue\">Number</th><th bgcolor=\"lightblue\">Name</th></tr></thead>\n";

    for (auto& entry : listOfChannelInfoRecords)
    {
          strm << "<tr><td>" <<entry.channelID.c_str()
               << "</td><td>" << entry.channelNumber.c_str()
               << "</td><td>" << entry.channelName.c_str()
               << "</td></tr>\n";
    }
    strm << "</table>"
         << "</body></html>\n";

    auto str = strm.str();
    messages_->setTextFormat(Qt::RichText);
    messages_->setText(str.c_str());
}



void org_alljoyn_SmartSpaces_Operation_Channel::slotOnSignalChannelListChanged()
{
        qInfo() << "Received signal ChannelListChanged";
}
