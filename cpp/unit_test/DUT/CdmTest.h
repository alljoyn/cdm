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

#ifndef HAETEST_H_
#define HAETEST_H_

#include <alljoyn/hae/HaeController.h>
#include <alljoyn/hae/DeviceListener.h>
#include <qcc/Event.h>
#include <gtest/gtest.h>

#include <iostream>
#include <vector>

#define TIMEOUT 30000

using namespace ajn;
using namespace services;

#define TEST_LOG_1(logMsg)  \
    std::cout << ++LOG_NO << ". " << logMsg << std::endl
#define TEST_LOG_2(logMsg)  \
    std::cout << "  * " << logMsg << std::endl
#define TEST_LOG_3(logMsg)  \
    std::cout << "    - " << logMsg << std::endl
#define TEST_LOG_OBJECT_PATH(logMsg)  \
    std::cout << "[ObjectPath : " << logMsg << "]" << std::endl

class InterfaceInfo
{
public:
    std::string busName;
    std::string deviceName;
    SessionPort sessionPort;
    SessionId sessionId;
    std::string objectPath;
    HaeAboutData aboutData;
    AboutObjectDescription aboutDescription;

    InterfaceInfo()
    {
    }
    InterfaceInfo(const char* name, SessionPort port, const char* path, HaeAboutData& data, AboutObjectDescription& description);
};

static const char* KEYX_ECDHE_PSK = "ALLJOYN_ECDHE_PSK";
static const char* ECDHE_KEYX = "ALLJOYN_ECDHE_PSK";

/* Client's ECDSA certificate and private key. These were generated with the command:
 *
 *   SampleCertificateUtility -createEE 1825 AllJoyn ECDHE Sample Client
 *
 * SampleCertificateUtility is a sample located in the same directory as this.
 */
static const char CLIENT_CERTIFICATE_PEM[] = "-----BEGIN CERTIFICATE-----\n"
    "MIIBgTCCASegAwIBAgIUK+FyqHDTwJQIGN8qL5LKvuMXvlYwCgYIKoZIzj0EAwIw\n"
    "NTEzMDEGA1UEAwwqQWxsSm95biBFQ0RIRSBTYW1wbGUgQ2VydGlmaWNhdGUgQXV0\n"
    "aG9yaXR5MB4XDTE1MDkxMjAyMTY0M1oXDTIwMDkxMDAyMTY0M1owJjEkMCIGA1UE\n"
    "AwwbQWxsSm95biBFQ0RIRSBTYW1wbGUgQ2xpZW50MFkwEwYHKoZIzj0CAQYIKoZI\n"
    "zj0DAQcDQgAENNaoEa6torBhw99OhA1GtHziPr3GgdSHmbggBYagf/sEj/bwim0P\n"
    "e/YuTYWkEhQkv30FdjKTybvWoCweaiZkDqMkMCIwCQYDVR0TBAIwADAVBgNVHSUE\n"
    "DjAMBgorBgEEAYLefAEBMAoGCCqGSM49BAMCA0gAMEUCIEeWUwtAKw0QKenLPPT6\n"
    "UQ5sveMbnCSBzx8MDTBMkarjAiEA1zyiRF6nst3ONfipCUr2+1lOBWb04ojZ4E+m\n"
    "oq7cR1w=\n"
    "-----END CERTIFICATE-----\n";
static const char CLIENT_KEY_PEM[] = "-----BEGIN EC PRIVATE KEY-----\n"
    "MDECAQEEIAsvmKOj5rmcfE56FhuKD8tRpiixXUyDycaISQslxaLIoAoGCCqGSM49\n"
    "AwEH\n"
    "-----END EC PRIVATE KEY-----\n";

/* Certificate Authority's ECDSA certificate. This is used to verify the remote peer's
 * certificate chain.
 *
 *    SampleCertificateUtility -createCA 3650 AllJoyn ECDHE Sample Certificate Authority
 *
 */
static const char CA_CERTIFICATE_PEM[] = "-----BEGIN CERTIFICATE-----\n"
    "MIIBnzCCAUWgAwIBAgIUdcyHkQndQDgjP2XnhmP43Kak/GAwCgYIKoZIzj0EAwIw\n"
    "NTEzMDEGA1UEAwwqQWxsSm95biBFQ0RIRSBTYW1wbGUgQ2VydGlmaWNhdGUgQXV0\n"
    "aG9yaXR5MB4XDTE1MDkxMjAyMTYzOFoXDTI1MDkwOTAyMTYzOFowNTEzMDEGA1UE\n"
    "AwwqQWxsSm95biBFQ0RIRSBTYW1wbGUgQ2VydGlmaWNhdGUgQXV0aG9yaXR5MFkw\n"
    "EwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEhUADDEGG1bvJ4qDDodD2maFmENFSEmhQ\n"
    "hvP4iJ82WT7XrhIx/L/XIZo9wKnwNsHJusLVXXMKjyUwcPuVpYU7JqMzMDEwDAYD\n"
    "VR0TBAUwAwEB/zAhBgNVHSUEGjAYBgorBgEEAYLefAEBBgorBgEEAYLefAEFMAoG\n"
    "CCqGSM49BAMCA0gAMEUCIAWutM+O60m/awMwJvQXHVGXq+z+6nac4KRLDT5OXqn1\n"
    "AiEAq/NwQWXJ/FYHBxVOXrKxGZXTFoBiudw9+konMAu1MaE=\n"
    "-----END CERTIFICATE-----\n";

/*
 * This is the local implementation of the an AuthListener.  ECDHEKeyXListener is
 * designed to only handle ECDHE Key Exchange Authentication requests.
 *
 * If any other authMechanism is used other than ECDHE Key Exchange authentication
 * will fail.
 */

class ECDHEKeyXListener : public AuthListener
{
public:

    ECDHEKeyXListener()
    {
    }

    bool RequestCredentials(const char* authMechanism, const char* authPeer, uint16_t authCount, const char* userId, uint16_t credMask, Credentials& creds);

    void AuthenticationComplete(const char* authMechanism, const char* authPeer, bool success);
};

class HAETest : public ::testing::Test, public DeviceListener, public SessionListener
{
public:
    virtual void SetUp();

    virtual void TearDown();

    virtual void OnDeviceAdded(const char* busname, SessionPort port, const HaeAboutData& data, const AboutObjectDescription& description);
    virtual void OnDeviceRemoved(const char* busname);
    virtual void OnDeviceSessionJoined(const DeviceInfoPtr& info);
    virtual void OnDeviceSessionLost(SessionId sessionId);

    void WaitForControllee(HaeInterfaceType type = (HaeInterfaceType)-1);
protected:
    HaeController* m_controller;
    BusAttachment* m_bus;
    qcc::String m_interfaceNameForTest;
    std::vector<InterfaceInfo> m_interfaces;
    qcc::Event eventOnDeviceAdded;
    int LOG_NO;
};

#endif  // HAETEST_H_
