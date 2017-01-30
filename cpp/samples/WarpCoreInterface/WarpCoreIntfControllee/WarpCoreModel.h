/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
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

#ifndef WARPCOREMODEL_H_
#define WARPCOREMODEL_H_

#include "WarpCoreIntfControlleeModel.h"
#include "../Utils/Command.h"

namespace ajn {
namespace services {
namespace emulator {


class WarpCoreModel : public virtual WarpCoreIntfControlleeModel {
  public:
    WarpCoreModel(const std::string& busPath);

    /**
     * Get WarpFactor
     * @return current warp factor
     */
    QStatus GetWarpFactor(double& out) const override;

     /**
     * Set WarpFactor
     * @param[in] value The warp factor to set
     * @return ER_OK on success
     */
    QStatus SetWarpFactor(const double value) override;

    /**
     * Get CurrentWarpFactor
     * @return current current warp factor
     */
    QStatus GetCurrentWarpFactor(double& out) const override;

    /**
     * Get IsEngaged
     * @return current is engaged
     */
    QStatus GetIsEngaged(bool& out) const override;

    /**
     * Handler for method Engage
     * @param[out] error Internal error code occurred during command execution
     * @return ER_OK on success
     */
    QStatus Engage(ErrorCode& error, CdmControllee& controllee) override;
    /**
     * Handler for method Disengage
     * @param[out] error Internal error code occurred during command execution
     * @return ER_OK on success
     */
    QStatus Disengage(ErrorCode& error, CdmControllee& controllee) override;

  private:
    std::string m_busPath;
};


QStatus HandleWarpCoreCommand(const Command& cmd, CdmControllee& controllee);

} // namespace emulator
} // namespace services
} // namespace ajn

#endif /* WARPCOREMODEL_H_ */