/******************************************************************************
 *  *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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


#ifndef CDM_SYSTEM_H_
#define CDM_SYSTEM_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/common/CdmTypes.h>

namespace ajn {
namespace services {
//======================================================================

/**
 * Class for launching an alternative router.
 */
class RouterLauncher
{
public:
    virtual ~RouterLauncher() {}

    virtual QStatus Start();

    /**
     * Tell the router to start stopping.
     */
    virtual QStatus Stop();

    /**
     * Wait for any threads in the router to stop.
     */
    virtual void Join() {}
};



class CdmSystem
{
  public:

    /**
     * Constructor
     */
    CdmSystem(const qcc::String& appName);

    ~CdmSystem();

    /**
     * Call this before starting the app to control the
     * receiving of messages from remote devices.
     * The default is true.
     */
    CdmSystem& SetAllowRemoteMessages(bool allow);

    /**
     * Set the router to be used.  If none is set then
     * the BundledRouter will be used. This can only be
     * set if the app has not been started.
     */
    CdmSystem& SetRouter(Ref<RouterLauncher> router);

    /**
     * Set the 'about' data in XML format.
     */
    CdmSystem& SetAboutData(const qcc::String& xml);

    /**
     * @return the bus attachment object. This is only available
     * after starting the app.
     */
    BusAttachment& GetBusAttachment();

    /**
     * Start up Alljoyn.
     */
    QStatus Start();

    /**
     * Stop Alljoyn.
     */
    QStatus Stop();

  private:
    class Impl;

    Impl* m_impl;
};

//======================================================================
} // namespace services
} // namespace ajn

#endif // CDM_SYSTEM_H_