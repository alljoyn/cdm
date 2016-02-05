/*
 * RobotCleaningCycleListener.cpp
 *
 *  Created on: Feb 2, 2016
 *      Author: jiny1u
 */

#include "RepeatModeListener.h"
#include <iostream>

using namespace ajn;
using namespace services;

QStatus RepeatModeListener::OnSetRepeatMode(const bool repeatMode)
{
    std::cout << "RepeatModeListener::OnSetRepeatMode() - repeatMode : " << repeatMode << std::endl;
    return ER_OK;
}

QStatus RepeatModeListener::OnGetRepeatMode(bool& repeatMode)
{
    std::cout << "RobotCleaningCycleListener::OnGetRepeatMode()" << std::endl;
    return ER_OK;
}


