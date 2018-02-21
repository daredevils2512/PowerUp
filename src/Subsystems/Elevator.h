#ifndef Elevator_H
#define Elevator_H

#include <Commands/Subsystem.h>
#include <WPILib.h>
#include <ctre/Phoenix.h>
class Elevator : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
std::shared_ptr<WPI_TalonSRX> motor;
//std::shared_ptr<frc::DigitalInput> bottom;


public:
	Elevator();
	void InitDefaultCommand();
	bool GetBottomSwitch();
	void RunLift(double speed);
	double GetLiftMagneticEncoder();
	double ResetMagneticEncoder();
	double CalculatePSpeed(double startingEncPos, double pValue);

	double sensorUnitsPerRotation = 3944;
	double sensorUnitsReset = 0.0;

	static constexpr double pValue = 0.01;
};

#endif  // Elevator_H
