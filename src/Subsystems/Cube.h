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
	std::shared_ptr<frc::DoubleSolenoid> cubeIntakeSolenoid;

public:
	Cube();
	void InitDefaultCommand();
	void SetIntakeSpeed(double speed);
	void ActuateIntake(frc::DoubleSolenoid::Value direction);

};

#endif  // CubeManipulator_H
