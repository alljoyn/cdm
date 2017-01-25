/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 * Source Project (AJOSP) Contributors and others.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * All rights reserved. This program and the accompanying materials are
 * made available under the terms of the Apache License, Version 2.0
 * which accompanies this distribution, and is available at
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Copyright 2016 Open Connectivity Foundation and Contributors to
 * AllSeen Alliance. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all
 * copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#ifndef HEATINGZONELISTENER_H_
#define HEATINGZONELISTENER_H_
#include <interfaces/controllee/operation/HeatingZoneIntfControllee.h>
#include <interfaces/controllee/operation/HeatingZoneIntfControlleeModel.h>

using namespace ajn;
using namespace services;


class HeatingZoneModel : public HeatingZoneIntfControlleeModel
{
public:
    HeatingZoneModel();

        /**
         * Handler for getting number of heating zones
         * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
         * @param[out] currentState currentState
         * @return ER_OK on success
         */
        virtual QStatus GetNumberOfHeatingZones(uint8_t& currentState) const override;
        /**
         * Handler for getting max heating levels
         * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
         * @param[out] maxHeatingLevels maxHeatingLevels
         * @return ER_OK on success
         */
        virtual QStatus GetMaxHeatingLevels(std::vector<uint8_t>& maxHeatingLevels) const override;
        /**
         * Handler for getting heating levels
         * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
         * @param[out] heatingLevels heatingLevels
         * @return ER_OK on success
         */
        virtual QStatus GetHeatingLevels(std::vector<uint8_t>& heatingLevels) const override;

        //==================================================
        // This is a side-channel to set the initial properties

        void SetNumberOfHeatingZones(uint8_t numberOfHeatingZones);
        void SetMaxHeatingLevels(const std::vector<uint8_t>& maxHeatingLevels);
        void SetHeatingLevels(const std::vector<uint8_t>& heatingLevels);

private:
        uint8_t m_numberOfHeatingZones;
        std::vector<uint8_t> m_maxHeatingLevels;
        std::vector<uint8_t> m_heatingLevels;
};

#endif /* HEATINGZONELISTENER_H_ */
