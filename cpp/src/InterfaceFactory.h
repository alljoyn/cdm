/******************************************************************************
 *  * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#ifndef INTERFACEFACTORY_H_
#define INTERFACEFACTORY_H_

#include <map>
#include <qcc/String.h>

#include <alljoyn/cdm/interfaces/CdmInterface.h>
#include <alljoyn/cdm/interfaces/CdmInterfaceListener.h>

namespace ajn {
class BusAttachment;
namespace services {

/**
 * Cdm Interface factory class.
 */
class InterfaceFactory {
  public:
    /**
     * Get Instance of InterfaceFactory - singleton implementation
     * @return instance
     */
    static InterfaceFactory* GetInstance();

    /**
     * Destructor of InterfaceFactory
     */
    ~InterfaceFactory() {}

    /**
     * Initialize InterfaceFactory
     * @param busAttachment
     * @return status
     */
    QStatus InitInterfaceFactory(BusAttachment* busAttachment);

    /**
     * Get CreateIntfControlleeFptr
     * @param interface type
     * @return CreateIntfControlleeFptr
     */
    CreateIntfControlleeFptr GetCreateIntfControlleeFptr(const CdmInterfaceType type);

    /**
     * Get CreateIntfControllerFptr
     * @param interface type
     * @return CreateIntfControllerFptr
     */
    CreateIntfControllerFptr GetCreateIntfControllerFptr(const CdmInterfaceType type);

    /**
     * Create Interface for controllee
     * @param type
     * @param listener
     * @param cdm bus object
     * @return CdmInterface
     */
    CdmInterface* CreateIntfControllee(const CdmInterfaceType type, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Create Interface for controller
     * @param type
     * @param listener
     * @param cdm proxy object
     * @return CdmInterface
     */
    CdmInterface* CreateIntfController(const CdmInterfaceType type, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Register vendor defined interface for controllee
     * @param interfaceName
     * @param CreateIntfControlleeFptr
     */
    void RegisterVendorDefinedIntfControllee(const CdmInterfaceType type, CreateIntfControlleeFptr createIntfControllee);

    /**
     * Register vendor defined interface for controller
     * @param interfaceName
     * @param CreateIntfControllerFptr
     */
    void RegisterVendorDefinedIntfController(const CdmInterfaceType type, CreateIntfControllerFptr createIntfController);

  private:
    /**
     * Constructor of InterfaceFactory
     */
    InterfaceFactory();

    /**
     * Copy constructor of InterfaceFactory
     */
    InterfaceFactory(const InterfaceFactory& src);


    /**
     * Assignment operator of InterfaceFactory
     * @param src
     * @return InterfaceFactory
     */
    InterfaceFactory& operator=(const InterfaceFactory& src);

    /**
     * Instance variable - InterfaceFactory is a signleton
     */
    static InterfaceFactory* s_instance;

    BusAttachment* m_busAttachment;
    std::map<CdmInterfaceType, CreateIntfControllerFptr> m_controllerCreators;
    std::map<CdmInterfaceType, CreateIntfControlleeFptr> m_controlleeCreators;
};

} //namespace services
} //namespace ajn

#endif /* INTERFACEFACTORY_H_ */