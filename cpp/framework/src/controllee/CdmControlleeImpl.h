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


#ifndef CDMCONTROLLEEIMPL_H_
#define CDMCONTROLLEEIMPL_H_

#include <map>
#include <atomic>

#include <alljoyn/Status.h>
#include <alljoyn/AboutObj.h>
#include <alljoyn/cdm/common/CdmTypes.h>
#include <alljoyn/cdm/common/CdmInterface.h>
#include <alljoyn/cdm/common/CdmInterfaceTypes.h>

#ifdef _MSC_VER
    #if _MSC_VER < 1900
        typedef std::atomic<bool> AtomicBool;
        #define __func__ __FUNCTION__
    #else
        typedef std::atomic_bool AtomicBool;
    #endif
#else
    typedef std::atomic_bool AtomicBool;
#endif


namespace ajn {

namespace services {

class CdmControlleeInterface;
class InterfaceControlleeModel;
class CdmAboutData;
class CdmBusObject;
class CdmBusListener;
class CdmControllee;

/**
 * Cdm ControlleeImpl class.
 * Used to create cdm controllee device.
 */
class CdmControlleeImpl {
  public:
    CdmControlleeImpl(BusAttachment& bus, CdmControllee& outer);
    CdmControlleeImpl(const std::atomic_bool &m_isStarted);

    ~CdmControlleeImpl();

    QStatus Start();

    QStatus Stop();

    Ref<CdmBusObject> GetCdmBusObject(const qcc::String& busPath);

    BusAttachment& GetBusAttachment() const { return m_bus; };

    Ref<CdmControlleeInterface> GetCdmInterface(const qcc::String& busPath, const qcc::String& interfaceName);
    void RegisterCdmInterface(const qcc::String& busPath, const qcc::String& interfaceName, Ref<CdmControlleeInterface> interface);
 private:
    QStatus RegisterBusObjects();

    QStatus RegisterBusListener();

    QStatus UnregisterBusListener();

    BusAttachment& m_bus;
    CdmControllee& m_outer;
    std::map<qcc::String, Ref<CdmBusObject>> m_cdmBusObjectsMap;
    std::map<std::pair<qcc::String, qcc::String>, Ref<CdmControlleeInterface>> m_interfaces;
    CdmBusListener* m_cdmBusListener;
    AtomicBool m_isStarted;
};

}
}

#endif  // CDMCONTROLLEEIMPL_H_
