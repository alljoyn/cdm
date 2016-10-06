/******************************************************************************
 *  * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#ifndef ENERGYUSAGEINTFCONTROLLEE_H_
#define ENERGYUSAGEINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/EnergyUsageInterface.h>

namespace ajn {
namespace services {

/**
 * EnergyUsage Interface Controllee class
 */
class EnergyUsageIntfControllee : public EnergyUsageInterface {
  public:
    /**
     * Constructor of EnergyUsageIntfControllee
     */
    EnergyUsageIntfControllee() {}

    /**
     * Destructor of EnergyUsageIntfControllee
     */
    virtual ~EnergyUsageIntfControllee() {}

    /**
     * Get cumulative energy
     * @return Cumulative energy
     */
    virtual const double GetCumulativeEnergy() const = 0;

    /**
     * Set cumulative energy
     * @param[in] cumulativeEnergy cumulative energy
     * @return ER_OK on success
     */
    virtual QStatus SetCumulativeEnergy(const double cumulativeEnergy) = 0;

    /**
     * Get precision
     * @return Precision
     */
    virtual const double GetPrecision() const = 0;

    /**
     * Set precision
     * @param[in] precision precision
     * @return ER_OK on success
     */
    virtual QStatus SetPrecision(const double precision) = 0;

    /**
     * Get the minimum update time
     * @return The minimum update time
     */
    virtual const uint16_t GetUpdateMinTime() const = 0;

    /**
     * Set the minimum update time
     * @param[in] updateMinTime the minimum update time
     * @return ER_OK on success
     */
    virtual QStatus SetUpdateMinTime(const uint16_t updateMinTime) = 0;
};

} //namespace services
} //namespace ajn

#endif /* ENERGYUSAGEINTFCONTROLLEE_H_ */