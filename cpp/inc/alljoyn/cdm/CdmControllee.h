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


#ifndef CDMCONTROLLEE_H_
#define CDMCONTROLLEE_H_

#include <alljoyn/Status.h>
#include <alljoyn/cdm/CdmTypes.h>
#include <alljoyn/cdm/CdmConfig.h>
#include <alljoyn/cdm/interfaces/CdmInterface.h>
#include <alljoyn/cdm/interfaces/CdmInterfaceTypes.h>

namespace ajn {

class BusAttachment;
class AuthListener;

namespace services {

class CdmInterface;
class InterfaceControlleeListener;
class CdmAboutData;
class CdmControlleeImpl;

/**
 * Cdm Controllee class.
 * Used to create cdm controllee device.
 */
class CdmControllee {
  public:
    /**
     * Constructor of CdmControllee
     * @param[in] bus bus attachment
     * @param[in] aboutData CDM About data
     */
    CdmControllee(
        BusAttachment& bus,
        Ref<CdmAnnouncer> announcer,
        Ref<CdmSecurity> security
        );

    /**
     * Destructor of CdmControllee
     */
    virtual ~CdmControllee();

    /**
     * Start controllee
     * @return ER_OK on success
     */
    QStatus Start();

    /**
     * Stop controllee
     * @return ER_OK on success
     */
    QStatus Stop();

    /**
     * Create interface
     * @param[in] type interface type
     * @param[in] objectPath the object path including the interface
     * @param[in] listener interface listener
     * @return Interface
     */
    CdmInterface* CreateInterface(const CdmInterfaceType type, const qcc::String& objectPath, InterfaceControlleeListener& listener);

    /**
     * Register vendor defined interface
     * @param[in] interfaceName interface name
     * @param[in] createIntfControllee interface creator function
     * @return CDM interface type
     */
    const CdmInterfaceType RegisterVendorDefinedInterface(const qcc::String& interfaceName, CreateIntfControlleeFptr createIntfControllee);

  private:
    CdmControlleeImpl* m_impl;

};

}
}

#endif // CDMCONTROLLEE_H_
