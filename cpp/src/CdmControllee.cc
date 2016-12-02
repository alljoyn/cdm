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
#include <qcc/String.h>

#include <alljoyn/cdm/CdmControllee.h>
#include "CdmControlleeImpl.h"

using namespace std;
using namespace qcc;

namespace ajn {
namespace services {

CdmControllee::CdmControllee(BusAttachment& bus, CdmAboutData* aboutData) :
    m_impl(new CdmControlleeImpl(bus, aboutData))
{
}

CdmControllee::~CdmControllee()
{
    if (m_impl) {
        delete m_impl;
        m_impl = 0;
    }
}

QStatus CdmControllee::EnablePeerSecurity(const char* authMechanisms,
                                          AuthListener* authListener,
                                          const char* keyStoreFileName,
                                          bool isKeyStoreShared)
{
    if (!m_impl) {
        return ER_FAIL;
    }
    return m_impl->EnablePeerSecurity(authMechanisms, authListener, keyStoreFileName, isKeyStoreShared);
}

QStatus CdmControllee::Start()
{
    if (!m_impl) {
        return ER_FAIL;
    }
    return m_impl->Start();
}

QStatus CdmControllee::Stop()
{
    if (!m_impl) {
        return ER_FAIL;
    }
    return m_impl->Stop();
}

CdmInterface* CdmControllee::CreateInterface(const CdmInterfaceType type, const qcc::String& objectPath, InterfaceControlleeListener& listener)
{
    if (!m_impl) {
        return NULL;
    }
    return m_impl->CreateInterface(type, objectPath, listener);
}

const CdmInterfaceType CdmControllee::RegisterVendorDefinedInterface(const qcc::String& interfaceName, CreateIntfControlleeFptr createIntfControllee)
{
    if (!m_impl) {
        return ER_FAIL;
    }
    return m_impl->RegisterVendorDefinedInterface(interfaceName, createIntfControllee);
}

} //namespace services
} //namespace ajn