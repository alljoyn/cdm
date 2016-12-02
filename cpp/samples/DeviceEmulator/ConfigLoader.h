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
#ifndef CONFIGLOADER_H_
#define CONFIGLOADER_H_

#include <string>
#include <vector>
#include <alljoyn/cdm/interfaces/CdmInterfaceTypes.h>

using namespace std;

namespace ajn {
namespace services {

typedef vector<pair<CdmInterfaceType, string> > InterfaceList; // <interface type, object path>

class CdmAboutData;

class ConfigLoader
{
  private:
    string m_path;

  public:
    ConfigLoader(const string& path) : m_path(path) {}
    bool Load(CdmAboutData& data, InterfaceList& list);

    static const char* DEVICE_EMULATOR;
    static const char* ABOUT_DATA;
    static const char* INTERFACE_LIST;
    static const char* OBJECT;
    static const char* PATH;
    static const char* INTERFACE;
    static const char* NAME;
};

}
}

#endif // CONFIGLOADER_H_