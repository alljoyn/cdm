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

#ifndef FANSPEEDLEVELINTFCONTROLLEE_H_
#define FANSPEEDLEVELINTFCONTROLLEE_H_

#include <memory>

#include <qcc/String.h>
#include <alljoyn/Status.h>

#include <alljoyn/cdm/util/CdmMsgCvt.h>
#include <alljoyn/cdm/controllee/CdmControlleeInterface.h>
#include <interfaces/common/operation/FanSpeedLevelInterface.h>

namespace ajn {

class BusAttachment;

namespace services {

class IntefaceControlleeModel;
class CdmBusObject;

/**
 * FanSpeedLevel Interface Controllee class
 */
class FanSpeedLevelIntfControllee final : public CdmControlleeInterface
{
  public:
    using AutoMode = FanSpeedLevelInterface::AutoMode;

    /**
     * Constructor of FanSpeedLevelIntfControllee
     */
    FanSpeedLevelIntfControllee(BusAttachment& busAttachment, Ref<InterfaceControlleeModel> model, CdmBusObject& cdmBusObject);

    /**
     * Destructor of FanSpeedLevelIntfControllee
     */
    ~FanSpeedLevelIntfControllee();

    const qcc::String& GetInterfaceName() const override;

    bool IsValid() const override { return m_impl != nullptr; }

    /**
     * Emits a changed signal for the FanSpeedLevel property
     * @param[in] newValue new value of fan speed level
     * @return ER_OK on success
     */
    QStatus EmitFanSpeedLevelChanged(const uint8_t newValue);

    /**
     * Emits a changed signal for the AutoMode property
     * @param[in] newValue new value of auto mode
     * @return ER_OK on success
     */
    QStatus EmitAutoModeChanged(const AutoMode newValue);

  private:

    class Impl;
    Impl* m_impl;
};

} //namespace services
} //namespace ajn

#endif /* FANSPEEDLEVELINTFCONTROLLEE_H_ */
