#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H
#include "Commands/Subsystem.h"
#include <WPILib.h>
#include "ctre/Phoenix.h"

class Drivetrain: public Subsystem {
private:
	std::shared_ptr<WPI_TalonSRX> FrontLeftMotor;
	std::shared_ptr<WPI_TalonSRX> RearLeftMotor;
	std::shared_ptr<WPI_TalonSRX> FrontRightMotor;
	std::shared_ptr<WPI_TalonSRX> RearRightMotor;
	std::shared_ptr<frc::DifferentialDrive> Chassis;
	std::shared_ptr<DoubleSolenoid> DriveTrainShift;

public:
	Drivetrain();
	void InitDefaultCommand();
	void DriveRobotArcade(double move, double turn);
	void DriveRobotTank(double leftSide, double rightSide);
	void Shifter (frc::DoubleSolenoid::Value dir);
	void SetAutonomous(bool isAutonomous);
	bool GetAutonomous();
	bool blockJoysticks;

};

#endif
