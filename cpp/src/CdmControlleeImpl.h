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


#ifndef CDMCONTROLLEEIMPL_H_
#define CDMCONTROLLEEIMPL_H_

#include <map>
#include <atomic>

#include <alljoyn/Status.h>
#include <alljoyn/AboutObj.h>
#include <alljoyn/cdm/CdmTypes.h>
#include <alljoyn/cdm/interfaces/CdmInterface.h>
#include <alljoyn/cdm/interfaces/CdmInterfaceTypes.h>

namespace ajn {

namespace services {

class CdmInterface;
class InterfaceControlleeListener;
class CdmAboutData;
class CdmBusObject;
class CdmBusListener;

/**
 * Cdm ControlleeImpl class.
 * Used to create cdm controllee device.
 */
class CdmControlleeImpl {
  public:
    /**
     * Constructor of CdmControlleeImpl
     */
    CdmControlleeImpl(
        BusAttachment& bus,
        Ref<CdmAnnouncer> announcer,
        Ref<CdmSecurity> security
        );

    /**
     * Destructor of CdmControlleeImpl
     */
    ~CdmControlleeImpl();

    /**
     * Start controllee
     * @return status
     * @todo
     */
    QStatus Start();

    /**
     * Stop controllee
     * @return status
     * @todo
     */
    QStatus Stop();

    /**
     * Create interface
     * @param[in] type
     * @param[in] objectPath
     * @param[in] listener
     * @return interface
     */
    CdmInterface* CreateInterface(const CdmInterfaceType type, const qcc::String& objectPath, InterfaceControlleeListener& listener);

    /**
     * Register vendor defined interface
     * @param[in] interfaceName
     * @param[in] creator
     * @return CdmInterfaceType
     */
    const CdmInterfaceType RegisterVendorDefinedInterface(const qcc::String& interfaceName, CreateIntfControlleeFptr createIntfControllee);

  private:
    /**
     * Register Cdm Bus object
     * @return status
     * @todo
     */
    QStatus RegisterBusObject();


    /**
     * Register Cdm Bus listener
     * @return status
     */
    QStatus RegisterBusListener();

    /**
     * Unregister Cdm Bus listener
     * @return status
     */
    QStatus UnregisterBusListener();

    /**
     * Check device type validation in about custom fields
     * @return status
     */
    QStatus CheckAboutDeviceTypeValidation();

    BusAttachment& m_bus;
    Ref<CdmAnnouncer> m_announcer;
    Ref<CdmSecurity> m_security;
    std::map<qcc::String, Ref<CdmBusObject>> m_cdmBusObjectsMap;
    CdmBusListener* m_cdmBusListener;
    std::atomic_bool m_isStarted;
};

}
}

#endif  // CDMCONTROLLEEIMPL_H_
