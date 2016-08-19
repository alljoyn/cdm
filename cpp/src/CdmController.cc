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

#include <qcc/Debug.h>
#include <alljoyn/Session.h>
#include <alljoyn/hae/LogModule.h>
#include <alljoyn/hae/HaeController.h>

#include "HaeControllerImpl.h"

using namespace ajn;
using namespace services;
using namespace qcc;

HaeController::HaeController(BusAttachment& bus, DeviceListener* listener)
    : m_impl(new HaeControllerImpl(bus, listener))
{

}

HaeController::~HaeController()
{
    if (m_impl) {
        delete m_impl;
        m_impl = 0;
    }
}

QStatus HaeController::EnablePeerSecurity(const char* authMechanisms,
                                          AuthListener* authListener,
                                          const char* keyStoreFileName,
                                          bool isKeyStoreShared)
{
    if (!m_impl) {
        return ER_FAIL;
    }
    return m_impl->EnablePeerSecurity(authMechanisms, authListener, keyStoreFileName, isKeyStoreShared);
}

QStatus HaeController::Init(const InterestDeviceList& list)
{
    if (!m_impl) {
        return ER_FAIL;
    }
    return m_impl->Init(list);
}

QStatus HaeController::Start()
{
    if (!m_impl) {
        return ER_FAIL;
    }
    return m_impl->Start();
}

QStatus HaeController::Stop()
{
    if (!m_impl) {
        return ER_FAIL;
    }
    return m_impl->Stop();
}

QStatus HaeController::JoinDevice(const std::string& busName, SessionPort port, const HaeAboutData& data,
                                  AboutObjectDescription& description)
{
    if (!m_impl) {
        return ER_FAIL;
    }
    return m_impl->JoinDevice(busName, port, data, description);
}

/*
QStatus HaeController::GetAboutObjectDescription(const DeviceInfo& deviceInfo, AboutObjectDescription& aboutObjectDesc)
{
    if (!m_impl) {
        return ER_FAIL;
    }

    return m_impl->GetAboutObjectDescription(deviceInfo, aboutObjectDesc);
}
*/

HaeInterface* HaeController::CreateInterface(const HaeInterfaceType type, const std::string& busName, const qcc::String& objectPath, const SessionId& sessionId, InterfaceControllerListener& listener)
{
    HaeInterface* interface = NULL;

    if (m_impl) {
        return m_impl->CreateInterface(type, busName, objectPath, sessionId, listener);
    }

    return interface;
}

const HaeInterfaceType HaeController::RegisterVendorDefinedInterface(const qcc::String& interfaceName, CreateIntfControllerFptr createIntfController)
{
    HaeInterfaceType type = UNDEFINED_INTERFACE;

    if (m_impl) {
        return m_impl->RegisterVendorDefinedInterface(interfaceName, createIntfController);
    }

    return type;
}
