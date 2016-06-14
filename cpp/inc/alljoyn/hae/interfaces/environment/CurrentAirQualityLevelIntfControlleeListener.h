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

#ifndef CURRENTAIRQUALITYLEVELINTFCONTROLLEELISTENER_H_
#define CURRENTAIRQUALITYLEVELINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/hae/interfaces/HaeInterfaceErrors.h>
#include <alljoyn/hae/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * CurrentAirQualityLevel Interface Controllee Listener class
 */
class CurrentAirQualityLevelIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of CurrentAirQualityLevelIntfControlleeListener
     */
    virtual ~CurrentAirQualityLevelIntfControlleeListener() {}

    /**
     * Handler for getting the contatminant type
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] type the contaminant type
     * @return ER_OK on success
     */
    virtual QStatus OnGetContaminantType(uint8_t& type) = 0;

    /**
     * Handler for getting current air quality level
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyLevel is true.
     * @param[out] value the air quality level
     * @return ER_OK on success
     */
    virtual QStatus OnGetCurrentLevel(uint8_t& value) = 0;

    /**
     * Handler for getting the maximum level of air quality
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyLevel is true.
     * @param[out] value the maximum level of air quality
     * @return ER_OK on success
     */
    virtual QStatus OnGetMaxLevel(uint8_t& value) = 0;

};

} //namespace services
} //namespace ajn

#endif /* CURRENTAIRQUALITYLEVELINTFCONTROLLEELISTENER_H_ */
