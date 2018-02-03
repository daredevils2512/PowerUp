/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/ClimberRunWing.h>
#include <Commands/CMG_NavXAutoTest.h>
#include <Commands/CMG_UltrasonicAutoTest.h>
#include <Commands/UltrasonicRelayOnOff.h>
#include "OI.h"

#include <WPILib.h>
#include "Commands/LowGear.h"
#include "Commands/HighGear.h"
#include "Commands/UltraSonicStraightDrive.h"
#include "Commands/PIDTurn.h"
#include "Commands/AutoStraightDrive.h"
#include "Commands/ClimberRunWing.h"
#include "Commands/CMG_UltrasonicRelaySwitching.h"
#include "Robot.h"
#include "Util.h"

OI::OI() {
	DRC_rightTrigger.WhileHeld (new LowGear());
	DRC_rightTrigger.WhenReleased (new HighGear());
//	DRC_aButton.WhenPressed(new CMG_NavXAutoTest());
//	DRC_yButton.WhenPressed(new UltrasonicStraightDrive(0.45, 100, Util::RobotSide::leftSide)); //0.5
//	DRC_bButton.WhenPressed(new AutoStraightDrive(24.0, -0.55));
//	DRC_xButton.WhenPressed(new CMG_UltrasonicRelaySwitching());
//	DRC_leftBumper.WhenPressed(new PIDTurn(-90));
//	DRC_rightBumper.WhenPressed(new PIDTurn(90));
//	DRC_startButton.WhenPressed (new CMG_UltrasonicAutoTest());

	CDB_topWhite.WhenPressed(new UltrasonicRelayOnOff(1));
	CDB_topRed.WhenPressed(new UltrasonicRelayOnOff(2));
//	CDB_middleWhite.WhenPressed(new UltrasonicRelayOnOff(3));
//	CDB_bigRed.WhileHeld(new ClimberRunWing(Climber::ClimberWing::leftWing, 0.8)); // run motors to move left wing up
//	CDB_bigRed.WhenReleased(new ClimberRunWing(Climber::ClimberWing::leftWing, 0.0));
//	CDB_bigWhite.WhileHeld(new ClimberRunWing(Climber::ClimberWing::rightWing, 0.8)); // run motors to move right wing up
//	CDB_bigWhite.WhileHeld(new ClimberRunWing(Climber::ClimberWing::rightWing, 0.0));

}

	double OI::GetTurn() {
		//gets turning values
		return Desensitize(driverController.GetRawAxis(4));
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
