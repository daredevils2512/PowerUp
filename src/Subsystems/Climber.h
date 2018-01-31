#ifndef Climber_H
#define Climber_H

#include <Commands/Subsystem.h>
#include <WPILib.h>
#include <ctre/Phoenix.h>

class Climber : public frc::Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	std::shared_ptr <WPI_TalonSRX> LeftWingMotor1;
	std::shared_ptr <WPI_TalonSRX> LeftWingMotor2;
	std::shared_ptr <WPI_TalonSRX> RightWingMotor1;
	std::shared_ptr <WPI_TalonSRX> RightWingMotor2;


public:
	Climber();
	void InitDefaultCommand();
	void SetLeftWingSpeed (double speed);
	void SetRightWingSpeed (double speed);
};

#endif  // Climber_H
