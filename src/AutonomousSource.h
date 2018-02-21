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
	virtual bool IsDoSwitch() = 0;
	virtual bool IsDoScale() = 0;
	virtual Robot::StartLocation GetStartLocation() = 0;
};

#endif /* SRC_AUTONOMOUSSOURCE_H_ */
