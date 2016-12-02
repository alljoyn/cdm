/******************************************************************************
 *  * 
 *    Copyright (c) 2016 Open Connectivity Foundation and AllJoyn Open
 *    Source Project Contributors and others.
 *    
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0

 ******************************************************************************/

#ifndef LAUNDRYCYCLEPHASEINTERFACE_H_
#define LAUNDRYCYCLEPHASEINTERFACE_H_

#include <vector>
#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterface.h>

namespace ajn {
namespace services {

/**
 * LaundryCyclePhase Interface class
 */
class LaundryCyclePhaseInterface : public CdmInterface {
  public:
    typedef struct {
        uint8_t phase;
        qcc::String name;
        qcc::String description;
    }LaundryPhaseDescriptor;

    typedef enum {
        LAUNDRY_PHASE_UNAVAILABLE,
        LAUNDRY_PHASE_PRE_WASHING,
        LAUNDRY_PHASE_WASHING,
        LAUNDRY_PHASE_RINSING,
        LAUNDRY_PHASE_SPINNING,
        LAUNDRY_PHASE_STEAM,
        LAUNDRY_PHASE_DRYING,
        LAUNDRY_PHASE_COOLING,
        LAUNDRY_PHASE_ANTICREASING
    }LaundryCyclePhase;

    typedef std::vector<LaundryCyclePhase> StandardCyclePhases;

    typedef std::vector<uint8_t> SupportedCyclePhases;
    typedef std::vector<LaundryPhaseDescriptor> CyclePhaseDescriptions;

    static const StandardCyclePhases m_standardCyclePhases;
    /**
     * Constructor of LaundryCyclePhase
     */
    LaundryCyclePhaseInterface() {}

    /**
     * Destructor of LaundryCyclePhase
     */
    virtual ~LaundryCyclePhaseInterface() {}

    /**
     * Get Interface Type
     * @return interface type
     */
    const CdmInterfaceType GetInterfaceType() const { return LAUNDRY_CYCLE_PHASE_INTERFACE; }

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
    static const qcc::String s_prop_CyclePhase;
    static const qcc::String s_prop_SupportedCyclePhases;
    static const qcc::String s_method_GetVendorPhasesDescription;


  private:
    static const qcc::String s_xml;
    static const uint16_t s_interfaceVersion;
};

} //namespace services
} //namespace ajn

#endif /* LAUNDRYCYCLEPHASEINTERFACE_H_ */