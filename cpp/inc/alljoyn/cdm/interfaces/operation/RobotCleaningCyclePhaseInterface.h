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

#ifndef ROBOTCLEANINGCYCLEPHASEINTERFACE_H_
#define ROBOTCLEANINGCYCLEPHASEINTERFACE_H_

#include <vector>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterface.h>

namespace ajn {
namespace services {

/**
 * RobotCleaningCyclePhase Interface class
 */
class RobotCleaningCyclePhaseInterface : public CdmInterface {
  public:
    typedef std::vector<uint8_t> SupportedCyclePhases;
    /**
     * CyclePhaseDescriptor struct
     */
    typedef struct {
        uint8_t phase;
        qcc::String name;
        qcc::String description;
    } CyclePhaseDescriptor;
    typedef std::vector<CyclePhaseDescriptor> CyclePhaseDescriptors;

    /**
     * Constructor of RobotCleaningCyclePhase
     */
    RobotCleaningCyclePhaseInterface() {}

    /**
     * Destructor of RobotCleaningCyclePhase
     */
    virtual ~RobotCleaningCyclePhaseInterface() {}

    /**
     * Get Interface Type
     * @return interface type
     */
    const CdmInterfaceType GetInterfaceType() const { return ROBOT_CLEANING_CYCLE_PHASE_INTERFACE; }

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

    enum {
        ROBOT_CLEANING_CYCLE_PHASE_CLEANING = 0,
        ROBOT_CLEANING_CYCLE_PHASE_HOMING
    };

    enum {
        MIN_ROBOT_CLEANING_STANDARD_CYCLE_PHASE = ROBOT_CLEANING_CYCLE_PHASE_CLEANING,
        MAX_ROBOT_CLEANING_STANDARD_CYCLE_PHASE = ROBOT_CLEANING_CYCLE_PHASE_HOMING,
        MIN_ROBOT_CLEANING_VENDOR_DEFINED_CYCLE_PHASE = 0x80
    };

  protected:
    static const qcc::String s_prop_Version;
    static const qcc::String s_prop_CyclePhase;
    static const qcc::String s_prop_SupportedCyclePhases;
    static const qcc::String s_method_GetVendorPhasesDescription;

  private:
    static const qcc::String s_xml;
    static const uint16_t s_interfaceVersion;
};

} //namespace services
} //namespace ajn

#endif /* ROBOTCLEANINGCYCLEPHASEINTERFACE_H_ */