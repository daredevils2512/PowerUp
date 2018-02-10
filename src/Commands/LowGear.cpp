/*
 * LowGear.cpp
 *
 *  Created on: Feb 3, 2018
 *      Author: noahg
 */

#include "Commands/LowGear.h"
#include "../RobotMap.h"

LowGear::LowGear() {
	// TODO Auto-generated constructor stub

}

void LowGear::Execute() {
	if (currentStatus == DoubleSolenoid::kOff) {
		currentStatus = DoubleSolenoid::kReverse;
		DrivetrainShift::Execute();
	}
}
