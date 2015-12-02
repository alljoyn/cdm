/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
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

#include <algorithm>
#include <alljoyn/hae/LogModule.h>

#include "HaeBusListener.h"

using namespace std;

namespace ajn {
namespace services {

HaeBusListener::HaeBusListener(BusAttachment& bus) :
    BusListener(), SessionPortListener(), SessionListener(), m_bus(bus), m_sessionPort(0)
{
}

HaeBusListener::~HaeBusListener()
{
}

void HaeBusListener::SetSessionPort(ajn::SessionPort sessionPort)
{
    m_sessionPort = sessionPort;
}

const SessionPort HaeBusListener::GetSessionPort() const
{
    return m_sessionPort;
}

bool HaeBusListener::AcceptSessionJoiner(ajn::SessionPort sessionPort, const char* joiner, const ajn::SessionOpts& opts)
{
    if (sessionPort != m_sessionPort) {
        return false;
    }

    QCC_DbgPrintf(("Accepting JoinSessionRequest"));
    return true;
}

void HaeBusListener::SessionJoined(SessionPort sessionPort, SessionId sessionId, const char* joiner)
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

void HaeBusListener::SessionLost(SessionId sessionId, SessionLostReason reason)
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

void HaeBusListener::BusStopping()
{
    // TBD
    QCC_LogError(ER_FAIL, ("TBD::%s", __func__));
}

void HaeBusListener::BusDisconnected()
{
    // TBD
    QCC_LogError(ER_FAIL, ("TBD::%s", __func__));
}

const vector<SessionId>& HaeBusListener::GetSessionIds() const
{
    return m_sessionIds;
}

} /* namespace services */
} /* namespace ajn */
