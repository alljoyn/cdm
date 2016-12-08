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

#ifndef TARGETTEMPERATUREINTFCONTROLLEE_H_
#define TARGETTEMPERATUREINTFCONTROLLEE_H_

#include <memory>

#include <qcc/String.h>
#include <alljoyn/Status.h>

#include <alljoyn/cdm/util/CdmMsgCvt.h>
#include <alljoyn/cdm/controllee/CdmControlleeInterface.h>
#include <interfaces/common/environment/TargetTemperatureInterface.h>

namespace ajn {

class BusAttachment;

namespace services {

class IntefaceControlleeModel;
class CdmBusObject;

/**
 * TargetTemperature Interface Controllee class
 */
class TargetTemperatureIntfControllee final : public CdmControlleeInterface
{
  public:

    /**
     * Constructor of TargetTemperatureIntfControllee
     */
    TargetTemperatureIntfControllee(BusAttachment& busAttachment, Ref<InterfaceControlleeModel> model, CdmBusObject& cdmBusObject);

    /**
     * Destructor of TargetTemperatureIntfControllee
     */
    ~TargetTemperatureIntfControllee();

    const qcc::String& GetInterfaceName() const override;

    bool IsValid() const override { return m_impl != nullptr; }

    /**
     * Emits a changed signal for the TargetValue property
     * @param[in] newValue new value of target value
     * @return ER_OK on success
     */
    QStatus EmitTargetValueChanged(const double newValue);

    /**
     * Emits a changed signal for the MinValue property
     * @param[in] newValue new value of min value
     * @return ER_OK on success
     */
    QStatus EmitMinValueChanged(const double newValue);

    /**
     * Emits a changed signal for the MaxValue property
     * @param[in] newValue new value of max value
     * @return ER_OK on success
     */
    QStatus EmitMaxValueChanged(const double newValue);

    /**
     * Emits a changed signal for the StepValue property
     * @param[in] newValue new value of step value
     * @return ER_OK on success
     */
    QStatus EmitStepValueChanged(const double newValue);

  private:

    class Impl;
    Impl* m_impl;
};

} //namespace services
} //namespace ajn

#endif /* TARGETTEMPERATUREINTFCONTROLLEE_H_ */