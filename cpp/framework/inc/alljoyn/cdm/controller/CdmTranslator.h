/******************************************************************************
 * 
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

#ifndef CDMTRANSLATOR_H_
#define CDMTRANSLATOR_H_

#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/common/CdmInterface.h>
#include <alljoyn/cdm/controller/InterfaceControllerListener.h>
#include <unordered_set>

namespace ajn {
namespace services {
class DeviceInfo;

/**
 * Function pointer that is used inside CDM to setup translators for new devices
 * When a device is found, these methods will be ran to allow a translator module to query the device and call RegisterTranslator() on the device info class
 */
typedef void (*CdmTranslatorAttachFunc)(BusAttachment& busAttachment, Ref<DeviceInfo> deviceInfo);

/**
 * This is a translator instance for a specific bus path and device
 */
class CdmTranslator {
public:
    virtual ~CdmTranslator() {}

    /**
     * Get a list of translated interfaces for this bus path
     * (These will be CDM interfaces)
     * @return unordered set of interface names
     */
    virtual const std::unordered_set<std::string>& GetInterfaces() = 0;

    /**
     * Create a CDM Interface Controller class for the interface on this bus path. Also and register the listener so async events can be processed
     * @return New CdmInterface specific to the interface type, or NULL on failure
     */
    virtual Ref<CdmInterface> CreateInterface(const std::string& ifaceName, Ref<InterfaceControllerListener> listener, Ref<ProxyBusObject> pbo) = 0;
};

} //namespace services
} //namespace ajn

#endif //CDMTRANSLATOR_H_
