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

#ifndef INTERFACEFACTORY_H_
#define INTERFACEFACTORY_H_

#include <map>
#include <qcc/String.h>

#include <alljoyn/hae/interfaces/HaeInterface.h>
#include <alljoyn/hae/interfaces/HaeInterfaceListener.h>

namespace ajn {
class BusAttachment;
namespace services {

/**
 * Hae Interface factory class.
 */
class InterfaceFactory {
  public:
    /**
     * Get Instance of InterfaceFactory - singleton implementation
     * @return instance
     */
    static InterfaceFactory* GetInstance();

    /**
     * Destructor of InterfaceFactory
     */
    ~InterfaceFactory() {}

    /**
     * Initialize InterfaceFactory
     * @param busAttachment
     * @return status
     */
    QStatus InitInterfaceFactory(BusAttachment* busAttachment);

    /**
     * Get CreateIntfControlleeFptr
     * @param interface type
     * @return CreateIntfControlleeFptr
     */
    CreateIntfControlleeFptr GetCreateIntfControlleeFptr(const HaeInterfaceType type);

    /**
     * Get CreateIntfControllerFptr
     * @param interface type
     * @return CreateIntfControllerFptr
     */
    CreateIntfControllerFptr GetCreateIntfControllerFptr(const HaeInterfaceType type);

    /**
     * Create Interface for controllee
     * @param type
     * @param listener
     * @param hae bus object
     * @return HaeInterface
     */
    HaeInterface* CreateIntfControllee(const HaeInterfaceType type, InterfaceControlleeListener& listener, HaeBusObject& haeBusObject);

    /**
     * Create Interface for controller
     * @param type
     * @param listener
     * @param hae proxy object
     * @return HaeInterface
     */
    HaeInterface* CreateIntfController(const HaeInterfaceType type, InterfaceControllerListener& listener, HaeProxyBusObject& haeProxyObject);

    /**
     * Register vendor defined interface for controllee
     * @param interfaceName
     * @param CreateIntfControlleeFptr
     */
    void RegisterVendorDefinedIntfControllee(const HaeInterfaceType type, CreateIntfControlleeFptr createIntfControllee);

    /**
     * Register vendor defined interface for controller
     * @param interfaceName
     * @param CreateIntfControllerFptr
     */
    void RegisterVendorDefinedIntfController(const HaeInterfaceType type, CreateIntfControllerFptr createIntfController);

  private:
    /**
     * Constructor of InterfaceFactory
     */
    InterfaceFactory();

    /**
     * Copy constructor of InterfaceFactory
     */
    InterfaceFactory(const InterfaceFactory& src);


    /**
     * Assignment operator of InterfaceFactory
     * @param src
     * @return InterfaceFactory
     */
    InterfaceFactory& operator=(const InterfaceFactory& src);

    /**
     * Instance variable - InterfaceFactory is a signleton
     */
    static InterfaceFactory* s_instance;

    BusAttachment* m_busAttachment;
    std::map<HaeInterfaceType, CreateIntfControllerFptr> m_controllerCreators;
    std::map<HaeInterfaceType, CreateIntfControlleeFptr> m_controlleeCreators;
};

} //namespace services
} //namespace ajn

#endif /* INTERFACEFACTORY_H_ */
