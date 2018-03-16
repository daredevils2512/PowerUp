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
#include "Commands/UltraSonicStraightDrive.h"
#include "Commands/PIDTurn.h"
#include "Commands/PIDDriveStraight.h"
#include "Commands/ClimberRunWing.h"
#include "Commands/ElevatorRunToHeight.h"
#include "Commands/ElevatorRunLift.h"
#include "Commands/CubeIntakeActuate.h"
#include "Commands/CubeRunIntake.h"
#include "Commands/LowGear.h"
#include "Commands/HighGear.h"
#include "Commands/AutoStraightDriveForward.h"
#include "Commands/AutoStraightDriveBackward.h"
#include "Robot.h"
#include "Util.h"


OI::OI() {
	DRC_leftTrigger.WhileHeld(new CubeRunIntake(-1.0)); //pull me in dad
		DRC_leftTrigger.WhenReleased(new CubeRunIntake(0.0));
	DRC_rightTrigger.WhileHeld(new LowGear()); //drop a gear
	DRC_rightTrigger.WhenReleased(new HighGear()); //and disappear
	DRC_leftBumper.WhenPressed(new CubeIntakeActuateOpen()); //spread
	DRC_rightBumper.WhenPressed(new CubeIntakeActuateClose()); //retract
	DRC_xButton.WhileHeld(new CubeRunIntake(1.0)); //thanks for flying air 2512
		DRC_xButton.WhenReleased(new CubeRunIntake(0.0));
//	DRC_xButton.WhileHeld(new ClimberRunWing (Climber::ClimberWing::leftWing , 0.8)); //Kahl left wing up
//	DRC_xButton.WhenReleased(new ClimberRunWing (Climber::ClimberWing::leftWing , 0.0)); //stop left wing
//	DRC_bButton.WhileHeld(new ClimberRunWing (Climber::ClimberWing::rightWing , 0.8)); //Kahl right wing up
//	DRC_bButton.WhenReleased(new ClimberRunWing (Climber::ClimberWing::rightWing , 0.0)); //stop right wing

	CDR_trigger.WhileHeld(new CMG_ExtakeCube()); //full send out
		CDR_trigger.WhenReleased(new CubeRunIntake(0.0));
	CDR_sideJoystickButton.WhileHeld(new CubeRunIntake(0.65)); //minimal cube out
		CDR_sideJoystickButton.WhenReleased(new CubeRunIntake(0.0));
	CDR_topLeftJoystick.WhileHeld (new CubeRunIntake(-1.0)); //run cube in //1.0
	CDR_topLeftJoystick.WhenReleased (new CubeRunIntake(0.0)); //stop intake
	CDR_bottomLeftJoystick.WhileHeld(new CubeRunIntake(0.4)); //run cube out //-1.0
	CDR_bottomLeftJoystick.WhenReleased(new CubeRunIntake(0.0)); //stop intake
	CDR_topRightJoystick.WhenPressed(new CubeIntakeActuateClose()); //actuate intake arms in
	CDR_bottomRightJoystick.WhenPressed(new CubeIntakeActuateOpen()); //actuate intake arms out

//	CDR_topLeftBase.WhenPressed(new CubeGrabberActuate(true)); //actuate grabbers to pinch the cube
//	CDR_topRightBase.WhenPressed(new CubeGrabberActuate(false)); //retract the grabbers to let go of cube
	CDR_middleLeftBase.WhileHeld(new CubeRunIntake(-1.0)); //alt run cube in
	CDR_middleLeftBase.WhenReleased(new CubeRunIntake(0.0)); //stop intake
	CDR_middleRightBase.WhileHeld(new CubeRunIntake(1.0)); //alt run cube out
	CDR_middleRightBase.WhenReleased(new CubeRunIntake(0.0)); //stop intake
//	CDR_bottomLeftBase.WhileHeld(new ClimberRunWing (Climber::ClimberWing::leftWing, 0.8)); //Dawson left wing up
//	CDR_bottomLeftBase.WhenReleased(new ClimberRunWing (Climber::ClimberWing::leftWing, 0.0)); //stop left wing
//	CDR_bottomRightBase.WhileHeld(new ClimberRunWing (Climber::ClimberWing::rightWing, 0.8)); //Dawson right wing up
//	CDR_bottomRightBase.WhenReleased(new ClimberRunWing (Climber::ClimberWing::rightWing, 0.0)); //right wing stop

	CDB_bigWhite.WhileHeld(new ElevatorRunLift (0.7)); //run lift up
	CDB_bigRed.WhileHeld(new ElevatorRunLift (-0.50)); //run lift down
	CDB_green.WhileHeld(new ElevatorRunLift(0.07)); //minute adjustment up
	CDB_yellow.WhileHeld(new ElevatorRunLift(-0.06)); //minute adjustment down
	CDB_topWhite.WhenPressed(new ElevatorRunToHeight(0.7, 6.5)); //Top scale
	CDB_topRed.WhenPressed(new ElevatorRunToHeight(0.7, 5.5)); //mid scale
	CDB_middleWhite.WhenPressed(new ElevatorRunToHeight(0.7, 4.3)); //bottom scale
	CDB_middleRed.WhenPressed(new ElevatorRunToHeight(0.7, 2)); //switch
	CDB_bottomWhite.WhenPressed(new ElevatorRunToHeight(0.7, 1.3)); //portal
	CDB_bottomRed.WhenPressed(new ElevatorRunToHeight(0.7, 0.15)); //bottom
}

	double OI::GetTurn() {
		//gets turning values
		return Desensitize(-driverController.GetRawAxis(4));
	}

	double OI::GetMove() {
		//gets forward/backward values
		return Desensitize(driverController.GetRawAxis(1));
	}

	double OI::Desensitize(double value) {
		//set threshold so tiny values on the joystick don't register,
		//sometimes resting value of joystick is not 0
		if (fabs(value) < 0.25) value = 0; //0.25
		return value;
	}

	double OI::GetLiftControl() {
		//manual control to control elevator movement with joystick
		return Desensitize(coDriverController.GetRawAxis(1));
	}
