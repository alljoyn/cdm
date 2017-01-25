/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 * Source Project (AJOSP) Contributors and others.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * All rights reserved. This program and the accompanying materials are
 * made available under the terms of the Apache License, Version 2.0
 * which accompanies this distribution, and is available at
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Copyright 2016 Open Connectivity Foundation and Contributors to
 * AllSeen Alliance. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all
 * copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <qcc/String.h>
#include "ControlleeSample.h"
#include "../SampleCertificateChainEngine.h"

using namespace std;
using namespace qcc;
using namespace ajn;
using namespace services;

#define ABOUT_SESSION_PORT 900
static const char* KEYX_ECDHE_NULL = "ALLJOYN_ECDHE_NULL";
static const char* KEYX_ECDHE_PSK = "ALLJOYN_ECDHE_PSK";
static const char* KEYX_ECDHE_ECDSA = "ALLJOYN_ECDHE_ECDSA";
static const char* ECDHE_KEYX = "ALLJOYN_ECDHE_ECDSA ALLJOYN_ECDHE_PSK ALLJOYN_ECDHE_NULL";
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

        printf("RequestCredentials for authenticating %s using mechanism %s authCount %d\n", authPeer, authMechanism, authCount);

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
            static const char ecdsaPrivateKeyPEM[] = {
                "-----BEGIN EC PRIVATE KEY-----\n"
                "MDECAQEEIP7pbEF7CiuHpW7FSodaUZRiBQKT0ydBJtm8TdaqFGRdoAoGCCqGSM49\n"
                "AwEH\n"
                "-----END EC PRIVATE KEY-----\n"

            };

            /* This chain is the service's certificate first followed by the CA's certificate.
             * This is not an array of strings; it is one single string with the certificates
             * concatenated together.
             *
             * A common optimization is to omit the trusted root from the chain, and only send
             * the end entity and any intermediate CAs, as presenting it to the remote peer is
             * not necessary; if the remote peer trusts the root, it already has the root's
             * certificate to check. It is included here for demonstrative purposes. */
            static const char ecdsaCertChainX509PEM[] = {
                "-----BEGIN CERTIFICATE-----\n"
                "MIIBgDCCASegAwIBAgIUaWYhK64WMTXX2P7Mx9+jPS8nM/IwCgYIKoZIzj0EAwIw\n"
                "NTEzMDEGA1UEAwwqQWxsSm95biBFQ0RIRSBTYW1wbGUgQ2VydGlmaWNhdGUgQXV0\n"
                "aG9yaXR5MB4XDTE1MDkxMjAyMjAzNVoXDTIwMDkxMDAyMjAzNVowJjEkMCIGA1UE\n"
                "AwwbQWxsSm95biBFQ0RIRSBTYW1wbGUgU2VydmVyMFkwEwYHKoZIzj0CAQYIKoZI\n"
                "zj0DAQcDQgAEDbQwLViVEHKnNwZ8DQJHIVoLohH4cInElLJ2DC73+eT8Y3Se2bMv\n"
                "yMFE70OovRyLnC53conK2WqIOQAOp92saKMkMCIwCQYDVR0TBAIwADAVBgNVHSUE\n"
                "DjAMBgorBgEEAYLefAEBMAoGCCqGSM49BAMCA0cAMEQCIHDb8SVrYon3EYaf6U57\n"
                "d+xcBtr4kAN8GXSrQ3zuVgGSAiB2o+faXMa6O3Ae5+dB3kPOVMiOFg3WryPgYEzb\n"
                "PN/PTg==\n"
                "-----END CERTIFICATE-----\n"
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
                "-----END CERTIFICATE-----\n"

            };
            /*
             * The application may provide the DSA private key and public key in the certificate.
             */
            if ((credMask& AuthListener::CRED_PRIVATE_KEY) == AuthListener::CRED_PRIVATE_KEY) {
                String pk(ecdsaPrivateKeyPEM, strlen(ecdsaPrivateKeyPEM));
                creds.SetPrivateKey(pk);
            }
            if ((credMask& AuthListener::CRED_CERT_CHAIN) == AuthListener::CRED_CERT_CHAIN) {
                String cert(ecdsaCertChainX509PEM, strlen(ecdsaCertChainX509PEM));
                creds.SetCertChain(cert);
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
                 * The application has to option to verify the certificate chain.  If the cert chain is validated and trusted then return true; otherwise, return false. */
                printf("VerifyCredentials receives cert chain %s\n", creds.GetCertChain().c_str());
            }
            return VerifyCertificateChain(creds);
        }
        return false;
    }

    void AuthenticationComplete(const char* authMechanism, const char* authPeer, bool success) {
        QCC_UNUSED(authPeer);
        printf("SampleServiceECDHE::AuthenticationComplete Authentication %s %s\n", authMechanism, success ? "successful" : "failed");
    }

};

static ECDHEKeyXListener s_authListener;

/////////////////////////////////////////////////////////////////////////////////////////
ControlleeSample::ControlleeSample(BusAttachment* bus, CdmAboutData* aboutData)
  : m_bus(bus), m_aboutData(aboutData), m_aboutObj(NULL), m_aboutSessionListener(NULL),
    m_controllee(NULL)
{
}

ControlleeSample::~ControlleeSample()
{
}


void ControlleeSample::InitSample()
{
}

QStatus ControlleeSample::Init()
{
    QStatus status = ER_OK;

    if (!m_aboutData) {
        status = ER_FAIL;
        printf("m_aboutData is NULL. (%s)\n", QCC_StatusText(status));
        return status;
    }

    m_controllee = new CdmControllee(*m_bus);
    if (!m_controllee) {
        status = ER_OUT_OF_MEMORY;
        printf("CdmControllee creation failed. (%s)\n", QCC_StatusText(status));
        return status;
    }

    InitSample();
    CreateInterfaces();

    status = m_bus->EnablePeerSecurity(ECDHE_KEYX, &s_authListener, "/.alljoyn_keystore/s_ecdhe.ks", false, NULL);
    if (ER_OK == status) {
        printf("EnablePeerSecurity successful.\n");
    } else {
        printf("EnablePeerSecurity failed (%s).\n", QCC_StatusText(status));
        return status;
    }

    m_controllee->Start();

    SetInitialProperty();

    status = AnnounceAboutObj();
    if (status != ER_OK){
        printf("AnnounceAboutObj failed. (%s)\n", QCC_StatusText(status));
        delete m_controllee;
        return status;
    }

    return status;
}

void ControlleeSample::Deinit()
{
    m_controllee->Stop();
    if (m_controllee) {
        delete m_controllee;
        m_controllee = 0;
    }

    UnannounceAboutObj();
}

QStatus ControlleeSample::AnnounceAboutObj()
{
    QStatus status = ER_OK;

    if (!m_bus) {
        status = ER_FAIL;
        printf("bus is NULL. (%s)", QCC_StatusText(status));
        return status;
    }

    m_aboutSessionListener = new AboutSessionListener();
    if (!m_aboutSessionListener) {
        status = ER_OUT_OF_MEMORY;
        printf("SessionPortListener creation failed. (%s)\n", QCC_StatusText(status));
        return status;
    }
    SessionPort port = ABOUT_SESSION_PORT;
    SessionOpts opts(SessionOpts::TRAFFIC_MESSAGES, false, SessionOpts::PROXIMITY_ANY, TRANSPORT_ANY);
    status = m_bus->BindSessionPort(port, opts, *m_aboutSessionListener);
    if (status != ER_OK) {
        delete m_aboutSessionListener;
        m_aboutSessionListener = NULL;
        printf("BindSessionPort failed. (%s)\n", QCC_StatusText(status));
        return status;
    }

    m_aboutObj = new AboutObj(*m_bus, BusObject::ANNOUNCED);
    if (!m_aboutObj) {
        delete m_aboutSessionListener;
        m_aboutSessionListener = NULL;
        printf("About Object creation failed. (%s)\n", QCC_StatusText(status));
        return status;
    }

    status = m_aboutObj->Announce(ABOUT_SESSION_PORT, *m_aboutData);
    if (status != ER_OK) {
        delete m_aboutObj;
        m_aboutObj = NULL;
        delete m_aboutSessionListener;
        m_aboutSessionListener = NULL;
        printf("About announcement failed. (%s)\n", QCC_StatusText(status));
        return status;
    }

    return status;
}

void ControlleeSample::UnannounceAboutObj()
{
    if (m_bus) {
        m_bus->UnbindSessionPort(ABOUT_SESSION_PORT);
    }

    if (m_aboutSessionListener) {
        delete m_aboutSessionListener;
        m_aboutSessionListener = NULL;

    }
}
