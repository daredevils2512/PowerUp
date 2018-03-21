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

	AddSequential(new PrintCurrentFPGATime());
	AddSequential(new ElevatorSafety());

	if (startingPosition == Robot::StartLocation::center) {
		std::cout << "The pleasures of a journey to the center of the mind..." << std::endl;
		if (doSwitch) {
			std::cout << "Y.?" << std::endl;
			SwitchY();
		} else {
			std::cout << "Choose my bluest tape and unlock my car" << std::endl;
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
	AddParallel(new ElevatorRunToHeight(0.7 , 2.6));
	AddSequential(new PIDDriveStraight(18));
	AddSequential(new Pause(0.4));
	AddSequential(new PIDTurn(45 * directionSwitch));
	AddSequential(new Pause(0.3));
	if (ourSwitch == 'L') {
		AddSequential(new PIDDriveStraight(66));
	} else {
		AddSequential(new PIDDriveStraight(54));
	}
	AddSequential(new Pause(0.3));
	AddSequential(new PIDTurn(45 * -directionSwitch));
	AddSequential(new Pause(0.3));
	AddSequential(new PIDDriveStraight(17, 2.0)); //18
	AddSequential(new CubeRunIntake(0.8,0.5));
	AddSequential(new AutoStraightDriveBackward(5,0.6)); //backing up
	AddSequential(new Pause(0.3));
	AddSequential(new PIDTurn(77.5 * -directionSwitch));
	AddSequential(new Pause(0.3));
	AddSequential(new ElevatorRunToHeight(0.5 , 0.08));
	AddParallel(new CubeRunIntake(-1.0,3));
	AddSequential(new AutoStraightDriveForward(34,0.6));
	AddSequential(new Pause(0.3));
	AddSequential(new AutoStraightDriveBackward(35,0.7));
	AddSequential(new PIDTurn(72.5 * directionSwitch));
	AddSequential(new Pause(0.3));
	AddSequential(new ElevatorRunToHeight(0.75 , 2.6));
	AddSequential(new Pause(0.3));
	AddSequential(new PIDDriveStraight(30)); //18 //25
	AddSequential(new CubeRunIntake(1.0,0.5));
}

 void AutoSelector::SameOutsideSwitch() {
	 AddSequential(new PIDDriveStraight(155.275));
	AddSequential(new PIDTurn(90 * directionSwitch));//turning towards the switch to drop cube
	AddSequential(new PIDDriveStraight(24));
	AddSequential(new CubeRunIntake(-1.0));				//bye bye cube
 }

 void AutoSelector::OppositeOutsideSwitch() {
	 AddSequential(new PIDDriveStraight(220));//driving out past the switch so we can go around
	AddSequential(new PIDTurn(90 * -directionSwitch));//turning to go around
	AddSequential(new PIDDriveStraight(194));	//zomming arround back
	AddSequential(new ElevatorRunToHeight(1.0, 3.0));
	AddSequential(new PIDTurn(90 * -directionSwitch));	//turning again
	AddSequential(new PIDDriveStraight(12));		//zooming onto side
	AddSequential(new CubeRunIntake(-0.6));
 }

void AutoSelector::OutsideStraightScale() {
	AddSequential(new PIDDriveStraight(258, 7.5));
	AddSequential(new Pause(0.2));
	AddSequential(new PIDTurn(45 * -directionScale));//turning towards the scale
	AddSequential(new Pause(0.2));
	AddSequential(new AutoStraightDriveBackward(9.5,0.7)); //backing up //7.5
	AddSequential(new Pause(0.2));
	AddSequential(new ElevatorRunToHeight(1.0, scaleHeight));  //Gonna be talller thane the scale
	AddSequential(new Pause(0.2));
//	AddSequential(new PIDDriveStraight(12)); //18 //zoom at scale
	AddSequential(new CubeRunIntake(1.0,1));	//bye bye cube
	AddSequential(new ElevatorRunToHeight(0.3, 0.08)); //0.3
//	AddSequential(new AutoStraightDrive(7.5,0.5)); //backing up more
	AddSequential(new PIDTurn(76 * -directionScale)); //82
	AddSequential(new AutoStraightDriveForward(48,0.6));
	AddSequential(new CubeRunIntake(1.0, 1));
	if (ourSwitch == scale) {
		std::cout << "She getting crunk in the club I mean she work" << std::endl;
		AddSequential(new ElevatorRunToHeight(1.0, 3.0));
		AddSequential(new CubeRunIntake(-0.6, 1.0));
	}
}

void AutoSelector::OutsideOppositeScale() {
	AddSequential(new PIDDriveStraight(188));	//zoom to other side
	AddSequential(new Pause(0.4));
	AddSequential(new PIDTurn(90 * directionScale));//turn to go across the back of switch
	AddSequential(new Pause(0.4));
	AddSequential(new PIDDriveStraight(160, 5.5));	//zoom to other side
	AddSequential(new Pause(0.4));
	AddSequential(new PIDTurn(110 * -directionScale));//turn to face opposite end of field
	AddSequential(new Pause(0.4));
//	AddSequential(new AutoStraightDrive(7,-0.6));
//	AddSequential(new Pause(0.4));
//	AddSequential(new PIDDriveStraight(87));	//drive to null zone
//	AddSequential(new PIDTurn(90 * directionScale));//turn to the scale
	AddSequential(new ElevatorRunToHeight(1.0, scaleHeight)); //Gonna be talller thane the scale
	AddSequential(new AutoStraightDriveForward(18,0.5));	//zoom at the scale
	AddSequential(new Pause(0.4));
	AddSequential(new CubeRunIntake(1.0,1));							//bye bye cube
	AddSequential(new ElevatorRunToHeight(0.5, 0.08));
	AddSequential(new AutoStraightDriveBackward(24, 1.5));
	AddSequential(new PIDTurn(180)); //82
	AddSequential(new AutoStraightDriveForward(24,0.6));
	AddSequential(new CubeRunIntake(1.0, 1));
	if (ourSwitch == scale) {
		std::cout << "It's so much pressure...and it's all in a day's work" << std::endl;
		AddSequential(new ElevatorRunToHeight(0.3,3.0));
		AddSequential(new CubeRunIntake(-0.6, 1.0));
	}
}
