#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H
#include "Commands/Subsystem.h"
#include <WPILib.h>
#include "ctre/Phoenix.h"

class Drivetrain: public Subsystem, public PIDOutput {
private:
	std::shared_ptr<WPI_TalonSRX> FrontLeftMotor;
	std::shared_ptr<WPI_TalonSRX> RearLeftMotor;
	std::shared_ptr<WPI_TalonSRX> FrontRightMotor;
	std::shared_ptr<WPI_TalonSRX> RearRightMotor;
	std::shared_ptr<frc::DifferentialDrive> Chassis;
	std::shared_ptr<DoubleSolenoid> DriveTrainShift;
	std::shared_ptr<frc::Encoder> leftEncoder;
	std::shared_ptr<frc::Encoder> rightEncoder;

	double pidOutput = 0;

public:
	Drivetrain();
	void InitDefaultCommand();
	virtual void PIDWrite(double output);
	void DriveRobotArcade(double move, double turn);
	void DriveRobotTank(double leftSide, double rightSide);
	double GetLeftEncoder();
	double GetRightEncoder();
	void ResetEncoders();
	void Shifter (frc::DoubleSolenoid::Value dir);
	void SetAutonomous(bool isAutonomous);
	bool GetAutonomous();
	bool blockJoysticks;

	bool IsPIDEnabled();
	double GetPIDOutput();

	void SetPIDSetpoint(double setpoint);
	void SetPIDEnabled(bool enabled);

};

#endif
