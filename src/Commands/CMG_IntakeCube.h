/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/CommandGroup.h>
#include "../Robot.h"
#include "CubeGrabberActuate.h"
#include "CubeIntakeActuateClose.h"
#include "CubeRunIntake.h"
#include "CubeSwitchCheck.h"
#include "Pause.h"

class CMG_IntakeCube : public frc::CommandGroup {
public:
	CMG_IntakeCube();
};

