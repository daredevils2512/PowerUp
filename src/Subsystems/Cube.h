#ifndef CubeManipulator_H
#define CubeManipulator_H

#include <Commands/Subsystem.h>
#include <WPILib.h>

class Cube : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	std::shared_ptr<frc::Spark> intakeMotor1;
	std::shared_ptr<frc::Spark> intakeMotor2;
	std::shared_ptr<frc::Spark> intakeMotor3;
	std::shared_ptr<frc::Spark> intakeMotor4;
	std::shared_ptr<frc::Spark> extakeMotor;
	std::shared_ptr<frc::DoubleSolenoid> cubeIntakeSolenoid;
	std::shared_ptr<frc::DoubleSolenoid> cubeExtakeSolenoid;



public:
	Cube();
	void InitDefaultCommand();
	void SetIntakeSpeed(double speed);
	void SetExtakeSpeed(double speed);
	void ActuateIntake(frc::DoubleSolenoid::Value direction);
	void ActuateExtake(frc::DoubleSolenoid::Value direction);

};

#endif  // CubeManipulator_H
