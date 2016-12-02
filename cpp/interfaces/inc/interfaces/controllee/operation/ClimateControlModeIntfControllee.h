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

#ifndef CLIMATECONTROLMODEINTFCONTROLLEE_H_
#define CLIMATECONTROLMODEINTFCONTROLLEE_H_

#include <memory>

#include <qcc/String.h>
#include <alljoyn/Status.h>

#include <alljoyn/cdm/util/CdmMsgCvt.h>
#include <alljoyn/cdm/controllee/CdmControlleeInterface.h>
#include <interfaces/common/operation/ClimateControlModeInterface.h>

namespace ajn {

class BusAttachment;

namespace services {

class IntefaceControlleeModel;
class CdmBusObject;

/**
 * ClimateControlMode Interface Controllee class
 */
class ClimateControlModeIntfControllee final : public CdmControlleeInterface
{
  public:
    using Mode = ClimateControlModeInterface::Mode;
    using OperationalState = ClimateControlModeInterface::OperationalState;

    /**
     * Constructor of ClimateControlModeIntfControllee
     */
    ClimateControlModeIntfControllee(BusAttachment& busAttachment, Ref<InterfaceControlleeModel> model, CdmBusObject& cdmBusObject);

    /**
     * Destructor of ClimateControlModeIntfControllee
     */
    ~ClimateControlModeIntfControllee();

    const qcc::String& GetInterfaceName() const override;

    bool IsValid() const override { return m_impl != nullptr; }

    /**
     * Emits a changed signal for the Mode property
     * @param[in] newValue new value of mode
     * @return ER_OK on success
     */
    QStatus EmitModeChanged(const Mode newValue);

    /**
     * Emits a changed signal for the SupportedModes property
     * @param[in] newValue new value of supported modes
     * @return ER_OK on success
     */
    QStatus EmitSupportedModesChanged(const std::vector<Mode> newValue);

    /**
     * Emits a changed signal for the OperationalState property
     * @param[in] newValue new value of operational state
     * @return ER_OK on success
     */
    QStatus EmitOperationalStateChanged(const OperationalState newValue);

  private:

    class Impl;
    Impl* m_impl;
};

} //namespace services
} //namespace ajn

#endif /* CLIMATECONTROLMODEINTFCONTROLLEE_H_ */
