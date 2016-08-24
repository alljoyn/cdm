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

#ifndef WINDDIRECTIONLISTENER_H_
#define WINDDIRECTIONLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/environment/WindDirectionIntfControllee.h>
#include <alljoyn/cdm/interfaces/environment/WindDirectionIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class WindDirectionListener : public WindDirectionIntfControlleeListener
{
  public:
    virtual QStatus OnSetHorizontalDirection(const uint16_t& value);
    virtual QStatus OnGetHorizontalDirection(uint16_t& value);
    virtual QStatus OnGetHorizontalMax(uint16_t& value);
    virtual QStatus OnSetHorizontalAutoMode(const uint8_t& value);
    virtual QStatus OnGetHorizontalAutoMode(uint8_t& value);
    virtual QStatus OnSetVerticalDirection(const uint16_t& value);
    virtual QStatus OnGetVerticalDirection(uint16_t& value);
    virtual QStatus OnGetVerticalMax(uint16_t& value);
    virtual QStatus OnSetVerticalAutoMode(const uint8_t& value);
    virtual QStatus OnGetVerticalAutoMode(uint8_t& value);
};

class WindDirectionCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    WindDirectionCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~WindDirectionCommands();

    virtual void Init();
    virtual void InitializeProperties();

    WindDirectionIntfControllee* GetInterface() { return m_intfControllee; }

    static void OnCmdGetHorizontalDirection(Commands* commands, std::string& cmd);
    static void OnCmdSetHorizontalDirection(Commands* commands, std::string& cmd);

    static void OnCmdGetHorizontalMax(Commands* commands, std::string& cmd);
    static void OnCmdSetHorizontalMax(Commands* commands, std::string& cmd);

    static void OnCmdGetHorizontalAutoMode(Commands* commands, std::string& cmd);
    static void OnCmdSetHorizontalAutoMode(Commands* commands, std::string& cmd);

    static void OnCmdGetVerticalDirection(Commands* commands, std::string& cmd);
    static void OnCmdSetVerticalDirection(Commands* commands, std::string& cmd);

    static void OnCmdGetVerticalMax(Commands* commands, std::string& cmd);
    static void OnCmdSetVerticalMax(Commands* commands, std::string& cmd);

    static void OnCmdGetVerticalAutoMode(Commands* commands, std::string& cmd);
    static void OnCmdSetVerticalAutoMode(Commands* commands, std::string& cmd);

  private:
    WindDirectionIntfControllee* m_intfControllee;
    WindDirectionListener m_listener;
};

#endif /* WINDDIRECTIONLISTENER_H_ */
