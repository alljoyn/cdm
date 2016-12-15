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

#include <alljoyn/cdm/util/CdmAnnouncer.h>
#include <alljoyn/cdm/common/CdmAboutData.h>
#include <alljoyn/Init.h>
#include <alljoyn/Session.h>
#include <alljoyn/SessionPortListener.h>
#include <alljoyn/AboutObj.h>
#include <alljoyn/AboutObjectDescription.h>

#include <iostream>

// REVISIT shouldn't this be declared somewhere useful?
#define ABOUT_SESSION_PORT 900

namespace ajn {
namespace services {
//======================================================================

// REVISIT concurrency?

class CdmAnnouncer::Impl
{
  public:

    class DefaultSessionListener : public SessionPortListener
    {
      public:
        /**
         * AcceptSessionJoiner - Receive request to join session and decide whether to accept it or not
         * @param sessionPort - the port of the request
         * @param joiner - the name of the joiner
         * @param opts - the session options
         * @return true/false
         */
        virtual bool AcceptSessionJoiner(SessionPort sessionPort, const char* joiner, const SessionOpts& opts) {
            QCC_UNUSED(sessionPort);
            QCC_UNUSED(joiner);
            QCC_UNUSED(opts);
            return true;
        }
    };


    Impl(BusAttachment& busAttachment)
      : m_bus(busAttachment),
        m_aboutData(mkRef<CdmAboutData>()),
        m_sessionListener(mkRef<DefaultSessionListener>())
    {
    }

    ~Impl()
    {
        Unannounce();
    }

    void SetAboutData(const qcc::String& xml);
    void SetAboutData(Ref<CdmAboutData> aboutData);
    void SetSessionListener(Ref<SessionPortListener> listener);

    QStatus Announce();
    QStatus Unannounce();

    BusAttachment& m_bus;
    qcc::String m_aboutXml;
    Ref<CdmAboutData> m_aboutData;
    Ref<AboutObj> m_aboutObj;
    Ref<SessionPortListener> m_sessionListener;

    bool m_externalData = false;
    bool m_announced = false;
};



void CdmAnnouncer::Impl::SetAboutData(const qcc::String& xml)
{
    m_aboutXml = xml;
    m_aboutData = mkRef<CdmAboutData>();
    m_externalData = false;
}



void CdmAnnouncer::Impl::SetAboutData(Ref<CdmAboutData> aboutData)
{
    m_aboutData = aboutData;
    m_externalData = true;
}



void CdmAnnouncer::Impl::SetSessionListener(Ref<SessionPortListener> listener)
{
    m_sessionListener = listener;
}



QStatus CdmAnnouncer::Impl::Announce()
{
    QStatus status = ER_OK;

    if (m_announced) {
        return ER_OK;
    }

    if (!m_externalData) {
        status = m_aboutData->CreateFromXml(m_aboutXml);
    }

    // If there was no AppId in the XML file, generate one
    uint8_t *appId = NULL;
    size_t appIdSize = 0;
    if (m_aboutData->GetAppId(&appId, &appIdSize) != ER_OK) {
        qcc::GUID128 uniqueAppId;
        m_aboutData->SetAppId(uniqueAppId.ToString().c_str());
        std::cout << "Using generated AppId: " << uniqueAppId.ToString().c_str() << std::endl;
    }

    // If there was no DeviceId in the XML file, generate one
    char *deviceId = NULL;
    if (m_aboutData->GetDeviceId(&deviceId) != ER_OK) {
        qcc::GUID128 uniqueDeviceId;
        m_aboutData->SetDeviceId(uniqueDeviceId.ToString().c_str());
        std::cout << "Using generated DeviceId: " << uniqueDeviceId.ToString().c_str() << std::endl;
    }

    if (ER_OK != status) {
        std::cerr << "About Data parsing failed: " << QCC_StatusText(status) << "\n";
        return status;
    }

    SessionPort port = ABOUT_SESSION_PORT;
    SessionOpts opts(SessionOpts::TRAFFIC_MESSAGES, false, SessionOpts::PROXIMITY_ANY, TRANSPORT_ANY);

    status = m_bus.BindSessionPort(port, opts, *m_sessionListener);

    if (status != ER_OK) {
        std::cerr << "BindSessionPort failed: " << QCC_StatusText(status) << "\n";
        return status;
    }

    m_aboutObj = Ref<AboutObj>(new AboutObj(m_bus, BusObject::ANNOUNCED));

    status = m_aboutObj->Announce(ABOUT_SESSION_PORT, *m_aboutData);

    if (status != ER_OK) {
        m_aboutObj.reset();
        std::cerr << "About announcement failed: " << QCC_StatusText(status) << "\n";
        return status;
    }

    m_announced = true;
    return ER_OK;
}



QStatus CdmAnnouncer::Impl::Unannounce()
{
    if (m_announced)
    {
        if (m_aboutObj) {
            m_aboutObj->Unannounce();
            m_aboutObj.reset();
        }

        m_bus.UnbindSessionPort(ABOUT_SESSION_PORT);
        m_announced = false;
    }

    return ER_OK;
}


//======================================================================


CdmAnnouncer::CdmAnnouncer(BusAttachment& busAttachment)
  : m_impl(new Impl(busAttachment))
{
}


CdmAnnouncer::~CdmAnnouncer()
{
    delete m_impl;
}



CdmAnnouncer& CdmAnnouncer::SetAboutData(const qcc::String& xml)
{
    m_impl->SetAboutData(xml);
    return *this;
}



CdmAnnouncer& CdmAnnouncer::SetAboutData(Ref<CdmAboutData> aboutData)
{
    m_impl->SetAboutData(aboutData);
    return *this;
}



CdmAnnouncer& CdmAnnouncer::SetSessionListener(Ref<SessionPortListener> listener)
{
    m_impl->SetSessionListener(listener);
    return *this;
}



QStatus CdmAnnouncer::Announce()
{
    return m_impl->Announce();
}



QStatus CdmAnnouncer::Unannounce()
{
    return m_impl->Unannounce();
}



Ref<CdmAboutData> CdmAnnouncer::GetAboutData() const
{
    return m_impl->m_aboutData;
}

//======================================================================
} //namespace services
} //namespace ajn