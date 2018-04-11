#ifndef Climber_H
#define Climber_H

#include <Commands/Subsystem.h>
#include <WPILib.h>
#include <ctre/Phoenix.h>

class Climber : public frc::Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

public:
	enum ForkDirection {
		fUp,
		fDown
	};

	enum ClawsDirection {
		cUp,
		cDown
	};

	Climber();
	void InitDefaultCommand();
	void SetClimbSpeed(double speed);
	void SetDeploySpeed(double speed);
	void SetForkDirection(ForkDirection direction);
	void SetClawsDirection(ClawsDirection direction);
};

#endif  // Climber_H
