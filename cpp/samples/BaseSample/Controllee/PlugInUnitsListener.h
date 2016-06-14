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

#ifndef PLUGINUNITSLISTENER_H_
#define PLUGINUNITSLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/hae/interfaces/operation/PlugInUnitsIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/PlugInUnitsIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class PlugInUnitsListener : public PlugInUnitsIntfControlleeListener
{
  public:
    virtual QStatus OnGetPlugInUnits(PlugInUnitsInterface::PlugInUnits& plugInUnits);

};

class PlugInUnitsCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    PlugInUnitsCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~PlugInUnitsCommands();

    virtual void Init();
    virtual void InitializeProperties();

    PlugInUnitsIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetPlugInUnits(Commands* commands, std::string& cmd);

  private:
    PlugInUnitsIntfControllee* m_intfControllee;
    PlugInUnitsListener m_listener;
};

#endif /* PLUGINUNITSLISTENER_H_ */
