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

#include <algorithm>
#include <alljoyn/cdm/common/LogModule.h>

#include "CdmBusListener.h"

using namespace std;

namespace ajn {
namespace services {

CdmBusListener::CdmBusListener(BusAttachment& bus) :
    BusListener(), SessionPortListener(), SessionListener(), m_bus(bus), m_sessionPort(0)
{
}

CdmBusListener::~CdmBusListener()
{
}

void CdmBusListener::SetSessionPort(ajn::SessionPort sessionPort)
{
    m_sessionPort = sessionPort;
}

const SessionPort CdmBusListener::GetSessionPort() const
{
    return m_sessionPort;
}

bool CdmBusListener::AcceptSessionJoiner(ajn::SessionPort sessionPort, const char* joiner, const ajn::SessionOpts& opts)
{
    if (sessionPort != m_sessionPort) {
        return false;
    }

    QCC_DbgPrintf(("Accepting JoinSessionRequest"));
    return true;
}

void CdmBusListener::SessionJoined(SessionPort sessionPort, SessionId sessionId, const char* joiner)
{
    if (find(m_sessionIds.begin(), m_sessionIds.end(), sessionId) != m_sessionIds.end()) {
        return;
    }
    m_sessionIds.push_back(sessionId);

    QStatus status = m_bus.SetSessionListener(sessionId, this);
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: failed to set session listener.", __func__));
    }
}

void CdmBusListener::SessionLost(SessionId sessionId, SessionLostReason reason)
{
    vector<SessionId>::iterator it = find(m_sessionIds.begin(), m_sessionIds.end(), sessionId);
    if (it != m_sessionIds.end()) {
        m_sessionIds.erase(it);
    }
    QStatus status = m_bus.SetSessionListener(sessionId, NULL);
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: failed to remove session listener.", __func__));
    }
}

void CdmBusListener::BusStopping()
{
    // TBD
    QCC_LogError(ER_FAIL, ("TBD::%s", __func__));
}

void CdmBusListener::BusDisconnected()
{
    // TBD
    QCC_LogError(ER_FAIL, ("TBD::%s", __func__));
}

const vector<SessionId>& CdmBusListener::GetSessionIds() const
{
    return m_sessionIds;
}

} /* namespace services */
} /* namespace ajn */