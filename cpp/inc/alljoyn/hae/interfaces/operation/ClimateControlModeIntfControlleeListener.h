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

#ifndef CLIMATECONTROLMODEINTFCONTROLLEELISTENER_H_
#define CLIMATECONTROLMODEINTFCONTROLLEELISTENER_H_

#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/hae/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * ClimateControlMode interface controllee listener class
 */
class ClimateControlModeIntfControlleeListener : public InterfaceControlleeListener {
  public:
    typedef std::vector<uint16_t> SupportedModes;

    /**
     * Destructor of ClimateControlModeIntfControlleeListener
     */
    virtual ~ClimateControlModeIntfControlleeListener() {}

    /**
     * Handler for setting mode
     * @param[in] mode mode
     * @return ER_OK on success
     */
    virtual QStatus OnSetMode(const uint16_t& mode) = 0;

    /**
     * Handler for getting mode
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] mode mode
     * @return ER_OK on success
     */
    virtual QStatus OnGetMode(uint16_t& mode) = 0;

    /**
     * Handler for getting supported modes
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] modes supported modes
     * @return ER_OK on success
     */
    virtual QStatus OnGetSupportedModes(SupportedModes& modes) = 0;

    /**
     * Handler for getting operating state
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] operatingState operating state
     * @return ER_OK on success
     */
    virtual QStatus OnGetOperatingState(uint16_t& operatingState) = 0;
};

} //namespace services
} //namespace ajn

#endif /* CLIMATECONTROLMODEINTFCONTROLLEELISTENER_H_ */
