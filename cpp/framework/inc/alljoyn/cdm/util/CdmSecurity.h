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


#ifndef CDM_SECURITY_H_
#define CDM_SECURITY_H_

#include <alljoyn/Status.h>
#include <alljoyn/cdm/common/CdmTypes.h>
#include <qcc/String.h>

namespace ajn {
namespace services {
//======================================================================


class CdmSecurity
{
  public:

    /**
     * Constructor
     * @param[in] busAttachment
     */
    CdmSecurity(BusAttachment& busAttachment);

    ~CdmSecurity();

    /**
     * After setting the security parameters, call this. It will call
     * BusAttachment::EnablePeerSecurity for you.
     */
    QStatus Enable();

    /**
     * After setting the security parameters, call this. It will call
     * BusAttachment::EnablePeerSecurity for you.
     *
     * @param[in] keyStoreFileName  filepath to the keystore
     * @param[in] isShared  is the keystore shared
     */
    QStatus Enable(const char* keyStoreFileName, bool isShared);

    /**
     * There may be multiple concatenated certificates within the string.
     */
    QStatus AddTrustedRoot(const qcc::String& cert);

    /**
     * Set the private key for ECDHE_ECDSA authentication.
     *
     * @param[in] key a PEM encoded key 
     */
    CdmSecurity& SetEcdsaPrivateKeyPEM(const qcc::String& key);

    /**
     * Set the certificate chain for ECDHE_ECDSA authentication.
     * The application may provide the DSA private key and public key in the certificate.
     *
     * @param[in] certChain one or more certificates in PEM format and concatenated together.
     */
    CdmSecurity& SetEcdsaCertChainX509PEM(const qcc::String& certChain);

    /**
     * @param[in] pwd a pre-shared key for the old ECDHE_PSK authentication method or
     * a password for the ECDHE_SPEKE method.
     */
    CdmSecurity& SetPassword(const qcc::String& pwd);

    /**
     * @param expirationSeconds  The master secret's expiration time in seconds.
     */
    CdmSecurity& SetExpiration(uint32_t expirationSeconds);

    /**
     * @param listener for security events.  This is optional.
     */
    CdmSecurity& SetPermissionListener(Ref<PermissionConfigurationListener> listener);

    /**
     * @param pathPrefix Extensions of .pub and .priv will be used
     * to read the files.
     */
    CdmSecurity& LoadFiles(const qcc::String& pathPrefix);

  private:
    class Impl;

    Impl* m_impl;
};

//======================================================================
} // namespace services
} // namespace ajn

#endif // CDM_SECURITY_H_
