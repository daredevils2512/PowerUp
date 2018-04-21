/*
 * HighGear.cpp
 *
 *  Created on: Feb 3, 2018
 *      Author: noahg
 */

#include <Commands/HighGear.h>
#include "../Robot.h"

HighGear::HighGear() {
	// TODO Auto-generated constructor stub

}

void HighGear::Execute() {
	if (currentStatus == DoubleSolenoid::kOff) {
		currentStatus = DoubleSolenoid::kForward;
		DrivetrainShift::Execute();
	}
}
