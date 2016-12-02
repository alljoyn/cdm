/******************************************************************************
 *  * 
 *    Copyright (c) 2016 Open Connectivity Foundation and AllJoyn Open
 *    Source Project Contributors and others.
 *    
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0

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