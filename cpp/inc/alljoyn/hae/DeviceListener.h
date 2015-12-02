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


#ifndef DEVICELISTENER_H_
#define DEVICELISTENER_H_

#include <map>
#include <alljoyn/Session.h>
#include <alljoyn/hae/DeviceInfo.h>

namespace ajn {
namespace services {

/**
 * Abstract base class implemented by User Application Developers. \n
 * The callbacks defined in this class allow the User Application
 * to be informed about some Hae Controller operations.
 */
class DeviceListener {
  public:
    /**
     * Destructor of DeviceListener
     */
    virtual ~DeviceListener() { }

    /**
     * Added device in the network
     * @param[in] busname bus name
     * @param[in] port port
     * @param[in] data HAE About data
     * @param[in] description About object description
     */
    virtual void OnDeviceAdded(const char* busname, SessionPort port, const HaeAboutData& data,
                               const AboutObjectDescription& description) = 0;

    /**
     * Removed device in the network
     * @param[in] busname bus name
     */
    virtual void OnDeviceRemoved(const char* busname) = 0;

    /**
     * Device session joined
     * @param[in] info device info pointer
     */
    virtual void OnDeviceSessionJoined(const DeviceInfoPtr& info) = 0;

    /**
     * Device session lost
     * @param[in] sessionId session id
     */
    virtual void OnDeviceSessionLost(SessionId sessionId) = 0;
};

}  // services
}  // ajn

#endif  // DEVICEMANAGER_H_
