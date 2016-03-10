/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#ifndef LAUNDRYCYCLEPHASEINTERFACE_H_
#define LAUNDRYCYCLEPHASEINTERFACE_H_

#include <vector>
#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/hae/interfaces/HaeInterface.h>

namespace ajn {
namespace services {

/**
 * LaundryCyclePhase Interface class
 */
class LaundryCyclePhaseInterface : public HaeInterface {
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
    const HaeInterfaceType GetInterfaceType() const { return LAUNDRY_CYCLE_PHASE_INTERFACE; }

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
