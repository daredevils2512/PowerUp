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

	Climber();
	void InitDefaultCommand();
	void SetClimbSpeed(double speed);
	void SetDeploySpeed(double speed);
	void SetForkDirection(ForkDirection direction);
};

#endif  // Climber_H
