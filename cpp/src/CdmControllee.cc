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
#include <qcc/String.h>

#include <alljoyn/hae/HaeControllee.h>
#include "HaeControlleeImpl.h"

using namespace std;
using namespace qcc;

namespace ajn {
namespace services {

HaeControllee::HaeControllee(BusAttachment& bus, HaeAboutData* aboutData) :
    m_impl(new HaeControlleeImpl(bus, aboutData))
{
}

HaeControllee::~HaeControllee()
{
    if (m_impl) {
        delete m_impl;
        m_impl = 0;
    }
}

QStatus HaeControllee::EnablePeerSecurity(const char* authMechanisms,
                                          AuthListener* authListener,
                                          const char* keyStoreFileName,
                                          bool isKeyStoreShared)
{
    if (!m_impl) {
        return ER_FAIL;
    }
    return m_impl->EnablePeerSecurity(authMechanisms, authListener, keyStoreFileName, isKeyStoreShared);
}

QStatus HaeControllee::Start()
{
    if (!m_impl) {
        return ER_FAIL;
    }
    return m_impl->Start();
}

QStatus HaeControllee::Stop()
{
    if (!m_impl) {
        return ER_FAIL;
    }
    return m_impl->Stop();
}

HaeInterface* HaeControllee::CreateInterface(const HaeInterfaceType type, const qcc::String& objectPath, InterfaceControlleeListener& listener)
{
    if (!m_impl) {
        return NULL;
    }
    return m_impl->CreateInterface(type, objectPath, listener);
}

const HaeInterfaceType HaeControllee::RegisterVendorDefinedInterface(const qcc::String& interfaceName, CreateIntfControlleeFptr createIntfControllee)
{
    if (!m_impl) {
        return ER_FAIL;
    }
    return m_impl->RegisterVendorDefinedInterface(interfaceName, createIntfControllee);
}

} //namespace services
} //namespace ajn
