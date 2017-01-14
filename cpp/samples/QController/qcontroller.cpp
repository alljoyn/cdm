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
#include <QTreeView>
#include <QTableView>
#include <QHeaderView>
#include <QFontDatabase>
#include <QLabel>
#include <QScrollBar>
#include <QSplitter>
#include <QTableWidget>
#include <QHeaderView>

#include <iostream>
using namespace std;

#include "qcontroller.h"
#include "commoncontrollermodel.h"
#include "LogModel.h"
#include "commoncontrollerimpl.h"
#include "InspectorWidget.h"

QController::QController(QWidget *parent) :
    QMainWindow(parent)
{
    setObjectName("QController");
    resize(1000, 800);

    QSplitter* centralWidget = new QSplitter(Qt::Vertical, this);

    QSplitter* deviceWidget = new QSplitter(Qt::Horizontal, centralWidget);

    QTreeView* deviceTree = new QTreeView();
    deviceTree->setObjectName("deviceTree");
    deviceTree->setAlternatingRowColors(true);
    deviceTree->setHeaderHidden(true);
    deviceTree->setSelectionBehavior(QAbstractItemView::SelectRows);
    deviceTree->setSelectionMode(QAbstractItemView::SingleSelection);
    deviceTree->setModel(new CommonControllerModel(deviceTree));

    InspectorWidget* inspector = new InspectorWidget();

    // make the device tree a bit smaller
    deviceWidget->addWidget(deviceTree);
    deviceWidget->addWidget(inspector);
    deviceWidget->setStretchFactor(0, 1);
    deviceWidget->setStretchFactor(1, 4);

    QObject::connect(deviceTree->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)), inspector, SLOT(deviceSelectionChanged(const QItemSelection&, const QItemSelection&)));


    logView = new QTableView(centralWidget);
    logView->setObjectName("logView");

    LogModel *logModel = new LogModel();
    logView->setModel(logModel);
    logView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    logView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    logView->setGridStyle(Qt::DashLine);
    logView->verticalHeader()->setVisible(false);
    logView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    logView->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
    logView->scrollToBottom();
    connect(logView->model(), SIGNAL(rowsInserted(QModelIndex,int,int)), this, SLOT(logScrollToBottom()));


    AJLogHandler *aj = new AJLogHandler(this);

    QObject::connect(aj, SIGNAL(logReceived(const QString &, const QString &, const QString &)), logModel, SLOT(logEntry(const QString &, const QString &, const QString &)));


    setCentralWidget(centralWidget);
}

QController::~QController()
{
}

void QController::logScrollToBottom()
{
    // TODO: Don't scroll to bottom if the user is scrolled somewhere in particular
    logView->scrollToBottom();
}
