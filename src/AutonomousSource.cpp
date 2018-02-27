/*
 * AutonomousSource.cpp
 *
 *  Created on: Feb 26, 2018
 *      Author: noahg
 */
#include "AutonomousSource.h"

bool AutonomousSource::IsDoSwitch() {
	return doSwitch;
}

bool AutonomousSource::IsDoScale() {
	return doScale;
}

Robot::StartLocation AutonomousSource::GetStartLocation() {
	return startingPosition;
}

