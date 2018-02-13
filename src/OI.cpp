/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/CMG_NavXAutoTest.h>
#include <Commands/CMG_UltrasonicAutoTest.h>
#include "OI.h"

#include <WPILib.h>
#include "Commands/UltraSonicStraightDrive.h"
#include "Commands/PIDTurn.h"
#include "Commands/PIDDriveStraight.h"
#include "Commands/ClimberRunWing.h"
#include "Commands/ElevatorRunToHeight.h"
#include "Commands/CubeIntakeActuate.h"
#include "Commands/CubeRunIntake.h"
#include "Commands/LowGear.h"
#include "Commands/HighGear.h"
#include "Robot.h"
#include "Util.h"


OI::OI() {
	DRC_rightTrigger.WhileHeld(new LowGear());
	DRC_rightTrigger.WhenReleased(new HighGear());
	DRC_aButton.WhenPressed(new CMG_NavXAutoTest());
	DRC_yButton.WhenPressed(new UltrasonicStraightDrive(0.55, 246
			, Util::RobotSide::leftSide)); //0.95 for straight //220 dist 206
	DRC_bButton.WhenPressed(new PIDDriveStraight(136.0));
	DRC_leftBumper.WhenPressed(new PIDTurn(-90));
	DRC_rightBumper.WhenPressed(new PIDTurn(90));
	DRC_startButton.WhenPressed (new CMG_UltrasonicAutoTest());
	DRC_leftTrigger.WhenPressed(new CubeIntakeActuate(true));
	DRC_leftTrigger.WhileHeld(new CubeRunIntake(1.0));
	DRC_leftTrigger.WhenReleased(new CubeIntakeActuate(false));
	DRC_leftTrigger.WhenReleased(new CubeRunIntake(-1.0));

	CDR_bottomLeftBase.WhenPressed(new CubeIntakeActuate(true));
	CDR_bottomRightBase.WhenPressed(new CubeIntakeActuate(false));
	CDR_middleLeftBase.WhileHeld(new CubeRunIntake(-1.0));
	CDR_middleLeftBase.WhenReleased(new CubeRunIntake(0.0));
	CDR_middleRightBase.WhileHeld(new CubeRunIntake(1.0));
	CDR_middleRightBase.WhenReleased(new CubeRunIntake(0.0));
	CDR_trigger.WhenPressed(new CubeIntakeActuate(true));
	CDR_trigger.WhileHeld(new CubeRunIntake(1.0));
	CDR_trigger.WhenReleased(new CubeRunIntake(0.0));
	CDR_trigger.WhenReleased(new CubeIntakeActuate(false));

	CDB_topWhite.WhenPressed(new ElevatorRunToHeight(0.5, 500)); //arbitrary numbers. Need testing
	CDB_topRed.WhenPressed(new ElevatorRunToHeight(0.5, 400)); //arbitrary numbers. Need testing
	CDB_middleWhite.WhenPressed(new ElevatorRunToHeight(0.5, 300)); //arbitrary numbers. Need testing
	CDB_middleRed.WhenPressed(new ElevatorRunToHeight(0.5, 0)); //arbitrary numbers. Need testing
	CDB_bigRed.WhileHeld(new ClimberRunWing (Climber::ClimberWing::leftWing, 0.8));
	CDB_bigRed.WhenReleased(new ClimberRunWing (Climber::ClimberWing::leftWing, 0.0));
	CDB_bigWhite.WhileHeld(new ClimberRunWing (Climber::ClimberWing::rightWing, 0.8));
	CDB_bigWhite.WhenReleased(new ClimberRunWing (Climber::ClimberWing::rightWing, 0.0));



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

	double OI::GetLiftControl() {
		return Desensitize(coDriverController.GetRawAxis(1));
	}
