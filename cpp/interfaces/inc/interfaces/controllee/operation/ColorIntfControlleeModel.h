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

#ifndef COLORINTFCONTROLLEELISTENER_H_
#define COLORINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/common/CdmInterfaceErrors.h>
#include <alljoyn/cdm/controllee/InterfaceControlleeModel.h>

#include <alljoyn/cdm/controllee/CdmControlleeInterface.h>
#include <interfaces/common/operation/ColorInterface.h>

namespace ajn {
namespace services {

/**
 * Color Model Interface class for the Controllee
 */
class ColorIntfControlleeModel : public virtual InterfaceControlleeModel {
  public:

    /**
     * Destructor of ColorIntfControlleeModel
     */
    virtual ~ColorIntfControlleeModel() {}

    /**
     * Get Hue
     * @return current hue
     */
    virtual QStatus GetHue(double& out) const = 0;

     /**
     * Set Hue
     * @param[in] value The hue to set
     * @return ER_OK on success
     */
    virtual QStatus SetHue(const double value) = 0;
    /**
     * Get Saturation
     * @return current saturation
     */
    virtual QStatus GetSaturation(double& out) const = 0;

     /**
     * Set Saturation
     * @param[in] value The saturation to set
     * @return ER_OK on success
     */
    virtual QStatus SetSaturation(const double value) = 0;

};

} //namespace services
} //namespace ajn

#endif /* COLORINTFCONTROLLEELISTENER_H_ */