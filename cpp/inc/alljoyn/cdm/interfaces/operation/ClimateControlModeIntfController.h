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

#ifndef CLIMATECONTROLMODEINTFCONTROLLER_H_
#define CLIMATECONTROLMODEINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/ClimateControlModeInterface.h>

namespace ajn {
namespace services {

/**
 * ClimateControlMode Interface Controller class
 */
class ClimateControlModeIntfController : public ClimateControlModeInterface {
  public:
    /**
     * Constructor of ClimateControlModeIntfController
     */
    ClimateControlModeIntfController() {}

    /**
     * Destructor of ClimateControlModeIntfController
     */
    virtual ~ClimateControlModeIntfController() {}

    /**
     * Get Mode property
     * (Current mode of device.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetMode(void* context = NULL) = 0;

    /**
     * Set Mode property
     * (Current mode of device.)
     * @param[in] value The mode to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetMode(const Mode value, void* context = NULL) = 0;

    /**
     * Get SupportedModes property
     * (Array of supported modes.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetSupportedModes(void* context = NULL) = 0;

    /**
     * Get OperationalState property
     * (Current status of device.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetOperationalState(void* context = NULL) = 0;
};

typedef std::shared_ptr<ClimateControlModeIntfController> ClimateControlModeIntfControllerPtr;

} //namespace services
} //namespace ajn

#endif /* CLIMATECONTROLMODEINTFCONTROLLER_H_ */
