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

#ifndef CURRENTPOWERINTFCONTROLLEE_H_
#define CURRENTPOWERINTFCONTROLLEE_H_

#include <memory>

#include <qcc/String.h>
#include <alljoyn/Status.h>

#include <alljoyn/cdm/util/CdmMsgCvt.h>
#include <alljoyn/cdm/controllee/CdmControlleeInterface.h>
#include <interfaces/common/operation/CurrentPowerInterface.h>

namespace ajn {

class BusAttachment;

namespace services {

class IntefaceControlleeModel;
class CdmBusObject;

/**
 * CurrentPower Interface Controllee class
 */
class CurrentPowerIntfControllee final : public CdmControlleeInterface
{
  public:

    /**
     * Constructor of CurrentPowerIntfControllee
     */
    CurrentPowerIntfControllee(BusAttachment& busAttachment, Ref<InterfaceControlleeModel> model, CdmBusObject& cdmBusObject);

    /**
     * Destructor of CurrentPowerIntfControllee
     */
    ~CurrentPowerIntfControllee();

    const qcc::String& GetInterfaceName() const override;

    bool IsValid() const override { return m_impl != nullptr; }

    /**
     * Emits a changed signal for the CurrentPower property
     * @param[in] newValue new value of current power
     * @return ER_OK on success
     */
    QStatus EmitCurrentPowerChanged(const double newValue);

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

#endif /* CURRENTPOWERINTFCONTROLLEE_H_ */