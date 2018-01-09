#pragma once

#include <WPILib.h>
#include"ctre/Phoenix.h"

class RobotMap {
public:
	static std::shared_ptr<WPI_TalonSRX> drivetrainFrontLeftMotor;
	static std::shared_ptr<WPI_TalonSRX> drivetrainRearLeftMotor;
	static std::shared_ptr<WPI_TalonSRX> drivetrainFrontRightMotor;
	static std::shared_ptr<WPI_TalonSRX> drivetrainRearRightMotor;
	static std::shared_ptr<frc::DifferentialDrive> drivetrainChassis;
	static std::shared_ptr<frc::DoubleSolenoid> drivetrainShifter;


	static void init();

};
