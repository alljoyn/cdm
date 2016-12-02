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

#ifndef INTERFACECONTROLLEE_H_
#define INTERFACECONTROLLEE_H_

#include <vector>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/MsgArg.h>
#include <alljoyn/MessageReceiver.h>
#include <alljoyn/cdm/common/CdmTypes.h>
#include <alljoyn/cdm/controllee/CdmControllee.h>

namespace ajn {
namespace services {

class CdmBusObject;

/**
 * InterfaceControllee class
 */
class InterfaceReceiver : public MessageReceiver {
  public:

    typedef void (InterfaceReceiver::* CdmMethodHandler)(const InterfaceDescription::Member* member, Message& message, CdmControllee& controllee);
    typedef std::vector<std::pair<const InterfaceDescription::Member*, InterfaceReceiver::CdmMethodHandler> > MethodHandlers;

    explicit InterfaceReceiver(CdmBusObject& cdmBusObject) : m_busObject(cdmBusObject) {};
    /**
     * Destructor of InterfaceControllee
     */
    virtual ~InterfaceReceiver() {}

    /**
     * Callback handler for getting property.
     * @param[in] propName identifies the property to get
     * @param[out] val returns the property value. The type of this value is the actual value type.
     * @return ER_OK on success
     */
    virtual QStatus OnGetProperty(const qcc::String& propName, MsgArg& val) = 0;

    /**
     * Callback handler for setting property.
     * @param[in] propName identifies the property to set
     * @param[in] val returns the property value. The type of this value is the actual value type.
     * @return ER_OK on success
     */
    virtual QStatus OnSetProperty(const qcc::String& propName, MsgArg& val) = 0;

    /**
     * Handler for method
     * @param[in] member method interface member entry.
     * @param[in] message the received method call message.
     */
    virtual void OnMethodHandler(const InterfaceDescription::Member* member, Message& msg, CdmControllee& controllee) = 0;

    /**
     * Get method handlers
     * @return MethodHandlers
     */
    virtual const MethodHandlers& GetMethodHanders() const = 0;

  protected:

    CdmBusObject& m_busObject;
};

} //namespace services
} //namespace ajn

#endif /* INTERFACECONTROLLEE_H_ */
