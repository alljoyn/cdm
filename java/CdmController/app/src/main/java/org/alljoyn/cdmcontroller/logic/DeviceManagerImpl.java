/*
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
 */

package org.alljoyn.cdmcontroller.logic;

import android.content.Context;
import android.content.Intent;
import android.util.Log;

import org.alljoyn.bus.AboutKeys;
import org.alljoyn.bus.AboutListener;
import org.alljoyn.bus.AboutObjectDescription;
import org.alljoyn.bus.AuthListener;
import org.alljoyn.bus.BusAttachment;
import org.alljoyn.bus.BusException;
import org.alljoyn.bus.BusListener;
import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.Status;
import org.alljoyn.bus.Variant;
import org.alljoyn.cdmcontroller.util.CdmUtil;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.Map;
import java.util.UUID;

public class DeviceManagerImpl extends DeviceManager {

    private final static String TAG = "CDM_DeviceManager";

    private Map<UUID, Device> deviceMap = new HashMap<UUID, Device>();

    private BusAttachment bus = null;

    private ECDHEPSKKeyXListener authListener = new ECDHEPSKKeyXListener();

    private BusListener cdmBusListener = new BusListener() {
        @Override
        public void busDisconnected() {
            super.busDisconnected();
        }

        @Override
        public void busStopping() {
            super.busStopping();
        }
    };

    public class ECDHEPSKKeyXListener implements AuthListener {
        private static final String TAG = "CDM_AuthListener";
        private boolean sendBackKeys = true;

        public ECDHEPSKKeyXListener() {
        }

        public String getMechanisms() {
            return "ALLJOYN_ECDHE_PSK";
        }

        public String getKeyStoreFileName() {
            return DeviceManagerImpl.this.context.getFileStreamPath("alljoyn_keystore").getAbsolutePath();
        }


        public boolean requested(String authMechanism, String authPeer, int count, String userName, AuthRequest[] requests) {
            try {
                Log.d(TAG, "Listener requested with mechanism " + authMechanism);
                if (!authMechanism.equals("ALLJOYN_ECDHE_NULL") &&
                        !authMechanism.equals("ALLJOYN_ECDHE_PSK") &&
                        !authMechanism.equals("ALLJOYN_ECDHE_ECDSA")) {
                    return false;
                }

                for (AuthRequest rqst : requests) {
                    if (rqst instanceof PrivateKeyRequest) {
                        /*
                         * Only the ALLJOYN_ECDHE_ECDSA requests for DSA private key.
                         */
                        if (sendBackKeys) {
                            PrivateKeyRequest pkRqst = (PrivateKeyRequest) rqst;
                            String privateKeyPEM = CLIENT_KEY_PEM;
                            pkRqst.setPrivateKey(privateKeyPEM);
                            Log.d(TAG, "Listener sends back private key " + privateKeyPEM);
                        }
                    } else if (rqst instanceof CertificateRequest) {
                        /*
                         * Only the ALLJOYN_ECDHE_ECDSA requests for certificate.
                         */
                        if (sendBackKeys) {
                            String certChainPEM = CLIENT_CERTIFICATE_PEM + CA_CERTIFICATE_PEM;
                            CertificateRequest certChainRqst = (CertificateRequest) rqst;
                            certChainRqst.setCertificateChain(certChainPEM);
                            Log.d(TAG, "Listener sends back cert chain " + certChainPEM);
                        }
                    } else if (rqst instanceof PasswordRequest) {
                        /*
                         * Only the ECDHE_PSK key exchange requests for the pre shared secret.
                         * Based on the pre shared secret id given the username input variable,
                         * the application can retrieve the pre shared secret
                         * from storage or from the end user.
                         * In this example, the pre shared secret is a hard coded string
                         */
                        PasswordRequest pskRqst = (PasswordRequest) rqst;
                        String psk = "faaa0af3dd3f1e0379da046a3ab6ca44";
                        pskRqst.setPassword(psk.toCharArray());
                        Log.d(TAG, "Listener sends back PSK " + psk);
                    } else if (rqst instanceof VerifyRequest) {
                        /*
                         * Only the ECDHE_ECDSA key exchange sends a VerifyRequest
                         * with the certificate chain from the peer for the
                         * application to verify.
                         * The application has to option to verify the certificate chain.
                         * If the cert chain is validated and trusted then return true; otherwise, return false.
                         */
                        VerifyRequest verifyRqst = (VerifyRequest) rqst;
                        String certPEM = verifyRqst.getCertificateChain();
                        Log.d(TAG, "Listener: verifying cert " + certPEM);
                    } else if (rqst instanceof ExpirationRequest) {
                        ExpirationRequest er = (ExpirationRequest) rqst;
                        er.setExpiration(100); /* expired 100 seconds from now */
                    }
                }

                return true;

            } catch (Exception ex) {
                Log.e(TAG, "Error processing auth request", ex);
            }
            return false;
        }

        public void completed(String authMechanism, String authPeer,
                              boolean authenticated) {
            if (!authenticated) {
                System.out.println("Authentication failed.");
            } else {
                System.out.println("Authentication successful.");
            }
        }

        private final String CA_CERTIFICATE_PEM =
                "-----BEGIN CERTIFICATE-----\n" +
                        "MIIBnzCCAUWgAwIBAgIUdcyHkQndQDgjP2XnhmP43Kak/GAwCgYIKoZIzj0EAwIw\n" +
                        "NTEzMDEGA1UEAwwqQWxsSm95biBFQ0RIRSBTYW1wbGUgQ2VydGlmaWNhdGUgQXV0\n" +
                        "aG9yaXR5MB4XDTE1MDkxMjAyMTYzOFoXDTI1MDkwOTAyMTYzOFowNTEzMDEGA1UE\n" +
                        "AwwqQWxsSm95biBFQ0RIRSBTYW1wbGUgQ2VydGlmaWNhdGUgQXV0aG9yaXR5MFkw\n" +
                        "EwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEhUADDEGG1bvJ4qDDodD2maFmENFSEmhQ\n" +
                        "hvP4iJ82WT7XrhIx/L/XIZo9wKnwNsHJusLVXXMKjyUwcPuVpYU7JqMzMDEwDAYD\n" +
                        "VR0TBAUwAwEB/zAhBgNVHSUEGjAYBgorBgEEAYLefAEBBgorBgEEAYLefAEFMAoG\n" +
                        "CCqGSM49BAMCA0gAMEUCIAWutM+O60m/awMwJvQXHVGXq+z+6nac4KRLDT5OXqn1\n" +
                        "AiEAq/NwQWXJ/FYHBxVOXrKxGZXTFoBiudw9+konMAu1MaE=\n" +
                        "-----END CERTIFICATE-----\n";

        private final String CLIENT_CERTIFICATE_PEM =
                "-----BEGIN CERTIFICATE-----\n" +
                        "MIIBgTCCASegAwIBAgIUK+FyqHDTwJQIGN8qL5LKvuMXvlYwCgYIKoZIzj0EAwIw\n" +
                        "NTEzMDEGA1UEAwwqQWxsSm95biBFQ0RIRSBTYW1wbGUgQ2VydGlmaWNhdGUgQXV0\n" +
                        "aG9yaXR5MB4XDTE1MDkxMjAyMTY0M1oXDTIwMDkxMDAyMTY0M1owJjEkMCIGA1UE\n" +
                        "AwwbQWxsSm95biBFQ0RIRSBTYW1wbGUgQ2xpZW50MFkwEwYHKoZIzj0CAQYIKoZI\n" +
                        "zj0DAQcDQgAENNaoEa6torBhw99OhA1GtHziPr3GgdSHmbggBYagf/sEj/bwim0P\n" +
                        "e/YuTYWkEhQkv30FdjKTybvWoCweaiZkDqMkMCIwCQYDVR0TBAIwADAVBgNVHSUE\n" +
                        "DjAMBgorBgEEAYLefAEBMAoGCCqGSM49BAMCA0gAMEUCIEeWUwtAKw0QKenLPPT6\n" +
                        "UQ5sveMbnCSBzx8MDTBMkarjAiEA1zyiRF6nst3ONfipCUr2+1lOBWb04ojZ4E+m\n" +
                        "oq7cR1w=\n" +
                        "-----END CERTIFICATE-----\n";

        private final String CLIENT_KEY_PEM =
                "-----BEGIN EC PRIVATE KEY-----\n" +
                        "MDECAQEEIAsvmKOj5rmcfE56FhuKD8tRpiixXUyDycaISQslxaLIoAoGCCqGSM49\n" +
                        "AwEH\n" +
                        "-----END EC PRIVATE KEY-----\n";
    };

    private AboutListener m_aboutListener = new AboutListener() {
        @Override
        public void announced(String busName, int version, short port, AboutObjectDescription[] aboutObjectDescriptions, Map<String, Variant> aboutData) {
            bus.enableConcurrentCallbacks();
            if (!aboutData.containsKey(Device.AboutDataKeys.DEVICE_TYPE_DESCRIPTION)) {
                return;
            }

            Log.d(TAG, "announced device : " + busName);

            try {
                byte[] byteUUID = aboutData.get(AboutKeys.ABOUT_APP_ID).getObject(byte[].class);
                UUID appId = CdmUtil.byteArrayToUUID(byteUUID);
                Device device = new DeviceImpl(DeviceManagerImpl.this.context, DeviceManagerImpl.this.bus, appId, busName, version, port, aboutObjectDescriptions, aboutData);
                deviceMap.put(appId, device);
                Intent intent = new Intent(MessageType.ON_DEVICE_ADDED);
                intent.putExtra(IntentKeys.DEVICE_ID, appId);
                DeviceManagerImpl.this.context.sendBroadcast(intent);
            } catch (BusException e) {
                e.printStackTrace();
            }
        }
    };


    public DeviceManagerImpl(Context c) {
        super(c);
    }

    public void init() {
        Log.d(TAG, "Init AllJoyn");

        org.alljoyn.bus.alljoyn.DaemonInit.PrepareDaemon(this.context);

        bus = new BusAttachment(this.context.getPackageName(), BusAttachment.RemoteMessage.Receive);
        Status status = bus.connect();
        if (status != Status.OK) {
            Log.e(TAG, "BusAttachment.connect() return error : " + status);
            return;
        }

        this.bus.registerAuthListener(this.authListener.getMechanisms(), this.authListener, this.authListener.getKeyStoreFileName(), true);

        this.bus.registerBusListener(cdmBusListener);
        this.bus.registerAboutListener(m_aboutListener);

        String[] interfaces = {"*"};

        status = this.bus.whoImplements(interfaces);
        if (status != Status.OK) {
            Log.e(TAG, "BusAttachment.whoImplements() return error : " + status);
        }
    }

    @Override
    public Device getDevice(UUID id) {
        return this.deviceMap.get(id);
    }

    @Override
    public void addDevice(Device device){
        this.deviceMap.put(device.getId(), device);
    }

    @Override
    public Collection<Device> getDevices() {
        Collection<Device> devices = new ArrayList<>();

        for(Device device : deviceMap.values()) {
            if(!device.canAddChildren()){
                devices.add(device);
            }
        }
        return devices;
    }

    @Override
    public Collection<Device> getDeviceGroups() {
        Collection<Device> deviceGroups = new ArrayList<>();

        for(Device device : deviceMap.values()) {
            if(device.canAddChildren()){
                deviceGroups.add(device);
            }
        }
        return deviceGroups;
    }

    @Override
    public void registerBusObject(BusObject busObject, String path) {
        this.bus.registerBusObject(busObject, path);
    }

    @Override
    public Status registerSignalHandlers(Object handler) {
        return this.bus.registerSignalHandlers(handler);
    }

    @Override
    public void unregisterSignalHandlers(Object handler) {
        this.bus.unregisterSignalHandlers(handler);
    }
}