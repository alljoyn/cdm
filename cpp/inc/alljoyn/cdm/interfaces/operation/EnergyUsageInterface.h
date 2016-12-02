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

#ifndef ENERGYUSAGEINTERFACE_H_
#define ENERGYUSAGEINTERFACE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterface.h>

namespace ajn {
namespace services {

/**
 * EnergyUsage Interface class
 */
class EnergyUsageInterface : public CdmInterface {
  public:
    /**
     * Constructor of EnergyUsage
     */
    EnergyUsageInterface() {}

    /**
     * Destructor of EnergyUsage
     */
    virtual ~EnergyUsageInterface() {}

    /**
     * Get Interface Type
     * @return interface type
     */
    const CdmInterfaceType GetInterfaceType() const { return ENERGY_USAGE_INTERFACE; }

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
    static const qcc::String s_prop_CumulativeEnergy;
    static const qcc::String s_prop_Precision;
    static const qcc::String s_prop_UpdateMinTime;
    static const qcc::String s_method_ResetCumulativeEnergy;

  private:
    static const qcc::String s_xml;
    static const uint16_t s_interfaceVersion;
};

} //namespace services
} //namespace ajn

#endif /* ENERGYUSAGEINTERFACE_H_ */