#ifndef CubeManipulator_H
#define CubeManipulator_H

#include <Commands/Subsystem.h>
#include <WPILib.h>
#include <ctre/Phoenix.h>

class Cube : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	std::shared_ptr <WPI_TalonSRX> intakeLeft;
	std::shared_ptr <WPI_TalonSRX> intakeRight;
	std::shared_ptr<frc::DoubleSolenoid> intakeSolenoid;
	std::shared_ptr<frc::DoubleSolenoid> grabSolenoid;
	std::shared_ptr<frc::DigitalInput> limitSwitch;

public:
	Cube();
	void InitDefaultCommand();
	void SetIntakeSpeed(double speed);
	void ActuateIntake(frc::DoubleSolenoid::Value direction);
	void ActuateGrabber (frc::DoubleSolenoid::Value direction);
	bool GetLimitSwitch();

};

#endif  // CubeManipulator_H
