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

#ifndef BRIGHTNESSINTFCONTROLLEELISTENER_H_
#define BRIGHTNESSINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/common/CdmInterfaceErrors.h>
#include <alljoyn/cdm/controllee/InterfaceControlleeModel.h>

#include <alljoyn/cdm/controllee/CdmControlleeInterface.h>
#include <interfaces/common/operation/BrightnessInterface.h>

namespace ajn {
namespace services {

/**
 * Brightness Model Interface class for the Controllee
 */
class BrightnessIntfControlleeModel : public virtual InterfaceControlleeModel {
  public:

    /**
     * Destructor of BrightnessIntfControlleeModel
     */
    virtual ~BrightnessIntfControlleeModel() {}

    /**
     * Get Brightness
     * @return current brightness
     */
    virtual QStatus GetBrightness(double& out) const = 0;

     /**
     * Set Brightness
     * @param[in] value The brightness to set
     * @return ER_OK on success
     */
    virtual QStatus SetBrightness(const double value) = 0;

};

} //namespace services
} //namespace ajn

#endif /* BRIGHTNESSINTFCONTROLLEELISTENER_H_ */
