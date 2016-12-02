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

#include <alljoyn/cdm/CdmControllee.h>
#include "CdmControlleeImpl.h"

using namespace std;
using namespace qcc;

namespace ajn {
namespace services {

CdmControllee::CdmControllee(
    BusAttachment& bus,
    Ref<CdmAnnouncer> announcer,
    Ref<CdmSecurity> security
    )
  : m_impl(new CdmControlleeImpl(bus, announcer, security))
{
}

CdmControllee::~CdmControllee()
{
    delete m_impl;
}

QStatus CdmControllee::Start()
{
    return m_impl->Start();
}

QStatus CdmControllee::Stop()
{
    return m_impl->Stop();
}

CdmInterface* CdmControllee::CreateInterface(const CdmInterfaceType type, const qcc::String& objectPath, InterfaceControlleeListener& listener)
{
    return m_impl->CreateInterface(type, objectPath, listener);
}

const CdmInterfaceType CdmControllee::RegisterVendorDefinedInterface(const qcc::String& interfaceName, CreateIntfControlleeFptr createIntfControllee)
{
    return m_impl->RegisterVendorDefinedInterface(interfaceName, createIntfControllee);
}

} //namespace services
} //namespace ajn
