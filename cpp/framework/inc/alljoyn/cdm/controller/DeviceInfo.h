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


#ifndef DEVICEINFO_H_
#define DEVICEINFO_H_

#include <map>
#include <memory>
#include <alljoyn/Session.h>
#include <alljoyn/cdm/common/CdmAboutData.h>
#include <alljoyn/cdm/common/CdmTypes.h>
#include <alljoyn/cdm/controller/CdmTranslator.h>
#include <alljoyn/AboutObjectDescription.h>

namespace ajn {

class BusAttachment;

namespace services {


/**
 * Device Info class
 */
class DeviceInfo {
  public:

    /**
     * Constructor of DeviceInfo
     */
    DeviceInfo();

    /**
     * Constructor of DeviceInfo
     * @param[in] name device name
     */
    DeviceInfo(const char* name);

    /**
     * Constructor of DeviceInfo
     * @param[in] name device name
     * @param[in] id session id
     * @param[in] port session port
     * @param[in] data CDM About data
     * @param[in] description About object description
     */
    DeviceInfo(const char* name, SessionId id, SessionPort port, const CdmAboutData& data, const AboutObjectDescription& description);

    /**
     * Destructor of DeviceInfo
     */
    virtual ~DeviceInfo();

    /**
     * Get bus name
     * @return Bus name
     */
    const std::string& GetBusName() const { return m_busName; }

    /**
     * Get session id
     * @return Session id
     */
    SessionId GetSessionId() const { return m_sessionId; }

    /**
     * Get session port
     * @return Session port
     */
    SessionPort GetSessionPort() const { return m_sessionPort; }

    /**
     * Get About data
     * @return About data
     */
    CdmAboutData& GetAboutData() { return m_aboutData; };

    /**
     * Get About object description
     * @return About object description
     */
    const AboutObjectDescription& GetAboutObjectDescription() { return m_aboutObjectDescription; };

    /**
     * Get a map of bus paths to translation modules
     * @return Translator map
     */
    const std::map<std::string, Ref<CdmTranslator>>& GetTranslators() { return m_translators; }

    /**
     * Add a translator module for a bus path
     * @return Translator map
     */
    void RegisterTranslator(const std::string& busPath, Ref<CdmTranslator> translator) { m_translators[busPath] = translator; }

  private:
    std::string m_busName;
    SessionId m_sessionId;
    SessionPort m_sessionPort;
    CdmAboutData m_aboutData;
    AboutObjectDescription m_aboutObjectDescription;
    std::map<std::string, Ref<CdmTranslator>> m_translators;
};

typedef std::map<SessionId, Ref<DeviceInfo>> DeviceMap;

}  // services
}  // ajn

#endif  // DEVICEINFO_H_