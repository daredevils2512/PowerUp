/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/CommandGroup.h>
#include "AutonomousSource.h"

class AutoSelector : public frc::CommandGroup {
public:
	AutoSelector(AutonomousSource* autonomousSource);
	void SwitchY();
	void SameOutsideSwitch();
	void OppositeOutsideSwitch();
	void OutsideStraightScale();
	void OutsideOppositeScale();
	//TODO Add in functions for doing alternate switch autos

private:
	static constexpr double scaleHeight = 6.8;
	bool doScale = false;
	bool doSwitch = false;
	int directionSwitch = 1;
	int directionScale = 1;
	char scale = ' ';
	char ourSwitch = ' ';
};

