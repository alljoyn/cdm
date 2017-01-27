/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/
#include "commoncontrollerimpl.h"
#include <qcc/Log.h>
#include <alljoyn/Init.h>
#include <alljoyn/version.h>

#include "interfaces/WarpCore/WarpCoreInterface.h"
#include "interfaces/WarpCore/WarpCoreIntfController.h"

using namespace ajn::services;

static const char* KEYX_ECDHE_NULL = "ALLJOYN_ECDHE_NULL";
static const char* KEYX_ECDHE_PSK = "ALLJOYN_ECDHE_PSK";
static const char* KEYX_ECDHE_ECDSA = "ALLJOYN_ECDHE_ECDSA";
static const char* ECDHE_KEYX = "ALLJOYN_ECDHE_PSK";
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


class ECDHEKeyXListener : public ajn::AuthListener {
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
            if ((credMask& ajn::AuthListener::CRED_USER_NAME) == ajn::AuthListener::CRED_USER_NAME) {
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
            creds.SetExpiration(100);  /* set the master secret expiry time to 100 seconds */
            return true;
        } else if (strcmp(authMechanism, KEYX_ECDHE_ECDSA) == 0) {
            /* Supply the private key and certificate. */
            qcc::String privateKeyPEM(CLIENT_KEY_PEM);
            qcc::String certChainPEM;
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
            if ((credMask& ajn::AuthListener::CRED_PRIVATE_KEY) == ajn::AuthListener::CRED_PRIVATE_KEY) {
                creds.SetPrivateKey(privateKeyPEM);
            }
            if ((credMask& ajn::AuthListener::CRED_CERT_CHAIN) == ajn::AuthListener::CRED_CERT_CHAIN) {
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
            if (creds.IsSet(ajn::AuthListener::CRED_CERT_CHAIN)) {
                /*
                 * AllJoyn sends back the certificate chain for the application to verify.
                 * The application has to option to verify the certificate
                 * chain.  If the cert chain is validated and trusted then return true; otherwise, return false.
                 */
                return true;
            }
            return true; //VerifyCertificateChain(creds);
        }
        return false;
    }

    void AuthenticationComplete(const char* authMechanism, const char* authPeer, bool success) {
        QCC_UNUSED(authPeer);
        printf("SampleClientECDHE::AuthenticationComplete Authentication %s %s\n", authMechanism, success ? "successful" : "failed");
    }
};

static ECDHEKeyXListener s_authListener;

//------------------------------------------------------------
// CommonControllerRoot
//------------------------------------------------------------

CommonControllerRoot::CommonControllerRoot(CommonControllerModel *model)
    : model(model)
{
    LockGuard lock(childrenMutex);

    qDebug() << "Starting controller";
    QStatus status = AllJoynInit();
    if (status != ER_OK) {
        qCritical() << "Failed to initialize alljoyn! " << status;
        return;
    }
    status = AllJoynRouterInit();
    if (status != ER_OK) {
        AllJoynShutdown();
        qCritical() << "Failed to initialize alljoyn router! " << status;
        return;
    }

    bus = new ajn::BusAttachment("QController", true);
    status = bus->Start();
    if (status != ER_OK) {
        qCritical() << "Failed to start bus router! " << status;
        delete bus;
        bus = NULL;
        return;
    }

    status = bus->Connect();
    if (status != ER_OK) {
        qCritical() << "Failed to connect bus router! " << status;
        delete bus;
        bus = NULL;
        return;
    }

    status = bus->EnablePeerSecurity(ECDHE_KEYX, &s_authListener, "/.alljoyn_keystore/c_ecdhe.ks", true);
    if (status != ER_OK) {
        qCritical() << "Failed to connect bus router! " << status;
    }

    controller = new ajn::services::CdmController(*bus, this);

    status = controller->Start();
    if (status != ER_OK) {
        qCritical() << "Failed to start controller! " << status;
        return;
    }

    status = controller->RegisterInterface(WarpCoreInterface::INTERFACE_NAME, WarpCoreIntfController::CreateInterface);
    if (status != ER_OK) {
        qCritical() << "Failed to register WarpCore " << status;
        return;
    }
}

CommonControllerRoot::~CommonControllerRoot()
{
    LockGuard lock(childrenMutex);

    if (bus)
    {
        bus->Stop();
        bus->Join();
        delete bus;
        bus = NULL;
    }
    AllJoynRouterShutdown();
    AllJoynShutdown();
}

QString CommonControllerRoot::name() const
{
    return "BUS";
}

void CommonControllerRoot::OnDeviceAdded(const char* busname, ajn::SessionPort port, const ajn::services::CdmAboutData& data, const ajn::AboutObjectDescription& description)
{
    qDebug() << "OnDeviceAdded: " << busname;
    QStatus status = controller->JoinDevice(busname, port, data, const_cast<ajn::AboutObjectDescription&>(description));
    if (status != ER_OK)
    {
        qWarning() << "JoinDevice failed - " << QCC_StatusText(status);
    }
}

void CommonControllerRoot::OnDeviceRemoved(const char* busname)
{
    qDebug() << "OnDeviceRemoved: " << busname;
}

void CommonControllerRoot::OnDeviceSessionJoined(const Ref<ajn::services::DeviceInfo> info)
{
    qDebug() << "OnDeviceSessionJoined: " << info->GetBusName().c_str() << " Session: " << info->GetSessionId();
    QMetaObject::invokeMethod(this, "addSession", Qt::QueuedConnection, Q_ARG(Ref<ajn::services::DeviceInfo>, info));
}

void CommonControllerRoot::OnDeviceSessionLost(ajn::SessionId sessionId)
{
    qDebug() << "OnDeviceSessionLost: " << sessionId;
    QMetaObject::invokeMethod(this, "removeSession", Qt::QueuedConnection, Q_ARG(unsigned int, sessionId));
}

void CommonControllerRoot::addSession(Ref<ajn::services::DeviceInfo> deviceinfo) {
    LockGuard lock(childrenMutex);
    model->beginInsertChild(this, children.size());
    children.push_back(new CommonControllerDevice(this, deviceinfo));
    model->endInsertChild();
}

void CommonControllerRoot::removeSession(unsigned int sessionId) {

    LockGuard lock(childrenMutex);
    int index = -1;
    for (size_t i=0; i<children.size(); i++)
    {
        if (children[i]->getDeviceInfo()->GetSessionId() == sessionId)
        {
            index = i;
            break;
        }
    }

    if (index >= 0)
    {
        model->beginRemoveChild(this, index);
        children.erase(children.begin() + index);
        model->endRemoveChild();
    }
}
