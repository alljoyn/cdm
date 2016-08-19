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

#ifndef INTERFACECONTROLLER_H_
#define INTERFACECONTROLLER_H_

#include <alljoyn/MessageReceiver.h>
#include <alljoyn/ProxyBusObject.h>

namespace ajn {
namespace services {

class HaeProxyBusObject;
/**
 * InterfaceController class
 */
class InterfaceController : public MessageReceiver, public ProxyBusObject::Listener, public ProxyBusObject::PropertiesChangedListener {
  public:

    /**
     * Constructor of InterfaceController
     */
    InterfaceController(HaeProxyBusObject& haeProxyObject) : m_proxyObject(haeProxyObject) {}

    /**
     * Destructor of InterfaceController
     */
    virtual ~InterfaceController() {}

  protected:
    HaeProxyBusObject& m_proxyObject;
};

} //namespace services
} //namespace ajn

#endif /* INTERFACECONTROLLER_H_ */
