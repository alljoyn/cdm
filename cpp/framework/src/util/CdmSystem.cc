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

#include <alljoyn/cdm/util/CdmSystem.h>
#include <alljoyn/cdm/common/CdmAboutData.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/Init.h>

namespace ajn {
namespace services {
//======================================================================

QStatus 
RouterLauncher::Start()
{
    return ER_OK;
}



QStatus 
RouterLauncher::Stop()
{
    return ER_OK;
}


//======================================================================

class CdmSystem::Impl
{
  public:

    Impl(const qcc::String& appName)
        : m_appName(appName)
    {
    }

    ~Impl()
    {
        Shutdown();
    }

    void SetRouter(Ref<RouterLauncher> router);
    void SetAboutData(const qcc::String& xml);
    void SetAllowRemoteMessages(bool allow);

    QStatus Start();
    QStatus Stop();
    void Shutdown();

    qcc::String m_appName;
    bool m_allowRemoteMsgs = true;

    Ref<RouterLauncher> m_router;
    Ref<BusAttachment> m_bus;

    enum StartState {
        Started, Stopped
    };

    StartState m_appState = Stopped;
    StartState m_routerState = Stopped;
    StartState m_busState = Stopped;
};



void CdmSystem::Impl::SetRouter(Ref<RouterLauncher> router)
{
    if (m_routerState == Stopped) {
        m_router = router;
    }
}



void CdmSystem::Impl::SetAllowRemoteMessages(bool allow)
{
    m_allowRemoteMsgs = allow;
}



QStatus CdmSystem::Impl::Start()
{
    QStatus status = ER_OK;

    if (m_appState != Stopped) {
        return ER_THREAD_RUNNING;
    }

    status = AllJoynInit();

    if (status != ER_OK) {
        printf("FAILED to init alljoyn\n");
        return status;
    }

    if (m_router) {
        status = m_router->Start();
    } else {
#ifdef ROUTER
        status = AllJoynRouterInit();
#else
        status = ER_OK;
#endif
    }

    if (status != ER_OK) {
        AllJoynShutdown();
        printf("FAILED to init router\n");
        return status;
    }

    m_routerState = Started;

    m_bus = mkRef<BusAttachment>(m_appName.c_str(), m_allowRemoteMsgs);
    status = m_bus->Start();

    if (ER_OK != status) {
        printf("BusAttachment::Start failed (%s)\n", QCC_StatusText(status));
        Shutdown();
        return status;
    }

    m_busState = Started;
    status = m_bus->Connect();

    if (ER_OK != status) {
        printf("BusAttachment::Connect failed (%s)\n", QCC_StatusText(status));
        Shutdown();
    }

    m_appState = Started;
    return ER_OK;
}



void CdmSystem::Impl::Shutdown()
{
    /**
     * Get everything shutdown. This might be in the case of an error.
     * BEWARE - You can't even safely destruct an AJ object after AllJoynShutdown()
     * has been called.  Delete all objects before the AllJoynShutdown().
     */
    switch (m_busState) {
    case Started:
        // A client may have monkeyed with the bus attachment state
        if (m_bus->IsStarted()) {
            if (m_bus->IsConnected()) {
                m_bus->Disconnect();
            }

            m_bus->Stop();
        }

        if (m_bus->IsStopping()) {
            m_bus->Join();
        }
        break;

    case Stopped:
        break;
    }

    m_busState = Stopped;
    m_bus.reset();

    switch (m_routerState) {
    case Started:
        if (m_router) {
            m_router->Stop();
            m_router->Join();
        } else {
#ifdef ROUTER
            AllJoynRouterShutdown();
#endif
        }
        break;

    case Stopped:
        break;
    }

    m_routerState = Stopped;
    m_router.reset();

    switch (m_appState) {
    case Started:
        AllJoynShutdown();
        break;

    case Stopped:
        break;
    }

    m_appState = Stopped;
}



QStatus CdmSystem::Impl::Stop()
{
    if (m_appState == Stopped) {
        return ER_DEAD_THREAD;
    }

    Shutdown();
    return ER_OK;
}


//======================================================================


CdmSystem::CdmSystem(const qcc::String& appName)
  : m_impl(new Impl(appName))
{
}


CdmSystem::~CdmSystem()
{
    delete m_impl;
}


CdmSystem& CdmSystem::SetAllowRemoteMessages(bool allow)
{
    m_impl->SetAllowRemoteMessages(allow);
    return *this;
}


CdmSystem& CdmSystem::SetRouter(Ref<RouterLauncher> router)
{
    m_impl->SetRouter(router);
    return *this;
}


QStatus CdmSystem::Start()
{
    return m_impl->Start();
}


QStatus CdmSystem::Stop()
{
    return m_impl->Stop();
}


BusAttachment& CdmSystem::GetBusAttachment()
{
    return *m_impl->m_bus;
}

//======================================================================
} //namespace services
} //namespace ajn