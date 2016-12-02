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

// This file is automatically generated. Do not edit it.

#ifndef COLORTEMPERATUREINTFCONTROLLEELISTENER_H_
#define COLORTEMPERATUREINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/common/CdmInterfaceErrors.h>
#include <alljoyn/cdm/controllee/InterfaceControlleeModel.h>

#include <alljoyn/cdm/controllee/CdmControlleeInterface.h>
#include <alljoyn/cdm/controllee/CdmControllee.h>
#include <interfaces/common/operation/ColorTemperatureInterface.h>

namespace ajn {
namespace services {

/**
 * ColorTemperature Model Interface class for the Controllee
 */
class ColorTemperatureIntfControlleeModel : public virtual InterfaceControlleeModel {
  public:

    /**
     * Destructor of ColorTemperatureIntfControlleeModel
     */
    virtual ~ColorTemperatureIntfControlleeModel() {}

    /**
     * Get Temperature
     * @return current temperature
     */
    virtual QStatus GetTemperature(double& out) const = 0;

     /**
     * Set Temperature
     * @param[in] value The temperature to set
     * @return ER_OK on success
     */
    virtual QStatus SetTemperature(const double value) = 0;
    /**
     * Get MinTemperature
     * @return current min temperature
     */
    virtual QStatus GetMinTemperature(double& out) const = 0;
    /**
     * Get MaxTemperature
     * @return current max temperature
     */
    virtual QStatus GetMaxTemperature(double& out) const = 0;

};

} //namespace services
} //namespace ajn

#endif /* COLORTEMPERATUREINTFCONTROLLEELISTENER_H_ */
