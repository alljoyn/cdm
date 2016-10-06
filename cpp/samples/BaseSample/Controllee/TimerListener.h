/******************************************************************************
 *  *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#ifndef TIMERLISTENER_H_
#define TIMERLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/TimerIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/TimerIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class TimerListener : public TimerIntfControlleeListener
{
  public:
        virtual QStatus GetReferenceTimer(int32_t& time) ;

        virtual QStatus GetTargetTimeToStart(int32_t& time) ;

        virtual QStatus GetTargetTimeToStop(int32_t& time) ;

        virtual QStatus GetEstimatedTimeToEnd(int32_t& time);

        virtual QStatus GetRunningTime(int32_t& time) ;

        virtual QStatus GetTargetDuration(int32_t& time);

        virtual QStatus OnSetTargetTimeToStart(int32_t time, ErrorCode& errorCode) ;

        virtual QStatus OnSetTargetTimeToStop(int32_t time, ErrorCode& errorCode) ;

};

class TimerCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    TimerCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~TimerCommands();

    virtual void Init();
    virtual void InitializeProperties();

    TimerIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetReferenceTimer(Commands* commands, std::string& cmd);
    static void OnCmdSetReferenceTimer(Commands* commands, std::string& cmd);

    static void OnCmdGetTargetTimeToStart(Commands* commands, std::string& cmd);
    static void OnCmdSetTargetTimeToStart(Commands* commands, std::string& cmd);

    static void OnCmdGetTargetTimeToStop(Commands* commands, std::string& cmd);
    static void OnCmdSetTargetTimeToStop(Commands* commands, std::string& cmd);

    static void OnCmdGetEstimatedTimeToEnd(Commands* commands, std::string& cmd);

    static void OnCmdGetRunningTime(Commands* commands, std::string& cmd);

    static void OnCmdGetTargetDuration(Commands* commands, std::string& cmd);

  private:
    TimerIntfControllee* m_intfControllee;
    TimerListener m_listener;
};


#endif /* WATERLEVELLISTENER_H_ */