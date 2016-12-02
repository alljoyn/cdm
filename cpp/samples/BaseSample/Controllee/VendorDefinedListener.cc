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

#include <iostream>
#include "VendorDefinedListener.h"

using namespace std;

QStatus VendorDefinedListener::OnSetTestProperty(int32_t property1)
{
    cout << "VendorDefinedListener::OnSetTestProperty() - property1 : " << property1 << endl;
    return ER_OK;
}

QStatus VendorDefinedListener::OnGetTestProperty(int32_t& property1)
{
    cout << "VendorDefinedListener::OnGetTestProperty()" << endl;
    return ER_OK;
}

QStatus VendorDefinedListener::OnTestMethod(int32_t arg1, qcc::String& errorName, qcc::String& errorMessage)
{
    cout << "VendorDefinedListener::OnTestMethod()- arg1 : " << arg1 << endl;
    return ER_OK;
}