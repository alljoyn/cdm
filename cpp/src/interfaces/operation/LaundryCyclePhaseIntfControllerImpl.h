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

#ifndef LAUNDRYCYCLEPHASEINTFCONTROLLERIMPL_H_
#define LAUNDRYCYCLEPHASEINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/LaundryCyclePhaseIntfController.h>

namespace ajn {
namespace services {

class LaundryCyclePhaseIntfControllerListener;
class CdmProxyBusObject;

/**
 * LaundryCyclePhase Interface Controller implementation class
 */
class LaundryCyclePhaseIntfControllerImpl : public InterfaceController, public LaundryCyclePhaseIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of LaundryCyclePhaseIntfControllerImpl
     */
    LaundryCyclePhaseIntfControllerImpl(BusAttachment& busAttachment, LaundryCyclePhaseIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of LaundryCyclePhaseIntfControllerImpl
     */
    virtual ~LaundryCyclePhaseIntfControllerImpl();

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
     * Get current cycle phase
     * @param[in] context
     * @return status
     */
    virtual QStatus GetCyclePhase(void* context);

    /**
     * Get list of supported cycle phases
     * @param[in] context
     * @return status
     */
    virtual QStatus GetSupportedCyclePhases(void* context );

    /**
     * Get vedor defined cycles descriptions
     * @param[in] context
     * @return status
     */
    virtual QStatus GetCyclePhasesDescriptions(const qcc::String& language, void* context);

  private:
    LaundryCyclePhaseIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);

    void GetCyclePhasePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetSupportedCyclePhasesPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetCyclePhasesDescriptionReplyHandler(Message& message, void* context);

    BusAttachment& m_busAttachment;
    LaundryCyclePhaseIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* LAUNDRYCYCLEPHASEINTFCONTROLLERIMPL_H_ */
