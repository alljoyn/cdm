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

#ifndef ONOFFSTATUSLISTENER_H_
#define ONOFFSTATUSLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/OnOffStatusIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/OnOffStatusIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class OnOffStatusListener : public OnOffStatusIntfControlleeListener
{
  public:
    virtual QStatus OnGetIsOn(bool& value);
};

////////////////////////////////////////////////////////////////////////////////

class OnOffStatusCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    OnOffStatusCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~OnOffStatusCommands();

    virtual void Init();

    OnOffStatusIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetIsOnStatus(Commands* commands, std::string& cmd);
    static void OnCmdSetIsOnStatus(Commands* commands, std::string& cmd);

  private:
    OnOffStatusIntfControllee* m_intfControllee;
    OnOffStatusListener m_listener;
};

#endif /* ONOFFSTATUSLISTENER_H_ */
