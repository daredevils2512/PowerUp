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
	char ourSwitch = gameMessage[0];
	char scale = gameMessage[1];
	//BalanceStates[2] = their switch

	Robot::StartLocation startingPosition = autonomousSource->GetStartLocation();
	bool doSwitch = autonomousSource->IsDoSwitch();
	bool doScale = autonomousSource->IsDoScale();

	int directionSwitch = (ourSwitch == 'L') ? -1 : 1; //directionSwitch equal to 1 if turning right and -1 if left
	int directionScale = (scale == 'L') ? -1 : 1;		//switched values so that -1 is always left

	Util::RobotSide trackingSide = (startingPosition == Robot::StartLocation::left) ?
		Util::RobotSide::leftSide : Util::RobotSide::rightSide;

	AddSequential(new PrintCurrentFPGATime());
	AddSequential(new ElevatorSafety());

	if (startingPosition == Robot::StartLocation::center) {
		std::cout << "We're in the center!" << std::endl;
		if (doSwitch) {
			//With 90 degree turns
//			std::cout << "Doing the easy peasy stuff" << std::endl;
//			AddSequential(new PIDDriveStraight(50));			//drive straight to get away from the wall
//			AddSequential(new PIDTurn(90 * directionSwitch));	//turning left or right based off of which side is ours
//			AddSequential(new PIDDriveStraight(56));			//going places
//			AddSequential(new PIDTurn(90 * -directionSwitch));	//turning back to be aimed at the switch
//			AddSequential(new PIDDriveStraight(54));			//running to the switch
//			AddSequential(new CubeRunIntake(-1.0));			//bye bye cube!
			//with 45 degree turns
			AddSequential(new PIDDriveStraight(18));
			AddSequential(new Pause(0.3));
			AddParallel(new ElevatorRunToHeight(0.7 , 2.6));
			AddSequential(new PIDDriveStraight(18));
			AddSequential(new Pause(0.4));
//			AddParallel(new ElevatorRunLift(0.1));
			AddSequential(new PIDTurn(45 * directionSwitch));
			AddSequential(new Pause(0.3));
			AddSequential(new PIDDriveStraight(70)); //68
			AddSequential(new Pause(0.3));
			AddSequential(new PIDTurn(45 * -directionSwitch));
			AddSequential(new Pause(0.1));
			AddSequential(new PIDDriveStraight(18)); //18
			AddSequential(new CubeRunIntake(-0.8,0.5));
			AddSequential(new AutoStraightDriveBackward(6,0.6)); //backing up
			AddSequential(new Pause(0.3));
			AddSequential(new PIDTurn(77.5 * -directionSwitch));
			AddSequential(new Pause(0.3));
			AddSequential(new ElevatorRunToHeight(0.5 , 0.08));
			AddParallel(new CubeRunIntake(1.0,3));
			AddSequential(new AutoStraightDriveForward(26,0.6));
			AddSequential(new Pause(0.3));
			AddSequential(new AutoStraightDriveBackward(27,0.7));
			AddSequential(new PIDTurn(72.5 * directionSwitch));
			AddSequential(new Pause(0.3));
			AddSequential(new ElevatorRunToHeight(0.75 , 2.6));
			AddSequential(new Pause(0.3));
			AddSequential(new PIDDriveStraight(15));
			AddSequential(new CubeRunIntake(-1.0,0.5));
		} else {
			std::cout << "Just going for a drive" << std::endl;
			AddSequential(new PIDDriveStraight(90));// drive forward and cross auto line
		}
	} else if (startingPosition == Robot::StartLocation::left
			|| startingPosition == Robot::StartLocation::right) {
		std::cout << "On one of the sides!" << std::endl;
		char sideCheck = (startingPosition == Robot::StartLocation::right) ? 'R' : 'L'; //If starting pos. is right, sideCheck is right otherwise left
		if (doSwitch && ourSwitch == sideCheck) { // If going to switch and we can actually do the switch
			std::cout << "Doing our switch good" << std::endl;
			AddSequential(new PIDDriveStraight(155.275));//zooming out to the middle of the switch and determinging where to go from there
			if (doScale) {
				std::cout << "We're try hards and doing both" << std::endl;
				if (scale == sideCheck) {
					std::cout << "It's on our side thankfully" << std::endl;
					// command group for positioning from mid-zone to the closest side of the balance, then placing
					AddSequential(new PIDDriveStraight(184));//driving to the scale zone
					AddSequential(new PIDTurn(90 * -directionScale));////turning towards it
					AddParallel(new ElevatorRunToHeight(0.7, scaleHeight));	//Gonna be talller thane the scale
					AddSequential(new PIDDriveStraight(12));	//zoom into it
					AddSequential(new CubeRunIntake(-1.0));			//bye bye cube
				} else {
					std::cout << "Darn, it's all the way over there" << std::endl;
					// command group for moving across mid-zone to the farthest side of the balance, then placing
					AddSequential(new PIDDriveStraight(64));//driving a little farther than the switch
					AddSequential(new PIDTurn(90 * -directionScale));//turning to go around
					AddSequential(new PIDDriveStraight(190));//going down past the switch
					AddSequential(new PIDTurn(90 * directionScale));//turning the opposite way
					AddParallel(new ElevatorRunToHeight(0.7, scaleHeight)); //Gonna be talller thane the scale
					AddSequential(new PIDDriveStraight(17.5));	//zoom at scale
					AddSequential(new CubeRunIntake(-1.0));			//bye bye cube
				}
			} else {
				std::cout << "We're normal and just gonna do the easy stuff" << std::endl;
				AddSequential(new PIDTurn(90 * directionSwitch));//turning towards the switch to drop cube
				AddSequential(new PIDDriveStraight(24));
				AddSequential(new CubeRunIntake(-1.0));				//bye bye cube
			}
			//if we aren't doing the scale, just don't move since we technically crossed the auto line anyway
		} else if (doSwitch && ourSwitch != sideCheck) {
			std::cout << "Doing our switch good over there" << std::endl;
			AddSequential(new PIDDriveStraight(220));//driving out past the switch so we can go around
			AddSequential(new PIDTurn(90 * -directionSwitch));//turning to go around
			AddSequential(new PIDDriveStraight(230));	//zomming arround back
			AddSequential(new PIDTurn(90 * -directionSwitch));	//turning again
			AddSequential(new PIDDriveStraight(66));		//zooming onto side
			AddSequential(new Pause(0.2));
			AddSequential(new PIDTurn(90 * -directionSwitch));	//and again....
			AddSequential(new PIDDriveStraight(34));		//zooming into it
		} else if (doScale) {
			std::cout << "Gonna go be tall cause we ate our veggies"
					<< std::endl;
			//move to common baseline zone + move to mid-zone of alliance
			std::cout << "Scale Side: " << scale << "; Start Spot: "
					<< sideCheck << std::endl;
			if (scale == sideCheck) {
				std::cout << "Less work cause it's on our side" << std::endl;
				// command group for positioning from mid-zone to closest side of the balance, then placing
				AddSequential(new PIDDriveStraight(258));
				AddSequential(new Pause(0.2));
//				AddSequential(new UltrasonicStraightDrive(0.75, 290, trackingSide)); //294	//driving with sensros down da wall
				AddSequential(new PIDTurn(45 * -directionScale));//turning towards the scale
				AddSequential(new Pause(0.2));
				AddSequential(new AutoStraightDriveBackward(9.5,0.7)); //backing up //7.5
				AddSequential(new Pause(0.2));
				AddSequential(new ElevatorRunToHeight(1.0, scaleHeight));  //Gonna be talller thane the scale
				AddSequential(new Pause(0.2));
//				AddSequential(new PIDDriveStraight(12)); //18 //zoom at scale
				AddSequential(new CubeRunIntake(-1.0,1));	//bye bye cube
				AddSequential(new ElevatorRunToHeight(0.3, 0.08));
				//AddSequential(new AutoStraightDrive(7.5,0.5)); //backing up more
				AddSequential(new PIDTurn(82 * -directionScale));
				AddSequential(new AutoStraightDriveForward(48,0.6));
			} else {
				std::cout << "It's all the way over there....Need more veggies"
						<< std::endl;
				// command group for moving across mid-zone to farthest side of the balance, then placing
//				AddSequential(new UltrasonicStraightDrive(0.75, 222, trackingSide));//drive with sensors down the wall
				AddSequential(new PIDDriveStraight(188));	//zoom to other side
				AddSequential(new Pause(0.4));
				AddSequential(new PIDTurn(90 * directionScale));//turn to go across the back of switch
				AddSequential(new Pause(0.4));
				AddSequential(new PIDDriveStraight(160));	//zoom to other side
				AddSequential(new Pause(0.4));
				AddSequential(new PIDTurn(110 * -directionScale));//turn to face opposite end of field
				AddSequential(new Pause(0.4));
				//AddSequential(new AutoStraightDrive(7,-0.6));
				//AddSequential(new Pause(0.4));
//				AddSequential(new PIDDriveStraight(87));	//drive to null zone
//				AddSequential(new PIDTurn(90 * directionScale));//turn to the scale
				AddSequential(new ElevatorRunToHeight(1.0, scaleHeight)); //Gonna be talller thane the scale
				AddSequential(new AutoStraightDriveForward(18,0.5));	//zoom at the scale
				AddSequential(new Pause(0.4));
				AddSequential(new CubeRunIntake(-1.0,1));							//bye bye cube
				AddParallel(new ElevatorRunToHeight(0.5, 0.08));
			}
		} else {
			std::cout << "One too many cookies....Gonna just go straight" << std::endl;
			AddSequential(new PIDDriveStraight(90)); 	//Or whatever the cross baseline distance is
		}
	} else {
		std::cout
				<< "Something went wrong. Aborting logic checking and driving straight"
				<< std::endl;
		AddSequential(new PIDDriveStraight(90)); 	//Or whatever the cross baseline distance is
	}
	AddSequential(new PrintCurrentFPGATime());
}

 void AutoSelector::CenterSwitch() {

}
void AutoSelector::OutsideStraightScale() {

}
