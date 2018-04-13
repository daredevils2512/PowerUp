#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H
#include "Commands/Subsystem.h"
#include <WPILib.h>
#include <vector>
#include "ctre/Phoenix.h"

class Drivetrain: public frc::Subsystem, public PIDOutput {
private:
	std::shared_ptr<WPI_TalonSRX> FrontLeftMotor;
	std::shared_ptr<WPI_TalonSRX> RearLeftMotor;
	std::shared_ptr<WPI_TalonSRX> FrontRightMotor;
	std::shared_ptr<WPI_TalonSRX> RearRightMotor;
	std::shared_ptr<frc::DifferentialDrive> ChassisFront;
	std::shared_ptr<frc::DifferentialDrive> ChassisRear;
	std::shared_ptr<DoubleSolenoid> DriveTrainShift;
	std::shared_ptr<frc::Encoder> leftEncoder;
	std::shared_ptr<frc::Encoder> rightEncoder;

	double pidOutput = 0;
	static constexpr double X_COLLISION_THRESHOLD = 0.75;
	static constexpr double Y_COLLISION_THRESHOLD = 0.75;
	static constexpr double Z_COLLISION_THRESHOLD = 0.50;
	//highest recorded was 1.25

	bool m_xCol = false;
	bool m_yCol = false;
	bool m_zCol = false;

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
	bool IsXCollided();
	bool IsYCollided();
	bool IsZCollided();
	void UpdateCollisionCounters();
	void TopTenBuilder(int num);
	void SetAutonomous(bool isAutonomous);
	bool GetAutonomous();
	bool blockJoysticks;

	bool IsPIDEnabled();
	double GetPIDOutput();

	void SetPIDSetpoint(double setpoint);
	void SetPIDEnabled(bool enabled);

	int m_xCollCount = 0;
	int m_yCollCount = 0;
	int m_zCollCount = 0;
	double m_currentXAccel = 0.0;
	double m_currentYAccel = 0.0;
	double m_currentZAccel = 0.0;

	std::vector<double> m_xTopTen;

};

#endif
