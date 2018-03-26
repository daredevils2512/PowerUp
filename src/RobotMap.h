#pragma once

#include <iostream>
#include <WPILib.h>
#include <ctre/Phoenix.h>
#include <AHRS.h>
#include "Util.h"
#include <Encoder.h>
#include "UltrasonicSensor.h"
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

	static std::shared_ptr<WPI_TalonSRX> cubeIntakeLeftMotor;
	static std::shared_ptr<WPI_TalonSRX> cubeIntakeRightMotor;
	static std::shared_ptr<frc::DoubleSolenoid> cubeIntakeSolenoid;
	static std::shared_ptr<frc::DoubleSolenoid> cubeIntakeGrabberSolenoid;
	static std::shared_ptr<frc::DigitalInput> cubeIntakeLimitSwitch;

	static std::shared_ptr<WPI_TalonSRX> climber;
	static std::shared_ptr<frc::DoubleSolenoid> climberFork;
	static std::shared_ptr<frc::DoubleSolenoid> climberClaws;

	static std::shared_ptr<UltrasonicSensor> ultrasonicFrontLeft;
	static std::shared_ptr<UltrasonicSensor> ultrasonicRearLeft;
	static std::shared_ptr<UltrasonicSensor> ultrasonicFrontRight;
	static std::shared_ptr<UltrasonicSensor> ultrasonicRearRight;

	static std::shared_ptr<WPI_TalonSRX> elevatorMotor;
	static std::shared_ptr<frc::DigitalInput> elevatorBottomSwitch;


	static void init();

};
