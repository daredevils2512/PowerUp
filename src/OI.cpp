/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"

#include <WPILib.h>
#include "Commands/_CMG_NavXAutoTest.h"
#include "Commands/CubeRunIntake.h"
#include "Commands/CubeRunExtake.h"
#include "Commands/CubeIntakeActuate.h"
#include "Commands/CubeExtakeActuate.h"


OI::OI() {
//	//DRC_aButton.WhenPressed(new _CMG_NavXAutoTest());
//	DRC_leftBumper.WhileHeld (new CubeIntakeActuate(true));
//	DRC_leftBumper.WhenReleased (new CubeIntakeActuate(false));
	DRC_leftBumper.WhileHeld(new CubeRunIntake(0.75));
	DRC_leftBumper.WhenReleased(new CubeRunIntake(0.0));
	DRC_rightBumper.WhileHeld(new CubeRunIntake(-0.75));
	DRC_leftBumper.WhenReleased(new CubeRunIntake(0.0));
//	DRC_xButton.WhenPressed(new CubeExtakeActuate(true));
//	DRC_yButton.WhenReleased(new CubeExtakeActuate(false));
	DRC_bButton.WhileHeld(new CubeRunExtake(0.75));
	DRC_bButton.WhenReleased(new CubeRunExtake(0.0));


}

	double OI::GetTurn() {
		//gets turning values
		return Desensitize(-driverController.GetRawAxis(4));
	}
	double OI::GetMove() {
		//gets forward/backward values
		return Desensitize(-driverController.GetRawAxis(1));
	}
	double OI::Desensitize(double value) {
		//set threshold so tiny values on the joystick don't register,
		//sometimes resting value of joystick is not 0
		if (fabs(value) < 0.3) value = 0;
		return value;
	}
