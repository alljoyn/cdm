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
#ifndef QCONTROLLER_INSPECTORWIDGET_H
#define QCONTROLLER_INSPECTORWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QItemSelection>
#include <map>

#include "commoncontrollerimpl.h"
#include "qcTypes.h"

class InspectorWidget : public QWidget
{
    Q_OBJECT
public:
    InspectorWidget(QWidget* parent = 0);
    ~InspectorWidget();

public slots:
    void deviceSelectionChanged(const QItemSelection&, const QItemSelection&);

private:
    void generateUi();
    void generateUi(CommonControllerDevice *);
    void generateUi(CommonControllerInterface *);
    void generateUi(CommonControllerPath *);

    typedef std::map<CommonControllerInterface*, QWidget*>  IfaceMap;
    typedef std::map<CommonControllerPath*, QWidget*>  PathMap;
    typedef std::map<CommonControllerDevice*, QWidget*>  DeviceMap;

    QBoxLayout* layout_;

    Mutex       devMutex_;
    DeviceMap   devices_;

    Mutex       pathMutex_;
    PathMap     paths_;

    Mutex       ifaceMutex_;
    IfaceMap    interfaces_;            // the actual interface widget

    Mutex       wrapMutex_;
    IfaceMap    wrappers_;              // widget that wraps the interface object

    Mutex       emptyMutex_;
    QWidget*    empty_;

    QWidget* getWidgetFromInterfaceName(CommonControllerInterface* iface);

    void    hideAll();
};

#endif //QCONTROLLER_INSPECTORWIDGET_H
