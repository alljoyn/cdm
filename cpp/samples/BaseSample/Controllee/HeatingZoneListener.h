/******************************************************************************
 * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#ifndef HEATINGZONELISTENER_H_
#define HEATINGZONELISTENER_H_
#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/HeatingZoneIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/HeatingZoneIntfControlleeListener.h>

using namespace ajn;
using namespace services;


class HeatingZoneListener : public HeatingZoneIntfControlleeListener
{

public:
        /**
         * Handler for getting number of heating zones
         * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
         * @param[out] currentState currentState
         * @return ER_OK on success
         */
        virtual QStatus OnGetNumberOfHeatingZones(uint8_t& currentState);
        /**
         * Handler for getting max heating levels
         * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
         * @param[out] maxHeatingLevels maxHeatingLevels
         * @return ER_OK on success
         */
        virtual QStatus OnGetMaxHeatingLevels(std::vector<uint8_t>& maxHeatingLevels);
        /**
         * Handler for getting heating levels
         * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
         * @param[out] heatingLevels heatingLevels
         * @return ER_OK on success
         */
        virtual QStatus OnGetHeatingLevels(std::vector<uint8_t>& heatingLevels);

};

class HeatingZoneCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    HeatingZoneCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~HeatingZoneCommands();

    virtual void Init();
    virtual void InitializeProperties();

    HeatingZoneIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetNumberOfHeatingZones(Commands* commands, std::string& cmd);
    static void OnCmdSetNumberOfHeatingZones(Commands* commands, std::string& cmd);

    static void OnCmdGetMaxHeatingLevels(Commands* commands, std::string& cmd);
    static void OnCmdGetHeatingLevels(Commands* commands, std::string& cmd);
  private:
    HeatingZoneIntfControllee* m_intfControllee;
    HeatingZoneListener m_listener;
};

#endif /* HEATINGZONELISTENER_H_ */