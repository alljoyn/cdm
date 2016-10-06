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

#ifndef TIMERINTERFACE_H_
#define TIMERINTERFACE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterface.h>

namespace ajn {
namespace services {

/**
 * Timer Interface class
 */
class TimerInterface : public CdmInterface {
  public:
    /**
     * Constructor of Timer
     */
    TimerInterface() {}

    /**
     * Destructor of Timer
     */
    virtual ~TimerInterface() {}

    /**
     * Get Interface Type
     * @return interface type
     */
    const CdmInterfaceType GetInterfaceType() const { return TIMER_INTERFACE; }

    /**
     * Get Introspection Xml
     * @return xml
     */
    virtual const qcc::String& GetIntrospectionXml() { return s_xml; }

    /**
     * Get Interface version
     * @return interface version
     */
    virtual const uint16_t GetInterfaceVersion() const { return s_interfaceVersion; }

    static const int32_t TIMER_FEATURE_NOT_APPLIED = 0x80000000;
    static const int32_t TIMER_NOT_SUPPORTED       = 0x80000001;

  protected:
    static const qcc::String s_prop_Version;
    static const qcc::String s_prop_ReferenceTimer;
    static const qcc::String s_prop_TargetTimeToStart;
    static const qcc::String s_prop_TargetTimeToStop;
    static const qcc::String s_prop_EstimatedTimeToEnd;
    static const qcc::String s_prop_RunningTime;
    static const qcc::String s_prop_TargetDuration;

    static const qcc::String s_method_SetTargetTimeToStart;
    static const qcc::String s_method_SetTargetTimeToStop;


  private:
    static const qcc::String s_xml;
    static const uint16_t s_interfaceVersion;
};

} //namespace services
} //namespace ajn

#endif /* TIMERINTERFACE_H_ */