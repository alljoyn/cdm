/******************************************************************************
 * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#ifndef BASESAMPLE_H_
#define BASESAMPLE_H_

#include <stack>
#include <alljoyn/Status.h>

class Commands;

class BaseSample {
  public:
    BaseSample();
    virtual ~BaseSample();

    void Startup();
    void Shutdown();

    void UpdateCurrentCommands();
    void PushCommands(Commands* commands);
    void PopCommands();
    Commands* GetCurrentCommands() { return m_CurrentCommands; }
    int GetCommandsQueueSize() {return static_cast<int>(m_CommandsQueue.size());}

    void Quit() { m_Quit = true; }

  protected:
    virtual QStatus Init() = 0;
    virtual void Deinit() = 0;

  private:
    bool m_Quit;
    std::stack<Commands*> m_CommandsQueue;
    Commands* m_CurrentCommands;
};

#endif // BASESAMPLE_H_