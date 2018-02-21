/*
 * FileAutonomousSource.h
 *
 *  Created on: Feb 20, 2018
 *      Author: noahg
 */

#ifndef SRC_FILEAUTONOMOUSSOURCE_H_
#define SRC_FILEAUTONOMOUSSOURCE_H_

#include <string>
#include "AutonomousSource.h"

class FileAutonomousSource :  public AutonomousSource {
public:
	FileAutonomousSource(std::string filename);
	virtual bool IsDoSwitch();
	virtual bool IsDoScale();
	virtual Robot::StartLocation GetStartLocation();

private:
	bool doSwitch = false;
	bool doScale = false;
	Robot::StartLocation startingPosition = Robot::StartLocation::unknown;
};

#endif /* SRC_FILEAUTONOMOUSSOURCE_H_ */

