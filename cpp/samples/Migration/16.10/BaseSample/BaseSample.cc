/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 * Source Project (AJOSP) Contributors and others.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * All rights reserved. This program and the accompanying materials are
 * made available under the terms of the Apache License, Version 2.0
 * which accompanies this distribution, and is available at
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Copyright 2016 Open Connectivity Foundation and Contributors to
 * AllSeen Alliance. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all
 * copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <limits>
#include "BaseSample.h"

using namespace std;

static volatile sig_atomic_t s_interrupt = false;
static void CDECL_CALL SigIntHandler(int sig)
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

    while (s_interrupt == false && m_Quit == false) {
        std::string inputString;
        std::cout << "Press Enter to quit ";
        std::getline(std::cin, inputString);
        m_Quit = true;
    }

    Deinit();
}

void BaseSample::Shutdown()
{

}

//////////////////////////////////////////////////////////////

