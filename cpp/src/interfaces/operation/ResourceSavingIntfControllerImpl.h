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

#ifndef RESOURCESAVINGINTFCONTROLLERIMPL_H_
#define RESOURCESAVINGINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/ResourceSavingIntfController.h>

namespace ajn {
namespace services {

class ResourceSavingIntfControllerListener;
class CdmProxyBusObject;

/**
 * ResourceSaving Interface Controller implementation class
 */
class ResourceSavingIntfControllerImpl : public InterfaceController, public ResourceSavingIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyBusObject);

    /**
     * Constructor of ResourceSavingIntfControllerImpl
     */
    ResourceSavingIntfControllerImpl(BusAttachment& busAttachment, ResourceSavingIntfControllerListener& listener, CdmProxyBusObject& cdmProxyBusObject);

    /**
     * Destructor of ResourceSavingIntfControllerImpl
     */
    virtual ~ResourceSavingIntfControllerImpl();

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
     * Get ResourceSavingMode property
     * (The current resource saving mode of the device; true if device in saving mode.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetResourceSavingMode(void* context);

    /**
     * Set ResourceSavingMode property
     * (The current resource saving mode of the device; true if device in saving mode.)
     * @param[in] value The resource saving mode to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetResourceSavingMode(const bool value, void* context);

  private:
    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void GetResourceSavingModePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetResourceSavingModePropertyCB(QStatus status, ProxyBusObject* obj, void* context);

    BusAttachment& m_busAttachment;
    ResourceSavingIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* RESOURCESAVINGINTFCONTROLLERIMPL_H_ */
