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

#ifndef WINDDIRECTIONINTFCONTROLLEE_H_
#define WINDDIRECTIONINTFCONTROLLEE_H_

#include <memory>

#include <qcc/String.h>
#include <alljoyn/Status.h>

#include <alljoyn/cdm/util/CdmMsgCvt.h>
#include <alljoyn/cdm/controllee/CdmControlleeInterface.h>
#include <interfaces/common/environment/WindDirectionInterface.h>

namespace ajn {

class BusAttachment;

namespace services {

class IntefaceControlleeModel;
class CdmBusObject;

/**
 * WindDirection Interface Controllee class
 */
class WindDirectionIntfControllee final : public CdmControlleeInterface
{
  public:
    using AutoMode = WindDirectionInterface::AutoMode;

    /**
     * Constructor of WindDirectionIntfControllee
     */
    WindDirectionIntfControllee(BusAttachment& busAttachment, Ref<InterfaceControlleeModel> model, CdmBusObject& cdmBusObject);

    /**
     * Destructor of WindDirectionIntfControllee
     */
    ~WindDirectionIntfControllee();

    const qcc::String& GetInterfaceName() const override;

    bool IsValid() const override { return m_impl != nullptr; }

    /**
     * Emits a changed signal for the HorizontalDirection property
     * @param[in] newValue new value of horizontal direction
     * @return ER_OK on success
     */
    QStatus EmitHorizontalDirectionChanged(const uint16_t newValue);

    /**
     * Emits a changed signal for the HorizontalMax property
     * @param[in] newValue new value of horizontal max
     * @return ER_OK on success
     */
    QStatus EmitHorizontalMaxChanged(const uint16_t newValue);

    /**
     * Emits a changed signal for the HorizontalAutoMode property
     * @param[in] newValue new value of horizontal auto mode
     * @return ER_OK on success
     */
    QStatus EmitHorizontalAutoModeChanged(const WindDirectionInterface::AutoMode newValue);

    /**
     * Emits a changed signal for the VerticalDirection property
     * @param[in] newValue new value of vertical direction
     * @return ER_OK on success
     */
    QStatus EmitVerticalDirectionChanged(const uint16_t newValue);

    /**
     * Emits a changed signal for the VerticalMax property
     * @param[in] newValue new value of vertical max
     * @return ER_OK on success
     */
    QStatus EmitVerticalMaxChanged(const uint16_t newValue);

    /**
     * Emits a changed signal for the VerticalAutoMode property
     * @param[in] newValue new value of vertical auto mode
     * @return ER_OK on success
     */
    QStatus EmitVerticalAutoModeChanged(const WindDirectionInterface::AutoMode newValue);

  private:

    class Impl;
    Impl* m_impl;
};

} //namespace services
} //namespace ajn

#endif /* WINDDIRECTIONINTFCONTROLLEE_H_ */
