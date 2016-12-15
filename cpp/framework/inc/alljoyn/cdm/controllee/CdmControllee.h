/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/


#ifndef CDMCONTROLLEE_H_
#define CDMCONTROLLEE_H_

#include <alljoyn/Status.h>
#include <alljoyn/cdm/common/CdmTypes.h>
#include <alljoyn/cdm/common/CdmConfig.h>
#include <alljoyn/cdm/common/CdmInterface.h>
#include <alljoyn/cdm/common/CdmInterfaceTypes.h>

namespace ajn {

class BusAttachment;
class AuthListener;

namespace services {

class CdmControlleeInterface;
class InterfaceControlleeModel;
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
     */
    CdmControllee(BusAttachment& bus);

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
     * Gets a CdmBusObject for the specified bus path
     * @param[in] busPath the bus path of the CdmBusObject
     * @return Shared ptr to the CdmBusObject
     */
    Ref<CdmBusObject> GetCdmBusObject(const qcc::String& busPath);

    template<typename InterfaceType>
    Ref<InterfaceType> GetInterface(const qcc::String& busPath, const qcc::String& interfaceName)
    {
        Ref<CdmControlleeInterface> interface = GetCdmControlleeInterface(busPath, interfaceName);
        return (interface) ? std::dynamic_pointer_cast<InterfaceType>(interface) : Ref<InterfaceType>();
    }

    template<typename InterfaceType>
    QStatus CreateInterface(Ref<InterfaceControlleeModel> model, const qcc::String& busPath)
    {
        Ref<CdmBusObject> busObject = GetCdmBusObject(busPath);
        BusAttachment& bus = GetBusAttachment();
        Ref<InterfaceType> interface = mkRef<InterfaceType>(bus, model, *busObject);
        if (interface)
        {
            RegisterCdmControlleeInterface(busPath, interface->GetInterfaceName(), interface);
            return ER_OK;
        }
        return ER_FAIL;
    }

 private:
    BusAttachment& GetBusAttachment() const;
    void RegisterCdmControlleeInterface(const qcc::String& busPath, const qcc::String& interfaceName, Ref<CdmControlleeInterface> interface);
    Ref<CdmControlleeInterface> GetCdmControlleeInterface(const qcc::String& busPath, const qcc::String& interfaceName) const;

    CdmControlleeImpl* m_impl;
};

}
}

#endif // CDMCONTROLLEE_H_