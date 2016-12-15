/******************************************************************************
 *  * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
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

#include <iostream>
#include <fstream>

#include "Config.h"
#include "../Utils/Utils.h"
#include "../../framework/src/util/BSXML.h"

using namespace std;

namespace ajn {
namespace services {
namespace emulator {
//======================================================================

using xml::Element;

class Config::Impl
{
public:

    Impl(const string& filePath);

    string      m_text;
    string      m_aboutData;

    bool        m_isValid = false;

    Config::ObjectVec m_objects;

    bool        ReadFile(const string& filePath);
    bool        ParseXml();
};



Config::Impl::Impl(const string& filePath)
{
    m_isValid = ReadFile(filePath);
    m_isValid = m_isValid && ParseXml();
}




bool
Config::Impl::ParseXml()
{
    bool ok = true;

    Element* root = 0;
    Element::GetRoot(m_text.c_str(), &root);

    if (root)
    {
        // Extract the about data
        std::vector<const Element *> nodes = root->GetPath("AboutData");

        if (nodes.size() == 1)
        {
            // Jigger the device name to include the host name
            for (auto* elem : nodes[0]->GetChildren())
            {
                if (elem->GetName() == "DeviceName")
                {
                    auto content = elem->GetContent() + ", " + utils::GetHostName();
                    elem->SetContent(content);
                    break;
                }
            }

            m_aboutData = nodes[0]->Generate();
        }
        else
        {
            ok = false;
        }

        if (ok)
        {
            // Extract the interfaces
            std::vector<const Element *> objects = root->GetPath("InterfaceList/Object");

            for (auto& obj : objects)
            {
                /** Each is 
                 *      <Object path='/CDM/Lamp'>
                 *          <Interface name='org.alljoyn.SmartSpaces.Operation.OnControl'/>
                 *      </Object>
                 */
                auto objPath = obj->GetAttribute("path");

                if (!objPath.empty())
                {
                    Config::Object object;
                    object.path = objPath;

                    std::vector<const Element *> ifaces = obj->GetPath("Interface");

                    for (auto& iface : ifaces)
                    {
                        Interface ifObj;

                        ifObj.name = iface->GetAttribute("name");

                        if (!ifObj.name.empty())
                        {
                            auto props = iface->GetPath("Property");
                            cout << "object path " << objPath << " : iface " << ifObj.name << " #props=" << props.size() << "\n";

                            for (auto& prop : props)
                            {
                                Property prObj;

                                prObj.name = prop->GetAttribute("name");
                                auto mode  = prop->GetAttribute("mode");

                                if (!prObj.name.empty())
                                {
                                    // There should be one child which is the initial state
                                    auto cs = prop->GetChildren();

                                    if (cs.size() == 1)
                                    {
                                        prObj.initialState = cs[0]->Generate();
                                        cout << "The initial state for " << objPath << " : " << ifObj.name << " is: " << prObj.initialState << "\n";
                                    }
                                    else
                                    if (cs.size() > 1)
                                    {
                                        cerr << "The initial state is confused for " << objPath << " : " << ifObj.name << "\n";
                                    }

                                    if (mode == "default")
                                    {
                                        prObj.mode = PropMode::Default;
                                    }
                                    else
                                    {
                                        prObj.mode = PropMode::Initialize;
                                    }

                                    ifObj.properties.push_back(prObj);
                                }
                            }

                            object.interfaces.push_back(ifObj);
                        }
                        else
                        {
                           ok = false;
                        }
                    }

                    m_objects.push_back(object);
                }
                else
                {
                   ok = false;
                }
            }
        }
    }

    delete root;
    return ok;
}



bool Config::Impl::ReadFile(const string& filePath)
{
    ifstream strm(filePath);

    while (strm)
    {
        string line;

        std::getline(strm, line);

        if (strm.eof())
        {
            return true;
        }

        if (strm.bad())
        {
            // must be some sort of error
            return false;
        }

        if (!line.empty())
        {
            m_text += line;
            m_text += "\n";
        }
    }

    return true;
}


//======================================================================

Config::Config(const string& filePath)
  : m_impl(new Impl(filePath))
{
}



Config::~Config()
{
    delete m_impl;
}



bool Config::IsValid() const
{
    return m_impl->m_isValid;
}



const std::string& Config::GetAboutData() const
{
    return m_impl->m_aboutData;
}


const Config::ObjectVec& Config::GetObjects() const
{
    return m_impl->m_objects;
}

//======================================================================
}}}