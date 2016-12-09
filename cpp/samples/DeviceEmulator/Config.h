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


#ifndef CDM_CONFIG_H_
#define CDM_CONFIG_H_

#include <string>
#include <vector>


namespace ajn {
namespace services {
namespace emulator {
//======================================================================

typedef std::vector<std::string> StringVec;

/**
 *  This reads the traditional device emulator XML file and produces
 *  some AboutData and a list of interfaces.
 */

class Config
{
public:
    enum class PropMode
    {
        Default,                        // only use it as a default
        Initialize                      // forceably initialise the property
    };

    struct Property
    {
        std::string name;
        std::string initialState;       // as xml
        PropMode    mode;
    };

    typedef std::vector<Property> PropertyVec;

    struct Interface
    {
        std::string name;
        PropertyVec properties;
    };

    typedef std::vector<Interface> InterfaceVec;

    struct Object
    {
        std::string path;
        InterfaceVec interfaces;
    };

    typedef std::vector<Object> ObjectVec;


    Config(const std::string& filePath);
    ~Config();

    bool IsValid() const;

    const std::string& GetAboutData() const;

    const ObjectVec& GetObjects() const;

private:
    class Impl;

    Impl* m_impl;
};

//======================================================================
}}}

#endif // CDM_CONFIG_H_