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

#ifndef CURRENTAIRQUALITYINTFCONTROLLEE_H_
#define CURRENTAIRQUALITYINTFCONTROLLEE_H_

#include <memory>

#include <qcc/String.h>
#include <alljoyn/Status.h>

#include <alljoyn/cdm/util/CdmMsgCvt.h>
#include <alljoyn/cdm/controllee/CdmControlleeInterface.h>
#include <interfaces/common/environment/CurrentAirQualityInterface.h>

namespace ajn {

class BusAttachment;

namespace services {

class IntefaceControlleeModel;
class CdmBusObject;

/**
 * CurrentAirQuality Interface Controllee class
 */
class CurrentAirQualityIntfControllee final : public CdmControlleeInterface
{
  public:
    using ContaminantType = CurrentAirQualityInterface::ContaminantType;

    /**
     * Constructor of CurrentAirQualityIntfControllee
     */
    CurrentAirQualityIntfControllee(BusAttachment& busAttachment, Ref<InterfaceControlleeModel> model, CdmBusObject& cdmBusObject);

    /**
     * Destructor of CurrentAirQualityIntfControllee
     */
    ~CurrentAirQualityIntfControllee();

    const qcc::String& GetInterfaceName() const override;

    bool IsValid() const override { return m_impl != nullptr; }

    /**
     * Emits a changed signal for the ContaminantType property
     * @param[in] newValue new value of contaminant type
     * @return ER_OK on success
     */
    QStatus EmitContaminantTypeChanged(const CurrentAirQualityInterface::ContaminantType newValue);

    /**
     * Emits a changed signal for the CurrentValue property
     * @param[in] newValue new value of current value
     * @return ER_OK on success
     */
    QStatus EmitCurrentValueChanged(const double newValue);

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
     * Emits a changed signal for the Precision property
     * @param[in] newValue new value of precision
     * @return ER_OK on success
     */
    QStatus EmitPrecisionChanged(const double newValue);

    /**
     * Emits a changed signal for the UpdateMinTime property
     * @param[in] newValue new value of update min time
     * @return ER_OK on success
     */
    QStatus EmitUpdateMinTimeChanged(const uint16_t newValue);

  private:

    class Impl;
    Impl* m_impl;
};

} //namespace services
} //namespace ajn

#endif /* CURRENTAIRQUALITYINTFCONTROLLEE_H_ */