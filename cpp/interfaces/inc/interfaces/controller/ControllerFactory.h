/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
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
#include <string>

#include <alljoyn/cdm/common/CdmInterface.h>

namespace ajn {
class BusAttachment;
namespace services {

/**
 * Cdm Interface factory class.
 */
class ControllerFactory {
  public:
    /**
     * Get Instance of ControllerFactory - singleton implementation
     * @return instance
     */
    static ControllerFactory& Instance();

    /**
     * Destructor of ControllerFactory
     */
    ~ControllerFactory() {}

    /**
     * Initialize ControllerFactory
     * @param busAttachment
     * @return status
     */
    QStatus InitControllerFactory(BusAttachment* busAttachment);

    /**
     * Get CreateIntfControllerFptr
     * @param interface name
     * @return CreateIntfControllerFptr
     */
    CreateIntfControllerFptr GetCreateIntfControllerFptr(const std::string& ifaceName);

    /**
     * Create Interface for controller
     * @param type
     * @param listener
     * @param cdm proxy object
     * @return CdmInterface
     */
    Ref<CdmInterface> CreateIntfController(const std::string& interfaceName, Ref<InterfaceControllerListener> listener, Ref<ProxyBusObject> cdmProxyObject);

    /**
     * Register an interface for controller
     * @param interfaceName
     * @param CreateIntfControllerFptr
     */
    QStatus RegisterIntfController(const std::string& interfaceName, CreateIntfControllerFptr createIntfController);

    /**
     * Unregister an interface for controller
     * @param interfaceName
     * @param CreateIntfControllerFptr
     */
    QStatus UnregisterIntfController(const std::string& interfaceName, CreateIntfControllerFptr createIntfController);

  private:
    /**
     * Constructor of ControllerFactory
     */
    ControllerFactory();

    ControllerFactory(const ControllerFactory& src) = delete;
    ControllerFactory& operator=(const ControllerFactory& src) = delete;

    BusAttachment* m_busAttachment;
    std::map<std::string, CreateIntfControllerFptr> m_controllerCreators;
};

} //namespace services
} //namespace ajn

#endif /* INTERFACEFACTORY_H_ */