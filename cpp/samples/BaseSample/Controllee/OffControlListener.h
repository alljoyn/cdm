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

#ifndef OFFCONTROLLISTENER_H_
#define OFFCONTROLLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/OffControlIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/OffControlIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class OffControlListener : public OffControlIntfControlleeListener
{
  public:
    virtual QStatus OnSwitchOff(ErrorCode& errorCode);
};
////////////////////////////////////////////////////////////////////////////////

class OffControlCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    OffControlCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~OffControlCommands();

    virtual void Init();

    OffControlIntfControllee* GetInterface() { return m_intfControllee; }

  private:
    OffControlIntfControllee* m_intfControllee;
    OffControlListener m_listener;
};


#endif /* OFFCONTROLLISTENER_H_ */
