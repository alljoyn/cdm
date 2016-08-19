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

#ifndef MOISTUREOUTPUTLEVELINTFCONTROLLEELISTENER_H_
#define MOISTUREOUTPUTLEVELINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * MoistureOutputLevel interface controllee listener class
 */
class MoistureOutputLevelIntfControlleeListener : public InterfaceControlleeListener {
  public:

    /**
     * Destructor of MoistureOutputLevelIntfControlleeListener
     */
    virtual ~MoistureOutputLevelIntfControlleeListener() {}

    /**
     * Handler for setting moisture output level
     * @param[in] value moisture output level
     * @return ER_OK on success
     */
    virtual QStatus OnSetMoistureOutputLevel(const uint8_t& value) = 0;

    /**
     * Handler for getting moisture output level
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value moisture output level
     * @return ER_OK on success
     */
    virtual QStatus OnGetMoistureOutputLevel(uint8_t& value) = 0;

    /**
     * Handler for getting the maximum moisture output level
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value the maximum moisture output level
     * @return ER_OK on success
     */
    virtual QStatus OnGetMaxMoistureOutputLevel(uint8_t& value) = 0;

    /**
     * Handler for setting auto mode
     * @param[in] autoMode auto mode
     * @return ER_OK on success
     */
    virtual QStatus OnSetAutoMode(const uint8_t& autoMode) = 0;

    /**
     * Handler for getting auto mode
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value auto mode
     * @return ER_OK on success
     */
    virtual QStatus OnGetAutoMode(uint8_t& value) = 0;
};

} //namespace services
} //namespace ajn




#endif /* MOISTUREOUTPUTLEVELINTFCONTROLLEELISTENER_H_ */
