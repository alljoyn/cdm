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
#include "qcontroller.h"
#include <QApplication>
#include <QCommandLineParser>
#include <qcc/String.h>

#include <iostream>
#include <vector>

using namespace std;

// Global command line options
bool QControllerDebugLog = false;


Q_DECLARE_METATYPE(Ref<ajn::services::DeviceInfo>)
Q_DECLARE_METATYPE(QStatus)
Q_DECLARE_METATYPE(uint8_t)
Q_DECLARE_METATYPE(uint16_t)
Q_DECLARE_METATYPE(int16_t)
Q_DECLARE_METATYPE(uint32_t)
Q_DECLARE_METATYPE(int32_t)
Q_DECLARE_METATYPE(uint64_t)
Q_DECLARE_METATYPE(int64_t)
Q_DECLARE_METATYPE(qcc::String)
Q_DECLARE_METATYPE(std::vector<uint8_t>)
Q_DECLARE_METATYPE(std::vector<qcc::String>)


// TODO REVISIT this may be no longer used
static const char* DefaultStyle =
"#alertsList {\n"
"   background-color: white;\n"
"   border: 1px solid;\n"
"   padding: 2px;\n"
"   }\n"
".alertDescription { margin-left: 5px; margin-right: 5px; }\n"
"*[severity=\"2\"]{ background-color: red }\n"
"*[severity=\"1\"]{ background-color: orange }\n"
;


int main(int argc, char *argv[])
{
    qRegisterMetaType<Ref<ajn::services::DeviceInfo>>();
    qRegisterMetaType<QStatus>("QStatus");
    qRegisterMetaType<uint8_t>("uint8_t");
    qRegisterMetaType<uint16_t>("uint16_t");
    qRegisterMetaType<int16_t>("int16_t");
    qRegisterMetaType<uint32_t>("uint32_t");
    qRegisterMetaType<int32_t>("int32_t");
    qRegisterMetaType<uint64_t>("uint64_t");
    qRegisterMetaType<int64_t>("int64_t");
    qRegisterMetaType<qcc::String>();
    qRegisterMetaType<std::vector<uint8_t>>("std::vector<uint8_t>");    // used by some AJ properties
    qRegisterMetaType<std::vector<uint8_t>>("std::vector<qcc::String>");

    QApplication a(argc, argv);

    QCommandLineParser argParser;

    argParser.addOptions({
        {"D", "Show debugging messages on stdout, not in the GUI"}
        });

    argParser.process(a.arguments());

    QControllerDebugLog = argParser.isSet("D");

    if (a.styleSheet().isEmpty())
    {
        a.setStyleSheet(DefaultStyle);
    }

    QController w;
    w.show();

    return a.exec();
}
