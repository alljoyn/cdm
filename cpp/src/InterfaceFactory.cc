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

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>

#include <alljoyn/hae/LogModule.h>

#include "InterfaceFactory.h"

// Controllee
#include "interfaces/operation/ChannelIntfControlleeImpl.h"
#include "interfaces/operation/AudioVideoInputIntfControlleeImpl.h"
#include "interfaces/operation/AudioVolumeIntfControlleeImpl.h"
#include "interfaces/input/HidIntfControlleeImpl.h"

// Controller
#include "interfaces/operation/AudioVolumeIntfControllerImpl.h"
#include "interfaces/operation/ChannelIntfControllerImpl.h"
#include "interfaces/operation/AudioVideoInputIntfControllerImpl.h"
#include "interfaces/input/HidIntfControllerImpl.h"

using namespace std;
using namespace qcc;

namespace ajn {
namespace services {

InterfaceFactory* InterfaceFactory::s_instance(0);

InterfaceFactory* InterfaceFactory::GetInstance()
{
    if (!s_instance) {
        s_instance = new InterfaceFactory();
    }
    return s_instance;
}

InterfaceFactory::InterfaceFactory() :
    m_busAttachment(0)
{
    // Controller
    m_controllerCreators[AUDIO_VOLUME_INTERFACE] = static_cast<CreateIntfControllerFptr>(&AudioVolumeIntfControllerImpl::CreateInterface);
    m_controllerCreators[CHANNEL_INTERFACE] = static_cast<CreateIntfControllerFptr>(&ChannelIntfControllerImpl::CreateInterface);
    m_controllerCreators[AUDIO_VIDEO_INPUT_INTERFACE] = static_cast<CreateIntfControllerFptr>(&AudioVideoInputIntfControllerImpl::CreateInterface);
    m_controllerCreators[HID_INTERFACE] = static_cast<CreateIntfControllerFptr>(&HidIntfControllerImpl::CreateInterface);

    // Controllee
    m_controlleeCreators[CHANNEL_INTERFACE] = static_cast<CreateIntfControlleeFptr>(&ChannelIntfControlleeImpl::CreateInterface);
    m_controlleeCreators[AUDIO_VIDEO_INPUT_INTERFACE] = static_cast<CreateIntfControlleeFptr>(&AudioVideoInputIntfControlleeImpl::CreateInterface);
    m_controlleeCreators[AUDIO_VOLUME_INTERFACE] = static_cast<CreateIntfControlleeFptr>(&AudioVolumeIntfControlleeImpl::CreateInterface);
    m_controlleeCreators[HID_INTERFACE] = static_cast<CreateIntfControlleeFptr>(&HidIntfControlleeImpl::CreateInterface);
}

InterfaceFactory::InterfaceFactory(const InterfaceFactory& src)
{
    m_busAttachment = src.m_busAttachment;
}

InterfaceFactory& InterfaceFactory::operator=(const InterfaceFactory& src)
{
    m_busAttachment = src.m_busAttachment;
    return *this;
}

QStatus InterfaceFactory::InitInterfaceFactory(BusAttachment* busAttachment)
{
    if (!busAttachment) {
        QCC_LogError(ER_BAD_ARG_1, ("%s: bus attachment is null.", __func__));
        return ER_BAD_ARG_1;
    }
    m_busAttachment = busAttachment;
    return ER_OK;
}

CreateIntfControlleeFptr InterfaceFactory::GetCreateIntfControlleeFptr(const HaeInterfaceType type)
{
    map<HaeInterfaceType, CreateIntfControlleeFptr>::iterator it;

    it = m_controlleeCreators.find(type);
    if (it == m_controlleeCreators.end()) {
        QCC_LogError(ER_FAIL, ("%s: could not found interface", __func__));
        return NULL;
    }

    return it->second;
}

CreateIntfControllerFptr InterfaceFactory::GetCreateIntfControllerFptr(const HaeInterfaceType type)
{
    map<HaeInterfaceType, CreateIntfControllerFptr>::iterator it;

    it = m_controllerCreators.find(type);
    if (it == m_controllerCreators.end()) {
        QCC_LogError(ER_FAIL, ("%s: could not found interface", __func__));
        return NULL;
    }

    return it->second;
}

HaeInterface* InterfaceFactory::CreateIntfControllee(const HaeInterfaceType type, InterfaceControlleeListener& listener, HaeBusObject& haeBusObject)
{
    HaeInterface* interface = NULL;
    QStatus status = ER_OK;

    if (!m_busAttachment) {
        QCC_LogError(ER_FAIL, ("%s: could not initialized controllee", __func__));
        return NULL;
    }

    CreateIntfControlleeFptr handler = GetCreateIntfControlleeFptr(type);
    if (!handler) {
        QCC_LogError(status, ("%s: could not found interface", __func__));
        return NULL;
    }

    interface = handler(*m_busAttachment, listener, haeBusObject);
    if (!interface) {
        QCC_LogError(status, ("%s: could not create interface", __func__));
        return NULL;
    }

    status = interface->Init();
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: could not init interface", __func__));
        delete interface;
        return NULL;
    }

    return interface;
}

HaeInterface* InterfaceFactory::CreateIntfController(const HaeInterfaceType type, InterfaceControllerListener& listener, HaeProxyBusObject& haeProxyObject)
{
    HaeInterface* interface = NULL;
    QStatus status = ER_OK;

    if (!m_busAttachment) {
        QCC_LogError(ER_FAIL, ("%s: could not initialized controllee", __func__));
        return NULL;
    }

    CreateIntfControllerFptr handler = GetCreateIntfControllerFptr(type);
    if (!handler) {
        QCC_LogError(status, ("%s: could not found interface", __func__));
        return NULL;
    }

    interface = handler(*m_busAttachment, listener, haeProxyObject);
    if (!interface) {
        QCC_LogError(status, ("%s: could not create interface", __func__));
        return NULL;
    }

    status = interface->Init();
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: could not init interface", __func__));
        delete interface;
        return NULL;
    }

    return interface;
}

void InterfaceFactory::RegisterVendorDefinedIntfControllee(const HaeInterfaceType type, CreateIntfControlleeFptr createIntfControllee)
{
    m_controlleeCreators[type] = createIntfControllee;
}

void InterfaceFactory::RegisterVendorDefinedIntfController(const HaeInterfaceType type, CreateIntfControllerFptr createIntfController)
{
    m_controllerCreators[type] = createIntfController;
}

}
}
