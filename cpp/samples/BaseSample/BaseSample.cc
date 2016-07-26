/******************************************************************************
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <limits>
#include "BaseSample.h"
#include "Commands.h"

using namespace std;

static volatile sig_atomic_t s_interrupt = false;
static void SigIntHandler(int sig)
{
    s_interrupt = true;
}

BaseSample::BaseSample()
: m_Quit(false)
{
}

BaseSample::~BaseSample()
{
}

void BaseSample::Startup()
{
#ifdef QCC_OS_LINUX
    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_handler = SigIntHandler;
    action.sa_flags = SA_SIGINFO;
    sigaction(SIGINT, &action, NULL);
#else
    signal(SIGINT, SigIntHandler);
#endif

    QStatus status = Init();
    if (status != ER_OK) {
        std::cout << "Init failed" << std::endl;
        exit(1);
    }

    if (m_CurrentCommands) {
        m_CurrentCommands->PrintCommands();
    }

    while (s_interrupt == false && m_Quit == false) {
        std::string inputString;
        std::cout << "# ";
        std::getline(std::cin, inputString);
        m_CurrentCommands->Execute(inputString);
    }

    Deinit();
}

void BaseSample::Shutdown()
{

}

void BaseSample::UpdateCurrentCommands()
{
    m_CurrentCommands = m_CommandsQueue.top();
}

void BaseSample::PushCommands(Commands* commands)
{
    if (!commands) {
        return;
    }
    commands->Init();
    m_CommandsQueue.push(commands);
    UpdateCurrentCommands();
}

void BaseSample::PopCommands()
{
    if (static_cast<int>(m_CommandsQueue.size()) > 1) {
        Commands* m_oldCommand = m_CurrentCommands;

        m_CommandsQueue.pop();
        UpdateCurrentCommands();

        ChildCommandMap &children = m_CurrentCommands->GetChildren();
        ChildCommandMap::iterator itr = children.begin();
        while(itr != children.end()) {
            if(itr->second == m_oldCommand) {
                itr->second = nullptr;
            }
            ++itr;
        }

        delete m_oldCommand;
        m_oldCommand = nullptr;

        m_CurrentCommands->PrintCommands();
    }
}

//////////////////////////////////////////////////////////////

