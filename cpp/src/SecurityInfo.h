 /******************************************************************************
 *  * 
 *    Copyright (c) 2016 Open Connectivity Foundation and AllJoyn Open
 *    Source Project Contributors and others.
 *    
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0

 ******************************************************************************/

#ifndef SECURITYINFO_H_
#define SECURITYINFO_H_

namespace ajn {
namespace services {

class SecurityInfo {
  public:
    SecurityInfo() :
        m_authMechanisms(NULL),
        m_authListener(NULL),
        m_keyStoreFileName(NULL),
        m_isKeyStoreShared(false)
        {}

    ~SecurityInfo() {}

    const char* m_authMechanisms;
    AuthListener* m_authListener;
    const char* m_keyStoreFileName;
    bool m_isKeyStoreShared;
};

}
}

#endif // SECURITYINFO_H_