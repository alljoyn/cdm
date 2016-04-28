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

#include "HaeTest.h"

InterfaceInfo::InterfaceInfo(const char* name, SessionPort port, const char* path, HaeAboutData& data) :
    busName(name), sessionPort(port), sessionId(0), objectPath(path)
{
    MsgArg* arg;
    data.GetField("DeviceName", arg, "en");
    const char* bus_name;
    arg->Get("s", &bus_name);

    deviceName = bus_name;
}

bool ECDHEKeyXListener::RequestCredentials(const char* authMechanism, const char* authPeer, uint16_t authCount, const char* userId, uint16_t credMask, Credentials& creds)
{
    QCC_UNUSED(userId);

    printf("RequestCredentials for authenticating peer name %s using mechanism %s authCount %d\n", authPeer, authMechanism, authCount);
    if (strcmp(authMechanism, KEYX_ECDHE_PSK) == 0) {
        /*
         * Solicit the Pre shared secret
         */
        if ((credMask & AuthListener::CRED_USER_NAME) == AuthListener::CRED_USER_NAME) {
            printf("RequestCredentials received psk ID %s\n", creds.GetUserName().c_str());
        }
        /*
         * Based on the pre shared secret id, the application can retrieve
         * the pre shared secret from storage or from the end user.
         * In this example, the pre shared secret is a hard coded string.
         * Pre-shared keys should be 128 bits long, and generated with a
         * cryptographically secure random number generator.
         */
        qcc::String psk("faaa0af3dd3f1e0379da046a3ab6ca44");
        creds.SetPassword(psk);
        creds.SetExpiration(100); /* set the master secret expiry time to 100 seconds */
        return true;
    }
    return false;
}

void ECDHEKeyXListener::AuthenticationComplete(const char* authMechanism, const char* authPeer, bool success)
{
    QCC_UNUSED(authPeer);
    printf("SampleClientECDHE::AuthenticationComplete Authentication %s %s\n", authMechanism, success ? "successful" : "failed");
}

void HAETest::SetUp()
{
    LOG_NO = 0;
    m_bus = new BusAttachment("CurrentTemperatureTest", true);
    if (!m_bus) {
        printf("BusAttachment creation failed.\n");
        ASSERT_TRUE(false);
    }

    QStatus status = m_bus->Start();
    if (ER_OK != status) {
        delete m_bus;
        ASSERT_TRUE(false)<< "BusAttachment::Start failed " << QCC_StatusText(status);
    }

    status = m_bus->Connect();
    if (ER_OK != status) {
        m_bus->Stop();
        m_bus->Join();
        delete m_bus;
        ASSERT_TRUE(false)<< "BusAttachment::Connect failed " << QCC_StatusText(status);
    }

    m_controller = new HaeController(*m_bus, this);
    status = m_controller->EnablePeerSecurity(ECDHE_KEYX, new ECDHEKeyXListener(), "/.alljoyn_keystore/c_ecdhe.ks", true);

    if (ER_OK == status) {
        printf("EnablePeerSecurity successful.\n");
    } else {
        ASSERT_TRUE(false)<< "EnablePeerSecurity failed " << QCC_StatusText(status);
    }
    m_controller->Start();
}

void HAETest::TearDown()
{
    m_controller->Stop();
    delete m_controller;
    if (m_bus) {
        m_bus->Disconnect();
        m_bus->Stop();
        m_bus->Join();
        delete m_bus;
        m_bus = NULL;
    }
    m_interfaces.clear();
}

void HAETest::WaitForControllee(HaeInterfaceType type)
{
    TEST_LOG_1("The test device listens for an About announcement from the application on the DUT.")
    m_interfaceNameForTest = HaeInterface::GetInterfaceName(type);
    ASSERT_EQ(qcc::Event::Wait(eventOnDeviceAdded, TIMEOUT), ER_OK)<< "Controllee device not found";
    qcc::String name = HaeInterface::GetInterfaceName(type);
    TEST_LOG_1("After receiving an About announcement from the application, the test device joins\n"
                 "   a session with the application at the port specified in the received About announcement\n"
                 "   if there is \"" + name.substr(name.find_last_of('.')+1) + "\" Interface on DUT.");
}

void HAETest::OnDeviceAdded(const char* busname, SessionPort port, const HaeAboutData& data, const AboutObjectDescription& description)
{
    size_t path_num = description.GetPaths(NULL, 0);
    const char** paths = new const char*[path_num];
    description.GetPaths(paths, path_num);

    bool isFound = false;
    for (size_t i = 0; i < path_num; ++i) {
        if (!strncmp(paths[i], "/About", strlen(paths[i]))) {
            continue;
        }
        size_t numInterfaces = description.GetInterfaces(paths[i], NULL, 0);
        const char** interfaces = new const char*[numInterfaces];
        description.GetInterfaces(paths[i], interfaces, numInterfaces);
        for (size_t j = 0; j < numInterfaces; ++j) {
            if (m_interfaceNameForTest.compare(interfaces[j]))
                continue;

            InterfaceInfo info(busname, port, paths[i], const_cast<HaeAboutData&>(data));
            m_controller->JoinDevice(info.busName, port, data, const_cast<AboutObjectDescription&>(description));
            m_interfaces.push_back(info);
            isFound = true;
        }
    }
    if (isFound)
        eventOnDeviceAdded.SetEvent();
}

void HAETest::OnDeviceRemoved(const char* busname)
{
}

void HAETest::OnDeviceSessionJoined(const DeviceInfoPtr& info)
{
}

void HAETest::OnDeviceSessionLost(SessionId id)
{
    ASSERT_TRUE(false);
}