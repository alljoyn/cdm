/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
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
#define THREADED 0

#include <string.h>

#if THREADED
#include <pthread.h>
#endif

#include <iostream>
using namespace std;

#include "Command.h"

namespace ajn {
namespace services {
//======================================================================

#if THREADED
static pthread_t irq;
#endif


struct IrqArg
{
    IrqArg(CommandHandler h, CdmControllee& c)
      : handler(h), controllee(c)
    {
    }

    CommandHandler handler;
    CdmControllee& controllee;
};



static void ParseCommand(char* buf, IrqArg& irqArg)
{
    /* The buffer may be altered by having NULs replace some characters.
    */
    Command cmd;
    const char* token;
    int step = 0;

    /* Split the line into words at white space.
    */
    for (token = strtok(buf, " \t");
         token;
         token = strtok(NULL, " \t"))
    {
        switch (step)
        {
        case 0:
            cmd.name = token;
            break;

        case 1:
            cmd.objPath = token;
            break;

        case 2:
            cmd.interface = token;
            break;

        case 3:
            cmd.property = token;
            break;

        default:
            break;
        }

        ++step;
    }

    (*irqArg.handler)(cmd, irqArg.controllee);
}



static void* IrqHandler(void* arg)
{
    auto* irqArg = reinterpret_cast<IrqArg*>(arg);
    char buf[BUFSIZ + 1];
    size_t cap = BUFSIZ;
    size_t len = 0;

    while(1)
    {
        int c = fgetc(stdin);

        if (c == EOF)
        {
            cerr << "Warning: stdin closed\n";
            break;
        }
        else
        if (c == '\n')
        {
            ParseCommand(buf, *irqArg);
            len = 0;
        }
        else
        if (len < cap)
        {
            buf[len++] = c;
            buf[len] = 0;
        }
        else
        {
            cerr << "Error: exceeded the command length\n";
            len = 0;
        }
    }

    return 0;
}



void StartCommands(CommandHandler handler, CdmControllee& controllee)
{
    IrqArg irqArg(handler, controllee);

#if THREADED
    if (pthread_create(&irq, NULL, &IrqHandler, (void*)&irqArg) != 0)
    {
        cerr << "Error setting up IRQ\n";
    }
#else
    IrqHandler(&irqArg);
#endif
}

//======================================================================
} // namespace services
} // namespace ajn
