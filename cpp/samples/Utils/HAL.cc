/******************************************************************************
 * 
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

#include <errno.h>
#include <sys/stat.h>
#include <thread>
#include <mutex>
#include <fstream>
#include <vector>

#include "HAL.h"
#include "Utils.h"
using namespace std;

namespace ajn {
namespace services {
namespace HAL {
//======================================================================

static const char PathDelim = '/';


//  These read and write actions can come from different threads.
using MutLock = std::lock_guard<std::mutex>;


class X::Impl
{
  public:
    Impl();
    ~Impl();

    void SetRootDir(const std::string& rootDir);
    Element* ReadPropertyXml(const string& busPath, const string& interface, const string& property);
    void WritePropertyXml(const string& busPath, const string& interface, const string& property, Element* xml, bool force);
    void WritePropertyXml(const string& busPath, const string& interface, const string& property, const string& xml, bool force);

    struct Failure : public std::exception
    {
    };

    string  m_rootDir;
    mutex   m_mutex;

    string  PropPath(const string& busPath, const string& interface, const string& property);
};



X::Impl::Impl()
{
}



X::Impl::~Impl()
{
}



void X::Impl::SetRootDir(const std::string& rootDir)
{
    m_rootDir = rootDir;
}


Element* X::Impl::ReadPropertyXml(const string& busPath, const string& interface, const string& property)
{
    MutLock lock(m_mutex);
    Element* elem = 0;

    try
    {
        auto path = PropPath(busPath, interface, property);
        ifstream strm(path);
        string text;

        while (strm)
        {
            string line;
            std::getline(strm, line);
            text += line;
            text += "\n";
        }

        if (text.empty())
        {
            cerr << "No XML in file " << path << "\n";
        }
        else
        if (ER_OK != Element::GetRoot(text.c_str(), &elem))
        {
            cerr << "Invalid XML in file " << path << "\n";
            delete elem;
            elem = 0;
        }
    }
    catch(...)
    {
    }

    return elem;
}



void X::Impl::WritePropertyXml(const string& busPath, const string& interface, const string& property, const string& xml, bool force)
{
    Element* elem = 0;

    if (ER_OK == Element::GetRoot(xml.c_str(), &elem))
    {
        WritePropertyXml(busPath, interface, property, elem, force);
    }

    delete elem;
    elem = 0;
}



void X::Impl::WritePropertyXml(const string& busPath, const string& interface, const string& property, Element* xml, bool force)
{
    MutLock lock(m_mutex);

    try
    {
        auto path = PropPath(busPath, interface, property);

        if (!force)
        {
            // If the file already exists then don't change it.
            ifstream strm(path);

            if (strm.is_open())
            {
                return;
            }
        }

        auto text = xml-> Generate();
        ofstream strm(path);

        if (strm)
        {
            strm << text << "\n";
        }
        else
        {
            cerr << "Cannot write to " << path << "\n";
        }
    }
    catch(...)
    {
    }
}



string X::Impl::PropPath(const string& busPath, const string& interface, const string& property)
{
    string path = m_rootDir;

    path += HAL::PathDelim;
    path += busPath;
    path += HAL::PathDelim;
    path += interface;

    if (ER_OK != utils::MkDirPath(path, HAL::PathDelim))
    {
        throw Failure();
    }

    path += "/";
    path += property;
    return path;
}

//======================================================================

X& X::instance()
{
    // C++ guarantees that only once thread will initialise the static. SO says:
    //    See 6.7 [stmt.dcl]/p4 of C++11 for the specification.
    //    Warning: VS-2013 does not yet implement thread-safe construction of function-local statics. But everyone else does.
    static unique_ptr<X> hal(new X);
    return *hal;
}



X::X()
  : m_impl (new Impl())
{
}



X::~X()
{
    delete m_impl;
}



void X::SetRootDir(const std::string& rootDir)
{
    m_impl->SetRootDir(rootDir);
}



Element* X::ReadPropertyXml(const string& busPath, const string& interface, const string& property)
{
    return m_impl->ReadPropertyXml(busPath, interface, property);
}



void X::WritePropertyXml(const string& busPath, const string& interface, const string& property, Element* xml, bool force)
{
    m_impl->WritePropertyXml(busPath, interface, property, xml, force);
}



void X::WritePropertyXml(const string& busPath, const string& interface, const string& property, const string& xml, bool force)
{
    m_impl->WritePropertyXml(busPath, interface, property, xml, force);
}


//======================================================================
} // namespace HAL
} // namespace services
} // namespace ajn
