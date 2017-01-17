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

// This file is automatically generated. Do not edit it.

#ifndef LANGUAGEDISPLAYINTFCONTROLLERLISTENER_H_
#define LANGUAGEDISPLAYINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/controller/InterfaceControllerListener.h>
#include <interfaces/common/userinterfacesettings/LanguageDisplayInterface.h>

namespace ajn {
namespace services {

/**
 * LanguageDisplay Interface Controller Listener class
 */
class LanguageDisplayIntfControllerListener : public InterfaceControllerListener {
  public:

    /**
     * Destructor of LanguageDisplayIntfControllerListener
     */
    virtual ~LanguageDisplayIntfControllerListener() {}

    /**
     * Callback handler for GetDisplayLanguage completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of DisplayLanguage
     *                  (The RFC 5646 tag of the current language being used by the device user interface)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetDisplayLanguage(QStatus status, const qcc::String& objectPath, const qcc::String& value, void* context) {}

    /**
     * Handler for DisplayLanguage property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of DisplayLanguage
     *                  (The RFC 5646 tag of the current language being used by the device user interface)
     */
    virtual void OnDisplayLanguageChanged(const qcc::String& objectPath, const qcc::String& value) {}

    /**
     * Callback handler for SetDisplayLanguage completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetDisplayLanguage(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for GetSupportedDisplayLanguages completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of SupportedDisplayLanguages
     *                  (The list of supported languages using RFC 5646 tags)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetSupportedDisplayLanguages(QStatus status, const qcc::String& objectPath, const std::vector<qcc::String>& value, void* context) {}

    /**
     * Handler for SupportedDisplayLanguages property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of SupportedDisplayLanguages
     *                  (The list of supported languages using RFC 5646 tags)
     */
    virtual void OnSupportedDisplayLanguagesChanged(const qcc::String& objectPath, const std::vector<qcc::String>& value) {}
};

} //namespace services
} //namespace ajn

#endif /* LANGUAGEDISPLAYINTFCONTROLLERLISTENER_H_ */
