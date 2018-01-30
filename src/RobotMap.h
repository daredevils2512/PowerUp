#pragma once

#include <iostream>
#include <WPILib.h>
#include <ctre/Phoenix.h>
#include <AHRS.h>
#include "Util.h"
#include <Encoder.h>
class RobotMap {
public:
	static std::shared_ptr<WPI_TalonSRX> drivetrainFrontLeftMotor;
	static std::shared_ptr<WPI_TalonSRX> drivetrainRearLeftMotor;
	static std::shared_ptr<WPI_TalonSRX> drivetrainFrontRightMotor;
	static std::shared_ptr<WPI_TalonSRX> drivetrainRearRightMotor;
	static std::shared_ptr<frc::DifferentialDrive> drivetrainChassis;
	static std::shared_ptr<frc::DoubleSolenoid> drivetrainShifter;
	static std::shared_ptr<frc::Encoder> drivetrainLeftEncoder;
	static std::shared_ptr<frc::Encoder> drivetrainRightEncoder;

	static std::shared_ptr<AHRS> navX;
	static std::shared_ptr<frc::PIDController> navXTurnController;

	static std::shared_ptr<frc::Spark> motor1;
	static std::shared_ptr<frc::Spark> motor2;
	static std::shared_ptr<frc::Spark> motor3;
	static std::shared_ptr<frc::Spark> motor4;
	static std::shared_ptr<frc::Spark> motor5;

	static std::shared_ptr<frc::DoubleSolenoid> cubeExtakeSolenoid;
	static std::shared_ptr<frc::DoubleSolenoid> cubeIntakeSolenoid;


	static std::shared_ptr<frc::AnalogInput> ultrasonicFrontLeft;
	static std::shared_ptr<frc::AnalogInput> ultrasonicRearLeft;
	static std::shared_ptr<frc::PIDController> ultrasonicTurnController;

	static std::shared_ptr<frc::DigitalOutput> ultrasonicRelay1;
	static std::shared_ptr<frc::DigitalOutput> ultrasonicRelay2;
	static std::shared_ptr<frc::DigitalOutput> ultrasonicRelay3;
	static std::shared_ptr<frc::DigitalOutput> ultrasonicRelay4;

	static void init();

};
