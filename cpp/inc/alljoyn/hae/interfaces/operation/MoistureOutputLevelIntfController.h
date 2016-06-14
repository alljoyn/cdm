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

#ifndef MOISTUREOUTPUTLEVELINTFCONTROLLER_H_
#define MOISTUREOUTPUTLEVELINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/hae/interfaces/operation/MoistureOutputLevelInterface.h>

namespace ajn {
namespace services {

/**
 * MoistureOutputLevel Interface Controller class
 */
class MoistureOutputLevelIntfController : public MoistureOutputLevelInterface {
  public:
    /**
     * Constructor of MoistureOutputLevelIntfController
     */
    MoistureOutputLevelIntfController() {}

    /**
     * Destructor of MoistureOutputLevelIntfController
     */
    virtual ~MoistureOutputLevelIntfController() {}

    /**
     * Get moisture output level
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetMoistureOutputLevel (void* context = NULL) = 0;

    /**
     * Set moisture output level
     * @param[in] value moisture output level
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetMoistureOutputLevel (const uint8_t value, void* context = NULL) = 0;

    /**
     * Get the maximum moisture output level
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetMaxMoistureOutputLevel (void* context = NULL) = 0;

    /**
     * Get auto mode
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetAutoMode (void* context = NULL) = 0;

    /**
     * Set auto mode
     * @param[in] autoMOde auto mode
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetAutoMode (const uint8_t autoMode, void* context = NULL) = 0;
};

} //namespace services
} //namespace ajn

#endif /* MOISTUREOUTPUTLEVELINTFCONTROLLER_H_ */
