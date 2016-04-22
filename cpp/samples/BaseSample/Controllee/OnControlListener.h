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

#ifndef ONCONTROLLISTENER_H_
#define ONCONTROLLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/hae/interfaces/operation/OnControlIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/OnControlIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class OnControlListener : public OnControlIntfControlleeListener
{
  public:
    virtual QStatus OnSwitchOn(ErrorCode& errorCode);
};
////////////////////////////////////////////////////////////////////////////////

class OnControlCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    OnControlCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~OnControlCommands();

    virtual void Init();

    OnControlIntfControllee* GetInterface() { return m_intfControllee; }

  private:
    OnControlIntfControllee* m_intfControllee;
    OnControlListener m_listener;
};

#endif /* ONCONTROLLISTENER_H_ */
