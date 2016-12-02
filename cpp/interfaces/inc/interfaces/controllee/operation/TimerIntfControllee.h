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

#ifndef TIMERINTFCONTROLLEE_H_
#define TIMERINTFCONTROLLEE_H_

#include <memory>

#include <qcc/String.h>
#include <alljoyn/Status.h>

#include <alljoyn/cdm/util/CdmMsgCvt.h>
#include <alljoyn/cdm/controllee/CdmControlleeInterface.h>
#include <interfaces/common/operation/TimerInterface.h>

namespace ajn {

class BusAttachment;

namespace services {

class IntefaceControlleeModel;
class CdmBusObject;

/**
 * Timer Interface Controllee class
 */
class TimerIntfControllee final : public CdmControlleeInterface
{
  public:

    /**
     * Constructor of TimerIntfControllee
     */
    TimerIntfControllee(BusAttachment& busAttachment, Ref<InterfaceControlleeModel> model, CdmBusObject& cdmBusObject);

    /**
     * Destructor of TimerIntfControllee
     */
    ~TimerIntfControllee();

    const qcc::String& GetInterfaceName() const override;

    bool IsValid() const override { return m_impl != nullptr; }

    /**
     * Emits a changed signal for the TargetTimeToStart property
     * @param[in] newValue new value of target time to start
     * @return ER_OK on success
     */
    QStatus EmitTargetTimeToStartChanged(const int32_t newValue);

    /**
     * Emits a changed signal for the TargetTimeToStop property
     * @param[in] newValue new value of target time to stop
     * @return ER_OK on success
     */
    QStatus EmitTargetTimeToStopChanged(const int32_t newValue);

    /**
     * Emits a changed signal for the TargetDuration property
     * @param[in] newValue new value of target duration
     * @return ER_OK on success
     */
    QStatus EmitTargetDurationChanged(const int32_t newValue);

  private:

    class Impl;
    Impl* m_impl;
};

} //namespace services
} //namespace ajn

#endif /* TIMERINTFCONTROLLEE_H_ */
