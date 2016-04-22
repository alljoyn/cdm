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

#ifndef AIRRECIRCULATIONMODELISTENER_H_
#define AIRRECIRCULATIONMODELISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/hae/interfaces/operation/AirRecirculationModeIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/AirRecirculationModeIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class AirRecirculationModeListener : public AirRecirculationModeIntfControlleeListener
{
  public:
    virtual QStatus OnSetIsRecirculating(const bool& isRecirculating);
    virtual QStatus OnGetIsRecirculating(bool& isRecirculating);
};

class AirRecirculationModeCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    AirRecirculationModeCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~AirRecirculationModeCommands();

    virtual void Init();

    AirRecirculationModeIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetIsRecirculating(Commands* commands, std::string& cmd);
    static void OnCmdSetIsRecirculating(Commands* commands, std::string& cmd);

  private:
    AirRecirculationModeIntfControllee* m_intfControllee;
    AirRecirculationModeListener m_listener;
};


#endif /* AIRRECIRCULATIONMODELISTENER_H_ */
