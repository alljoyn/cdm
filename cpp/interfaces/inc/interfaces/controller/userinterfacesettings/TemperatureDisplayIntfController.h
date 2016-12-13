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

// This file is automatically generated. Do not edit it.

#ifndef TEMPERATUREDISPLAYINTFCONTROLLER_H_
#define TEMPERATUREDISPLAYINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/common/CdmTypes.h>
#include <interfaces/common/userinterfacesettings/TemperatureDisplayInterface.h>

namespace ajn {
namespace services {

/**
 * TemperatureDisplay Interface Controller class
 */
class TemperatureDisplayIntfController : public TemperatureDisplayInterface {
  public:
    /**
     * The LSF translater inherits and redefines this class.
     * Also std:make_shared needs this to be public.
     */
    TemperatureDisplayIntfController(
        BusAttachment& busAttachment,
        Ref<InterfaceControllerListener> listener,
        Ref<ProxyBusObject> cdmProxyObject
        );

    /**
     * Destructor of TemperatureDisplayIntfController
     */
    virtual ~TemperatureDisplayIntfController();

    /**
     * Create interface
     */
    static Ref<CdmInterface> CreateInterface(BusAttachment& busAttachment, Ref<InterfaceControllerListener> listener, Ref<ProxyBusObject> ProxyBusObject);

    /**
     * Initialize interface
     * @return status
     */
    virtual QStatus Init() override;

    virtual BusAttachment& GetBusAttachment() const override;



    /**
     * Get DisplayTemperatureUnit property
     * (The unit being used to display temperature (0=C, 1=F, 2 =K))
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetDisplayTemperatureUnit(void* context = NULL);

    /**
     * Set DisplayTemperatureUnit property
     * (The unit being used to display temperature (0=C, 1=F, 2 =K))
     * @param[in] value The display temperature unit to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetDisplayTemperatureUnit(const uint8_t value, void* context = NULL);

    /**
     * Get SupportedDisplayTemperatureUnits property
     * (List of supported temperature units)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetSupportedDisplayTemperatureUnits(void* context = NULL);

  private:

    class Impl;

    Impl* m_impl;
};

} //namespace services
} //namespace ajn

#endif /* TEMPERATUREDISPLAYINTFCONTROLLER_H_ */
