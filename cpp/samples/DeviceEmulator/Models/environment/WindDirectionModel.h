/******************************************************************************
 *  *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#ifndef WINDDIRECTIONMODEL_H_
#define WINDDIRECTIONMODEL_H_

#include <interfaces/controllee/environment/WindDirectionIntfControlleeModel.h>

namespace ajn {
namespace services {
namespace emulator {


class WindDirectionModel : public virtual WindDirectionIntfControlleeModel {
  public:
    WindDirectionModel(const std::string& busPath);

    /**
     * Get HorizontalDirection
     * @return current horizontal direction
     */
    QStatus GetHorizontalDirection(uint16_t& out) const override;

     /**
     * Set HorizontalDirection
     * @param[in] value The horizontal direction to set
     * @return ER_OK on success
     */
    QStatus SetHorizontalDirection(const uint16_t value) override;

    /**
     * Get HorizontalMax
     * @return current horizontal max
     */
    QStatus GetHorizontalMax(uint16_t& out) const override;

    /**
     * Get HorizontalAutoMode
     * @return current horizontal auto mode
     */
    QStatus GetHorizontalAutoMode(WindDirectionInterface::AutoMode& out) const override;

     /**
     * Set HorizontalAutoMode
     * @param[in] value The horizontal auto mode to set
     * @return ER_OK on success
     */
    QStatus SetHorizontalAutoMode(const WindDirectionInterface::AutoMode value) override;

    /**
     * Get VerticalDirection
     * @return current vertical direction
     */
    QStatus GetVerticalDirection(uint16_t& out) const override;

     /**
     * Set VerticalDirection
     * @param[in] value The vertical direction to set
     * @return ER_OK on success
     */
    QStatus SetVerticalDirection(const uint16_t value) override;

    /**
     * Get VerticalMax
     * @return current vertical max
     */
    QStatus GetVerticalMax(uint16_t& out) const override;

    /**
     * Get VerticalAutoMode
     * @return current vertical auto mode
     */
    QStatus GetVerticalAutoMode(WindDirectionInterface::AutoMode& out) const override;

     /**
     * Set VerticalAutoMode
     * @param[in] value The vertical auto mode to set
     * @return ER_OK on success
     */
    QStatus SetVerticalAutoMode(const WindDirectionInterface::AutoMode value) override;


  private:
    std::string m_busPath;
};

} // namespace emulator
} // namespace services
} // namespace ajn

#endif /* WINDDIRECTIONMODEL_H_ */