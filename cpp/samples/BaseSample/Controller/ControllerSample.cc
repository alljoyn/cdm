#include <qcc/String.h>
#include <qcc/Log.h>
#include "ControllerSample.h"
#include "BasicCommands.h"
#include "DeviceCommands.h"
#include "../SampleCertificateChainEngine.h"

using namespace std;
using namespace qcc;
using namespace ajn;
using namespace services;

static const char* KEYX_ECDHE_NULL = "ALLJOYN_ECDHE_NULL";
static const char* KEYX_ECDHE_PSK = "ALLJOYN_ECDHE_PSK";
static const char* KEYX_ECDHE_ECDSA = "ALLJOYN_ECDHE_ECDSA";
static const char* ECDHE_KEYX = "ALLJOYN_ECDHE_PSK";

/* Client's ECDSA certificate and private key. These were generated with the command:
 *
 *   SampleCertificateUtility -createEE 1825 AllJoyn ECDHE Sample Client
 *
 * SampleCertificateUtility is a sample located in the same directory as this.
 */
static const char CLIENT_CERTIFICATE_PEM[] =
    "-----BEGIN CERTIFICATE-----\n"
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
static const char CLIENT_KEY_PEM[] =
    "-----BEGIN EC PRIVATE KEY-----\n"
    "MDECAQEEIAsvmKOj5rmcfE56FhuKD8tRpiixXUyDycaISQslxaLIoAoGCCqGSM49\n"
    "AwEH\n"
    "-----END EC PRIVATE KEY-----\n";

/* Certificate Authority's ECDSA certificate. This is used to verify the remote peer's
 * certificate chain.
 *
 *    SampleCertificateUtility -createCA 3650 AllJoyn ECDHE Sample Certificate Authority
 *
 */
static const char CA_CERTIFICATE_PEM[] =
    "-----BEGIN CERTIFICATE-----\n"
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

class ECDHEKeyXListener : public AuthListener {
  public:

    ECDHEKeyXListener()
    {
    }

    bool RequestCredentials(const char* authMechanism, const char* authPeer, uint16_t authCount, const char* userId, uint16_t credMask, Credentials& creds)
    {
        QCC_UNUSED(userId);

        printf("RequestCredentials for authenticating peer name %s using mechanism %s authCount %d\n", authPeer, authMechanism, authCount);
        if (strcmp(authMechanism, KEYX_ECDHE_NULL) == 0) {
            creds.SetExpiration(100);  /* set the master secret expiry time to 100 seconds */
            return true;
        } else if (strcmp(authMechanism, KEYX_ECDHE_PSK) == 0) {
            /*
             * Solicit the Pre shared secret
             */
            if ((credMask& AuthListener::CRED_USER_NAME) == AuthListener::CRED_USER_NAME) {
                printf("RequestCredentials received psk ID %s\n", creds.GetUserName().c_str());
            }
            /*
             * Based on the pre shared secret id, the application can retrieve
             * the pre shared secret from storage or from the end user.
             * In this example, the pre shared secret is a hard coded string.
             * Pre-shared keys should be 128 bits long, and generated with a
             * cryptographically secure random number generator.
             */
            String psk("faaa0af3dd3f1e0379da046a3ab6ca44");
            creds.SetPassword(psk);
            creds.SetExpiration(100);  /* set the master secret expiry time to 100 seconds */
            return true;
        } else if (strcmp(authMechanism, KEYX_ECDHE_ECDSA) == 0) {
            /* Supply the private key and certificate. */
            String privateKeyPEM(CLIENT_KEY_PEM);
            String certChainPEM;
            /* In constructing the certificate chain, the node's certificate comes first,
             * and then each Certificate Authority appears in order, with the last entry being the
             * root certificate. In this sample, we only have a chain of length two. If there were
             * additional intermediate CAs along the path, those would appear in order between the end
             * entity certificate and the root.
             *
             * It's a common optimization to omit the root certificate since the remote peer should already
             * have it, if it's a trusted root. Since this chain has no intermediates, we include the whole
             * chain for demonstrative purposes. */
            certChainPEM.assign(CLIENT_CERTIFICATE_PEM);
            certChainPEM.append(CA_CERTIFICATE_PEM);
            if ((credMask& AuthListener::CRED_PRIVATE_KEY) == AuthListener::CRED_PRIVATE_KEY) {
                creds.SetPrivateKey(privateKeyPEM);
            }
            if ((credMask& AuthListener::CRED_CERT_CHAIN) == AuthListener::CRED_CERT_CHAIN) {
                creds.SetCertChain(certChainPEM);
            }
            creds.SetExpiration(100);  /* set the master secret expiry time to 100 seconds */
            return true;
        }
        return false;
    }

    bool VerifyCredentials(const char* authMechanism, const char* authPeer, const Credentials& creds)
    {
        QCC_UNUSED(authPeer);
        /* only the ECDHE_ECDSA calls for peer credential verification */
        if (strcmp(authMechanism, KEYX_ECDHE_ECDSA) == 0) {
            if (creds.IsSet(AuthListener::CRED_CERT_CHAIN)) {
                /*
                 * AllJoyn sends back the certificate chain for the application to verify.
                 * The application has to option to verify the certificate
                 * chain.  If the cert chain is validated and trusted then return true; otherwise, return false.
                 */
                return true;
            }
            return VerifyCertificateChain(creds);
        }
        return false;
    }

    void AuthenticationComplete(const char* authMechanism, const char* authPeer, bool success) {
        QCC_UNUSED(authPeer);
        printf("SampleClientECDHE::AuthenticationComplete Authentication %s %s\n", authMechanism, success ? "successful" : "failed");
    }
};

static ECDHEKeyXListener s_authListener;

/////////////////////////////////////////////////////////////////////////////////////////
ControllerSample::ControllerSample(BusAttachment* bus)
  : m_bus(bus), m_controller(NULL), m_rootCommands(NULL)
{
}

ControllerSample::~ControllerSample()
{
}

QStatus ControllerSample::Init()
{
    QStatus status = ER_OK;

    m_controller = new HaeController(*m_bus, this);
    if (!m_controller) {
        status = ER_OUT_OF_MEMORY;
        printf("Controller creation failed (%s)\n", QCC_StatusText(status));
        return status;
    }
    m_rootCommands = new BasicControllerCommands(this);
    if (!m_rootCommands) {
        status = ER_OUT_OF_MEMORY;
        delete m_controller;
        printf("m_rootCommand creation failed (%s)\n", QCC_StatusText(status));
        return status;
    }
    PushCommands(m_rootCommands);

    InterestDeviceList list;
    status = m_controller->Init(list);
    if (ER_OK != status) {
        delete m_controller;
        m_controller = NULL;
        delete m_rootCommands;
        m_rootCommands = NULL;
        printf("Controller init failed (%s)\n", QCC_StatusText(status));
        return status;
    }

    //QCC_SetDebugLevel("ALLJOYN", 3);
    //QCC_SetDebugLevel("ALLJOYN_AUTH", 3);
    //QCC_SetDebugLevel("CRYPTO", 3);
    //QCC_SetDebugLevel("AUTH_KEY_EXCHANGER", 3);

    /*
     * note the location of the keystore file has been specified and the
     * isShared parameter is being set to true. So this keystore file can
     * be used by multiple applications.
     */
    status = m_controller->EnablePeerSecurity(ECDHE_KEYX, &s_authListener, "/.alljoyn_keystore/c_ecdhe.ks", true);

    if (ER_OK == status) {
        printf("EnablePeerSecurity successful.\n");
    } else {
        printf("EnablePeerSecurity failed (%s).\n", QCC_StatusText(status));
    }

    status = m_controller->Start();
    if (ER_OK != status) {
        delete m_controller;
        m_controller = NULL;
        delete m_rootCommands;
        m_rootCommands = NULL;
        printf("Controller start failed (%s)\n", QCC_StatusText(status));
        return status;
    }

    return status;
}

void ControllerSample::Deinit()
{
    m_controller->Stop();
    if (m_controller) {
        delete m_controller;
        m_controller = 0;
    }

    if (m_rootCommands) {
        delete m_rootCommands;
        m_rootCommands = 0;
    }
}

void ControllerSample::OnDeviceAdded(const char* busname,
        SessionPort port,
        const HaeAboutData& data,
        const AboutObjectDescription& description)
{
    cout << "Device Added (bus: " << busname <<",  port: "<< port << ")" << endl;
    //printAboutData(const_cast<HaeAboutData&>(data), "en", 2);

    FoundDeviceInfo info(busname, port, const_cast<HaeAboutData&>(data), const_cast<AboutObjectDescription&>(description));
    m_deviceList[busname] = info;
}

void ControllerSample::OnDeviceRemoved(const char* busname)
{
    cout << "Device lost(device name: "<< busname << ")" << endl;

    FoundDeviceMap::iterator itr = m_deviceList.begin();
    while (itr != m_deviceList.end()) {
        if (itr->first.compare(busname) == 0) {
            m_deviceList.erase(itr);
        }
        ++itr;
    }
}

void ControllerSample::OnDeviceSessionJoined(const DeviceInfoPtr& info)
{
    cout << "Device session joined (session id: "<< info->GetSessionId() << ")" << endl;

    m_deviceList[info->GetBusName()].sessionId = info->GetSessionId();

    m_lastSession = info->GetSessionId();

    DeviceCommands* command = new DeviceCommands(this, const_cast<DeviceInfoPtr&>(info));
    GetCurrentCommands()->RegisterChildCommands(info->GetBusName(), command);
    PushCommands(command);
}

void ControllerSample::OnDeviceSessionLost(SessionId id)
{
    cout << "Device session lost(session id: "<< id << ")" << endl;

    while(GetCommandsQueueSize() > 1) {
        PopCommands();
    }
}

FoundDeviceInfo* ControllerSample::GetFoundDeviceInfo(int index)
{
    FoundDeviceMap::iterator itr = m_deviceList.begin();
    while (index != 1 && itr != m_deviceList.end()) {
        ++itr;
        --index;
    }
    if (itr != m_deviceList.end()) {
        return &(itr->second);
    }
    return 0;
}

HaeInterface* ControllerSample::CreateInterface(const HaeInterfaceType type, const std::string& busName, const qcc::String& objectPath, const SessionId& sessionId, InterfaceControllerListener& listener)
{
    return m_controller->CreateInterface(type, busName, objectPath, sessionId, listener);
}


const HaeInterfaceType ControllerSample::RegisterVendorDefinedInterface(const qcc::String& interfaceName, CreateIntfControllerFptr createIntfController)
{
    return m_controller->RegisterVendorDefinedInterface(interfaceName, createIntfController);
}

void ControllerSample::DropDeviceSession()
{
    QStatus status = ER_OK;

    cout << "Dropping session for device: " << m_lastSession << endl;

    status = m_bus->LeaveSession(m_lastSession);
    if(status != ER_OK) {
        cout << "Failed to leave the session: " << status << endl;
    }
}