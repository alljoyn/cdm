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

#include <alljoyn/cdm/controllee/CdmControllee.h>
#include "CdmControlleeImpl.h"

using namespace std;
using namespace qcc;

namespace ajn {
namespace services {

CdmControllee::CdmControllee(BusAttachment& bus)
  : m_impl(new CdmControlleeImpl(bus))
{
}

CdmControllee::~CdmControllee()
{
    delete m_impl;
}

QStatus CdmControllee::Start(bool emitOnSetProperty)
{
    return m_impl->Start(emitOnSetProperty);
}

QStatus CdmControllee::Stop()
{
    return m_impl->Stop();
}

bool CdmControllee::EmitChangedSignalOnSetProperty() const
{
    return m_impl->EmitChangedSignalOnSet();
}

Ref<CdmBusObject> CdmControllee::GetCdmBusObject(const qcc::String& busPath)
{
    return m_impl->GetCdmBusObject(busPath);
}

BusAttachment& CdmControllee::GetBusAttachment() const
{
    return m_impl->GetBusAttachment();
}

void CdmControllee::RegisterCdmControlleeInterface(const qcc::String& busPath, const qcc::String& interfaceName, Ref<CdmControlleeInterface> interface)
{
    m_impl->RegisterCdmInterface(busPath, interfaceName, interface);
}

Ref<CdmControlleeInterface> CdmControllee::GetCdmControlleeInterface(const qcc::String& busPath, const qcc::String& interfaceName) const
{
    return m_impl->GetCdmInterface(busPath, interfaceName);
}

void ignore_unused(CdmControllee&) {};

} //namespace services
} //namespace ajn
