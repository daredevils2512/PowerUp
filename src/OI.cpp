/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"

#include <WPILib.h>
#include "Commands/_CMG_NavXAutoTest.h"
#include "Commands/UltraSonicStraightDrive.h"
#include "Commands/PIDTurn.h"
#include "Commands/AutoStraightDrive.h"
#include "Commands/_CMG_UltrasonicAutoTest.h"
#include "Commands/RelayOnOff.h"
#include "Robot.h"
#include "Util.h"

OI::OI() {
	DRC_aButton.WhenPressed(new _CMG_NavXAutoTest());
	DRC_yButton.WhenPressed(new UltrasonicStraightDrive(0.70, 224, Util::RobotSide::leftSide)); //0.5
	DRC_bButton.WhenPressed(new AutoStraightDrive(24.0, -0.55));
	DRC_xButton.WhenPressed(new RelayOnOff());
	DRC_leftBumper.WhenPressed(new PIDTurn(-90));
	DRC_rightBumper.WhenPressed(new PIDTurn(90));
	DRC_startButton.WhenPressed (new _CMG_UltrasonicAutoTest());
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
		if (fabs(value) < 0.25) value = 0; //0.3
		return value;
	}
