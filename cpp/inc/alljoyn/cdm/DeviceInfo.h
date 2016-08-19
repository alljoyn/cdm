/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
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


#ifndef DEVICEINFO_H_
#define DEVICEINFO_H_

#include <map>
#include <memory>
#include <alljoyn/Session.h>
#include <alljoyn/hae/HaeAboutData.h>
#include <alljoyn/AboutObjectDescription.h>

namespace ajn {

class BusAttachment;

namespace services {

class HaeProxyBusObject;
typedef std::map<qcc::String, HaeProxyBusObject*> HaeProxyObjectMap;

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
     * @param[in] data HAE About data
     * @param[in] description About object description
     */
    DeviceInfo(const char* name, SessionId id, SessionPort port, const HaeAboutData& data, const AboutObjectDescription& description);

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
     * Get HAE Proxy bus object
     * @param[in] bus bus attachment
     * @param[in] objectPath the object path
     * @return HAE Proxy bus object
     */
    HaeProxyBusObject* GetHaeProxyBusObject(BusAttachment& bus, const qcc::String& objectPath);

    /**
     * Get About object description
     * @return About object description
     */
    const AboutObjectDescription& GetAboutObjectDescription() { return m_aboutObjectDescription; };

  private:
    std::string m_busName;
    SessionId m_sessionId;
    SessionPort m_sessionPort;
    HaeAboutData m_aboutData;
    AboutObjectDescription m_aboutObjectDescription;
    HaeProxyObjectMap m_haeProxyObjectsMap;
};

typedef std::shared_ptr<DeviceInfo> DeviceInfoPtr;
typedef std::map<SessionId, DeviceInfoPtr> DeviceMap;

}  // services
}  // ajn

#endif  // DEVICEINFO_H_
