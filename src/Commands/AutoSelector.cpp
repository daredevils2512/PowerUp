/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#include <Commands/AutoStraightDriveForward.h>
#include <iostream>

#include "AutoSelector.h"
#include "Robot.h"
#include "Commands/Drive.h"
#include "Commands/CubeIntakeActuate.h"
#include "Commands/CubeRunIntake.h"
#include "Commands/CubeIntakeActuateOpen.h"
#include "Commands/ElevatorRunToHeight.h"
#include "Commands/ElevatorRunLift.h"
#include "Commands/PIDTurn.h"
#include "Commands/PIDDriveStraight.h"
#include "Commands/UltrasonicStraightDrive.h"
#include "Commands/PrintCurrentFPGATime.h"
#include "Commands/Pause.h"
#include "Commands/AutoTimedDrive.h"
#include "Commands/ElevatorSafety.h"
#include "Commands/AutoStraightDriveBackward.h"

AutoSelector::AutoSelector(AutonomousSource* autonomousSource) {
	std::string gameMessage =
			frc::DriverStation::GetInstance().GetGameSpecificMessage();
	if (gameMessage.length() == 0)
		return;
	ourSwitch = gameMessage[0];
	scale = gameMessage[1];
	//BalanceStates[2] = their switch

	Robot::StartLocation startingPosition = autonomousSource->GetStartLocation();
	doSwitch = autonomousSource->IsDoSwitch();
	doScale = autonomousSource->IsDoScale();

	directionSwitch = (ourSwitch == 'L') ? -1 : 1; //directionSwitch equal to 1 if turning right and -1 if left
	directionScale = (scale == 'L') ? -1 : 1;		//switched values so that -1 is always left

//	Util::RobotSide trackingSide = (startingPosition == Robot::StartLocation::left) ?
//		Util::RobotSide::leftSide : Util::RobotSide::rightSide;

	AddSequential(new PrintCurrentFPGATime());
	AddSequential(new ElevatorSafety());

	if (startingPosition == Robot::StartLocation::center) {
		std::cout << "The pleasures of a journey to the center of the mind..." << std::endl;
		if (doSwitch) {
			std::cout << "no u" << std::endl;
			SwitchY();
		} else {
			std::cout << "I need you in my life, please don't go switching sides" << std::endl;
			AddSequential(new PIDDriveStraight(90));// drive forward and cross auto line
		}
	} else if (startingPosition == Robot::StartLocation::left || startingPosition == Robot::StartLocation::right) {
		std::cout << "The world sees me one way..." << std::endl;
		char sideCheck = (startingPosition == Robot::StartLocation::right) ? 'R' : 'L'; //If starting pos. is right, sideCheck is right otherwise left
		if (doSwitch) {
			std::cout << "Hey switch, turn it over and hit it" << std::endl;
			if (ourSwitch == sideCheck) { // If going to switch and we can actually do the switch
				std::cout << "Doing our switch da very best. Like no one ever did..." << std::endl;
				SameOutsideSwitch();
			} else if (ourSwitch != sideCheck) {
				std::cout << "Over the ethernet bump and through the cubes, to the opposite side we go!" << std::endl;
				OppositeOutsideSwitch();
			}
		} else if (doScale) {
			std::cout << "Do Re Mi Fa So LAAAA Ti Do" << std::endl;
			//move to common baseline zone + move to mid-zone of alliance
			if (scale == sideCheck) {
				std::cout << "But right now...My time is theirs" << std::endl;
				OutsideStraightScale();
			} else {
				std::cout << "Over there, over there" << std::endl;
				OutsideOppositeScale();
			}
		} else {
			std::cout << "One too many cookies....Gonna just go straight" << std::endl;
			AddSequential(new PIDDriveStraight(104)); 	//Or whatever the cross baseline distance is
		}
	} else {
		std::cout << "Rocket man burning out his fuse up here alone" << std::endl;
		AddSequential(new PIDDriveStraight(104)); 	//Or whatever the cross baseline distance is
	}
	AddSequential(new PrintCurrentFPGATime());
}

 void AutoSelector::SwitchY() {
	AddSequential(new PIDDriveStraight(18));
	AddSequential(new Pause(0.3));//t
	AddParallel(new ElevatorRunToHeight(0.7 , 2.7)); //0.7,2.6
	AddSequential(new PIDDriveStraight(18));
	AddSequential(new Pause(0.3)); //0.4
	AddSequential(new PIDTurn(45 * directionSwitch));
	AddSequential(new Pause(0.25)); //0.3
	if (ourSwitch == 'L') {
		AddSequential(new PIDDriveStraight(69)); //66
	}else{
		AddSequential(new PIDDriveStraight(56)); //54
	}
	AddSequential(new Pause(0.25)); //0.3
	AddSequential(new PIDTurn(38 * -directionSwitch)); //45
	AddSequential(new Pause(0.25)); //0.3
	if (ourSwitch == 'L') {
		AddSequential(new PIDDriveStraight(17, 1.5)); //18
	}else{
		AddSequential(new PIDDriveStraight(26, 2.5)); //18
	}
	AddSequential(new CubeRunIntake(0.65,0.5)); //0.8 for power
	if (ourSwitch == 'L') {
		AddSequential(new AutoStraightDriveBackward(5,0.7));
	}else{
		AddSequential(new AutoStraightDriveBackward(6.5,0.7)); //5 inches
	}
	AddSequential(new Pause(0.25)); //0.3
	if (ourSwitch == 'L') {
		AddSequential(new PIDTurn(72 * -directionSwitch)); //77.5
	}else{
		AddSequential(new PIDTurn(68.5 * -directionSwitch)); //73.5
	}
	AddSequential(new Pause(0.28)); //0.3
	AddSequential(new ElevatorRunToHeight(0.5 , 0.0)); //0 inches
	AddParallel(new CubeRunIntake(-1.0,3));
	AddSequential(new AutoStraightDriveForward(27,0.6)); //34
	AddSequential(new Pause(0.3)); //0.3
	if (ourSwitch == 'L') {
		AddSequential(new AutoStraightDriveBackward(14,0.8)); //35
	}else{
		AddSequential(new AutoStraightDriveBackward(11,0.8)); //26
	}
	AddSequential(new Pause(0.1));
	if (ourSwitch == 'L') {
		AddSequential(new PIDTurn(72 * directionSwitch)); //72.5
	}else{
		AddSequential(new PIDTurn(69 * directionSwitch));
	}
	AddSequential(new Pause(0.2)); //0.3
	AddSequential(new ElevatorRunToHeight(0.75 , 2.5));
	AddSequential(new Pause(0.2)); //0.3
	AddSequential(new PIDDriveStraight(30 , 2.0)); //18 //25
	AddSequential(new CubeRunIntake(0.4,0.5));
	AddSequential(new CubeIntakeActuateOpen());
}

 void AutoSelector::SameOutsideSwitch() {
	AddSequential(new PIDDriveStraight(155.275));
	AddSequential(new PIDTurn(90 * directionSwitch));//turning towards the switch to drop cube
	AddSequential(new PIDDriveStraight(24));
	AddSequential(new CubeRunIntake(0.6,0.5)); //bye bye cube
	AddSequential(new AutoStraightDriveBackward(5,0.6));
 }

 void AutoSelector::OppositeOutsideSwitch() {
	AddSequential(new PIDDriveStraight(220));//driving out past the switch so we can go around
	AddSequential(new PIDTurn(90 * -directionSwitch));//turning to go around
	AddSequential(new PIDDriveStraight(194));	//zomming arround back
	AddSequential(new ElevatorRunToHeight(1.0, 3.0));
	AddSequential(new PIDTurn(90 * -directionSwitch));	//turning again
	AddSequential(new PIDDriveStraight(12));		//zooming onto side
	AddSequential(new CubeRunIntake(0.6,0.5));
	AddSequential(new AutoStraightDriveBackward(5,0.6));
 }

void AutoSelector::OutsideStraightScale() {
	AddSequential(new PIDDriveStraight(185,4.5,0.9)); //258, 6.0 timeout //208 inches at 80
	AddSequential(new Pause(0.4)); //0.2
	AddSequential(new PIDTurn(37 * -directionScale, 0.6));//turning towards the scale //45 deg
	AddSequential(new Pause(0.2));
	AddSequential(new ElevatorRunToHeight(1.0, scaleHeight));  //Gonna be talller thane the scale
	AddSequential(new Pause(0.2));
	AddSequential(new CubeRunIntake(1.0,0.5));	//bye bye cube
	AddSequential(new Pause(0.2));
	AddSequential(new ElevatorRunToHeight(0.3, 0.0)); //0.08
	AddSequential(new Pause(0.2));
	AddSequential(new PIDTurn(105 * -directionScale , 0.8)); //76
	AddSequential(new Pause(0.3));
	AddParallel(new CubeRunIntake(-1.0, 3)); //3 second intake
	AddSequential(new AutoStraightDriveForward(39,0.75)); //0.6
	if (ourSwitch == scale) {
		std::cout << "She getting crunk in the club I mean she work" << std::endl;
		AddSequential(new Pause(0.3));
		AddSequential(new ElevatorRunToHeight(0.7, 2.6));
		AddSequential(new Pause(0.2));
		AddSequential(new CubeRunIntake(0.7, 1.0));
	}
}

void AutoSelector::OutsideOppositeScale() {
//	AddSequential(new PIDDriveStraight(104));
	AddSequential(new PIDDriveStraight(154,4.5,0.9));	//zoom to other side
	AddSequential(new Pause(0.45));
	AddSequential(new PIDTurn(91.2 * directionScale));//turn to go across the back of switch //90 deg
	AddSequential(new Pause(0.3));
	AddSequential(new PIDDriveStraight(139, 4.5,0.9));	//zoom to other side //160
	AddSequential(new Pause(0.3));
	AddSequential(new PIDTurn(90 * -directionScale));//turn to face opposite end of field
	AddSequential(new Pause(0.25));
	AddSequential(new ElevatorRunToHeight(1.0, scaleHeight)); //Gonna be talller thane the scale
	AddSequential(new AutoStraightDriveForward(16,0.5));	//zoom at the scale
	AddSequential(new Pause(0.2));
	AddSequential(new CubeRunIntake(1.0,0.5));							//bye bye cube
	AddSequential(new ElevatorRunToHeight(0.5, 0.00)); //0.08
	AddSequential(new Pause(0.2));
	AddSequential(new AutoStraightDriveBackward(22, 0.8));
	AddSequential(new PIDTurn(-110)); //82


//	AddSequential(new Pause(0.2));
//	AddParallel(new CubeRunIntake(-1.0, 2)); //1 second timeout
//	AddSequential(new AutoStraightDriveForward(24,0.6));
//	AddParallel(new CubeRunIntake(-1.0, 2)); //1 second timeout
//	if (ourSwitch == scale) {
//		std::cout << "It's so much pressure...and it's all in a day's work" << std::endl;
//		AddSequential(new Pause(0.2));
//		AddSequential(new ElevatorRunToHeight(0.7,2.6));
//		AddSequential(new CubeRunIntake(0.6, 1.0));
//	}
}
