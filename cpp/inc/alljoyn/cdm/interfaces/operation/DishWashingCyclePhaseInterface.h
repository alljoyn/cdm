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

#ifndef DISHWASHINGCYCLEPHASEINTERFACE_H_
#define DISHWASHINGCYCLEPHASEINTERFACE_H_

#include <vector>
#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterface.h>

namespace ajn {
namespace services {

/**
 * DishWashingCyclePhase Interface class
 */
class DishWashingCyclePhaseInterface : public CdmInterface {
  public:

    typedef struct {
        uint8_t phase;
        qcc::String name;
        qcc::String description;
    }DishWashingPhaseDescriptor;

    typedef enum {
        DISH_WASHING_PHASE_UNAVAILABLE,
        DISH_WASHING_PHASE_PRE_WASH,
        DISH_WASHING_PHASE_WASH,
        DISH_WASHING_PHASE_RINSE,
        DISH_WASHING_PHASE_DRY
    }DishWashingCyclePhase;

    typedef std::vector<DishWashingCyclePhase> StandardCyclePhases;

    typedef std::vector<uint8_t> SupportedCyclePhases;
    typedef std::vector<DishWashingPhaseDescriptor> CyclePhaseDescriptions;

    static const StandardCyclePhases m_standardCyclePhases;
    /**
     * Constructor of DishWashingCyclePhase
     */
    DishWashingCyclePhaseInterface() {}

    /**
     * Destructor of DishWashingCyclePhase
     */
    virtual ~DishWashingCyclePhaseInterface() {}

    /**
     * Get Interface Type
     * @return interface type
     */
    const CdmInterfaceType GetInterfaceType() const { return DISH_WASHING_CYCLE_PHASE_INTERFACE; }

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

#endif /* DISHWASHINGCYCLEPHASEINTERFACE_H_ */