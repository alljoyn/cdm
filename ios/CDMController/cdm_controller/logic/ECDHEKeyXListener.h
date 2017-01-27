////////////////////////////////////////////////////////////////////////////////
// 
// Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
//    Source Project (AJOSP) Contributors and others.
// 
//    SPDX-License-Identifier: Apache-2.0
// 
//    All rights reserved. This program and the accompanying materials are
//    made available under the terms of the Apache License, Version 2.0
//    which accompanies this distribution, and is available at
//    http://www.apache.org/licenses/LICENSE-2.0
// 
//    Copyright 2016 Open Connectivity Foundation and Contributors to
//    AllSeen Alliance. All rights reserved.
// 
//    Permission to use, copy, modify, and/or distribute this software for
//    any purpose with or without fee is hereby granted, provided that the
//    above copyright notice and this permission notice appear in all
//    copies.
// 
//     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
//     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
//     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
//     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
//     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
//     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
//     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
//     PERFORMANCE OF THIS SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#ifndef ECDHEKeyXListener_h
#define ECDHEKeyXListener_h

#import "AuthListener.h"

using namespace std;
using namespace qcc;
using namespace ajn;
using namespace services;

/* This is a list of PEM-encoded CA certificates which forms our trusted root list.
 * If one of these certificates is ever seen on a chain, the chain is considered trusted.
 */
static const char* TRUSTED_ROOTS_PEM[] = {
    /* AllJoyn ECDHE Sample Unused Certificate Authority
     *
     * This is included to demonstrate having more than one trusted root, but as the
     * name implies, it doesn't issue any certificates in this sample. */
    "-----BEGIN CERTIFICATE-----\n"
    "MIIBijCCATCgAwIBAgIUVSjE1Fv/6jP30BfkRXmSoA8sEkIwCgYIKoZIzj0EAwIw\n"
    "PDE6MDgGA1UEAwwxQWxsSm95biBFQ0RIRSBTYW1wbGUgVW51c2VkIENlcnRpZmlj\n"
    "YXRlIEF1dGhvcml0eTAeFw0xNTA1MDcxNzE0MDdaFw0yNTA1MDQxNzE0MDdaMDwx\n"
    "OjA4BgNVBAMMMUFsbEpveW4gRUNESEUgU2FtcGxlIFVudXNlZCBDZXJ0aWZpY2F0\n"
    "ZSBBdXRob3JpdHkwWTATBgcqhkjOPQIBBggqhkjOPQMBBwNCAAS7SmQ19lKjLo2C\n"
    "yyqubmHPRNAo8Eo/i300UWhNAkurVy/WJ3zFMxYNwJeenZ46qJsYb4faZp3iuXF7\n"
    "mllsClzjoxAwDjAMBgNVHRMEBTADAQH/MAoGCCqGSM49BAMCA0gAMEUCIQD/zB3n\n"
    "0+gxUHOdZZadDfLQjMuFxR3LMzUqdBbYZudOGwIgKPT2KYGTW7P/H1hIM6wAyHBB\n"
    "lBOnPXqXjFLodiM+8zM=\n"
    "-----END CERTIFICATE-----\n",
    /* AllJoyn ECDHE Sample Certificate Authority
     * This CA issued the certificates used for the Client and Service in this sample. */
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

static QStatus CountChunksFromEncoded(const String& encoded, const char* beginToken, const char* endToken, size_t* count)
{
    size_t pos;

    *count = 0;
    qcc::String remainder = encoded;
    for (;;) {
        pos = remainder.find(beginToken);
        if (pos == qcc::String::npos) {
            /* no more */
            return ER_OK;
        }
        remainder = remainder.substr(pos + strlen(beginToken));
        pos = remainder.find(endToken);
        if (pos == qcc::String::npos) {
            return ER_OK;
        }
        *count += 1;
        remainder = remainder.substr(pos + strlen(endToken));
    }
    /* Unreachable. */
}

static QStatus GetCertCount(const String& encoded, size_t* count)
{
    const char* const BEGIN_CERT_TAG = "-----BEGIN CERTIFICATE-----";
    const char* const END_CERT_TAG = "-----END CERTIFICATE-----";
    *count = 0;
    return CountChunksFromEncoded(encoded, BEGIN_CERT_TAG, END_CERT_TAG, count);
}

bool VerifyCertificateChain(const AuthListener::Credentials& creds)
{
    /* This certificate chain verification engine does the following:
     *
     * 1. Verifies all certificates in the chain are time-valid.
     * 2. Verifies that all CA's in the chain have the CA flag set to TRUE,
     * 3. Verifies the cryptographic binding between each certificate.
     * 4. Verifies the certificates chain up to one of the trusted roots.
     * 5. Verifies the end-entity certificate is an identity certificate, and the chain is valid
     *    for this purpose.
     *
     * Other implementations may make app-dependent decisions, such as verifying the certificate's
     * subject name equals some known value. */

    /* If we didn't get a certificate chain, there's nothing to validate! */
    if (!creds.IsSet(AuthListener::CRED_CERT_CHAIN)) {
        printf("VerifyCertificateChain FAILED: No certificate chain provided!\n");
        return false;
    }

    /* Decode the list of roots into an array of CertificateX509 objects to later check against. */
    size_t numberOfRoots = sizeof(TRUSTED_ROOTS_PEM) / sizeof(TRUSTED_ROOTS_PEM[0]);
    CertificateX509* trustedRoots = new CertificateX509[numberOfRoots];
    CertificateX509* certChain = NULL;

    QStatus status = ER_OK;

    for (size_t i = 0; (ER_OK == status) && (i < numberOfRoots); i++) {
        status = trustedRoots[i].DecodeCertificatePEM(TRUSTED_ROOTS_PEM[i]);
        if (ER_OK != status) {
            /* Note that PRIuSIZET is not a standards-defined constant, but is defined in AllJoyn to select the
             * correct platform-dependent format specifier for type size_t.
             */
            printf("VerifyCertificateChain FAILED: Failed to decode trusted root at position %" PRIuSIZET ". Status is %s.\n",
                   i, QCC_StatusText(status));
        }
    }

    size_t chainLength = 0;
    if (ER_OK == status) {
        /* Decode the certificates in the chain into another array of CertificateX509 objects. */
        status = GetCertCount(creds.GetCertChain(), &chainLength);
        if (ER_OK != status) {
            printf("VerifyCertificateChain FAILED: Could not get length of certificate chain. Status is %s.\n", QCC_StatusText(status));
        }
    }

    if (ER_OK == status) {
        certChain = new CertificateX509[chainLength];
        status = CertificateX509::DecodeCertChainPEM(creds.GetCertChain(), certChain, chainLength);

        if (ER_OK != status) {
            printf("VerifyCertificateChain FAILED: Failed to decode certificate chain. Status is %s.\n", QCC_StatusText(status));
        }
    }

    /* Here is where you could check additional properties of the certificate, depending on your application and scenario's
     * needs.
     *
     * If you make use of the CN or OU fields of the Distinguished Name, remember that these are UTF-8 strings, so
     * make sure you use a string type that understands UTF-8! In particular, you should never interpret these
     * as null-terminated C strings, because a legal UTF-8 string could have a NUL character anywhere in it. */
    bool trusted = false;

    if (ER_OK == status) {
        /* Most of the time in your code you'll be writing code to check identity certificates, and so we check for that
         * type of certificate in this sample. */
        if (certChain[0].GetType() == CertificateX509::IDENTITY_CERTIFICATE) {
            /* Ensure that the Extended Key Usages are valid for the whole chain. In AllJoyn, we insist the end-entity
             * certificate is not unrestricted (has at least one EKU). We then make sure every Certificate Authority to the
             * root has that EKU present or is unrestricted. We recommend all CA's, including roots, be issued with AllJoyn
             * EKUs to ensure they are not used for other purposes. */
            trusted = CertificateX509::ValidateCertificateTypeInCertChain(certChain, chainLength);
        }

        /* However, we also need to check for unrestricted certificates here.
         * The reason to allow unrestricted here is for backwards compatibility
         * with pre-1509 peers that use certificates without EKUs in Security 1.0
         * contexts. Certificates created by AllJoyn in 1509 and above will always
         * have an EKU indicating the type. */
        if (certChain[0].GetType() == CertificateX509::UNRESTRICTED_CERTIFICATE) {
            /* Loop through and determine if the entire cert chain has type UNRESTRICTED_CERTIFICATE. */
            trusted = true;
            for (size_t iCert = 1; iCert < chainLength; iCert++) {
                if (certChain[iCert].GetType() != CertificateX509::UNRESTRICTED_CERTIFICATE) {
                    trusted = false;
                    break;
                }
            }
        }
        /* trusted will remain false if certificate is not an identity certificate or the whole cert chain is unrestricted. */
    }

    if (trusted && (ER_OK == status)) {
        trusted = false;
        for (size_t iCert = 0; iCert < chainLength; iCert++) {
            /* Every certificate must be time-valid. */
            status = certChain[iCert].VerifyValidity();
            if (ER_OK != status) {
                printf("VerifyCertificatechain FAILED; following certificate is not time valid:\n%s\n",
                       certChain[iCert].ToString().c_str());
                status = ER_OK; /* Reset to ER_OK to signal there was no internal failure. trusted is false. */
                break;
            }

            /* If the current certificate is issued by a trusted root, we're done. */
            for (size_t iRoot = 0; iRoot < numberOfRoots; iRoot++) {
                if (trustedRoots[iRoot].IsIssuerOf(certChain[iCert])) {
                    printf("VerifyCertificateChain SUCCEEDED; trusted root certificate is:\n%s\n",
                           trustedRoots[iRoot].ToString().c_str());
                    trusted = true;
                    /* This break gets us out of this iRoot for loop. */
                    break;
                }
            }
            if (trusted) {
                /* And if we've decided the chain is trusted, break out of the iCert for loop too. */
                break;
            }

            /* If not, and there's a next certificate in the chain, check the chaining between the i'th certificate
             * and the i+1'th.
             */
            if ((iCert + 1) < chainLength) {
                /* First, the next certificate in the chain must be a CA certificate. */
                if (!certChain[iCert + 1].IsCA()) {
                    printf("VerifyCertificateChain FAILED: following certificate is not a CA certificate:\n%s\n",
                           certChain[iCert + 1].ToString().c_str());
                    break;
                }
                /* Now check the chaining. IsIssuerOf checks both that the issuer DN of the i'th certificate equals
                 * the subject DN of the i+1'th certificate in the chain, and verifies the cryptographic signature
                 * was produced by the i+1'th certificate. */
                if (!certChain[iCert + 1].IsIssuerOf(certChain[iCert])) {
                    /* Note that PRIuSIZET is not a standards-defined constant, but is defined in AllJoyn to select the
                     * correct platform-dependent format specifier for type size_t.
                     */
                    printf("VerifyCertificateChain FAILED: certificate at position %" PRIuSIZET " did not issue certificate at position %" PRIuSIZET "\n"
                           "Certificate[%" PRIuSIZET "]:\n%s\n"
                           "Certificate[%" PRIuSIZET "]:\n%s\n",
                           iCert + 1,
                           iCert,
                           iCert + 1,
                           certChain[iCert + 1].ToString().c_str(),
                           iCert,
                           certChain[iCert].ToString().c_str());
                    break;
                }
            }
        }
    }

    /* At this point one of three things has happened:
     * status is not ER_OK: something failed before we could even check the chain, and so we're failing;
     * status is ER_OK and trusted is false: we successfully checked the chain but no trusted root was found
     * or a certificate was not time-valid;
     * or status is ER_OK and trusted is true: we successfully checked the chain and found a trusted root in the path.
     *
     * Clean up and return the appropriate result.
     */

    delete[] trustedRoots;
    delete[] certChain;

    if (ER_OK != status) {
        /* In this case, we're returning false because of some internal failure. */
        return false;
    } else {
        /* Otherwise, return the trusted result. */
        if (!trusted) {
            printf("VerifyCertificateChain FAILED: did not see a trusted root in the chain.\n");
        }
        return trusted;
    }
}

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

#endif /* ECDHEKeyXListener_h */
