/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "CenterSwitchAuto.h"
#include "PIDDriveStraight.h"
#include "PIDTurn.h"
#include "Pause.h"
#include "Elevator.h"
#include "ElevatorRunLift.h"
#include "Cube.h"


CenterSwitchAuto::CenterSwitchAuto() {

	AddSequential(new PIDDriveStraight(1));
	AddSequential(new Pause(0.0));
	AddSequential(new PIDTurn(-1));
	AddSequential(new Pause(0.0));
	AddSequential(new PIDDriveStraight(1));
	AddSequential(new Pause(0));
	AddSequential(new PIDTurn(0.0));
	AddSequential(new Pause(0.0));
	AddSequential(new PIDDriveStraight(1));
	AddSequential(new Pause(0));
	AddSequential(new ElevatorRunLift(0.0));
	AddSequential(new Pause(0));
	
	
















}
