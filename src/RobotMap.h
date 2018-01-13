#pragma once

#include <WPILib.h>
#include <ctre/Phoenix.h>
#include <AHRS.h>
#include "Util.h"

class RobotMap {
public:
	static std::shared_ptr<WPI_TalonSRX> drivetrainFrontLeftMotor;
	static std::shared_ptr<WPI_TalonSRX> drivetrainRearLeftMotor;
	static std::shared_ptr<WPI_TalonSRX> drivetrainFrontRightMotor;
	static std::shared_ptr<WPI_TalonSRX> drivetrainRearRightMotor;
	static std::shared_ptr<frc::DifferentialDrive> drivetrainChassis;
	static std::shared_ptr<frc::DoubleSolenoid> drivetrainShifter;

	static std::shared_ptr<AHRS> navX;
	static std::shared_ptr<frc::PIDController> navXTurnController;
	static void init();

};
