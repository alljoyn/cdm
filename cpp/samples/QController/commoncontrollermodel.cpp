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
#include "commoncontrollermodel.h"
#include "commoncontrollerimpl.h"

#include <QIcon>

CommonControllerModel::CommonControllerModel(QAbstractItemView *view)
    : QAbstractItemModel(view), view(view), root(new CommonControllerRoot(this))
{
}

CommonControllerModel::~CommonControllerModel()
{
    delete root;
}

QVariant CommonControllerModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    CommonControllerNode *item = static_cast<CommonControllerNode*>(index.internalPointer());

    switch (role) {
    case Qt::DisplayRole:
        if (index.column() == 0)
        {
            return item->name();
        }
        else
        {
            return QVariant();
        }

    default:
        return QVariant();
    }
}

Qt::ItemFlags CommonControllerModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return 0;
    }

    return QAbstractItemModel::flags(index);
}

QVariant CommonControllerModel::headerData(int, Qt::Orientation, int) const
{
    return QVariant();
}

QModelIndex CommonControllerModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    CommonControllerNode *parentItem;

    if (!parent.isValid())
        parentItem = root;
    else
        parentItem = static_cast<CommonControllerNode*>(parent.internalPointer());

    CommonControllerNode *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex CommonControllerModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    CommonControllerNode *node = static_cast<CommonControllerNode*>(index.internalPointer());
    CommonControllerNode *nodeParent = node->parent();

    if (nodeParent == root)
        return QModelIndex();

    return createIndex(nodeParent->parent()->childIndex(node), 0, nodeParent);
}

int CommonControllerModel::rowCount(const QModelIndex &parent) const
{
    CommonControllerNode *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = root;
    else
        parentItem = static_cast<CommonControllerNode*>(parent.internalPointer());

    return parentItem->childCount();
}

int CommonControllerModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QModelIndex CommonControllerModel::nodeToIndex(CommonControllerNode *node) const
{
    CommonControllerNode *nodeParent = node->parent();
    if (nodeParent)
    {
        return createIndex(nodeParent->childIndex(node), 0, node);
    }
    else
    {
        return createIndex(0, 0, node);
    }
}
