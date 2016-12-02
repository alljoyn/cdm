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

#include <qcc/Debug.h>
#include <alljoyn/Session.h>
#include <alljoyn/cdm/LogModule.h>
#include <alljoyn/cdm/CdmController.h>

#include "CdmControllerImpl.h"

using namespace ajn;
using namespace services;
using namespace qcc;

CdmController::CdmController(BusAttachment& bus, DeviceListener* listener)
    : m_impl(new CdmControllerImpl(bus, listener))
{

}

CdmController::~CdmController()
{
    if (m_impl) {
        delete m_impl;
        m_impl = 0;
    }
}

QStatus CdmController::EnablePeerSecurity(const char* authMechanisms,
                                          AuthListener* authListener,
                                          const char* keyStoreFileName,
                                          bool isKeyStoreShared)
{
    if (!m_impl) {
        return ER_FAIL;
    }
    return m_impl->EnablePeerSecurity(authMechanisms, authListener, keyStoreFileName, isKeyStoreShared);
}

QStatus CdmController::Init(const InterestDeviceList& list)
{
    if (!m_impl) {
        return ER_FAIL;
    }
    return m_impl->Init(list);
}

QStatus CdmController::Start()
{
    if (!m_impl) {
        return ER_FAIL;
    }
    return m_impl->Start();
}

QStatus CdmController::Stop()
{
    if (!m_impl) {
        return ER_FAIL;
    }
    return m_impl->Stop();
}

QStatus CdmController::JoinDevice(const std::string& busName, SessionPort port, const CdmAboutData& data,
                                  AboutObjectDescription& description)
{
    if (!m_impl) {
        return ER_FAIL;
    }
    return m_impl->JoinDevice(busName, port, data, description);
}

/*
QStatus CdmController::GetAboutObjectDescription(const DeviceInfo& deviceInfo, AboutObjectDescription& aboutObjectDesc)
{
    if (!m_impl) {
        return ER_FAIL;
    }

    return m_impl->GetAboutObjectDescription(deviceInfo, aboutObjectDesc);
}
*/

CdmInterface* CdmController::CreateInterface(const CdmInterfaceType type, const std::string& busName, const qcc::String& objectPath, const SessionId& sessionId, InterfaceControllerListener& listener)
{
    CdmInterface* interface = NULL;

    if (m_impl) {
        return m_impl->CreateInterface(type, busName, objectPath, sessionId, listener);
    }

    return interface;
}

const CdmInterfaceType CdmController::RegisterVendorDefinedInterface(const qcc::String& interfaceName, CreateIntfControllerFptr createIntfController)
{
    CdmInterfaceType type = UNDEFINED_INTERFACE;

    if (m_impl) {
        return m_impl->RegisterVendorDefinedInterface(interfaceName, createIntfController);
    }

    return type;
}