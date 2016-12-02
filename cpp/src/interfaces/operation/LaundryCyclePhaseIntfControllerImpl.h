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

/**
 * LaundryCyclePhase Interface Controller implementation class
 */
class LaundryCyclePhaseIntfControllerImpl : public InterfaceController, public LaundryCyclePhaseIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, ProxyBusObject& ProxyBusObject);

    /**
     * Constructor of LaundryCyclePhaseIntfControllerImpl
     */
    LaundryCyclePhaseIntfControllerImpl(BusAttachment& busAttachment, LaundryCyclePhaseIntfControllerListener& listener, ProxyBusObject& ProxyBusObject);

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
     * Get CyclePhase property
     * (Current cycle phase. Range value [0x00-0x7F] is for standard phases; range value [0x80-0xFF] is for vendor-defined phases and so the meanings depend on manufacturer.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetCyclePhase(void* context);

    /**
     * Get SupportedCyclePhases property
     * (List of supported cycle phases.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetSupportedCyclePhases(void* context);

    /**
     * Call GetVendorPhasesDescription method
     * (Get cycle phases description.)
     * @param[in] languageTag Preferred language to be used in selecting the output strings.
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetVendorPhasesDescription(const qcc::String& languageTag, void* context);

  private:
    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void GetCyclePhasePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetSupportedCyclePhasesPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetVendorPhasesDescriptionReplyHandler(Message& message, void* context);

    BusAttachment& m_busAttachment;
    LaundryCyclePhaseIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* LAUNDRYCYCLEPHASEINTFCONTROLLERIMPL_H_ */
