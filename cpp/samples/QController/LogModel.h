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
#ifndef QCONTROLLER_LOGMODEL_H
#define QCONTROLLER_LOGMODEL_H

#include <QDebug>
#include <QAbstractListModel>
#include <qcc/Debug.h>
#include <mutex>


class AJLogHandler : public QObject
{
    Q_OBJECT
public:
    AJLogHandler(QObject *parent);
    virtual ~AJLogHandler();

    // For handling messages from AllJoyn (QCC)
    static void ajCallback(DbgMsgType type, const char* module, const char* message, void* context);
    void ajHandler(DbgMsgType type, const char* module, const char* message);

signals:
    void logReceived(const QString &type, const QString &module, const QString &message);

private:
    static AJLogHandler *s_handler;
};

class LogModel : public QAbstractListModel
{
    Q_OBJECT
public:
    LogModel(size_t max = 1024);
    ~LogModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parents) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

public slots:
    void logEntry(const QString &type, const QString &module, const QString &message);

private:

    struct LogEntry
    {
        QString type;
        QString module;
        QString message;
    };
    typedef std::recursive_mutex Mutex;
    typedef std::lock_guard<Mutex> LockGuard;

    std::vector<LogEntry> entries;
    const size_t maxSize;
    size_t startIndex;
    mutable Mutex mutex;
};

#endif //QCONTROLLER_LOGMODEL_H
