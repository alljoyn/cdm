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
#ifndef QCONTROLLER_QSTRINGCONVERSION_H
#define QCONTROLLER_QSTRINGCONVERSION_H

#include <QString>
#include <qcc/String.h>
#include <vector>
#include <sstream>

///////////////
// QStringTo //
///////////////

template<typename T> static T QStringTo(const QString& str, bool* ok)
{
    if (ok) *ok = false;
    return T();
}

template<> qcc::String QStringTo<qcc::String>(const QString& str, bool* ok)
{
    if (ok) *ok = true;
    return str.toUtf8().data();
}

template<> bool QStringTo<bool>(const QString& str, bool* ok)
{
    QString lower = str.toLower();
    if (lower == "1" || lower == "true" || lower == "on" || lower == "y" || lower == "yes")
    {
        if (ok) *ok = true;
        return true;
    }
    if (lower == "0" || lower == "false" || lower == "off" || lower == "n" || lower == "no")
    {
        if (ok) *ok = true;
        return false;
    }
    if (ok) *ok = false;
    return false;
}

template<> unsigned char QStringTo<unsigned char>(const QString& str, bool* rok)
{
    bool ok;
    unsigned short v = str.toUShort(&ok);
    if (v > 255)
    {
        v = 0;
        ok = false;
    }

    if (rok) *rok = ok;
    return (unsigned char)v;
}

template<> short QStringTo<short>(const QString& str, bool* ok)
{ return str.toShort(ok); }

template<> unsigned short QStringTo<unsigned short>(const QString& str, bool* ok)
{ return str.toUShort(ok); }

template<> int QStringTo<int>(const QString& str, bool* ok)
{ return str.toInt(ok); }

template<> unsigned int QStringTo<unsigned int>(const QString& str, bool* ok)
{ return str.toUInt(ok); }

template<> long QStringTo<long>(const QString& str, bool* ok)
{ return str.toLong(ok); }

template<> unsigned long QStringTo<unsigned long>(const QString& str, bool* ok)
{ return str.toULong(ok); }

template<> long long QStringTo<long long>(const QString& str, bool* ok)
{ return str.toLongLong(ok); }

template<> unsigned long long QStringTo<unsigned long long>(const QString& str, bool* ok)
{ return str.toULongLong(ok); }

template<> float QStringTo<float>(const QString& str, bool* ok)
{ return str.toFloat(ok); }

template<> double QStringTo<double>(const QString& str, bool* ok)
{ return str.toDouble(ok); }

/////////////////
// QStringFrom //
/////////////////

template<typename T> static QString QStringFrom(const T& v)
{ return QString(); }

template<> QString QStringFrom(const qcc::String& v)
{ return v.c_str(); }

template<> QString QStringFrom(const bool& v)
{ return v ? "true" : "false"; }

template<> QString QStringFrom(const unsigned char& v)
{ return QString::number(v); }

template<> QString QStringFrom(const short& v)
{ return QString::number(v); }

template<> QString QStringFrom(const unsigned short& v)
{ return QString::number(v); }

template<> QString QStringFrom(const int& v)
{ return QString::number(v); }

template<> QString QStringFrom(const long& v)
{ return QString::number(v); }

template<> QString QStringFrom(const unsigned long& v)
{ return QString::number(v); }

template<> QString QStringFrom(const long long& v)
{ return QString::number(v); }

template<> QString QStringFrom(const unsigned long long& v)
{ return QString::number(v); }

template<> QString QStringFrom(const float& v)
{ return QString::number(v); }

template<> QString QStringFrom(const double& v)
{ return QString::number(v); }

template<> QString QStringFrom(const std::vector<uint8_t>& v)
{
    std::ostringstream strm;
    bool first = true;

    for (auto n : v)
    {
        if (!first)
        {
            strm << " ";
        }
        strm << (unsigned)n;
        first = false;
    }

    return QString::fromStdString(strm.str());
}

template<> QString QStringFrom(const std::vector<qcc::String>& v)
{
    std::ostringstream strm;
    bool first = true;

    for (auto n : v)
    {
        if (!first)
        {
            strm << " ";
        }
        strm << n.c_str();
        first = false;
    }

    return QString::fromStdString(strm.str());
}


#endif //QCONTROLLER_QSTRINGCONVERSION_H
