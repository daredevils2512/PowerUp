/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/CMG_IntakeCube.h>
#include <Commands/CMG_ExtakeCube.h>
#include "OI.h"

#include <WPILib.h>
#include "Commands/ClimberRunWinch.h"
#include "Commands/ClimberRunDeploy.h"
#include "Commands/UltraSonicStraightDrive.h"
#include "Commands/PIDTurn.h"
#include "Commands/PIDDriveStraight.h"
#include "Commands/ElevatorRunToHeight.h"
#include "Commands/ElevatorRunLift.h"
#include "Commands/CubeIntakeActuate.h"
#include "Commands/ElevatorResetEncoder.h"
#include "Commands/CubeRunIntake.h"
#include "Commands/LowGear.h"
#include "Commands/HighGear.h"
#include "Commands/AutoStraightDriveForward.h"
#include "Commands/AutoStraightDriveBackward.h"
#include "Commands/CubeIntakeDeploy.h"
#include "Robot.h"
#include "Util.h"


OI::OI() {
	DRC_leftTrigger.WhileHeld(new CubeRunIntake(-1.0)); //pull me in dad
		DRC_leftTrigger.WhenReleased(new CubeRunIntake(0.0));
	DRC_rightTrigger.WhileHeld(new HighGear()); //drop a gear
	DRC_rightTrigger.WhenReleased(new LowGear());
	DRC_leftBumper.WhenPressed(new CubeIntakeActuateOpen()); //spread
	DRC_rightBumper.WhenPressed(new CubeIntakeActuateClose()); //retract
	DRC_xButton.WhileHeld(new CubeRunIntake(1.0)); //thanks for flying air 2512
		DRC_xButton.WhenReleased(new CubeRunIntake(0.0));

	CDR_trigger.WhileHeld(new CMG_ExtakeCube()); //normal send out
		CDR_trigger.WhenReleased(new CubeRunIntake(0.0));
	CDR_sideJoystickButton.WhileHeld(new CubeRunIntake(0.55)); //medium send out
		CDR_sideJoystickButton.WhenReleased(new CubeRunIntake(0.0));
	CDR_topLeftJoystick.WhileHeld (new CubeRunIntake(1.0)); //full send out
	CDR_topLeftJoystick.WhenReleased (new CubeRunIntake(0.0)); //stop intake
	CDR_bottomLeftJoystick.WhileHeld(new CubeRunIntake(0.4)); //soft send out
	CDR_bottomLeftJoystick.WhenReleased(new CubeRunIntake(0.0)); //stop intake
	CDR_topRightJoystick.WhenPressed(new CubeIntakeActuateClose()); //actuate intake arms in
	CDR_bottomRightJoystick.WhenPressed(new CubeIntakeActuateOpen()); //actuate intake arms out

	CDR_topLeftBase.WhenPressed(new CubeIntakeDeploy(true)); //deploy intake
	CDR_topRightBase.WhenPressed(new CubeIntakeDeploy(false)); //back
	CDR_middleLeftBase.WhileHeld(new CubeRunIntake(-1.0)); //alt run cube in
	CDR_middleLeftBase.WhenReleased(new CubeRunIntake(0.0)); //stop intake
	CDR_middleRightBase.WhileHeld(new CubeRunIntake(1.0)); //alt run cube out
	CDR_middleRightBase.WhenReleased(new CubeRunIntake(0.0)); //stop intake
//	CDR_bottomLeftBase.WhileHeld(new ClimberRunWinch(-1.0)); //run winch out, robot down
//	CDR_bottomLeftBase.WhenReleased(new ClimberRunWinch(0.0));

	CDB_bigWhite.WhileHeld(new ElevatorRunLift (0.7)); //run lift up
	CDB_bigRed.WhileHeld(new ElevatorRunLift (-0.50)); //run lift down
	CDB_green.WhenPressed(new ElevatorResetEncoder()); //manually reset encoder
//	CDB_yellow.WhileHeld(new ClimberRunWinch(1.0)); //run winch in, robot up
//	CDB_yellow.WhenReleased(new ClimberRunWinch(0.0));
//	CDB_topWhite.WhileHeld(new ClimberRunDeploy(1.0)); //hooks up
//	CDB_topWhite.WhenReleased(new ClimberRunDeploy(0.0));
//	CDB_topRed.WhileHeld(new ClimberRunDeploy(-0.75)); //hooks down
//	CDB_topRed.WhenReleased(new ClimberRunDeploy(0.0));
	CDB_middleWhite.WhenPressed(new ElevatorRunToHeight(0.7, 5.5)); //middle scale
	CDB_middleRed.WhenPressed(new ElevatorRunToHeight(0.7, 2.6)); //switch
	CDB_bottomWhite.WhenPressed(new ElevatorRunToHeight(0.7, 1.42)); //portal
	CDB_bottomRed.WhenPressed(new ElevatorRunToHeight(0.7, 0.5)); //cube carry height
}

	double OI::GetTurn() {
		//gets turning values
		double val = Desensitize(-driverController.GetRawAxis(4));
		return val;
	}

	double OI::GetMove() {
		//gets forward/backward values
		double val = Desensitize(driverController.GetRawAxis(1))*1.1;
		return Exponate(val);
	}

	double OI::Exponate(double val){
		return pow( ( std::max(0.0, fabs(val)-0.15 ) ) * (1.0/(1.0-0.15)), 2.0) * GetSign(val);
	}

	double OI::Desensitize(double value) {
		//set threshold so tiny values on the joystick don't register,
		//sometimes resting value of joystick is not 0
		if (fabs(value) < 0.15) value = 0;
		return value;
	}
	double OI::GetSign(double value){
		//returning if a double is positive or negative
		return (double) value < 0 ? -1.0 : 1.0;
	}

	double OI::GetLiftControl() {
		//manual control to control elevator movement with joystick
		return Desensitize(coDriverController.GetRawAxis(1));
	}
