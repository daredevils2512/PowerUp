/*
 * AutoStraightDriveBackward.h
 *
 *  Created on: Mar 5, 2018
 *      Author: cmorton
 */

#ifndef SRC_COMMANDS_AUTOSTRAIGHTDRIVEBACKWARD_H_
#define SRC_COMMANDS_AUTOSTRAIGHTDRIVEBACKWARD_H_

#include <Commands/AutoStraightDriveForward.h>

class AutoStraightDriveBackward: public AutoStraightDriveForward {
public:
	AutoStraightDriveBackward(double targetFeet, double speed);
	virtual ~AutoStraightDriveBackward();
};

#endif /* SRC_COMMANDS_AUTOSTRAIGHTDRIVEBACKWARD_H_ */
