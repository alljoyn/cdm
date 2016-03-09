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

#ifndef CYCLECONTROLINTFCONTROLLERIMPL_H_
#define CYCLECONTROLINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/hae/interfaces/InterfaceController.h>
#include <alljoyn/hae/interfaces/operation/CycleControlIntfController.h>

namespace ajn {
namespace services {

class CycleControlIntfControllerListener;
class HaeProxyBusObject;

/**
 * CycleControl Interface Controller implementation class
 */
class CycleControlIntfControllerImpl : public InterfaceController, public CycleControlIntfController {
  public:
    /**
     * Create interface
     */
    static HaeInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, HaeProxyBusObject& haeProxyObject);

    /**
     * Constructor of CycleControlIntfControllerImpl
     */
    CycleControlIntfControllerImpl(BusAttachment& busAttachment, CycleControlIntfControllerListener& listener, HaeProxyBusObject& haeProxyObject);

    /**
     * Destructor of CycleControlIntfControllerImpl
     */
    virtual ~CycleControlIntfControllerImpl();

    /**
     * Initialize interface
     * @return status
     */
    virtual QStatus Init();

    /**
     * Get bus attachment
     * @return bus attachment
     */
    virtual BusAttachment& GetBusAttachment() const { return m_busAttachment; }

    /**
     * Get operational state
     * @param[in] context
     * @return status
     */
    virtual QStatus GetOperationalState(void* context);

    /**
     * Get supported operational commands
     * @param[in] context
     * @return status
     */
    virtual QStatus GetSupportedOperationalCommands(void* context);

    /**
     * Get supported operational states
     * @param[in] context
     * @return status
     */
    virtual QStatus GetSupportedOperationalStates(void* context);

    /**
     * Execute command
     * @param[in] command to execute
     * @param[in] context
     * @return status
     */
    virtual QStatus ExecuteCommand(const CycleControlOperationalCommand command, void* context);

  private:
    CycleControlIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);

    void GetOperationalStatePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    void GetSupportedOperationalCommandsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    void GetSupportedOperationalStatesPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    void EndOfCycleEmitted(const InterfaceDescription::Member* member, const char* srcPath, Message& message);

    void ExecuteCommandReplyHandler(Message& message, void* context);

    BusAttachment& m_busAttachment;
    CycleControlIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* CYCLECONTROLINTFCONTROLLERIMPL_H_ */
