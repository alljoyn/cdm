/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <algorithm>
#include <iostream>
#include <map>

#include "Commands.h"
#include "../Utils/Utils.h"

using namespace std;

namespace ajn {
namespace services {
namespace emulator {
//======================================================================

class Commands::Impl
{
public:
    Impl()
    {
    }

    typedef map<string, Commands::Subscriber> SubMap;
    typedef map<string, string> HelpMap;

    SubMap      m_subs;
    HelpMap     m_help;

    void Subscribe(const string& key, Commands::Subscriber sub, const string& help);
    bool Publish(const string& key, const StringVec& args);
    bool Publish(const string& command);
    StringVec Help() const;
};



void Commands::Impl::Subscribe(const string& key, Commands::Subscriber sub, const string& help)
{
    m_subs[key] = sub;
    m_help[key] = help;
}



bool Commands::Impl::Publish(const string& key, const StringVec& args)
{
    auto iter = m_subs.find(key);

    if (iter != m_subs.end())
    {
        return (iter->second)(key, args);
    }

    return false;
}



bool Commands::Impl::Publish(const string& command)
{
    auto args = utils::SplitWords(command);

    if (!args.empty())
    {
        auto key = args[0];
        args.erase(args.begin());
        return Publish(key, args);
    }

    return false;
}



StringVec Commands::Impl::Help() const
{
    StringVec result;

    for (auto& pair : m_help)
    {
        result.push_back(pair.second);
    }

    std::sort(result.begin(), result.end());
    return result;
}


//======================================================================

Commands& Commands::Instance()
{
    static Commands* cmds = 0;

    if (!cmds)
    {
        cmds = new Commands();
    }

    return *cmds;
}



Commands::Commands()
  : m_impl(new Impl())
{
}



Commands::~Commands()
{
    delete m_impl;
}



bool Commands::Subscribe(const string& key, Subscriber subscriber, const string& help)
{
    m_impl->Subscribe(key, subscriber, help);
    return true;
}



bool Commands::Publish(const string& key, const StringVec& args)
{
    return m_impl->Publish(key, args);
}



bool Commands::Publish(const string& command)
{
    return m_impl->Publish(command);
}



StringVec Commands::Help() const
{
    return m_impl->Help();
}

//======================================================================
}}}
