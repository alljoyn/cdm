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

#ifndef COLORINTFCONTROLLER_H_
#define COLORINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/ColorInterface.h>

namespace ajn {
namespace services {

/**
 * Color Interface Controller class
 */
class ColorIntfController : public ColorInterface {
  public:
    /**
     * Constructor of ColorIntfController
     */
    ColorIntfController() {}

    /**
     * Destructor of ColorIntfController
     */
    virtual ~ColorIntfController() {}

    /**
     * Get Hue property
     * (Hue of the device.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetHue(void* context = NULL) = 0;

    /**
     * Set Hue property
     * (Hue of the device.)
     * @param[in] value The hue to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetHue(const double value, void* context = NULL) = 0;

    /**
     * Get Saturation property
     * (Saturation of the device.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetSaturation(void* context = NULL) = 0;

    /**
     * Set Saturation property
     * (Saturation of the device.)
     * @param[in] value The saturation to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetSaturation(const double value, void* context = NULL) = 0;
};

typedef std::shared_ptr<ColorIntfController> ColorIntfControllerPtr;

} //namespace services
} //namespace ajn

#endif /* COLORINTFCONTROLLER_H_ */
