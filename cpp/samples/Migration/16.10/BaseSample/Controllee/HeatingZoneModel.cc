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

#include <iostream>
#include "HeatingZoneModel.h"
#include "ControlleeSample.h"

using namespace std;

HeatingZoneModel::HeatingZoneModel()
  : m_numberOfHeatingZones(0)
{
}


QStatus HeatingZoneModel::GetNumberOfHeatingZones(uint8_t& currentState) const
{
    cout << "HeatingZoneModel::OnGetNumberOfHeatingZones()" << endl;
    currentState = m_numberOfHeatingZones;
    return ER_OK;
}
QStatus HeatingZoneModel::GetMaxHeatingLevels(std::vector<uint8_t>& maxHeatingLevels) const
{
    cout << "HeatingZoneModel::OnGetMaxHeatingLevels()" << endl;
    maxHeatingLevels = m_maxHeatingLevels;
    return ER_OK;
}
QStatus HeatingZoneModel::GetHeatingLevels(std::vector<uint8_t>& heatingLevels) const
{
    cout << "HeatingZoneModel::OnGetHeatingLevels()" << endl;
    heatingLevels = m_heatingLevels;
    return ER_OK;
}


void HeatingZoneModel::SetNumberOfHeatingZones(uint8_t numberOfHeatingZones)
{
    m_numberOfHeatingZones = numberOfHeatingZones;
}

void HeatingZoneModel::SetMaxHeatingLevels(const std::vector<uint8_t>& maxHeatingLevels)
{
    m_maxHeatingLevels = maxHeatingLevels;
}

void HeatingZoneModel::SetHeatingLevels(const std::vector<uint8_t>& heatingLevels)
{
    m_heatingLevels = heatingLevels;
}