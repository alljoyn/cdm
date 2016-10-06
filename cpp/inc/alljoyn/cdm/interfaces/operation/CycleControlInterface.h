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
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#ifndef CYCLECONTROLINTERFACE_H_
#define CYCLECONTROLINTERFACE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <vector>
#include <alljoyn/cdm/interfaces/CdmInterface.h>

namespace ajn {
namespace services {
/**
 * CycleControl Interface class
 */
class CycleControlInterface : public CdmInterface {
  public:
    typedef enum
    {
        OPERATIONAL_STATE_IDLE,
        OPERATIONAL_STATE_WORKING,
        OPERATIONAL_STATE_READY_TO_START,
        OPERATIONAL_STATE_DELAYED_START,
        OPERATIONAL_STATE_PAUSED,
        OPERATIONAL_STATE_END_OF_CYCLE
    } CycleControlOperationalState;

    typedef enum
    {
        OPERATIONAL_COMMAND_START,
        OPERATIONAL_COMMAND_STOP,
        OPERATIONAL_COMMAND_PAUSE,
        OPERATIONAL_COMMAND_RESUME
    }CycleControlOperationalCommand;

    static const qcc::String OPERATIONAL_STATE_STRINGS[6];
    static const qcc::String OPERATIONAL_COMMAND_STRINGS[4];

    typedef std::vector<CycleControlOperationalCommand> SupportedOperationalCommands;
    typedef std::vector<CycleControlOperationalState> SupportedOperationalStates;

    /**
     * Constructor of CycleControl
     */
    CycleControlInterface() {}

    /**
     * Destructor of CycleControl
     */
    virtual ~CycleControlInterface() {}

    /**
     * Get Interface Type
     * @return interface type
     */
    const CdmInterfaceType GetInterfaceType() const { return CYCLE_CONTROL_INTERFACE; }

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

  protected:
    static const qcc::String s_prop_Version;
    static const qcc::String s_prop_OperationalState;
    static const qcc::String s_prop_SupportedOperationalCommands;
    static const qcc::String s_prop_SupportedOperationalStates;
    static const qcc::String s_method_ExecuteCommand;
  private:
    static const qcc::String s_xml;
    static const uint16_t s_interfaceVersion;
};

} //namespace services
} //namespace ajn

#endif /* CYCLECONTROLINTERFACE_H_ */