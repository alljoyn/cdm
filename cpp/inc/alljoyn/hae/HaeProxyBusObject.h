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

#ifndef HAEPROXYBUSOBJECT_H_
#define HAEPROXYBUSOBJECT_H_

#include <map>
#include <qcc/String.h>
#include <alljoyn/ProxyBusObject.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/hae/interfaces/HaeInterfaceTypes.h>

namespace ajn {
namespace services {

class HaeInterface;
class InterfaceControllerListener;
/**
 * Hae ProxyBusObject class.
 */
class HaeProxyBusObject : public ProxyBusObject {
  public:

    /**
     * Constructor of HaeProxyBusObject
     */
    HaeProxyBusObject(BusAttachment& busAttachment, std::string const& busName, qcc::String const& objectPath, SessionId sessionId);

    /**
     * Destructor of HaeProxyBusObject
     */
    ~HaeProxyBusObject();

    /**
     * Create anb add interface to BusObject
     * @param[in] type  interface type
     * @param[in] listener  interface controller listener
     * @return interface
     */
    HaeInterface* CreateInterface(const HaeInterfaceType type, InterfaceControllerListener& listener);


  private:

    BusAttachment& m_busAttachment;
    std::map<qcc::String, HaeInterface*> m_haeInterfacesMap;
};

}
}

#endif /* HAEPROXYBUSOBJECT_H_ */
