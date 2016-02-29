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

#ifndef ROBOTCLEANINGCYCLEPHASEINTFCONTROLLERIMPL_H_
#define ROBOTCLEANINGCYCLEPHASEINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/hae/interfaces/InterfaceController.h>
#include <alljoyn/hae/interfaces/operation/RobotCleaningCyclePhaseIntfController.h>

namespace ajn {
namespace services {

class RobotCleaningCyclePhaseIntfControllerListener;
class HaeProxyBusObject;

/**
 * RobotCleaningCyclePhase Interface Controller implementation class
 */
class RobotCleaningCyclePhaseIntfControllerImpl : public InterfaceController, public RobotCleaningCyclePhaseIntfController {
  public:
    /**
     * Create interface
     */
    static HaeInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, HaeProxyBusObject& haeProxyObject);

    /**
     * Constructor of RobotCleaningCyclePhaseIntfControllerImpl
     */
    RobotCleaningCyclePhaseIntfControllerImpl(BusAttachment& busAttachment, RobotCleaningCyclePhaseIntfControllerListener& listener, HaeProxyBusObject& haeProxyObject);

    /**
     * Destructor of RobotCleaningCyclePhaseIntfControllerImpl
     */
    virtual ~RobotCleaningCyclePhaseIntfControllerImpl();

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
     * Get cycle phase
     * @param[in] context
     * @return status
     */
    QStatus GetCyclePhase(void* context);

    /**
     * Get supported cycle phases
     * @param[in] context
     * @return status
     */
    QStatus GetSupportedCyclePhases(void* context);

    /**
     * Get vendor phases description
     * @param[in] language tag
     * @param[in] context
     * @return status
     */
    virtual QStatus GetVendorPhasesDescription(const qcc::String& languageTag, void* context);

  private:
    RobotCleaningCyclePhaseIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void GetCyclePhasePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetSupportedCyclePhasesPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetVendorPhasesDescriptionReplyHandler(Message& message, void* context);

    BusAttachment& m_busAttachment;
    RobotCleaningCyclePhaseIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* ROBOTCLEANINGCYCLEPHASEINTFCONTROLLERIMPL_H_ */
