/*
 * AutoStraightDriveBackward.cpp
 *
 *  Created on: Mar 5, 2018
 *      Author: cmorton
 */

#include <Commands/AutoStraightDriveBackward.h>

AutoStraightDriveBackward::AutoStraightDriveBackward(double targetFeet, double speed) : AutoStraightDriveForward(targetFeet, speed){
	//since we are supering to forward, we have to be positive
	this->m_speed = abs(speed);
}

AutoStraightDriveBackward::~AutoStraightDriveBackward() {
	// TODO Auto-generated destructor stub
}

