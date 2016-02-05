/*
 * RobotCleaningCycleListener.h
 *
 *  Created on: Feb 2, 2016
 *      Author: jiny1u
 */

#ifndef REPEATMODELISTENER_H_
#define REPEATMODELISTENER_H_

#include <alljoyn/hae/interfaces/operation/RepeatModeIntfControlleeListener.h>

namespace ajn {
namespace services {


class RepeatModeListener : public RepeatModeIntfControlleeListener {
public:
    virtual QStatus OnSetRepeatMode(const bool repeatMode);
    virtual QStatus OnGetRepeatMode(bool& repeatMode);
};

} /* namespace services */
} /* namespace ajn */
#endif /* REPEATMODELISTENER_H_ */
