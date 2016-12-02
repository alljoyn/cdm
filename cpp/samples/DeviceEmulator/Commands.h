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

#ifndef CDM_COMMANDS_H_
#define CDM_COMMANDS_H_

#include <string>
#include <vector>
#include <functional>
#include <alljoyn/cdm/controllee/CdmControllee.h>


namespace ajn {
namespace services {
namespace emulator {
//======================================================================

typedef std::vector<std::string> StringVec;

/**
 *  This is a singleton that models can subscribe to to get
 *  out-of-band commands.  It is expected that subscriptions
 *  are down at static initialisation time so we don't worry about
 *  threads.
 */

class Commands
{
public:
    typedef std::function<bool(const std::string& key, const StringVec& args, CdmControllee& controllee)> Subscriber;

    static Commands& Instance();

    ~Commands();

    bool    Subscribe(const std::string& key, Subscriber subscriber, const std::string& help);
    bool    Publish(const std::string& key, const StringVec& args, CdmControllee& controllee);
    bool    Publish(const std::string& command, CdmControllee& controllee);
    StringVec Help() const;

private:
    Commands();

    class Impl;

    Impl* m_impl;
};

//======================================================================
}}}

#endif // CDM_COMMANDS_H_
