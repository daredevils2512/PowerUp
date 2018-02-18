#ifndef Elevator_H
#define Elevator_H

#include <Commands/Subsystem.h>
#include <WPILib.h>
#include <ctre/Phoenix.h>
class Elevator : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
//std::shared_ptr<WPI_TalonSRX> left;
//std::shared_ptr<WPI_TalonSRX> right;
std::shared_ptr<WPI_TalonSRX> motor;
std::shared_ptr<frc::DigitalInput> top;
std::shared_ptr<frc::DigitalInput> bottom;
std::shared_ptr<frc::Encoder> encoder;



public:
	Elevator();
	void InitDefaultCommand();
	bool GetTopSwitch();
	bool GetBottomSwitch();
	double GetLiftEncoder();
	void ResetLiftEncoder();
	void RunLift(double speed);
	double GetLiftMagneticEncoder();

	double sensorUnitsPerRotation = 1024; // arbitrary number
};

#endif  // Elevator_H
