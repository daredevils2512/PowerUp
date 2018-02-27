/*
 * AutonomousSource.h
 *
 *  Created on: Feb 20, 2018
 *      Author: noahg
 */

#ifndef SRC_AUTONOMOUSSOURCE_H_
#define SRC_AUTONOMOUSSOURCE_H_

#include "Robot.h"

class AutonomousSource {
public:
	virtual bool IsDoSwitch();
	virtual bool IsDoScale();
	virtual Robot::StartLocation GetStartLocation();
	virtual ~AutonomousSource() {};

protected:
	bool doSwitch = false;
	bool doScale = false;
	Robot::StartLocation startingPosition = Robot::StartLocation::unknown;
};

#endif /* SRC_AUTONOMOUSSOURCE_H_ */
